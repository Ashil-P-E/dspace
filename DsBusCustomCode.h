/** <!------------------------------------------------------------------------->
*
*   @file DsBusCustomCode.h
*
*   @brief DsBusCustomCode data type and function declarations
*
*   @description
*       This file is the public interface of the DsBusCustomCode.
*       Before it is included in the user code, DS_BUS_CUSTOM_FEATURE_NAME
*       must be defined in the respective user code.
*
*   @copyright
*       Copyright 2022, dSPACE GmbH. All rights reserved.
*
*<!-------------------------------------------------------------------------->*/

#ifndef DSBUSCUSTOMCODE_H
#define DSBUSCUSTOMCODE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Include file for public (i.e. usable in the user code) functions */

#include <stdlib.h>
#include <string.h>
#include <DSMSG.h>
#include <dsstd.h>

#if defined(VEOS_PLATFORM) || (defined(DS_PLATFORM_SMART) && !defined(DS_PLATFORM_SMARTRTK)) || defined(_DSHOST)
#include <Platform_Types.h>
#include <Std_Types.h>

/* Additional types for older platform types */
#if !defined(PLATFORM_AR_MAJOR_VERSION) && !defined(PLATFORM_AR_RELEASE_MAJOR_VERSION)
/* The standard AUTOSAR type for 64 bit signed integer */
typedef signed long long sint64;
/* The standard AUTOSAR type for 64 bit unsigned integer */
typedef unsigned long long uint64;
#endif

#else

/* AUTOSAR type definitions for platforms without these. (not complete) */

#ifndef E_OK
#define E_OK        0x00u
#endif

#ifndef E_NOT_OK
#define E_NOT_OK    0x01u
#endif

/* Void pointer to zero. */
#ifndef NULL_PTR
#define NULL_PTR ((void *)0)
#endif

/* Definitions for TRUE and FALSE. */
#ifndef TRUE
#define TRUE 1
#endif 
#ifndef FALSE
#define FALSE 0
#endif 

#if (defined DS_PLATFORM_PPC) && (defined __GNUC__)
typedef unsigned char boolean;
/* The standard AUTOSAR type for 8 bit unsigned integer */
typedef unsigned char uint8;
/* The standard AUTOSAR type for 16 bit unsigned integer */
typedef unsigned short uint16;
/* The standard AUTOSAR type for 32 bit unsigned integer */
typedef unsigned int uint32;
/* The standard AUTOSAR type for 64 bit unsigned integer */
typedef unsigned long long uint64;
/* The standard AUTOSAR type for 8 bit signed integer */
typedef signed char sint8;
/* The standard AUTOSAR type for 16 bit signed integer */
typedef signed short sint16;
/* The standard AUTOSAR type for 32 bit signed integer */
typedef signed int sint32;
/* The standard AUTOSAR type for 64 bit signed integer */
typedef long long sint64;

/* The standard AUTOSAR type for 32 bit floating-point number */
typedef float float32;
/* The standard AUTOSAR type for 64 bit floating-point number */
typedef double float64;
#else
typedef unsigned char boolean;
/* The standard AUTOSAR type for 8 bit unsigned integer */
typedef unsigned char uint8;
/* The standard AUTOSAR type for 16 bit unsigned integer */
typedef unsigned short int uint16;
/* The standard AUTOSAR type for 32 bit unsigned integer */
typedef unsigned long int uint32;
/* The standard AUTOSAR type for 64 bit unsigned integer */
typedef unsigned long long uint64;
/* The standard AUTOSAR type for 8 bit signed integer */
typedef signed char sint8;
/* The standard AUTOSAR type for 16 bit signed integer */
typedef signed short int sint16;
/* The standard AUTOSAR type for 32 bit signed integer */
typedef signed long int sint32;
/* The standard AUTOSAR type for 64 bit signed integer */
typedef signed long long sint64;

/* The standard AUTOSAR type for 32 bit floating-point number */
typedef float float32;
/* The standard AUTOSAR type for 64 bit floating-point number */
typedef double float64;
#endif

typedef uint8 Std_ReturnType;

#endif

/* Interim solution due to no rtlib_malloc()/rtlib_free() in VEOS */
#ifdef VEOS_PLATFORM
void* rtlib_malloc(size_t size);

void rtlib_free(void* ptr);
#endif

/* Return value if a parameter was not set */
#define E_PARAMETER_NOT_SET 0xFF
/* Return value if a given handle was invalid */
#define E_INVALID_HANDLE 0xFE

