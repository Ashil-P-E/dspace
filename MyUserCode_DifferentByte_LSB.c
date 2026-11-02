/* Start of feature parameter definition, must be at the beginning of the file, before all includes, etc. */
#define DS_BUS_CUSTOM_FEATURE_NAME MyUserCode_DifferentByte_LSB
/* End of feature parameter definition */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <DsBusCustomCode_PduUserCode.h>

#define CUSTOM_CRC_OK                       0x00
#define CUSTOM_CRC_FAILED                   0x01
#define CUSTOM_CRC_COUNTER_FAILED           0x02
#define CUSTOM_CRC_COUNTER_INITIALIZED      0x04

/* struct to store custom counter counter */
struct UserCode_FeatureData
{
    uint32 counter_value;               /* current counter value */
    uint32 counter_is_initialized;      /* flag to indicate counter is initialized */
};

/* ----------------------------------------------------------
   HELPER FUNCTIONS FOR BIT-LEVEL SIGNAL READ / WRITE
   ---------------------------------------------------------- */

/* Write ONLY the target bits (e.g., 4-bit signal) */
static inline void writeSignalBits(uint8* bytePtr, uint8 value, uint32 startBit, uint32 bitLength)
{	
	uint8 startBit_m = sizeof(startBit) * CHAR_BIT - bitLength;
    uint8 mask = ((1u << bitLength) - 1u) << startBit_m;

    *bytePtr &= ~mask; /* clear only target bits */
    *bytePtr |= ((value << startBit) & mask); /* set new bits */
}

/* Read ONLY the target bits (e.g., 4-bit signal) */
static inline uint8 readSignalBits(uint8 byteValue, uint32 startBit, uint32 bitLength)
{	
	uint8 startBit_m = sizeof(startBit) * CHAR_BIT - bitLength;
    uint8 mask = ((1u << bitLength) - 1u);
    return (byteValue >> startBit_m) & mask;
}


/* ----------------------------------------------------------
   APPLICATION INIT
   ---------------------------------------------------------- */
Std_ReturnType DsBusCustomCode_onApplicationInit(DsBusCustomCodePduFeatureHandle PduFeatureHandle)
{
    /* declare data pointers. */
    uint8* featureDataPtr;
    char* featureDescriptor;
    struct UserCode_FeatureData* featureInstanceData;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DsBusCustomCode_getDescriptor(PduFeatureHandle, &featureDescriptor);

    featureInstanceData = (struct UserCode_FeatureData*) malloc(sizeof(struct UserCode_FeatureData));
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, featureInstanceData);

    featureInstanceData->counter_value = 0;
    featureInstanceData->counter_is_initialized = 0;

    featureDataPtr = (uint8*)featureInstanceData;
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePduFeature_setFeatureDataPtr(PduFeatureHandle, featureDataPtr));

    return E_OK;
}



/* ----------------------------------------------------------
   MAIN FEATURE EXECUTION
   ---------------------------------------------------------- */
