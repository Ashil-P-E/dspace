/** <!------------------------------------------------------------------------->
*
*   @file DsBusCustomCode.c
*
*   @brief DsBusCustomCode data type and function declarations
*
*   @description
*       This file is the public interface of the DsBusCustomCode.
*
*   @copyright
*       Copyright 2022, dSPACE GmbH. All rights reserved.
*
*<!-------------------------------------------------------------------------->*/

#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#include <DsBusCustomCode_Internal.h>

#define DSBUSCUSTOMCODE_VERSION "1.0.3"

#ifdef BUILT_WITH_VERSION
#include "git_version.h"
#else
#define DSBUSCUSTOMCODE_VERSION_HASH ""
#define DSBUSCUSTOMCODE_VERSION_HASH_TXT ""
#endif

/* Custom code handle default descriptor */
char g_DsBusCustomCodeDefaultDescriptor[] = "DsBusCustomCode";
char g_DsBusCustomCodePduFeatureDescriptor[] = "DsBusCustomCode PDU Feature Handle";
char g_DsBusCustomCodePduDescriptor[] = "DsBusCustomCode PDU Handle";
char g_DsBusCustomCodeEcuDescriptor[] = "DsBusCustomCode ECU Handle";
char g_DsBusCustomCodeCommunicationClusterDescriptor[] = "DsBusCustomCode Communication Cluster Handle";
char g_DsBusCustomCodeSignalDescriptor[] = "DsBusCustomCode Signal Handle";
char g_DsBusCustomCodeUserPortDescriptor[] = "DsBusCustomCode UserPort Handle";

/* Interim solution due to no rtlib_malloc()/rtlib_free() in VEOS */
#ifdef VEOS_PLATFORM

void* rtlib_malloc(size_t size)
{
    void* ptr;

    ptr = malloc(size);

    return ptr;
}

void rtlib_free(void* ptr)
{
    free(ptr);
}
#endif

static uint8 isInitialized = 0;

Std_ReturnType PrintVersion(uint8 init)
{
    if (init == 0)
    {
        DSBUSCUSTOMCODE_INFO_PRINTF(DSBUSCUSTOMCODE_INFO_VERSION,
                                    g_DsBusCustomCodeDefaultDescriptor,
                                    DSBUSCUSTOMCODE_VERSION,
                                    DSBUSCUSTOMCODE_VERSION_HASH_TXT);
    }

    return E_OK;
}

/* Common handle functions */
#if defined(HOST_DEBUG)
/* Only used for unit test of DsBusCustomCode interface */
Std_ReturnType DsBusCustomCode_generateHandle(DsBusCustomCodeHandle* Handle)
{
    DsBusCustomCodeInfoType* p;

    PrintVersion(isInitialized);
    isInitialized = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (*Handle)
    {
        rtlib_free(*Handle);
    }

    p = (DsBusCustomCodeInfoType*)rtlib_malloc(sizeof(DsBusCustomCodeInfoType));
    if (NULL_PTR == p)
    {
        *Handle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodeInfoType));
    *Handle = (DsBusCustomCodeHandle)p;

    return E_OK;
}
#endif

Std_ReturnType DsBusCustomCode_getName(DsBusCustomCodeHandle Handle, char** Name)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Name);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.NameIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Name = ((DsBusCustomCodeInfoType*)Handle)->Handle.Name;

    return E_OK;
}

Std_ReturnType DsBusCustomCode_setName(DsBusCustomCodeHandle Handle, char* Name)
{
    char* TempNew;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Name);

    TempNew = (char*)rtlib_malloc(strlen(Name) + 1);

    if (NULL_PTR == TempNew)
    {
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    strcpy(TempNew, Name);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.NameIsSet == 1)
    {
        rtlib_free(((DsBusCustomCodeInfoType*)Handle)->Handle.Name);
    }

    ((DsBusCustomCodeInfoType*)Handle)->Handle.Name = TempNew;
    ((DsBusCustomCodeInfoType*)Handle)->Handle.NameIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCode_getDescriptor(DsBusCustomCodeHandle Handle, char** Descriptor)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Descriptor);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptorIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Descriptor = ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor;

    return E_OK;
}

