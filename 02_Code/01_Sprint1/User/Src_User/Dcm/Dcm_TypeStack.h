/****************************************************************************
* File Name : Dcm_TypeStack.h
*
* Modules : Diagnostic Communication management Layer head file
*
* Summary : 1.The file define use data type in diagnostic communication layer.
*
*
*
* Reference Documents : None
*
/****************************************************************************
* Author : Mingfen XIAO
* Version : V0.1
* Date	: 2018-12-10
* Description : 1.Create the modules
* 				2.Initialization Version
****************************************************************************/
#ifndef _DCM_TYPESTACK_H_
#define _DCM_TYPESTACK_H_

/*Include head files AREA*/
/*
 * Negative Response Code (NRC) definition and values
 * Reference <<ISO 14229-1 2013>>.
 * */
#define DCM_NRC_PR				(0x00)	/*positiveResponse*/
#define DCM_NRC_GR				(0x10)  /*generalReject*/
#define DCM_NRC_SNS				(0x11)  /*serviceNotSupported*/
#define DCM_NRC_SFNS			(0x12)  /*sub-functionNotSupported*/
#define DCM_NRC_IMLOIF			(0x13)  /*incorrectMessageLengthOrInvalidFormat*/
#define DCM_NRC_RTL				(0x14)  /*responseTooLong*/
#define DCM_NRC_BRR				(0x21)  /*busyRepeatRequest*/
#define DCM_NRC_CNC				(0x22)  /*conditionsNotCorrect*/
#define DCM_NRC_RSE				(0x24)  /*requestSequenceError*/
#define DCM_NRC_NRFSC			(0x25)  /*noResponseFromSubnetComponent*/
#define DCM_NRC_FPEORA			(0x26)  /*FailurePreventsExecutionOfRequestedAction*/
#define DCM_NRC_ROOR			(0x31)  /*requestOutOfRange*/
#define DCM_NRC_SAD				(0x33)  /*securityAccessDenied*/
#define DCM_NRC_IK				(0x35)  /*invalidKey*/
#define DCM_NRC_ENOA			(0x36)  /*exceedNumberOfAttempts*/
#define DCM_NRC_RTDNE			(0x37)  /*requiredTimeDelayNotExpired*/
#define DCM_NRC_UDNA			(0x70)  /*uploadDownloadNotAccepted*/
#define DCM_NRC_TDS				(0x71)  /*transferDataSuspended*/
#define DCM_NRC_GPF				(0x72)  /*generalProgrammingFailure*/
#define DCM_NRC_WBSC			(0x73)  /*wrongBlockSequenceCounter*/
#define DCM_NRC_RCRRP			(0x78)  /*requestCorrectlyReceived-ResponsePending*/
#define DCM_NRC_SFNISAS			(0x7E)  /*sub-functionNotSupportedInActiveSession*/
#define DCM_NRC_SNSIAS			(0x7F)  /*serviceNotSupportedInActiveSession*/
#define DCM_NRC_RPMTH			(0x81)  /*rpmTooHigh*/
#define DCM_NRC_RPMTL			(0x82)  /*rpmTooLow*/
#define DCM_NRC_EIR				(0x83)  /*engineIsRunning*/
#define DCM_NRC_EINR			(0x84)  /*engineIsNotRunning*/
#define DCM_NRC_ERTTL			(0x85)  /*engineRunTimeTooLow*/
#define DCM_NRC_TEMPTH			(0x86)  /*temperatureTooHigh*/
#define DCM_NRC_TEMPTL			(0x87)  /*temperatureTooLow*/
#define DCM_NRC_VSTH			(0x88)  /*vehicleSpeedTooHigh*/
#define DCM_NRC_VSTL			(0x89)  /*vehicleSpeedTooLow*/
#define DCM_NRC_TPTH			(0x8A)  /*throttle/PedalTooHigh*/
#define DCM_NRC_TPTL			(0x8B)  /*throttle/PedalTooLow*/
#define DCM_NRC_TRNIN			(0x8C)  /*transmissionRangeNotInNeutral*/
#define DCM_NRC_TRNIG			(0x8D)  /*transmissionRangeNotInGear*/
#define DCM_NRC_BSNC			(0x8F)  /*brakeSwitch(es)NotClosed (Brake Pedal not pressed or not applied)*/
#define DCM_NRC_SLNIP			(0x90)  /*shifterLeverNotInPark*/
#define DCM_NRC_TCCL			(0x91)  /*torqueConverterClutchLocked*/
#define DCM_NRC_VTH				(0x92)  /*voltageTooHigh*/
#define DCM_NRC_VTL				(0x93)  /*voltageTooLow*/

#endif /* _DCM_TYPESTACK_H_ */