/* Access Point */

/* Helper function to concatenate strings via preprocessor */
#define BUS_CUSTOM_CODE_CONCAT_INTERN(X,Y) DsBusCustomCode_ ## X ## _ ## Y
/* Helper function to concatenate strings via preprocessor */
#define BUS_CUSTOM_CODE_CONCAT(X,Y) BUS_CUSTOM_CODE_CONCAT_INTERN(X,Y)

/* Application init access point function for a specific feature */
#define DsBusCustomCode_onApplicationInit BUS_CUSTOM_CODE_CONCAT(onApplicationInit, DS_BUS_CUSTOM_FEATURE_NAME)
/* PDU feature execution access point function for a specific feature */
#define DsBusCustomCode_onPduFeatureExecution BUS_CUSTOM_CODE_CONCAT(onPduFeatureExecution, DS_BUS_CUSTOM_FEATURE_NAME)

/* Error Helper */

/* Defined in DsBusCustomCode interface */
extern char g_DsBusCustomCodeDefaultDescriptor[];

#define MSG_SM_DSBUSCUSTOMCODE 0

/* Version text for DsBusCustomCode */
#define DSBUSCUSTOMCODE_INFO_VERSION                           E_OK
#define DSBUSCUSTOMCODE_INFO_VERSION_TXT                       "%s: Version %s %s"

/* At least one function argument was a NULL pointer. */
#define DSBUSCUSTOMCODE_ERROR_NULL_POINTER                     E_NOT_OK
#define DSBUSCUSTOMCODE_ERROR_NULL_POINTER_TXT                 "%s: Handle %s was a NULL pointer. "                   \
                                                               "(Function: %s, Line: %d, File: %s)"

/* A memory allocation error occurred. */
#define DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION                E_NOT_OK
#define DSBUSCUSTOMCODE_ERROR_MEMORY_ALLOCATION_TXT            "%s: A memory allocation error occurred. "             \
                                                               "(Function: %s, Line: %d, File: %s)"

/* The provided function returned with an error code. */
#define DSBUSCUSTOMCODE_ERROR_TRY                              E_NOT_OK
#define DSBUSCUSTOMCODE_ERROR_TRY_TXT                          "%s: Call of %s returned with E_NOT_OK. "              \
                                                               "(Function: %s, Line: %d, File: %s)"

/* A mandatory user parameter was not set. */
#define DSBUSCUSTOMCODE_ERROR_MANDATORY_PARAMETER_MISSING      E_NOT_OK
#define DSBUSCUSTOMCODE_ERROR_MANDATORY_PARAMETER_MISSING_TXT  "%s: Call of %s returned with E_PARAMETER_NOT_SET, "   \
                                                               "although the parameter is mandatory. "                \
                                                               "(Function: %s, Line: %d, File: %s)"

/* At least one handle initialization failed */
#define DSBUSCUSTOMCODE_ERROR_HANDLE_INIT                      E_NOT_OK
#define DSBUSCUSTOMCODE_ERROR_HANDLE_INIT_TXT                  "%s: At least one handle initialization failed. "      \
                                                               "(Function: %s, Line: %d, File: %s)"

