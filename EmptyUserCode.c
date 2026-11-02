#define DS_BUS_CUSTOM_FEATURE_NAME EmptyUserCode

#include <dsstd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <DsBusCustomCode_PduUserCode.h>

Std_ReturnType DsBusCustomCode_onApplicationInit(DsBusCustomCodePduFeatureHandle PduFeatureHandle)
{
	return E_OK;
}



Std_ReturnType DsBusCustomCode_onPduFeatureExecution(DsBusCustomCodePduFeatureHandle PduFeatureHandle)
{
	/*************** declare required handles, data pointers, and variables, for example, the following: ***************/	
	/* declare data pointers. */
	char* featureDescriptor;
	DsBusCustomCodePduHandle pduHandle;
	
	/* the pointer SduDataPtr points to the SDU bytes, i.e., the data bytes of the PDU */
	uint8* IPdu_SduDataPtr;		
	/* this handle represents the signals of a PDU specified in the PDU User Code feature*/
	DsBusCustomCodeSignalHandle *Signals;
	/* this handle represents the user ports that are available for the PDU User Code feature of a PDU */
	DsBusCustomCodeUserPortHandle* UserPorts;
	
	/* variables for the user-signals: bit-position */
	uint32 ISignalPos;
	/* variable for checking the PDU direction */
	boolean isTx;
	
	/* Feature handle & data */
	DSBUSCUSTOMCODE_CHECK_NULL(g_DsBusCustomCodeDefaultDescriptor, PduFeatureHandle);
	DSBUSCUSTOMCODE_TRY(g_DsBusCustomCodeDefaultDescriptor, DsBusCustomCode_getDescriptor(PduFeatureHandle, &featureDescriptor));
	/* this handle represents a PDU */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePduFeature_getPdu(PduFeatureHandle, &pduHandle));
	
	/* get the SduDataPtr pointer of a PDU. The pointer points to the SDU bytes, i.e., the data bytes of the PDU */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getSduDataPtr(pduHandle, &IPdu_SduDataPtr));

	/* get the array of the user signals that are specified for a PDU */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getUserSignals(PduFeatureHandle, &Signals));
	
	/* get the array of the user ports that are specified for a PDU via the PDU User Code feature */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeUserCodePduFeature_getUserPorts(PduFeatureHandle, &UserPorts));
	
	/* get the direction of a PDU, i.e, whether a PDU is transmitted (TX PDU) or received (RX PDU) */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodePdu_getIsTx(pduHandle, &isTx));
	
	/* The start bit position determines the first bit in the payload of a PDU that is used by the signal */
	DSBUSCUSTOMCODE_TRY(featureDescriptor, DsBusCustomCodeSignal_getStartBitPosition(Signals[0], &ISignalPos));
	
	
	
	/*************** This code is being executed when transmitting the PDU ***************/
	if(isTx)
	{
		msg_info_printf(0,0,"******************** Info onPduFeatureExecution Tx *************************");
		msg_info_printf(0,0,"Transmitting frame with ISignal on byte: %d and Value: %d", ISignalPos >> 3, IPdu_SduDataPtr[ISignalPos >> 3]);
		DsBusCustomCodeUserPort_setPortData(UserPorts[0], 123);
	}
	
	/*************** This code is being executed when receiving the PDU ***************/
	else
	{
		msg_info_printf(0,0,"******************** Info onPduFeatureExecution Rx *************************");
		msg_info_printf(0,0,"Receiving frame with ISignal on byte: %d and Value: %d", ISignalPos >> 3, IPdu_SduDataPtr[ISignalPos >> 3]);
		
		DsBusCustomCodeUserPort_setPortData(UserPorts[0], 456);
		DsBusCustomCodeUserCodePduFeature_setResult(PduFeatureHandle, 0);
	}
	
	return E_OK;
}



