/** <!------------------------------------------------------------------------->
*
*   @file DsBusCustomCode_Internal.h
*
*   @brief DsBusCustomCode data type and function declarations
*
*   @description
*       This file is the internal interface of the DsBusCustomCode.
*
*   @copyright
*       Copyright 2020, dSPACE GmbH. All rights reserved.
*
*<!-------------------------------------------------------------------------->*/

#ifndef DSBUSCUSTOMCODE_INTERNAL_H
#define DSBUSCUSTOMCODE_INTERNAL_H

/* Include file for internal function (i.e., usable in the bus implementation software, but not in the user code) */

#include "DsBusCustomCode.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Common BusCustomCode handle types */
#if defined(HOST_DEBUG)
/* Only used for unit test of DsBusCustomCode interface */
#define DSCUSTOM_BUSRTCODE_HANDLE_TYPE_COMMON 0
#endif
#define DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE_INIT 1
#define DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU_FEATURE 2
#define DSCUSTOM_BUSRTCODE_HANDLE_TYPE_PDU 3
#define DSCUSTOM_BUSRTCODE_HANDLE_TYPE_ECU 4
#define DSCUSTOM_BUSRTCODE_HANDLE_TYPE_COMMUNICATION_CLUSTER 5
#define DSCUSTOM_BUSRTCODE_HANDLE_TYPE_SIGNAL 6
#define DSCUSTOM_BUSRTCODE_HANDLE_TYPE_USERPORT 7

#define DSCUSTOM_PDU_PDU_TYPE_IPDU 1
#define DSCUSTOM_PDU_PDU_TYPE_NMPDU 2
#define DSCUSTOM_PDU_PDU_TYPE_USER_DEFINED_PDU 4
#define DSCUSTOM_PDU_PDU_TYPE_GENERAL_PURPOSE_PDU 8
#define DSCUSTOM_PDU_PDU_TYPE_LPDU 16

#define DSCUSTOM_PDU_PDU_SUBTYPE_ISIGNAL_IPDU 1
#define DSCUSTOM_PDU_PDU_SUBTYPE_MULTIPLEXED_IPDU 2
#define DSCUSTOM_PDU_PDU_SUBTYPE_CONTAINER_IPDU 4
#define DSCUSTOM_PDU_PDU_SUBTYPE_SECURED_IPDU 8
#define DSCUSTOM_PDU_PDU_SUBTYPE_USER_DEFINED_IPDU 16
#define DSCUSTOM_PDU_PDU_SUBTYPE_GENERAL_PURPOSE_IPDU 32
#define DSCUSTOM_PDU_PDU_SUBTYPE_DCM_IPDU 64
#define DSCUSTOM_PDU_PDU_SUBTYPE_J1939_DCM_IPDU 128
#define DSCUSTOM_PDU_PDU_SUBTYPE_NPDU 256


/**
*    Interim implementation of DS_READ_U64 and DS_WRITE_U64
*    In general, these functions are provided by platform header file (e.g. dsstd.h)
*    TODO: Validate, if this is still required. 
*/
#if !defined(DSACCESS64_SIMPLE_IMPL) && !defined(DSACCESS64_COMPLEX_IMPL)

#ifdef __GNUC__
    #define __DSACCESS64_UNUSED__    __attribute__((__unused__))        /* Prevents "unused static function" warnings */
#else
    #define __DSACCESS64_UNUSED__
#endif

    /* Declarations */
    static inline ULong64 DS_READ_U64 (const void *pMem)            __DSACCESS64_UNUSED__;
    static inline void    DS_WRITE_U64(void *pMem, ULong64 Val64)   __DSACCESS64_UNUSED__;

    /* Definitions */
    static inline ULong64 DS_READ_U64(const void *pMem)
    {
        return *(ULong64*)pMem;
    }
    static inline void    DS_WRITE_U64(void *pMem, ULong64 Val64)
    {
        *(ULong64*)pMem = Val64;
    }
#endif  /* !DSACCESS64_SIMPLE_IMPL && !DSACCESS64_COMPLEX_IMPL */


/**
*   @internal
*   Handle structure
*/
typedef struct
{
    /* Type of the handle */
    uint32 HandleType;
    uint32 HandleTypeIsSet;
    /* Version of the handle */
    uint32 HandleVersion;
    uint32 HandleVersionIsSet;
    /* Length of the handle (set for creating a copy of a handle) */
    uint32 HandleLength;
    uint32 HandleLengthIsSet;
    /* Handle descriptor (used for error handling) */
    char* HandleDescriptor;
    uint32 HandleDescriptorIsSet;
    /* Name */
    char* Name;
    uint32 NameIsSet;
} DsBusCustomCodeHandleParameterStruct;