/* Wrapper for msg_info_printf function including return statement */
#define DSBUSCUSTOMCODE_INFO_PRINTF(Code, ...)                                                                        \
{                                                                                                                     \
    msg_info_printf(MSG_SM_DSBUSCUSTOMCODE, Code, Code##_TXT, __VA_ARGS__);                                           \
    return Code;                                                                                                      \
}

/* Wrapper for msg_error_printf function including return statement */
#define DSBUSCUSTOMCODE_ERROR_PRINTF(Code, ...)                                                                       \
{                                                                                                                     \
    msg_error_printf(MSG_SM_DSBUSCUSTOMCODE, Code, Code##_TXT, __VA_ARGS__);                                          \
    return Code;                                                                                                      \
}

/* Macro for NULL pointer checks to avoid code bloat */
#define DSBUSCUSTOMCODE_CHECK_NULL(Descriptor, Argument)                                                              \
{                                                                                                                     \
    if (NULL == (Argument))                                                                                           \
    {                                                                                                                 \
        DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_NULL_POINTER,                                              \
                                     Descriptor,                                                                      \
                                     #Argument,                                                                       \
                                     __FUNCTION__,                                                                    \
                                     (unsigned int)__LINE__,                                                          \
                                     __FILE__);                                                                       \
    }                                                                                                                 \
}

/* Macro for function call success/fail check to avoid code bloat */
#define DSBUSCUSTOMCODE_TRY(Descriptor, Expr)                                                                         \
{                                                                                                                     \
    Std_ReturnType _Error = (Expr);                                                                                   \
                                                                                                                      \
    if ((E_PARAMETER_NOT_SET) == _Error)                                                                              \
    {                                                                                                                 \
     DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_MANDATORY_PARAMETER_MISSING,                                  \
                                  Descriptor,                                                                         \
                                  #Expr,                                                                              \
                                  __FUNCTION__,                                                                       \
                                  (unsigned int)__LINE__,                                                             \
                                  __FILE__);                                                                          \
    }                                                                                                                 \
    else if ((E_OK) != _Error)                                                                                        \
    {                                                                                                                 \
     DSBUSCUSTOMCODE_ERROR_PRINTF(DSBUSCUSTOMCODE_ERROR_TRY,                                                          \
                                  Descriptor,                                                                         \
                                  #Expr,                                                                              \
                                  __FUNCTION__,                                                                       \
                                  (unsigned int)__LINE__,                                                             \
                                  __FILE__);                                                                          \
    }                                                                                                                 \
}

/* Signal-to-PDU mapping byte order enumeration */
typedef enum
{
    BigEndian,
    LittleEndian,
    Opaque
} DsBusCustomCode_ByteOrderType;

/* PDU-specific mapping CAN addressing mode enumeration */
typedef enum
{
    Standard = 1,
    Extended = 2
} DsBusCustomCode_CanAddressingModeType;

/* PDU-specific mapping CAN frame behavior type enumeration */
typedef enum
{
    Can20 = 1,
    CanFd = 2
} DsBusCustomCode_FrameBehaviorType;

/* PDU-specific mapping LIN frame checksum type enumeration */
typedef enum
{
    Classic = 1,
    Enhanced = 2
} DsBusCustomCode_LinChecksumType;

/* PDU-specific CAN addressing mode type enumeration */
typedef DsBusCustomCode_CanAddressingModeType CanAddressingModeType;

/* PDU-specific frame behavior type enumeration */
typedef DsBusCustomCode_FrameBehaviorType FrameBehaviorType;

/* PDU-specific LIN frame checksum type enumeration */
typedef DsBusCustomCode_LinChecksumType LinChecksumType;

/* PDU-specific CAN frame triggering structure */
typedef struct
{
    uint32 Identifier;
    CanAddressingModeType AddresingMode;
    FrameBehaviorType FrameBehavior;
} DsBusCustomCodePduCanFrameTriggeringStruct;

/* PDU-specific LIN frame triggering structure */
typedef struct
{
    uint32 Identifier;
    LinChecksumType ChecksumType;
} DsBusCustomCodePduLinFrameTriggeringStruct;

/* PDU-specific type for CAN frame triggering */
typedef DsBusCustomCodePduCanFrameTriggeringStruct DsBusCustomCodeCanFrameTriggeringType;

/* PDU-specific type for LIN frame triggering */
typedef DsBusCustomCodePduLinFrameTriggeringStruct DsBusCustomCodeLinFrameTriggeringType;

/* PDU-specific CAN Channel Name structure */
typedef struct
{
    char* CanChannelName;
} DsBusCustomCodePduCanChannelNameStruct;

/* PDU-specific type for CAN Channel Name */
typedef DsBusCustomCodePduCanChannelNameStruct DsBusCustomCodeCanChannelNameType;

/* Generic DsBusCustomCode handle. All other handles can be used in place of this. */
typedef uint8* DsBusCustomCodeHandle;

/* ECU-specific handle */
typedef uint8* DsBusCustomCodeEcuHandle;

/* Cluster-specific handle */
typedef uint8* DsBusCustomCodeCommunicationClusterHandle;

/* PDU-specific handle */
typedef uint8* DsBusCustomCodePduHandle;

/**
*   Signal-specific handle
*   @description
*   - The handle is created during application initialization.
*     It is used to retrieve signal parameters applying one of the following API methods.
*   - #DsBusCustomCodeSignal_getStartBitPosition
*   - #DsBusCustomCodeSignal_getLength
*   - #DsBusCustomCodeSignal_getEndianness
*/
typedef uint8* DsBusCustomCodeSignalHandle;