Std_ReturnType DsBusCustomCode_setDescriptor(DsBusCustomCodeHandle Handle, char* Descriptor)
{
    char* TempNew;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Descriptor);

    TempNew = (char*)rtlib_malloc(strlen(Descriptor) + 1);

    if (NULL_PTR == TempNew)
    {
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    strcpy(TempNew, Descriptor);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptorIsSet == 1)
    {
        rtlib_free(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor);
    }

    ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor = TempNew;
    ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptorIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCode_getHandleType(DsBusCustomCodeHandle Handle, uint32* Type)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Type);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleTypeIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Type = ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType;

    return E_OK;
}

Std_ReturnType DsBusCustomCode_setHandleType(DsBusCustomCodeHandle Handle, uint32 Type)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType = Type;
    ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleTypeIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCode_getHandleLength(DsBusCustomCodeHandle Handle, uint32* Length)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Length);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleLengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Length = ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleLength;

    return E_OK;
}

Std_ReturnType DsBusCustomCode_setHandleLength(DsBusCustomCodeHandle Handle, uint32 Length)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleLength = Length;
    ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleLengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCode_getHandleVersion(DsBusCustomCodeHandle Handle, uint32* Version)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Version);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleVersionIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Version = ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleVersion;

    return E_OK;
}

Std_ReturnType DsBusCustomCode_setHandleVersion(DsBusCustomCodeHandle Handle, uint32 Version)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleVersion = Version;
    ((DsBusCustomCodeInfoType*)Handle)->Handle.HandleVersionIsSet = 1;

    return E_OK;
}

/* PDU feature functions */
Std_ReturnType DsBusCustomCodePduFeature_generateHandle(DsBusCustomCodePduFeatureHandle* PduFeatureHandle)
{
    DsBusCustomCodePduFeatureInfoType* p;

    PrintVersion(isInitialized);
    isInitialized = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);

    if (*PduFeatureHandle)
    {
        rtlib_free(*PduFeatureHandle);
    }

    p = (DsBusCustomCodePduFeatureInfoType*)rtlib_malloc(sizeof(DsBusCustomCodePduFeatureInfoType));
    if (NULL_PTR == p)
    {
        *PduFeatureHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodePduFeatureInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodePduFeatureInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodePduFeatureDescriptor) != E_OK)
    {
        rtlib_free(p);
        *PduFeatureHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodePduFeatureDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    *PduFeatureHandle = (DsBusCustomCodePduFeatureHandle)p;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePduFeature_getIsPduFeatureHandle(DsBusCustomCodePduHandle PduHandle, boolean* Value)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduHandle)->Handle.HandleDescriptor, Value);

    if (((DsBusCustomCodeInfoType*)PduHandle)->Handle.HandleType == DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        *Value = TRUE;
    }
    else
    {
        *Value = FALSE;
    }

    return E_OK;
}

Std_ReturnType DsBusCustomCodePduFeature_getIsPduHandle(DsBusCustomCodePduHandle PduHandle, boolean* Value)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduHandle)->Handle.HandleDescriptor, Value);

    if (((DsBusCustomCodeInfoType*)PduHandle)->Handle.HandleType == DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        *Value = TRUE;
    }
    else
    {
        *Value = FALSE;
    }

    return E_OK;
}

