/** <!------------------------------------------------------------------------->
*
*   @file DsBusCustomCode_PduUserCode.h
*
*   @brief PduUserCode data type and function declarations
*
*   @description
*       This file is the public interface of the PDU User Code feature.
*       Before it is included in the user code, DS_BUS_CUSTOM_FEATURE_NAME
*       must be defined in the respective user code.
*
*   @copyright
*       Copyright 2020, dSPACE GmbH. All rights reserved.
*
*<!-------------------------------------------------------------------------->*/

#ifndef DSBUSCUSTOMCODE_PDUUSERCODE_H
#define DSBUSCUSTOMCODE_PDUUSERCODE_H

#include "DsBusCustomCode_Internal.h"

#ifdef __cplusplus
extern "C" {
#endif

/** <!------------------------------------------------------------------------->
*   Get the result of the PDU User Code feature for a specific PDU
*
*   @description
*   - This function allows the user to get the result of the PDU User
*     Code feature related to a specific PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during initialization
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeUserCodePduFeature_setResult()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param Data A Pointer to a variable to receive the feature state
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeUserCodePduFeature_getResult(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                           uint32* Data);

/** <!------------------------------------------------------------------------->
*   Set the result of the PDU User Code feature for a specific PDU
*
*   @description
*   - This function allows the user to set the result of the PDU User Code
*     feature related to a specific PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during initialization
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeUserCodePduFeature_getResult()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param Data The new feature state
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeUserCodePduFeature_setResult(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                           uint32 Data);

/** <!------------------------------------------------------------------------->
*   Get the number of user signals related to the PDU User Code feature of a
*   specific PDU
*
*   @description
*   - This function allows the user to get the number of user signals related to
*     the PDU User Code feature of a specific PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during initialization
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeUserCodePduFeature_getNumberOfUserSignals()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param Data A Pointer to a variable to receive the number of user signals
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeUserCodePduFeature_getNumberOfUserSignals(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                        uint32* Data);

/** <!------------------------------------------------------------------------->
*   Get the array of user signals related to the PDU User Code feature of a
*   specific PDU
*
*   @description
*   - This function allows the user to get the array of user signals related to
*     a specific PDU.
*   - The size of the array that can be received with a function call to
*   - #DsBusCustomCodeUserCodePduFeature_getSignalsCount() will specify the upper
*     boundary of the array.
*   - Single entries of the array might be zero, if the signal was not specified.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during initialization
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeUserCodePduFeature_getUserSignals()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param Data A Pointer to a pointer of the first element of the signal array.
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeUserCodePduFeature_getUserSignals(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                DsBusCustomCodeSignalHandle** Data);

/** <!------------------------------------------------------------------------->
*   Get the number of user defined ports related to the PDU User Code feature of a
*   specific PDU
*
*   @description
*   - This function allows the user to get the number of user defined ports related to
*     the PDU User Code feature of a specific PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during initialization
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeUserCodePduFeature_getNumberOfUserPorts()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param Data A Pointer to a variable to receive the number of user ports
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeUserCodePduFeature_getNumberOfUserPorts(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                                      uint32* Data);

/** <!------------------------------------------------------------------------->
*   Get the array of user defined ports related to the PDU User Code feature of a
*   specific PDU
*
*   @description
*   - This function allows the user to get the array of user defined ports related to
*     a specific PDU.
*
*   @note
*   - Thread-safe: yes
*   - Intended use: during initialization
*   - Execution time: deterministic
*
*   @see
*   - #DsBusCustomCodeUserCodePduFeature_getUserPorts()
*
*   @parameters
*       @param PduFeatureHandle A DsBusCustomCode PDU feature handle
*       @param Data A Pointer to a pointer of the first element of the user port array.
*
*   @return
*   - #E_OK or
*   - #E_NOT_OK or
*   - #E_PARAMETER_NOT_SET if the parameter was not set
*   - #E_INVALID_HANDLE if the handle was invalid (e.g., a NULL pointer)
*<!-------------------------------------------------------------------------->*/
Std_ReturnType DsBusCustomCodeUserCodePduFeature_getUserPorts(DsBusCustomCodePduFeatureHandle PduFeatureHandle,
                                                              DsBusCustomCodeUserPortHandle** Data);

#ifdef __cplusplus
}
#endif

#endif /* DSBUSCUSTOMCODE_PDUUSERCODE_H */