/**
*   UserPort-specific handle
*   @description
*   - The handle is created during application initialization.
*     It is used to retrieve UserPorts parameters applying one of the following API methods.
*   - #DsBusCustomCodeUserPort_getDirection
*   - #DsBusCustomCodeUserPort_setPortData
*   - #DsBusCustomCodeUserPort_getPortData
*/
typedef uint8* DsBusCustomCodeUserPortHandle;

/* PDU feature-specific handle */
typedef uint8* DsBusCustomCodePduFeatureHandle;

/** <!------------------------------------------------------------------------->
*   Get the descriptor of a DsBusCustomCode handle
*
*   @description
*   - This function gets the descriptor of a DsBusCustomCode handle
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCode_getName()
*
*   @code
*   // Declare pointer for descriptor
*   char* featureDescriptor;
*   // Let the pointer point to the descriptor
*   DsBusCustomCode_getDescriptor(PduFeatureHandle, &featureDescriptor);
*   @endcode
*
*   @parameters
*       @param Handle A DsBusCustomCode handle
*       @param Descriptor The descriptor of the handle
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g. a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCode_getDescriptor(DsBusCustomCodeHandle Handle, char** Descriptor);

/** <!------------------------------------------------------------------------->
*   Get the name of a handle
*
*   @description
*   - This function gets the name of the element represented by DsBusCustomCode
*     handle
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCode_getDescriptor()
*
*   @code
*   // Declare pointer for name
*   char* name;
*   // Let the pointer point to the name
*   DsBusCustomCode_getName(PduFeatureHandle, &name);
*   @endcode
*
*   @parameters
*       @param Handle A DsBusCustomCode handle
*       @param Name The name of the element represented by DsBusCustomCode handle
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCode_getName(DsBusCustomCodeHandle Handle, char** Name);

/** <!------------------------------------------------------------------------->
*   Get the name of a CAN channel
*
*   @description
*   - This function gets the CAN Channel name type of a PDU
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCode_getDescriptor()
*
*   @code
*   // Declare pointer for name
*   char* name;
*   // Let the pointer point to the name
*   DsBusCustomCode_getName(PduFeatureHandle, &name);
*   @endcode
*
*   @parameters
*       @param Handle A DsBusCustomCode handle
*       @param Name The name of the element represented by DsBusCustomCode handle
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePdu_getCanChannelName(DsBusCustomCodePduHandle PduHandle, char** Name);

/* PDU */

/** <!------------------------------------------------------------------------->
*   Get the SDU length (i.e., the payload length) of a PDU in bytes
*
*   @description
*   - This function gets the length of the SDU of a PDU in bytes
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePdu_getSduDataPtr()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param SduLength The SDU length in bytes
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePdu_getSduLength(DsBusCustomCodePduHandle PduHandle, uint32* SduLength);

/** <!------------------------------------------------------------------------->
*   Get the pointer to the SDU bytes (the data bytes) of a PDU
*
*   @description
*   - This function gets the pointer to SDU bytes (the data bytes) of a PDU
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePdu_getSduLength()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param SduDataPtr The pointer to the SDU bytes (the data bytes)
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePdu_getSduDataPtr(DsBusCustomCodePduHandle PduHandle, uint8** SduDataPtr);

/** <!------------------------------------------------------------------------->
*   Get the transmission direction
*
*   @description
*   - This function gets information whether the transmission direction of
*     the PDU is TX or RX
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePdu_getSduLength()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param IsTx Returns TRUE if the PDU direction is TX and FALSE if the
*                   PDU direction is RX
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g. a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePdu_getIsTx(DsBusCustomCodePduHandle PduHandle, boolean* IsTx);

/** <!------------------------------------------------------------------------->
*   Get the SDU identifier, address mode and behavior type
*
*   @description
*   - This function gets the ID, Addressing Mode (Standard, Extended) and
*     Behavior Type (Can20, CanFd) of a PDU
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePdu_getCanFrameTriggering()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param DsBusCustomCodeCanFrameTriggering structure of (.Identifier)
*                                                PDU ID, (.AddressingMode)
*                                                and (.FrameBehavior)
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePdu_getCanFrameTriggering(DsBusCustomCodePduHandle PduHandle,
                                                        DsBusCustomCodeCanFrameTriggeringType* DsBusCustomCodeCanFrameTriggering);

/** <!------------------------------------------------------------------------->
*   Get the SDU checksum type (i.e., Classic, Enhanced) and ID of a LIN PDU
*
*   @description
*   - This function gets the Checksum type (Classic, Enhanced) and ID of a
*     LIN SDU
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePdu_getLinFrameTriggering()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param DsBusCustomCodeLinFrameTriggering structure (.Identifier) ID and
*                                                (.ChecksumType) Checksum type of
*                                                LIN PDU
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePdu_getLinFrameTriggering(DsBusCustomCodePduHandle PduHandle,
                                                        DsBusCustomCodeLinFrameTriggeringType* DsBusCustomCodeLinFrameTriggering);

/* Secured IPDU */

