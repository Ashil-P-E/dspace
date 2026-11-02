#define DS_BUS_CUSTOM_FEATURE_NAME SavvyCRC_RPM
#include <stdlib.h>
#include <DsBusCustomCode_PduUserCode.h>
#include "savvycan_crc_common.h"

#define SAVVYCAN_APPLICATION_ID ((uint16)0x32u)
#define SAVVYCAN_COUNTER_LENGTH 8u
#define SAVVYCAN_COUNTER_POLICY 0u
#define SAVVYCAN_DLC 8u

typedef struct
{
    uint8 counterValue;
} RPM_CallbackState;

/* Called once when this PDU User Code feature is initialized. */
Std_ReturnType DsBusCustomCode_onApplicationInit(
    DsBusCustomCodePduFeatureHandle PduFeatureHandle)
{
    uint8 *featureDataPtr;
    char *featureDescriptor;
    RPM_CallbackState *state;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor,
                               PduFeatureHandle);

    DSBUSCUSTOMCODE_TRY(g_DsBusCustomCodeDefaultDescriptor,
                        DsBusCustomCode_getDescriptor(PduFeatureHandle,
                                                      &featureDescriptor));

    state = (RPM_CallbackState *)malloc(sizeof(*state));
    DSBUSCUSTOMCODE_CHECK_NULL(featureDescriptor, state);

    /* The original SavvyCAN script initializes byte 1 to zero. */
    state->counterValue = 0u;
    featureDataPtr = (uint8 *)state;

    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodePduFeature_setFeatureDataPtr(
                            PduFeatureHandle, featureDataPtr));
    return E_OK;
}

/* Called for this PDU each time the PDU User Code feature executes. */
Std_ReturnType DsBusCustomCode_onPduFeatureExecution(
    DsBusCustomCodePduFeatureHandle PduFeatureHandle)
{
    RPM_CallbackState *state;
    char *featureDescriptor;
    DsBusCustomCodePduHandle pduHandle;
    DsBusCustomCodeSignalHandle *signals;
    uint32 signalCount;
    uint32 sduLength;
    uint32 counterStartBit;
    uint32 counterLength;
    uint32 crcStartBit;
    uint32 crcLength;
    uint8 *sduDataPtr;
    boolean isTx = FALSE;
    uint8 crcValue;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor,
                               PduFeatureHandle);

    DSBUSCUSTOMCODE_TRY(g_DsBusCustomCodeDefaultDescriptor,
                        DsBusCustomCode_getDescriptor(PduFeatureHandle,
                                                      &featureDescriptor));
    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodePduFeature_getFeatureDataPtr(
                            PduFeatureHandle, (uint8 **)&state));
    DSBUSCUSTOMCODE_CHECK_NULL(featureDescriptor, state);

    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodePduFeature_getPdu(PduFeatureHandle,
                                                          &pduHandle));
    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodePdu_getSduLength(pduHandle,
                                                        &sduLength));
    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodePdu_getSduDataPtr(pduHandle,
                                                         &sduDataPtr));
    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodePdu_getIsTx(pduHandle, &isTx));

    /* These source scripts calculate CRC only for transmitted frames. */
    if (!isTx) {
        return E_OK;
    }
    if ((sduLength != SAVVYCAN_DLC) || (sduDataPtr == NULL)) {
        return E_NOT_OK;
    }

    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodeUserCodePduFeature_getUserSignals(
                            PduFeatureHandle, &signals));
    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodeUserCodePduFeature_getNumberOfUserSignals(
                            PduFeatureHandle, &signalCount));

    if ((signalCount < 2u) || (signals == NULL) ||
        (signals[0] == NULL) || (signals[1] == NULL)) {
        return E_NOT_OK;
    }

    /* User Signal 0 is the counter; User Signal 1 is the CRC. */
    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodeSignal_getStartBitPosition(
                            signals[0], &counterStartBit));
    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodeSignal_getLength(
                            signals[0], &counterLength));
    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodeSignal_getStartBitPosition(
                            signals[1], &crcStartBit));
    DSBUSCUSTOMCODE_TRY(featureDescriptor,
                        DsBusCustomCodeSignal_getLength(
                            signals[1], &crcLength));

    /* Fail safely if the ConfigurationDesk User Signal setup is incorrect. */
    if ((counterStartBit != 8u) ||
        (counterLength != SAVVYCAN_COUNTER_LENGTH) ||
        (crcStartBit != 0u) || (crcLength != 8u)) {
        return E_NOT_OK;
    }

    /* Write current counter first, then calculate CRC exactly like SavvyCAN. */
    SavvyCan_WriteSignalBits(sduDataPtr, counterStartBit, counterLength,
                             state->counterValue);
    crcValue = SavvyCan_CalculateCRC8(SAVVYCAN_APPLICATION_ID, sduDataPtr);
    SavvyCan_WriteSignalBits(sduDataPtr, crcStartBit, crcLength, crcValue);

#if SAVVYCAN_COUNTER_POLICY == 1u
    /*
     * Preserve the WHEEL_SPEED JS quirk: it increments the entire byte 1,
     * then the next counter is the resulting low nibble. This intentionally
     * retains the influence of the rear-wheel-speed high nibble.
     */
    state->counterValue = (uint8)(SavvyCan_IncrementAliveCounter(sduDataPtr[1])
                                  & 0x0Fu);
#else
    state->counterValue =
        SavvyCan_IncrementAliveCounter(state->counterValue);
#endif

    return E_OK;
}