typedef struct
{
    uint32 Feature;
    uint32 FeatureIsSet;
    uint8* FeatureDataPtr;
    uint32 FeatureDataPtrIsSet;
} DsBusCustomCodeFeatureParameterStruct;

typedef struct
{
    DsBusCustomCodePduHandle Pdu;
    uint32 PduIsSet;
    DsBusCustomCodeEcuHandle Ecu;
    uint32 EcuIsSet;
    DsBusCustomCodeCommunicationClusterHandle CommunicationCluster;
    uint32 CommunicationClusterIsSet;
} DsBusCustomCodePduFeatureParameterStruct;

typedef struct
{
    uint32 SduLength;
    uint32 SduLengthIsSet;
    uint8* SduDataPtr;
    uint32 SduDataPtrIsSet;
    boolean IsTx;
    uint32 IsTxIsSet;
    uint32 PduType;
    uint32 PduTypeIsSet;
    uint32 PduSubType;
    uint32 PduSubTypeIsSet;
    uint32 PduRoles;
    uint32 PduRolesIsSet;
    DsBusCustomCodePduCanFrameTriggeringStruct DsBusCustomCodeCanFrameTriggering;
    uint32 DsBusCustomCodeCanFrameTriggeringIsSet;
    DsBusCustomCodePduLinFrameTriggeringStruct DsBusCustomCodeLinFrameTriggering;
    uint32 DsBusCustomCodeLinFrameTriggeringIsSet;
    char* DsBusCustomCodePduCanChannelName;
    uint32 DsBusCustomCodePduCanChannelNameIsSet;
} DsBusCustomCodePduParameterStruct;

typedef struct
{
    uint32 StartBitPosition;
    uint32 StartBitPositionIsSet;
    uint32 Length;
    uint32 LengthIsSet;
    uint32 Endianness;
    uint32 EndiannessIsSet;
    uint32 SignalRole;
    uint32 SignalRoleIsSet;
} DsBusCustomCodeSignalParameterStruct;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
} DsBusCustomCodeInfoType;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
    DsBusCustomCodeFeatureParameterStruct Feature;
    DsBusCustomCodePduFeatureParameterStruct PduFeature;
} DsBusCustomCodePduFeatureInfoType;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
} DsBusCustomCodeEcuInfoType;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
} DsBusCustomCodeCommunicationClusterInfoType;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
    DsBusCustomCodePduParameterStruct Pdu;
} DsBusCustomCodePduInfoType;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
    DsBusCustomCodeSignalParameterStruct Signal;
} DsBusCustomCodeSignalInfoType;

typedef struct
{
    boolean IsOut;
    uint32 IsOutIsSet;
    float64 UserPortData;
    uint32 UserPortDataIsSet;
} DsBusCustomCodeUserPortParameterStruct;

typedef struct
{
    DsBusCustomCodeHandleParameterStruct Handle;
    DsBusCustomCodeUserPortParameterStruct UserPort;
} DsBusCustomCodeUserPortInfoType;

Std_ReturnType PrintVersion(uint8 init);

/* Private custom interface, only for bus implementation software */

#if defined(HOST_DEBUG)
/* Only used for unit test of DsBusCustomCode interface */
Std_ReturnType DsBusCustomCode_generateHandle(DsBusCustomCodeEcuHandle* EcuHandle);
#endif
Std_ReturnType DsBusCustomCode_setDescriptor(DsBusCustomCodeHandle Handle, char* Descriptor);
Std_ReturnType DsBusCustomCode_setName(DsBusCustomCodeHandle Handle, char* Name);
Std_ReturnType DsBusCustomCode_setHandleVersion(DsBusCustomCodeHandle Handle, uint32 Version);
Std_ReturnType DsBusCustomCode_getHandleVersion(DsBusCustomCodeHandle Handle, uint32* Version);
Std_ReturnType DsBusCustomCode_setHandleLength(DsBusCustomCodeHandle Handle, uint32 Length);
Std_ReturnType DsBusCustomCode_getHandleLength(DsBusCustomCodeHandle Handle, uint32* Length);
Std_ReturnType DsBusCustomCode_setHandleType(DsBusCustomCodeHandle Handle, uint32 Type);
Std_ReturnType DsBusCustomCode_getHandleType(DsBusCustomCodeHandle Handle, uint32* Type);

