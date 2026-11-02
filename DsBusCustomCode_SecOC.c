/** <!------------------------------------------------------------------------->
*
*   @file DsBusCustomCode_SecOC.c
*
*   @brief SecOC feature data type and function declarations
*
*   @description
*       This file is the public interface of the SecOC feature.
*       Refer to the corresponding header file for further documentation.
*
*   @copyright
*       Copyright 2020, dSPACE GmbH. All rights reserved.
*
*<!-------------------------------------------------------------------------->*/

#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#include <DsBusCustomCode_SecOC_Internal.h>

#include <stdlib.h>
#include <string.h>

/* Marker if module is initialized. Used for e.g. print version only once. */
static uint8 isInitalizedSecOC = 0;

/* Default descriptor for a created SecOC feature handle. See DsBusCustomCodeSecOCPduFeature_generateHandle() */
char g_DsBusCustomCodeSecOCFeatureDescriptor[] = "DsBusCustomCode SecOC Feature";

/* Default descriptor for a created SecOC RX feature handle. See DsBusCustomCodeSecOCRxPduFeature_generateHandle() */
char g_DsBusCustomCodeSecOCRxFeatureDescriptor[] = "DsBusCustomCode SecOC RX Feature Handle";

/* Default descriptor for a created SecOC TX feature handle. See DsBusCustomCodeSecOCTxPduFeature_generateHandle() */
char g_DsBusCustomCodeSecOCTxFeatureDescriptor[] = "DsBusCustomCode SecOC TX Feature Handle";

/* Default descriptor for a created Secured IPDU handle. See DsBusCustomCodeSecuredIPdu_generateHandle() */
char g_DsBusCustomCodeSecuredIPDUDescriptor[] = "DsBusCustomCode Secured IPDU Handle";