Std_ReturnType DsBusCustomCode_onPduFeatureExecution(DsBusCustomCodePduFeatureHandle PduFeatureHandle)
{
    /* declare data pointers. */
    struct UserCode_FeatureData* featureDataPtr;
    char* featureDescriptor;
    DsBusCustomCodePduHandle pduHandle;
    uint8* IPdu_SduDataPtr;
    uint32 IPdu_SduLength;
    boolean isTx = FALSE;

    DsBusCustomCodeSignalHandle *Signals;
    uint32 SignalCount;
    uint32 ISignalCounterPos;
    uint32 ISignalCrcPos;
    uint32 ISignalCounterLength;
    uint32 ISignalCrcLength;

    uint32 UserPortCount;
    DsBusCustomCodeUserPortHandle* UserPorts;

    boolean portIsOut[16]; /* Safe upper bound */
    DsBusCustomCodeCanFrameTriggeringType My_CanFrameTriggering;
    uint32 My_ID;
    uint8 My_AddressingMode;
    uint8 My_FrameBehavior;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_TRY(g_DsBusCustomCodeDefaultDescriptor, DsBusCustomCode_getDescriptor(PduFeatureHandle, &featureDescriptor));
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePduFeature_getFeatureDataPtr(PduFeatureHandle, (uint8**)&featureDataPtr));

    /* PDU INFO */
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePduFeature_getPdu(PduFeatureHandle, &pduHandle));
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getSduLength(pduHandle, &IPdu_SduLength));
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getSduDataPtr(pduHandle, &IPdu_SduDataPtr));
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getIsTx(pduHandle, &isTx));

    /* SIGNALS */
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getUserSignals(PduFeatureHandle, &Signals));
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getNumberOfUserSignals(PduFeatureHandle, &SignalCount));

    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getStartBitPosition(Signals[0], &ISignalCounterPos));
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getStartBitPosition(Signals[1], &ISignalCrcPos));

    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getLength(Signals[0], &ISignalCounterLength));
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getLength(Signals[1], &ISignalCrcLength));

    /* USER PORTS */
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getUserPorts(PduFeatureHandle, &UserPorts));
    DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getNumberOfUserPorts(PduFeatureHandle, &UserPortCount));

    for (uint32 i = 0; i < UserPortCount; i++)
        DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserPort_getDirection(UserPorts[i], &portIsOut[i]));

    /* CAN Frame Triggering */
    DsBusCustomCodePdu_getCanFrameTriggering(pduHandle, &My_CanFrameTriggering);
    My_ID = (uint32)My_CanFrameTriggering.Identifier;
    My_AddressingMode = (uint8)My_CanFrameTriggering.AddresingMode;
    My_FrameBehavior = (uint8)My_CanFrameTriggering.FrameBehavior;

    if (portIsOut[0]) DsBusCustomCodeUserPort_setPortData(UserPorts[0], My_ID);
    if (portIsOut[1]) DsBusCustomCodeUserPort_setPortData(UserPorts[1], My_AddressingMode);
    if (portIsOut[2]) DsBusCustomCodeUserPort_setPortData(UserPorts[2], My_FrameBehavior);

    /* COMPUTE BYTE + BIT POSITIONS */
    uint32 counterByteIndex = ISignalCounterPos >> 3;
    uint32 counterBitOffset = ISignalCounterPos & 0x07;

    uint32 crcByteIndex = ISignalCrcPos >> 3;
    uint32 crcBitOffset = ISignalCrcPos & 0x07;

    uint8 tmpcrcval = 0;
    uint32 tmpPos = IPdu_SduLength;


    /* ----------------------------------------------------------
       TX SIDE
       ---------------------------------------------------------- */
    if (isTx)
    {
        /* Update counter only in its defined bit range */
        uint8 counterMask = (1u << ISignalCounterLength) - 1u;
        uint8 counterValue = (++featureDataPtr->counter_value) & counterMask;

        if (counterByteIndex < IPdu_SduLength)
        {
            writeSignalBits(&IPdu_SduDataPtr[counterByteIndex],
                            counterValue,
                            counterBitOffset,
                            ISignalCounterLength);
        }

        /* Compute CRC over all bytes except CRC byte */
        while (tmpPos)
        {
            tmpPos--;
            if (tmpPos != crcByteIndex)
                tmpcrcval += (0xFF ^ IPdu_SduDataPtr[tmpPos]);
        }

        /* Store CRC only in target signal bits */
        if (crcByteIndex < IPdu_SduLength)
        {
            uint8 crcMask = (1u << ISignalCrcLength) - 1u;
            uint8 crcValue = tmpcrcval & crcMask;

            writeSignalBits(&IPdu_SduDataPtr[crcByteIndex],
                            crcValue,
                            crcBitOffset,
                            ISignalCrcLength);
        }
    }

    /* ----------------------------------------------------------
       RX SIDE
       ---------------------------------------------------------- */
    else
    {
        uint32 status = CUSTOM_CRC_OK;

        /* Read only the counter bits */
        if (counterByteIndex < IPdu_SduLength)
        {
            uint8 receivedCounter = readSignalBits(IPdu_SduDataPtr[counterByteIndex],
                                                   counterBitOffset,
                                                   ISignalCounterLength);

            if (!featureDataPtr->counter_is_initialized)
            {
                featureDataPtr->counter_value = receivedCounter;
                featureDataPtr->counter_is_initialized = 1;
                status |= CUSTOM_CRC_COUNTER_INITIALIZED;
            }
            else
            {
                featureDataPtr->counter_value++;

                uint8 expected = featureDataPtr->counter_value &
                                 ((1u << ISignalCounterLength) - 1u);

                if (expected != receivedCounter)
                {
                    featureDataPtr->counter_is_initialized = 0;
                    status |= CUSTOM_CRC_COUNTER_FAILED;
                    msg_info_printf(0,0,"RX Counter failed");
                }
            }
        }

        /* Recompute CRC */
        if (crcByteIndex < IPdu_SduLength)
        {
            while (tmpPos)
            {
                tmpPos--;
                if (tmpPos != crcByteIndex)
                    tmpcrcval += (0xFF ^ IPdu_SduDataPtr[tmpPos]);
            }

            uint8 receivedCRC = readSignalBits(IPdu_SduDataPtr[crcByteIndex],
                                               crcBitOffset,
                                               ISignalCrcLength);

            uint8 expectedCRC = tmpcrcval &
                                ((1u << ISignalCrcLength) - 1u);

            if (receivedCRC != expectedCRC)
                status |= CUSTOM_CRC_FAILED;
        }

        DsBusCustomCodeUserCodePduFeature_setResult(PduFeatureHandle, status);
    }

    return E_OK;
}