/* ECU/Cluster */
Std_ReturnType DsBusCustomCodeEcu_generateHandle(DsBusCustomCodeEcuHandle* EcuHandle);
Std_ReturnType DsBusCustomCodeCommunicationCluster_generateHandle(DsBusCustomCodeCommunicationClusterHandle* CommunicationClusterHandle);
Std_ReturnType DsBusCustomCodeCommunicationCluster_initHandle(DsBusCustomCodeCommunicationClusterInfoType* CommunicationClusterHandle);
Std_ReturnType DsBusCustomCodePduFeature_setEcu(DsBusCustomCodePduFeatureHandle Handle,
                                                DsBusCustomCodeEcuHandle EcuHandle);
Std_ReturnType DsBusCustomCodePduFeature_setCommunicationCluster(DsBusCustomCodePduFeatureHandle Handle,
                                                                 DsBusCustomCodeCommunicationClusterHandle CommunicationClusterHandle);

/* PDU */
Std_ReturnType DsBusCustomCodePdu_generateHandle(DsBusCustomCodePduHandle* PduHandle);
Std_ReturnType DsBusCustomCodePdu_setSduDataPtr(DsBusCustomCodePduHandle PduHandle, uint8* SduDataPtr);
Std_ReturnType DsBusCustomCodePdu_setSduLength(DsBusCustomCodePduHandle PduHandle, uint32 SduLength);
Std_ReturnType DsBusCustomCodePdu_setIsTx(DsBusCustomCodePduHandle PduHandle, boolean IsTx);
Std_ReturnType DsBusCustomCodePdu_setPduType(DsBusCustomCodePduHandle Handle, uint32 Data);
Std_ReturnType DsBusCustomCodePdu_getPduType(DsBusCustomCodePduHandle Handle, uint32* PduType);
Std_ReturnType DsBusCustomCodePdu_setPduSubType(DsBusCustomCodePduHandle Handle, uint32 Data);
Std_ReturnType DsBusCustomCodePdu_getPduSubType(DsBusCustomCodePduHandle Handle, uint32* PduSubType);
Std_ReturnType DsBusCustomCodePdu_setPduRoles(DsBusCustomCodePduHandle Handle, uint32 Data);
Std_ReturnType DsBusCustomCodePdu_getPduRoles(DsBusCustomCodePduHandle Handle, uint32* PduRoles);
Std_ReturnType DsBusCustomCodePdu_setCanFrameTriggering(DsBusCustomCodePduHandle Handle,
                                                        DsBusCustomCodeCanFrameTriggeringType DsBusCustomCodeCanFrameTriggering);
Std_ReturnType DsBusCustomCodePdu_setLinFrameTriggering(DsBusCustomCodePduHandle Handle,
                                                        DsBusCustomCodeLinFrameTriggeringType DsBusCustomCodeLinFrameTriggering);
Std_ReturnType DsBusCustomCodePdu_setCanChannelName(DsBusCustomCodePduHandle Handle, const char* Data);

/* Signal */
Std_ReturnType DsBusCustomCodeSignal_generateHandle(DsBusCustomCodeSignalHandle* SignalHandle);
Std_ReturnType DsBusCustomCodeSignal_setStartBitPosition(DsBusCustomCodeSignalHandle Handle, uint32 Data);
Std_ReturnType DsBusCustomCodeSignal_setLength(DsBusCustomCodeSignalHandle Handle, uint32 Data);
Std_ReturnType DsBusCustomCodeSignal_setEndianness(DsBusCustomCodeSignalHandle Handle,
                                                   DsBusCustomCode_ByteOrderType Data);
Std_ReturnType DsBusCustomCodeSignal_setSignalRole(DsBusCustomCodeSignalHandle Handle, uint32 Data);
Std_ReturnType DsBusCustomCodeSignal_getSignalRole(DsBusCustomCodeSignalHandle Handle, uint32* Data);

/* User Ports */
Std_ReturnType DsBusCustomCodeUserPort_generateHandle(DsBusCustomCodeUserPortHandle* UserPortHandle);
Std_ReturnType DsBusCustomCodeUserPort_setDirection(DsBusCustomCodeUserPortHandle UserPortHandle, boolean Data);

/* PDU Feature */
Std_ReturnType DsBusCustomCodePduFeature_generateHandle(DsBusCustomCodePduFeatureHandle* PduFeatureHandle);
Std_ReturnType DsBusCustomCodePduFeature_setPdu(DsBusCustomCodePduFeatureHandle PduFeatureHandle, DsBusCustomCodePduHandle PduHandle);

#ifdef __cplusplus
}
#endif

#endif /* DSBUSCUSTOMCODE_INTERNAL_H */