/** <!------------------------------------------------------------------------->
*   Get the data ID of a secured IPDU
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePdu_getKeyId()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param DataId The data ID
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g. a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getDataId(DsBusCustomCodePduHandle PduHandle, uint16* DataId);

/** <!------------------------------------------------------------------------->
*   Get the key ID of a secured IPDU
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePdu_getDatId()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param KeyId The key ID
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getKeyId(DsBusCustomCodePduHandle PduHandle, uint32* KeyId);

/** <!------------------------------------------------------------------------->
*   Is the secured IPDU used as cryptographic IPDU?
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU handle
*       @param UseAsCryptographicIPdu TRUE, if the secured IPDU is used as
*                                     cryptographic IPDU, otherwise FALSE
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getUseAsCryptographicPdu(DsBusCustomCodePduHandle PduHandle,
                                                                   boolean* UseAsCryptographicIPdu);

/** <!------------------------------------------------------------------------->
*   Get the length in bits of the authenticator that is included in the payload
*   of the secured IPDU
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getFreshnessValueLength()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU Handle
*       @param AuthInfoTxLength The length in bits of the authenticator that is
*                               included in the payload of the secured IPDU
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g. a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getAuthInfoTxLength(DsBusCustomCodePduHandle PduHandle,
                                                              uint32* AuthInfoTxLength);

/** <!------------------------------------------------------------------------->
*   Get the length of the freshness value in bits
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getAuthInfoTxLength()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU Handle
*       @param FreshnessValueLength Length of the freshness value in bits
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g. a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessValueLength(DsBusCustomCodePduHandle PduHandle,
                                                                  uint32* FreshnessValueLength);

/** <!------------------------------------------------------------------------->
*   Get the length in bits of the freshness value that is included in the
*   payload of the secured IPDU
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSecuredIPdu_getAuthInfoTxLength()
*   - #DsBusCustomCodeSecuredIPdu_getFreshnessValueLength()
*
*   @parameters
*       @param PduHandle A DsBusCustomCode PDU Handle
*       @param FreshnessValueTxLength Length in bits of the freshness value
*                                     that is included in the payload of the
*                                     secured IPDU
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g. a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSecuredIPdu_getFreshnessValueTxLength(DsBusCustomCodePduHandle PduHandle,
                                                                    uint32* FreshnessValueTxLength);

/* PDU Feature */

/** <!------------------------------------------------------------------------->
*   Get the PDU related to a PDU feature
*
*   @description
*   - This function gets a handle to the PDU which is related to the provided
*     PDU feature
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param PduHandle The PDU handle of the PDU related to the provided PDU
*                        feature
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePduFeature_getPdu(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                DsBusCustomCodePduHandle* PduHandle);

/** <!------------------------------------------------------------------------->
*   Set a pointer to a user-defined data structure related to a PDU feature
*
*   @description
*   - This function allows the user to set a pointer to a data structure
*     related to a PDU feature. The data structure can be defined by the
*     user and is set during initialization time. This data structure
*     related to the PDU feature can be retrieved during feature execution
*     or application stop by using DsBusCustomCodePduFeature_getFeatureDataPtr
*     and allows for keeping PDU feature-specific data and states
*     (e.g., handles of lower layer function, counters, etc.) between
*     initialization and runtime and during subsequent feature execution calls.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during initialization
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePduFeature_getFeatureDataPtr()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param FeatureDataPtr The pointer to the user-defined data structure
*                             (to be casted to uint8*)
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePduFeature_setFeatureDataPtr(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                           uint8* FeatureDataPtr);

/** <!------------------------------------------------------------------------->
*   Get a pointer to a user-defined data structure related to a PDU feature
*
*   @description
*   - This function allows the user to get a pointer to a data structure
*     related to a PDU feature previously stored using
*     DsBusCustomCodePduFeature_setFeatureDataPtr.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodePduFeature_setFeatureDataPtr()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param FeatureDataPtr The pointer to the user-defined data structure
*                             (to be casted from uint8* to the data type of
*                             the user-defined data structure)
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePduFeature_getFeatureDataPtr(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                           uint8** FeatureDataPtr);

/* ECU/Cluster */

