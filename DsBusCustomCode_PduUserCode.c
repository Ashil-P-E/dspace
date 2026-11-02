/** <!------------------------------------------------------------------------->
*
*   @file DsBusCustomCode_PduUserCode.c
*
*   @brief PduUserCode data type and function declarations
*
*   @description
*       This file is the public interface of the PDU User Code feature.
*
*   @copyright
*       Copyright 2020, dSPACE GmbH. All rights reserved.
*
*<!-------------------------------------------------------------------------->*/

#include <DsBusCustomCode_PduUserCode_Internal.h>

#include <stdlib.h>
#include <string.h>

static uint8 isInitalized = 0;

char g_DsBusCustomCodeUserCodeFeatureDescriptor[] = "DsBusCustomCode UserCode Feature";
char g_DsBusCustomCodeUserCodePduFeatureDescriptor[] = "DsBusCustomCode Signals Handle";

Std_ReturnType DsBusCustomCodeUserCodePduFeature_generateHandle(DsBusCustomCodePduFeatureHandle* PduFeatureHandle)
{
    DsBusCustomCodeUserCodePduFeatureInfoType* p;

    PrintVersion(isInitalized);
    isInitalized = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);

    if (*PduFeatureHandle)
    {
        rtlib_free(*PduFeatureHandle);
    }

    p = (DsBusCustomCodeUserCodePduFeatureInfoType*)rtlib_malloc(sizeof(DsBusCustomCodeUserCodePduFeatureInfoType));
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeUserCodeFeatureDescriptor, p);
    if (NULL_PTR == p)
    {
        *PduFeatureHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     __LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodeUserCodePduFeatureInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodeUserCodePduFeatureInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodeUserCodeFeatureDescriptor) != E_OK)
    {
        rtlib_free(p);
        *PduFeatureHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodeUserCodeFeatureDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    p->Feature.Feature = DSCUSTOM_PDU_FEATURE_USERCODE;
    p->Feature.FeatureIsSet = 1;

    *PduFeatureHandle = (DsBusCustomCodePduFeatureHandle)p;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserCodePduFeature_getResult(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                           uint32* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->ResultIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->Result;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserCodePduFeature_setResult(DsBusCustomCodePduFeatureHandle Handle, uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeUserCodePduFeatureInfoType*)Handle)->Result = Data;
    ((DsBusCustomCodeUserCodePduFeatureInfoType*)Handle)->ResultIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserCodePduFeature_setUserSignals(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                DsBusCustomCodeSignalHandle* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->Signals = Data;
    ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->SignalsIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserCodePduFeature_getUserSignals(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                DsBusCustomCodeSignalHandle** Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->SignalsIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->Signals;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserCodePduFeature_setNumberOfUserSignals(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                        uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->SignalsCount = Data;
    ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->SignalsCountIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserCodePduFeature_getNumberOfUserSignals(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                        uint32* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->SignalsCountIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->SignalsCount;

    return E_OK;
}

/* User Ports */
Std_ReturnType DsBusCustomCodeUserCodePduFeature_setUserPorts(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                              DsBusCustomCodeUserPortHandle* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->UserPorts = Data;
    ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->UserPortsIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserCodePduFeature_getUserPorts(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                              DsBusCustomCodeUserPortHandle** Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }
    
    if (((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->UserPortsIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }


    *Data = ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->UserPorts;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserCodePduFeature_setNumberOfUserPorts(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                      uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->UserPortsCount = Data;
    ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->UserPortsCountIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserCodePduFeature_getNumberOfUserPorts(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                      uint32* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->UserPortsCountIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = ((DsBusCustomCodeUserCodePduFeatureInfoType*)PduFeatureHandle)->UserPortsCount;

    return E_OK;
}