Std_ReturnType DsBusCustomCodePduFeature_getPdu(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                DsBusCustomCodePduHandle* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduFeatureInfoType*)PduFeatureHandle)->PduFeature.PduIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = (DsBusCustomCodePduHandle)((DsBusCustomCodePduFeatureInfoType*)PduFeatureHandle)->PduFeature.Pdu;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePduFeature_setPdu(DsBusCustomCodePduFeatureHandle Handle, DsBusCustomCodePduHandle Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduFeatureInfoType*)Handle)->PduFeature.Pdu = (DsBusCustomCodePduHandle)Data;
    ((DsBusCustomCodePduFeatureInfoType*)Handle)->PduFeature.PduIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePduFeature_getEcu(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                DsBusCustomCodeEcuHandle* EcuHandle)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleDescriptor, EcuHandle);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduFeatureInfoType*)PduFeatureHandle)->PduFeature.EcuIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *EcuHandle = (DsBusCustomCodeEcuHandle)((DsBusCustomCodePduFeatureInfoType*)PduFeatureHandle)->PduFeature.Ecu;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePduFeature_setEcu(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                DsBusCustomCodeEcuHandle EcuHandle)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduFeatureInfoType*)PduFeatureHandle)->PduFeature.Ecu = (DsBusCustomCodeEcuHandle)EcuHandle;
    ((DsBusCustomCodePduFeatureInfoType*)PduFeatureHandle)->PduFeature.EcuIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePduFeature_getCommunicationCluster(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                 DsBusCustomCodeCommunicationClusterHandle* CommunicationClusterHandle)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleDescriptor,
                                 CommunicationClusterHandle);

    if (((DsBusCustomCodeInfoType*)PduFeatureHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduFeatureInfoType*)PduFeatureHandle)->PduFeature.CommunicationClusterIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *CommunicationClusterHandle = (DsBusCustomCodeCommunicationClusterHandle)((DsBusCustomCodePduFeatureInfoType*)
        PduFeatureHandle)->PduFeature.CommunicationCluster;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePduFeature_setCommunicationCluster(DsBusCustomCodePduFeatureHandle Handle,
                                                                 DsBusCustomCodeCommunicationClusterHandle CommunicationClusterHandle)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduFeatureInfoType*)Handle)->PduFeature.CommunicationCluster = \
        (DsBusCustomCodeCommunicationClusterHandle)CommunicationClusterHandle;
    ((DsBusCustomCodePduFeatureInfoType*)Handle)->PduFeature.CommunicationClusterIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePduFeature_getFeatureDataPtr(DsBusCustomCodePduFeatureHandle Handle,
                                                           uint8** FeatureDataPtr)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, FeatureDataPtr);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduFeatureInfoType*)Handle)->Feature.FeatureDataPtrIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *FeatureDataPtr = (uint8*)((DsBusCustomCodePduFeatureInfoType*)Handle)->Feature.FeatureDataPtr;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePduFeature_setFeatureDataPtr(DsBusCustomCodePduFeatureHandle Handle,
                                                           uint8* FeatureDataPtr)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduFeatureInfoType*)Handle)->Feature.FeatureDataPtr = (uint8*)FeatureDataPtr;
    ((DsBusCustomCodePduFeatureInfoType*)Handle)->Feature.FeatureDataPtrIsSet = 1;

    return E_OK;
}

/* Cluster/ECU functions */
Std_ReturnType DsBusCustomCodeEcu_generateHandle(DsBusCustomCodeEcuHandle* EcuHandle)
{
    DsBusCustomCodeEcuInfoType* p;

    PrintVersion(isInitialized);
    isInitialized = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, EcuHandle);

    if (*EcuHandle)
    {
        rtlib_free(*EcuHandle);
    }

    p = (DsBusCustomCodeEcuInfoType*)rtlib_malloc(sizeof(DsBusCustomCodeEcuInfoType));
    if (NULL_PTR == p)
    {
        *EcuHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodeEcuInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_ECU) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodeEcuInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodeEcuDescriptor) != E_OK)
    {
        rtlib_free(p);
        *EcuHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodeEcuDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    *EcuHandle = (DsBusCustomCodeEcuHandle)p;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeCommunicationCluster_generateHandle(DsBusCustomCodeCommunicationClusterHandle* CommunicationClusterHandle)
{
    DsBusCustomCodeCommunicationClusterInfoType* p;

    PrintVersion(isInitialized);
    isInitialized = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, CommunicationClusterHandle);

    if (*CommunicationClusterHandle)
    {
        rtlib_free(*CommunicationClusterHandle);
    }

    p = (DsBusCustomCodeCommunicationClusterInfoType*)
        rtlib_malloc(sizeof(DsBusCustomCodeCommunicationClusterInfoType));

    if (NULL_PTR == p)
    {
        *CommunicationClusterHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodeCommunicationClusterInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_COMMUNICATION_CLUSTER) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodeCommunicationClusterInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodeCommunicationClusterDescriptor) != E_OK)
    {
        rtlib_free(p);
        *CommunicationClusterHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    *CommunicationClusterHandle = (DsBusCustomCodeCommunicationClusterHandle)p;

    return E_OK;
}