Std_ReturnType DsBusCustomCodeSecuredIPdu_generateHandle(DsBusCustomCodePduHandle* PduHandle)
{
    DsBusCustomCodeSecuredIPduInfoType* p;

    PrintVersion(isInitalizedSecOC);
    isInitalizedSecOC = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduHandle);

    if (*PduHandle)
    {
        rtlib_free(*PduHandle);
    }

    p = (DsBusCustomCodeSecuredIPduInfoType*)rtlib_malloc(sizeof(DsBusCustomCodeSecuredIPduInfoType));
    if (NULL_PTR == p)
    {
        *PduHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodeSecuredIPduInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodeSecuredIPduInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodeSecuredIPDUDescriptor) != E_OK)
    {
        rtlib_free(p);
        *PduHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodeSecuredIPDUDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    p->Pdu.PduType = DSCUSTOM_PDU_PDU_SUBTYPE_SECURED_IPDU;
    p->Pdu.PduTypeIsSet = 1;

    *PduHandle = (DsBusCustomCodePduHandle)p;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getDataId(DsBusCustomCodePduHandle Handle,
                                                    uint16* DataId)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, DataId);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.DataIdIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *DataId = (uint16)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.DataId;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setDataId(DsBusCustomCodePduHandle Handle,
                                                    uint16 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.DataId = (uint16)Data;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.DataIdIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getKeyId(DsBusCustomCodePduHandle Handle,
                                                   uint32* KeyId)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, KeyId);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.KeyIdIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *KeyId = (uint32)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.KeyId;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setKeyId(DsBusCustomCodePduHandle Handle,
                                                   uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.KeyId = (uint32)Data;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.KeyIdIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthenticPdu(DsBusCustomCodePduHandle Handle,
                                                          DsBusCustomCodePduHandle* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthenticPduIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = (DsBusCustomCodePduHandle)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthenticPdu;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthenticPdu(DsBusCustomCodePduHandle Handle,
                                                          DsBusCustomCodePduHandle Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthenticPdu = (DsBusCustomCodePduHandle)Data;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthenticPduIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthInfoTxLength(DsBusCustomCodePduHandle Handle,
                                                              uint32* AuthInfoTxLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, AuthInfoTxLength);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthInfoTxLengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *AuthInfoTxLength = (uint32)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthInfoTxLength;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthInfoTxLength(DsBusCustomCodePduHandle Handle,
                                                              uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthInfoTxLength = (uint32)Data;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthInfoTxLengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessValueLength(DsBusCustomCodePduHandle Handle,
                                                                  uint32* FreshnessValueLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, FreshnessValueLength);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueLengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *FreshnessValueLength = (uint32)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueLength;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setFreshnessValueLength(DsBusCustomCodePduHandle Handle,
                                                                  uint32 FreshnessValueLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueLength = (uint32)FreshnessValueLength;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueLengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessValueTxLength(DsBusCustomCodePduHandle Handle,
                                                                    uint32* FreshnessValueTxLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, FreshnessValueTxLength);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueTxLengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *FreshnessValueTxLength = (uint32)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueTxLength;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setFreshnessValueTxLength(DsBusCustomCodePduHandle Handle,
                                                                    uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueTxLength = (uint32)Data;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueTxLengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getUseAsCryptographicPdu(DsBusCustomCodePduHandle Handle,
                                                                   boolean* UseAsCryptographicIPdu)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, UseAsCryptographicIPdu);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseAsCryptographicIPduIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *UseAsCryptographicIPdu = (boolean)((DsBusCustomCodeSecuredIPduInfoType*)
        Handle)->SecuredIPdu.UseAsCryptographicIPdu;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setUseAsCryptographicPdu(DsBusCustomCodePduHandle Handle,
                                                                   boolean UseAsCryptographicIPdu)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseAsCryptographicIPdu = (boolean)UseAsCryptographicIPdu;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseAsCryptographicIPduIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthAlgorithmName(DsBusCustomCodePduHandle Handle,
                                                               char** AuthAlgorithmNamePtr)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, AuthAlgorithmNamePtr);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthAlgorithmNamePtrIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *AuthAlgorithmNamePtr = (char*)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthAlgorithmNamePtr;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthAlgorithmName(DsBusCustomCodePduHandle Handle,
                                                               char* AuthAlgorithmNamePtr)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, AuthAlgorithmNamePtr);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthAlgorithmNamePtr = (char*)AuthAlgorithmNamePtr;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthAlgorithmNamePtrIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthDataFreshnessLength(DsBusCustomCodePduHandle Handle,
                                                                     uint16* AuthDataFreshnessLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, AuthDataFreshnessLength);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthDataFreshnessLengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *AuthDataFreshnessLength = (uint16)((DsBusCustomCodeSecuredIPduInfoType*)
        Handle)->SecuredIPdu.AuthDataFreshnessLength;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthDataFreshnessLength(DsBusCustomCodePduHandle Handle,
                                                                     uint16 AuthDataFreshnessLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthDataFreshnessLength = \
        (uint16)AuthDataFreshnessLength;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthDataFreshnessLengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthDataFreshnessStartPosition(DsBusCustomCodePduHandle Handle,
                                                                            uint16* AuthDataFreshnessStartPosition)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor,
                               AuthDataFreshnessStartPosition);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthDataFreshnessStartPositionIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *AuthDataFreshnessStartPosition = (uint16)((DsBusCustomCodeSecuredIPduInfoType*)
        Handle)->SecuredIPdu.AuthDataFreshnessStartPosition;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthDataFreshnessStartPosition(DsBusCustomCodePduHandle Handle,
                                                                            uint16 AuthDataFreshnessStartPosition)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthDataFreshnessStartPosition = \
        (uint16)AuthDataFreshnessStartPosition;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthDataFreshnessStartPositionIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthenticationBuildAttempts(DsBusCustomCodePduHandle Handle,
                                                                         uint16* AuthenticationBuildAttempts)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor,
                               AuthenticationBuildAttempts);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthenticationBuildAttemptsIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *AuthenticationBuildAttempts = (int)((DsBusCustomCodeSecuredIPduInfoType*)
        Handle)->SecuredIPdu.AuthenticationBuildAttempts;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthenticationBuildAttempts(DsBusCustomCodePduHandle Handle,
                                                                         uint16 AuthenticationBuildAttempts)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthenticationBuildAttempts = \
        (uint16)AuthenticationBuildAttempts;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthenticationBuildAttemptsIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthenticationRetries(DsBusCustomCodePduHandle Handle,
                                                                   uint32* AuthenticationRetries)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, AuthenticationRetries);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthenticationRetriesIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *AuthenticationRetries = (uint32)((DsBusCustomCodeSecuredIPduInfoType*)
        Handle)->SecuredIPdu.AuthenticationRetries;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthenticationRetries(DsBusCustomCodePduHandle Handle,
                                                                   uint32 AuthenticationRetries)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthenticationRetries = (uint32)AuthenticationRetries;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthenticationRetriesIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessCounterSyncAttempts(DsBusCustomCodePduHandle Handle,
                                                                          uint32* FreshnessCounterSyncAttempts)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor,
                               FreshnessCounterSyncAttempts);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessCounterSyncAttemptsIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *FreshnessCounterSyncAttempts = (uint32)((DsBusCustomCodeSecuredIPduInfoType*)
        Handle)->SecuredIPdu.FreshnessCounterSyncAttempts;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setFreshnessCounterSyncAttempts(DsBusCustomCodePduHandle Handle,
                                                                          uint32 FreshnessCounterSyncAttempts)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessCounterSyncAttempts = \
        (uint32)FreshnessCounterSyncAttempts;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessCounterSyncAttemptsIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessTimestampPeriodFactor(DsBusCustomCodePduHandle Handle,
                                                                            uint32* FreshnessTimestampPeriodFactor)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor,
                               FreshnessTimestampPeriodFactor);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessTimestampPeriodFactorIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *FreshnessTimestampPeriodFactor = (uint32)((DsBusCustomCodeSecuredIPduInfoType*)
        Handle)->SecuredIPdu.FreshnessTimestampPeriodFactor;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setFreshnessTimestampPeriodFactor(DsBusCustomCodePduHandle Handle,
                                                                            uint32 FreshnessTimestampPeriodFactor)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessTimestampPeriodFactor = \
        (uint32)FreshnessTimestampPeriodFactor;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessTimestampPeriodFactorIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessValueId(DsBusCustomCodePduHandle Handle,
                                                              uint16* FreshnessValueId)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, FreshnessValueId);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueIdIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *FreshnessValueId = (uint16)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueId;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setFreshnessValueId(DsBusCustomCodePduHandle Handle,
                                                              uint16 FreshnessValueId)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueId = (uint16)FreshnessValueId;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.FreshnessValueIdIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getMessageLinkLength(DsBusCustomCodePduHandle Handle,
                                                               uint16* MessageLinkLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, MessageLinkLength);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.MessageLinkLengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *MessageLinkLength = (uint16)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.MessageLinkLength;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setMessageLinkLength(DsBusCustomCodePduHandle Handle,
                                                               uint16 MessageLinkLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.MessageLinkLength = (uint16)MessageLinkLength;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.MessageLinkLengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getMessageLinkPosition(DsBusCustomCodePduHandle Handle,
                                                                 uint16* MessageLinkPosition)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, MessageLinkPosition);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.MessageLinkPositionIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *MessageLinkPosition = (uint16)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.MessageLinkPosition;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setMessageLinkPosition(DsBusCustomCodePduHandle Handle,
                                                                 uint16 MessageLinkPosition)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.MessageLinkPosition = (uint16)MessageLinkPosition;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.MessageLinkPositionIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getRxSecurityVerification(DsBusCustomCodePduHandle Handle,
                                                                    boolean* RxSecurityVerification)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, RxSecurityVerification);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.RxSecurityVerificationIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *RxSecurityVerification = (boolean)((DsBusCustomCodeSecuredIPduInfoType*)
        Handle)->SecuredIPdu.RxSecurityVerification;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setRxSecurityVerification(DsBusCustomCodePduHandle Handle,
                                                                    boolean RxSecurityVerification)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.RxSecurityVerification = \
        (boolean)RxSecurityVerification;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.RxSecurityVerificationIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getTimeStampRxAcceptanceWindow(DsBusCustomCodePduHandle Handle,
                                                                         uint64* TimeStampRxAcceptanceWindow)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor,
                               TimeStampRxAcceptanceWindow);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.TimeStampRxAcceptanceWindowIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *TimeStampRxAcceptanceWindow = (uint64)((DsBusCustomCodeSecuredIPduInfoType*)
        Handle)->SecuredIPdu.TimeStampRxAcceptanceWindow;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setTimeStampRxAcceptanceWindow(DsBusCustomCodePduHandle Handle,
                                                                         uint64 TimeStampRxAcceptanceWindow)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.TimeStampRxAcceptanceWindow = \
        (uint64)TimeStampRxAcceptanceWindow;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.TimeStampRxAcceptanceWindowIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getUseAuthDataFreshness(DsBusCustomCodePduHandle Handle,
                                                                  boolean* UseAuthDataFreshness)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, UseAuthDataFreshness);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseAuthDataFreshnessIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *UseAuthDataFreshness = (boolean)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseAuthDataFreshness;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setUseAuthDataFreshness(DsBusCustomCodePduHandle Handle,
                                                                  boolean UseAuthDataFreshness)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseAuthDataFreshness = (boolean)UseAuthDataFreshness;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseAuthDataFreshnessIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getUseFreshnessTimestamp(DsBusCustomCodePduHandle Handle,
                                                                   boolean* UseFreshnessTimestamp)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, UseFreshnessTimestamp);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseFreshnessTimestampIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *UseFreshnessTimestamp = (boolean)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseFreshnessTimestamp;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setUseFreshnessTimestamp(DsBusCustomCodePduHandle Handle,
                                                                   boolean UseFreshnessTimestamp)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseFreshnessTimestamp = (boolean)UseFreshnessTimestamp;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.UseFreshnessTimestampIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthPduHeaderLength(DsBusCustomCodePduHandle Handle,
                                                                 uint8* AuthPduHeaderLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, AuthPduHeaderLength);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthPduHeaderLengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *AuthPduHeaderLength = ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthPduHeaderLength;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setAuthPduHeaderLength(DsBusCustomCodePduHandle Handle,
                                                                 uint8 AuthPduHeaderLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthPduHeaderLength = AuthPduHeaderLength;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.AuthPduHeaderLengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getSecuredAreaLength(DsBusCustomCodePduHandle Handle,
                                                               uint32* SecuredAreaLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, SecuredAreaLength);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.SecuredAreaLengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *SecuredAreaLength = (uint32)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.SecuredAreaLength;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setSecuredAreaLength(DsBusCustomCodePduHandle Handle,
                                                               uint32 SecuredAreaLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.SecuredAreaLength = (uint32)SecuredAreaLength;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.SecuredAreaLengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_getSecuredAreaOffset(DsBusCustomCodePduHandle Handle,
                                                               uint32* SecuredAreaOffset)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, SecuredAreaOffset);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.SecuredAreaOffsetIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *SecuredAreaOffset = (uint32)((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.SecuredAreaOffset;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecuredIPdu_setSecuredAreaOffset(DsBusCustomCodePduHandle Handle,
                                                               uint32 SecuredAreaOffset)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.SecuredAreaOffset = (uint32)SecuredAreaOffset;
    ((DsBusCustomCodeSecuredIPduInfoType*)Handle)->SecuredIPdu.SecuredAreaOffsetIsSet = 1;

    return E_OK;
}

#if defined(HOST_DEBUG)
Std_ReturnType DsBusCustomCodeSecOCPduFeature_generateHandle(DsBusCustomCodePduFeatureHandle* PduFeatureHandle)
{
    DsBusCustomCodeSecOCPduFeatureInfoType* p;

    PrintVersion(isInitalizedSecOC);
    isInitalizedSecOC = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);

    if (*PduFeatureHandle)
    {
        rtlib_free(*PduFeatureHandle);
    }

    p = (DsBusCustomCodeSecOCPduFeatureInfoType*)rtlib_malloc(sizeof(DsBusCustomCodeSecOCPduFeatureInfoType));
    if (NULL_PTR == p)
    {
        *PduFeatureHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodeSecOCPduFeatureInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodeSecOCPduFeatureInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodeSecOCFeatureDescriptor) != E_OK)
    {
        rtlib_free(p);
        *PduFeatureHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodeSecOCFeatureDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    p->Feature.Feature = DSCUSTOM_PDU_FEATURE_SECOC;
    p->Feature.FeatureIsSet = 1;

    *PduFeatureHandle = (DsBusCustomCodePduFeatureHandle)p;

    return E_OK;
}
#endif

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_generateHandle(DsBusCustomCodePduFeatureHandle* PduFeatureHandle)
{
    DsBusCustomCodeSecOCTxPduFeatureInfoType* p;

    PrintVersion(isInitalizedSecOC);
    isInitalizedSecOC = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);

    if (*PduFeatureHandle)
    {
        rtlib_free(*PduFeatureHandle);
    }

    p = (DsBusCustomCodeSecOCTxPduFeatureInfoType*)rtlib_malloc(sizeof(DsBusCustomCodeSecOCTxPduFeatureInfoType));
    if (NULL_PTR == p)
    {
        *PduFeatureHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodeSecOCTxPduFeatureInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodeSecOCTxPduFeatureInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodeSecOCTxFeatureDescriptor) != E_OK)
    {
        rtlib_free(p);
        *PduFeatureHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodeSecOCTxFeatureDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    p->Feature.Feature = DSCUSTOM_PDU_FEATURE_SECOCTX;
    p->Feature.FeatureIsSet = 1;

    *PduFeatureHandle = (DsBusCustomCodePduFeatureHandle)p;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_generateHandle(DsBusCustomCodePduFeatureHandle* PduFeatureHandle)
{
    DsBusCustomCodeSecOCRxPduFeatureInfoType* p;

    PrintVersion(isInitalizedSecOC);
    isInitalizedSecOC = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);

    if (*PduFeatureHandle)
    {
        rtlib_free(*PduFeatureHandle);
    }

    p = (DsBusCustomCodeSecOCRxPduFeatureInfoType*)rtlib_malloc(sizeof(DsBusCustomCodeSecOCRxPduFeatureInfoType));
    if (NULL_PTR == p)
    {
        *PduFeatureHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodeSecOCRxPduFeatureInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodeSecOCRxPduFeatureInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodeSecOCRxFeatureDescriptor) != E_OK)
    {
        rtlib_free(p);
        *PduFeatureHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodeSecOCTxFeatureDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    p->Feature.Feature = DSCUSTOM_PDU_FEATURE_SECOCRX;
    p->Feature.FeatureIsSet = 1;

    *PduFeatureHandle = (DsBusCustomCodePduFeatureHandle)p;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCPduFeature_getKeyLength(DsBusCustomCodePduFeatureHandle Handle,
                                                           uint32* KeyLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, KeyLength);

    if (    ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE
        || (   ((DsBusCustomCodePduFeatureInfoType*)Handle)->Feature.Feature != DSCUSTOM_PDU_FEATURE_SECOCRX
            && ((DsBusCustomCodePduFeatureInfoType*)Handle)->Feature.Feature != DSCUSTOM_PDU_FEATURE_SECOCTX
            && ((DsBusCustomCodePduFeatureInfoType*)Handle)->Feature.Feature != DSCUSTOM_PDU_FEATURE_SECOC))
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyLengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *KeyLength = (uint32)((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyLength;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCPduFeature_setKeyLength(DsBusCustomCodePduFeatureHandle Handle,
                                                           uint32 KeyLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyLength = (uint32)KeyLength;
    ((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyLengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCPduFeature_getKeyPtr(DsBusCustomCodePduFeatureHandle Handle,
                                                        uint8** KeyPtr)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, KeyPtr);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyPtrIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *KeyPtr = (uint8*)((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyPtr;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCPduFeature_setKeyPtr(DsBusCustomCodePduFeatureHandle Handle,
                                                        uint8* KeyPtr)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, KeyPtr);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyPtr = (uint8*)KeyPtr;
    ((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyPtrIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCPduFeature_getKeyAsString(DsBusCustomCodePduFeatureHandle Handle,
                                                             char** Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, Data);

    if (    ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE
        || (   ((DsBusCustomCodePduFeatureInfoType*)Handle)->Feature.Feature != DSCUSTOM_PDU_FEATURE_SECOCRX
            && ((DsBusCustomCodePduFeatureInfoType*)Handle)->Feature.Feature != DSCUSTOM_PDU_FEATURE_SECOCTX
            && ((DsBusCustomCodePduFeatureInfoType*)Handle)->Feature.Feature != DSCUSTOM_PDU_FEATURE_SECOC))
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyAsStringIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = (char*)((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyAsString;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCPduFeature_setKeyAsString(DsBusCustomCodePduFeatureHandle Handle,
                                                             const char* Data)
{
    char* TempNew;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    TempNew = (char*)rtlib_malloc(strlen(Data) + 1);

    if (NULL_PTR == TempNew)
    {
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    strcpy(TempNew, Data);
    if (((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyAsStringIsSet == 1)
    {
        rtlib_free(((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyAsString);
    }

    ((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyAsString = TempNew;
    ((DsBusCustomCodeSecOCPduFeatureInfoType*)Handle)->SecOCPduFeature.KeyAsStringIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCPduFeature_getAuthenticatorPositionOffset(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                             sint32* AuthenticatorPositionOffset)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleDescriptor,
                               AuthenticatorPositionOffset);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCPduFeatureInfoType*)PduFeatureHandle)->SecOCPduFeature.AuthenticatorPositionOffsetIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *AuthenticatorPositionOffset = (sint32)((DsBusCustomCodeSecOCPduFeatureInfoType*)
        PduFeatureHandle)->SecOCPduFeature.AuthenticatorPositionOffset;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCPduFeature_setAuthenticatorPositionOffset(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                             sint32 AuthenticatorPositionOffset)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCPduFeatureInfoType*)PduFeatureHandle)->SecOCPduFeature.AuthenticatorPositionOffset = \
        (sint32)AuthenticatorPositionOffset;
    ((DsBusCustomCodeSecOCPduFeatureInfoType*)PduFeatureHandle)->SecOCPduFeature.AuthenticatorPositionOffsetIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getAuthenticationType(DsBusCustomCodePduFeatureHandle Handle,
                                                                      uint32* AuthenticationType)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, AuthenticationType);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.AuthenticationTypeIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *AuthenticationType = (uint32)((DsBusCustomCodeSecOCTxPduFeatureInfoType*)
        Handle)->SecOCTxPduFeature.AuthenticationType;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setAuthenticationType(DsBusCustomCodePduFeatureHandle Handle,
                                                                      uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.AuthenticationType = (uint32)Data;
    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.AuthenticationTypeIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getCalculatedFreshnessValue(DsBusCustomCodePduFeatureHandle Handle,
                                                                            uint64* CalculatedFreshnessValue)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, CalculatedFreshnessValue);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.CalculatedFreshnessValueIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }
    
    DS_WRITE_U64(CalculatedFreshnessValue, DS_READ_U64(&((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.CalculatedFreshnessValue));
    
    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setCalculatedFreshnessValue(DsBusCustomCodePduFeatureHandle Handle,
                                                                            uint64 CalculatedFreshnessValue)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.CalculatedFreshnessValue = \
        (uint64)CalculatedFreshnessValue;
    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.CalculatedFreshnessValueIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getEnableAuthentication(DsBusCustomCodePduFeatureHandle Handle,
                                                                        uint32* EnableAuthentication)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, EnableAuthentication);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.EnableAuthenticationIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *EnableAuthentication = (uint32)((DsBusCustomCodeSecOCTxPduFeatureInfoType*)
        Handle)->SecOCTxPduFeature.EnableAuthentication;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setEnableAuthentication(DsBusCustomCodePduFeatureHandle Handle,
                                                                        uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.EnableAuthentication = (uint32)Data;
    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.EnableAuthenticationIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getEnableFreshnessValueCalculation(DsBusCustomCodePduFeatureHandle Handle,
                                                                                   uint32* EnableFreshnessValueCalculation)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor,
                               EnableFreshnessValueCalculation);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.EnableFreshnessValueCalculationIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *EnableFreshnessValueCalculation = (uint32)((DsBusCustomCodeSecOCTxPduFeatureInfoType*)
        Handle)->SecOCTxPduFeature.EnableFreshnessValueCalculation;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setEnableFreshnessValueCalculation(DsBusCustomCodePduFeatureHandle Handle,
                                                                                   uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.EnableFreshnessValueCalculation = \
        (uint32)Data;
    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.EnableFreshnessValueCalculationIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getFreshnessValueOffset(DsBusCustomCodePduFeatureHandle Handle,
                                                                        sint64* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.FreshnessValueOffsetIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = (sint64)((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.FreshnessValueOffset;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setFreshnessValueOffset(DsBusCustomCodePduFeatureHandle Handle,
                                                                        sint64 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.FreshnessValueOffset = (sint64)Data;
    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.FreshnessValueOffsetIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getUserDefinedAuthenticatorPtr(DsBusCustomCodePduFeatureHandle Handle,
                                                                               uint8** UserDefinedAuthenticatorPtr)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor,
                               UserDefinedAuthenticatorPtr);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.UserDefinedAuthenticatorPtrIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *UserDefinedAuthenticatorPtr = (uint8*)((DsBusCustomCodeSecOCTxPduFeatureInfoType*)
        Handle)->SecOCTxPduFeature.UserDefinedAuthenticatorPtr;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setUserDefinedAuthenticatorPtr(DsBusCustomCodePduFeatureHandle Handle,
                                                                               uint8* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.UserDefinedAuthenticatorPtr = (uint8*)Data;
    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.UserDefinedAuthenticatorPtrIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_getUserDefinedFreshnessValue(DsBusCustomCodePduFeatureHandle Handle,
                                                                             uint64* UserDefinedFreshnessValue)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, UserDefinedFreshnessValue);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.UserDefinedFreshnessValueIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *UserDefinedFreshnessValue = (uint64)((DsBusCustomCodeSecOCTxPduFeatureInfoType*)
        Handle)->SecOCTxPduFeature.UserDefinedFreshnessValue;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCTxPduFeature_setUserDefinedFreshnessValue(DsBusCustomCodePduFeatureHandle Handle,
                                                                             uint64 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.UserDefinedFreshnessValue = (uint64)Data;
    ((DsBusCustomCodeSecOCTxPduFeatureInfoType*)Handle)->SecOCTxPduFeature.UserDefinedFreshnessValueIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_getCalculatedFreshnessValue(DsBusCustomCodePduFeatureHandle Handle,
                                                                            uint64* CalculatedFreshnessValue)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, CalculatedFreshnessValue);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.CalculatedFreshnessValueIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    DS_WRITE_U64(CalculatedFreshnessValue, DS_READ_U64(&((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.CalculatedFreshnessValue));
    
    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_setCalculatedFreshnessValue(DsBusCustomCodePduFeatureHandle Handle,
                                                                            uint64 CalculatedFreshnessValue)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.CalculatedFreshnessValue = \
        (uint64)CalculatedFreshnessValue;
    ((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.CalculatedFreshnessValueIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_getEnableVerification(DsBusCustomCodePduFeatureHandle Handle,
                                                                      uint32* EnableVerification)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, EnableVerification);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.EnableVerificationIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *EnableVerification = (uint32)((DsBusCustomCodeSecOCRxPduFeatureInfoType*)
        Handle)->SecOCRxPduFeature.EnableVerification;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_setEnableVerification(DsBusCustomCodePduFeatureHandle Handle,
                                                                      uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.EnableVerification = (uint32)Data;
    ((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.EnableVerificationIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_getFreshnessValueOffset(DsBusCustomCodePduFeatureHandle Handle,
                                                                        sint64* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.FreshnessValueOffsetIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = (sint64)((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.FreshnessValueOffset;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_getVerificationResult(DsBusCustomCodePduFeatureHandle Handle,
                                                                      uint32* VerificationResult)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, VerificationResult);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.VerificationResultIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *VerificationResult = (uint32)((DsBusCustomCodeSecOCRxPduFeatureInfoType*)
        Handle)->SecOCRxPduFeature.VerificationResult;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSecOCRxPduFeature_setVerificationResult(DsBusCustomCodePduFeatureHandle Handle,
                                                                      uint32 VerificationResult)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.VerificationResult = \
        (uint32)VerificationResult;
    ((DsBusCustomCodeSecOCRxPduFeatureInfoType*)Handle)->SecOCRxPduFeature.VerificationResultIsSet = 1;

    return E_OK;
}