/** <!------------------------------------------------------------------------->
*   Get the communication cluster that is related to a PDU feature
*
*   @description
*   - This function gets a handle to the communication cluster, which is
*     related to the provided PDU feature. Using the communication cluster
*     handle allows to get the name of the related communication cluster
*     by calling DsBusCustomCode_getName(). This value might be set,
*     depending on whether the PDU feature execution is performed once
*     per communication cluster or once per transmitting or receiving ECU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCode_getName()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param CommunicationClusterHandle The communication cluster handle
*                                         of the communication cluster related
*                                         to the provided PDU feature
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePduFeature_getCommunicationCluster(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                 DsBusCustomCodeCommunicationClusterHandle* CommunicationClusterHandle);

/** <!------------------------------------------------------------------------->
*   Get the ECU that is related to a PDU feature
*
*   @description
*   - This function gets a handle to the ECU that is related to the provided
*     PDU feature. Using the ECU handle allows for getting the name of the
*     related ECU by calling DsBusCustomCode_getName(). This value might be
*     set, depending on whether the PDU feature execution is performed once
*     per communication cluster or once per transmitting or receiving ECU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCode_getName()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param EcuHandle The ECU handle of the ECU related to the provided
*                        PDU feature
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodePduFeature_getEcu(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                DsBusCustomCodeEcuHandle* EcuHandle);

/* Signal functions */

/** <!------------------------------------------------------------------------->
*   Get the start bit position of a signal
*
*   @description
*   - This function gets the signal's start bit position in bits in a PDU
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSignal_getLength()
*
*   @parameters
*       @param Handle A DsBusCustomCode handle
*       @param Data The signal start bit position in bits
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSignal_getStartBitPosition(DsBusCustomCodeSignalHandle Handle, uint32* Data);

/** <!------------------------------------------------------------------------->
*   Get the length of a signal
*
*   @description
*   - This function gets the signal's length at the PDU in bits
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSignal_getStartBitPosition()
*
*   @parameters
*       @param Handle A DsBusCustomCode handle
*       @param Data The signal length in bits
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSignal_getLength(DsBusCustomCodeSignalHandle Handle, uint32* Data);

/** <!------------------------------------------------------------------------->
*   Get the endianness of a signal
*
*   @description
*   - This function gets the signal's endianness at the PDU in bits
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeSignal_getStartBitPosition()
*
*   @parameters
*       @param Handle A DsBusCustomCode handle
*       @param Data The signal endianness as DsBusCustomCode_ByteOrderType
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeSignal_getEndianness(DsBusCustomCodeSignalHandle Handle,
                                                   DsBusCustomCode_ByteOrderType* Data);

/* UserPort functions */

/** <!------------------------------------------------------------------------->
*   Get direction of user port
*
*   @description
*   - This function gets the user port's direction
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param UserPortHandle A DsBusCustomCode handle
*       @param Data The direction of port of type boolean, 1=Out, 0=In
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeUserPort_getDirection(DsBusCustomCodeUserPortHandle UserPortHandle,
                                                    boolean* Data);

/** <!------------------------------------------------------------------------->
*   Set data value of user port
*
*   @description
*   - This function sets the user port's data value
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param UserPortHandle A DsBusCustomCode handle
*       @param Data The data of type float64
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeUserPort_setPortData(DsBusCustomCodeUserPortHandle UserPortHandle,
                                                   float64 Data);

/** <!------------------------------------------------------------------------->
*   Get data value of user port
*
*   @description
*   - This function gets the user port's data value
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during runtime
*   - Execution time: deterministic
*
*   @parameters
*       @param UserPortHandle A DsBusCustomCode handle
*       @param Data A pointer to data of type float64
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeUserPort_getPortData(DsBusCustomCodeUserPortHandle UserPortHandle,
                                                   float64* Data);

#ifdef __cplusplus
}
#endif

#endif /* DSBUSCUSTOMCODE_H */