/* PDU functions */
Std_ReturnType DsBusCustomCodePdu_generateHandle(DsBusCustomCodePduHandle* PduHandle)
{
    DsBusCustomCodePduInfoType* p;

    PrintVersion(isInitialized);
    isInitialized = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduHandle);

    if (*PduHandle)
    {
        rtlib_free(*PduHandle);
    }

    p = (DsBusCustomCodePduInfoType*)rtlib_malloc(sizeof(DsBusCustomCodePduInfoType));
    if (NULL_PTR == p)
    {
        *PduHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodePduInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodePduInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodePduDescriptor) != E_OK)
    {
        rtlib_free(p);
        *PduHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodePduDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    *PduHandle = (DsBusCustomCodePduHandle)p;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_getSduLength(DsBusCustomCodePduHandle Handle, uint32* SduLength)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, SduLength);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduInfoType*)Handle)->Pdu.SduLengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *SduLength = (uint32)((DsBusCustomCodePduInfoType*)Handle)->Pdu.SduLength;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_setSduLength(DsBusCustomCodePduHandle Handle, uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.SduLength = (uint32)Data;
    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.SduLengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_getSduDataPtr(DsBusCustomCodePduHandle Handle, uint8** SduDataPtr)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, SduDataPtr);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduInfoType*)Handle)->Pdu.SduDataPtrIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *SduDataPtr = (uint8*)((DsBusCustomCodePduInfoType*)Handle)->Pdu.SduDataPtr;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_setSduDataPtr(DsBusCustomCodePduHandle Handle, uint8* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.SduDataPtr = (uint8*)Data;
    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.SduDataPtrIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_getIsTx(DsBusCustomCodePduHandle Handle, boolean* IsTx)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, IsTx);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduInfoType*)Handle)->Pdu.IsTxIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *IsTx = (boolean)((DsBusCustomCodePduInfoType*)Handle)->Pdu.IsTx;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_setIsTx(DsBusCustomCodePduHandle Handle, boolean Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.IsTx = (boolean)Data;
    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.IsTxIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_setPduType(DsBusCustomCodePduHandle Handle, uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduType = Data;
    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduTypeIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_getPduType(DsBusCustomCodePduHandle Handle, uint32* PduType)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, PduType);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduTypeIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *PduType = ((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduType;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_setPduSubType(DsBusCustomCodePduHandle Handle, uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduSubType = Data;
    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduSubTypeIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_getPduSubType(DsBusCustomCodePduHandle Handle, uint32* PduSubType)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, PduSubType);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduSubTypeIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *PduSubType = ((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduSubType;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_setPduRoles(DsBusCustomCodePduHandle Handle, uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduRoles = Data;
    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduRolesIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_getPduRoles(DsBusCustomCodePduHandle Handle, uint32* PduRoles)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, PduRoles);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduRolesIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *PduRoles = ((DsBusCustomCodePduInfoType*)Handle)->Pdu.PduRoles;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_setCanFrameTriggering(DsBusCustomCodePduHandle Handle,
                                                        DsBusCustomCodeCanFrameTriggeringType DsBusCustomCodeCanFrameTriggering)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodeCanFrameTriggering = DsBusCustomCodeCanFrameTriggering;
    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodeCanFrameTriggeringIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_getCanFrameTriggering(DsBusCustomCodePduHandle Handle,
                                                        DsBusCustomCodeCanFrameTriggeringType* DsBusCustomCodeCanFrameTriggering)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor,
                               DsBusCustomCodeCanFrameTriggering);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodeCanFrameTriggeringIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *DsBusCustomCodeCanFrameTriggering = ((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodeCanFrameTriggering;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_setLinFrameTriggering(DsBusCustomCodePduHandle Handle,
                                                        DsBusCustomCodeLinFrameTriggeringType DsBusCustomCodeLinFrameTriggering)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodeLinFrameTriggering = DsBusCustomCodeLinFrameTriggering;
    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodeLinFrameTriggeringIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_getLinFrameTriggering(DsBusCustomCodePduHandle Handle,
                                                        DsBusCustomCodeLinFrameTriggeringType* DsBusCustomCodeLinFrameTriggering)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor,
                               DsBusCustomCodeLinFrameTriggering);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodeLinFrameTriggeringIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *DsBusCustomCodeLinFrameTriggering = ((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodeLinFrameTriggering;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_setCanChannelName(DsBusCustomCodePduHandle Handle, const char* Data)
{
    char* TempNew;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
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
    if (((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodePduCanChannelNameIsSet == 1)
    {
        rtlib_free(((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodePduCanChannelName);
    }

    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodePduCanChannelName = TempNew;
    ((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodePduCanChannelNameIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodePdu_getCanChannelName(DsBusCustomCodePduHandle Handle,
                                                    char** DsBusCustomCodePduCanChannelName)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor,
                               DsBusCustomCodePduCanChannelName);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodePduCanChannelNameIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *DsBusCustomCodePduCanChannelName = ((DsBusCustomCodePduInfoType*)Handle)->Pdu.DsBusCustomCodePduCanChannelName;
    return E_OK;
}

/* Signal functions */
Std_ReturnType DsBusCustomCodeSignal_generateHandle(DsBusCustomCodeSignalHandle* SignalHandle)
{
    DsBusCustomCodeSignalInfoType* p;

    PrintVersion(isInitialized);
    isInitialized = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, SignalHandle);

    if (*SignalHandle)
    {
        rtlib_free(*SignalHandle);
    }

    p = (DsBusCustomCodeSignalInfoType*)rtlib_malloc(sizeof(DsBusCustomCodeSignalInfoType));
    if (NULL_PTR == p)
    {
        *SignalHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodeSignalInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_SIGNAL) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodeSignalInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodeSignalDescriptor) != E_OK)
    {
        rtlib_free(p);
        *SignalHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodeSignalDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    *SignalHandle = (DsBusCustomCodeSignalHandle)p;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSignal_setStartBitPosition(DsBusCustomCodeSignalHandle Handle, uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_SIGNAL)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.StartBitPosition = (uint32)Data;
    ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.StartBitPositionIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSignal_getStartBitPosition(DsBusCustomCodeSignalHandle Handle, uint32* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_SIGNAL)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSignalInfoType*)Handle)->Signal.StartBitPositionIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.StartBitPosition;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSignal_setLength(DsBusCustomCodeSignalHandle Handle, uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_SIGNAL)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.Length = (uint32)Data;
    ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.LengthIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSignal_getLength(DsBusCustomCodeSignalHandle Handle, uint32* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_SIGNAL)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSignalInfoType*)Handle)->Signal.LengthIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.Length;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSignal_setEndianness(DsBusCustomCodeSignalHandle Handle,
                                                   DsBusCustomCode_ByteOrderType Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_SIGNAL)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.Endianness = Data;
    ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.EndiannessIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSignal_getEndianness(DsBusCustomCodeSignalHandle Handle,
                                                   DsBusCustomCode_ByteOrderType* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_SIGNAL)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSignalInfoType*)Handle)->Signal.EndiannessIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.Endianness;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSignal_setSignalRole(DsBusCustomCodeSignalHandle Handle, uint32 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_SIGNAL)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.SignalRole = (uint32)Data;
    ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.SignalRoleIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeSignal_getSignalRole(DsBusCustomCodeSignalHandle Handle, uint32* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, Handle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)Handle)->Handle.HandleDescriptor, Data);

    if (((DsBusCustomCodeInfoType*)Handle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_SIGNAL)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeSignalInfoType*)Handle)->Signal.SignalRoleIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = ((DsBusCustomCodeSignalInfoType*)Handle)->Signal.SignalRole;

    return E_OK;
}

/* User Port functions */
Std_ReturnType DsBusCustomCodeUserPort_generateHandle(DsBusCustomCodeUserPortHandle* UserPortHandle)
{
    DsBusCustomCodeUserPortInfoType* p;

    PrintVersion(isInitialized);
    isInitialized = 1;

    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, UserPortHandle);

    if (*UserPortHandle)
    {
        rtlib_free(*UserPortHandle);
    }

    p = (DsBusCustomCodeUserPortInfoType*)rtlib_malloc(sizeof(DsBusCustomCodeUserPortInfoType));
    
    if (NULL_PTR == p)
    {
        *UserPortHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION,
                                     g_DsBusCustomCodeDefaultDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    memset(p, 0, sizeof(DsBusCustomCodeUserPortInfoType));

    if (   DsBusCustomCode_setHandleType((DsBusCustomCodeHandle)p, DSCUSTOM_BUSRTCODE_HANDLE_TYPE_USERPORT) != E_OK
        || DsBusCustomCode_setHandleLength((DsBusCustomCodeHandle)p, sizeof(DsBusCustomCodeUserPortInfoType)) != E_OK
        || DsBusCustomCode_setHandleVersion((DsBusCustomCodeHandle)p, 0x00010000) != E_OK
        || DsBusCustomCode_setDescriptor((DsBusCustomCodeHandle)p, g_DsBusCustomCodeUserPortDescriptor) != E_OK)
    {
        rtlib_free(p);
        *UserPortHandle = NULL_PTR;
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_HANDLE_INIT,
                                     g_DsBusCustomCodeUserPortDescriptor,
                                     __FUNCTION__,
                                     (unsigned int)__LINE__,
                                     __FILE__);
    }

    *UserPortHandle = (DsBusCustomCodeUserPortHandle)p;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserPort_setPortData(DsBusCustomCodeUserPortHandle UserPortHandle,
                                                   float64 Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, UserPortHandle);

    if (((DsBusCustomCodeInfoType*)UserPortHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_USERPORT)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeUserPortInfoType*)UserPortHandle)->UserPort.UserPortData = (float64)Data;
    ((DsBusCustomCodeUserPortInfoType*)UserPortHandle)->UserPort.UserPortDataIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserPort_getPortData(DsBusCustomCodeUserPortHandle UserPortHandle,
                                                   float64* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, UserPortHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)UserPortHandle)->Handle.HandleDescriptor, Data);
    
    if (((DsBusCustomCodeInfoType*)UserPortHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_USERPORT)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeUserPortInfoType*)UserPortHandle)->UserPort.UserPortDataIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = ((DsBusCustomCodeUserPortInfoType*)UserPortHandle)->UserPort.UserPortData;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserPort_setDirection(DsBusCustomCodeUserPortHandle UserPortHandle,
                                                    boolean Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, UserPortHandle);

    if (((DsBusCustomCodeInfoType*)UserPortHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_USERPORT)
    {
        return E_NOT_OK;
    }

    ((DsBusCustomCodeUserPortInfoType*)UserPortHandle)->UserPort.IsOut = (boolean)Data;
    ((DsBusCustomCodeUserPortInfoType*)UserPortHandle)->UserPort.IsOutIsSet = 1;

    return E_OK;
}

Std_ReturnType DsBusCustomCodeUserPort_getDirection(DsBusCustomCodeUserPortHandle UserPortHandle,
                                                    boolean* Data)
{
    DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, UserPortHandle);
    DSBUSCUSTOMCODE_CHECK_NULL(((DsBusCustomCodeInfoType*)UserPortHandle)->Handle.HandleDescriptor, Data);
    
    if (((DsBusCustomCodeInfoType*)UserPortHandle)->Handle.HandleType != DSCUSTOM_BUSRTCODE_HANDLE_TYPE_USERPORT)
    {
        return E_NOT_OK;
    }

    if (((DsBusCustomCodeUserPortInfoType*)UserPortHandle)->UserPort.IsOutIsSet == 0)
    {
        return E_PARAMETER_NOT_SET;
    }

    *Data = ((DsBusCustomCodeUserPortInfoType*)UserPortHandle)->UserPort.IsOut;

    return E_OK;
}
