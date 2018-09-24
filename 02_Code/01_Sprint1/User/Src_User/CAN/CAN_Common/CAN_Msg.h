#ifndef 	_CAN_MSG_H
#define 	_CAN_MSG_H

typedef struct
{
	uint8_t  OMS;
	uint8_t  op;
}CANMsgType;
/*HMI transmit message to CAN */

/*HMI->CAN operation GID */
#define LMS_CAN_RX_VEHICLE            0xe0
#define LMS_CAN_RX_NAVI                  0xe1
#define LMS_CAN_RX_DTV                    0xe2
#define LMS_CAN_RX_MEDIA                0xe3
#define LMS_CAN_RX_SYS				0xe4


/*HMI->CAN operation SID */
#define SID_CAN_RX_CAR_SETTING    	0x0B
#define SID_CAN_RX_NAVI_INFO        	0x01
#define SID_CAN_RX_DTV_CMD           	0x02
#define SID_CAN_RX_MEDIA_INFO	0x01
#define SID_CAN_RX_MEDIA_TIME	0x02
#define SID_CAN_RX_MEDIA_TITLE     	0x03

#define SID_CAN_RX_SYS_STATE		0x01
#define SID_CAN_RX_SYS_CLK		0x02
#define SID_CAN_RX_AVM_SLIP	0x03
#define SID_CAN_RX_DATA_REQ		0x04
/*--add it for exchanging machine---ztqin 20150112*/
#define OP_CAN_RX_VEHICLE_TBOX_VIN	     0x06/*receive APU's VIN*/
#define OP_CAN_RX_VEHICLE_TBOX_PHONE  0x07/*receive APU's PHONE*/

#define AMP_TYPE_POW		0x01
#define AMP_TYPE_MUTE		0x02
#define AMP_POW_OFF				0x00
#define AMP_POW_ON				0x01
#define AMP_MUTE_OFF				0x00
#define AMP_MUTE_ON				0x01


/*HMI->CAN operation Value */
#define OP_CAN_RX_VEHICLE_BACKCAR              0x00
#define OP_CAN_RX_VEHICLE_ATMOSPHER         0x01
#define OP_CAN_RX_VEHICLE_LAMP                    0x02

#define OP_CAN_RX_VEHICLE_WINDOW_ALL         0x03
#define OP_CAN_RX_VEHICLE_WINDOW_FL           0x04
#define OP_CAN_RX_VEHICLE_WINDOW_FR           0x05
#define OP_CAN_RX_VEHICLE_WINDOW_RL           0x06
#define OP_CAN_RX_VEHICLE_WINDOW_RR           0x07
#define OP_CAN_RX_VEHICLE_WINDOW_HEAD       0x08

#define OP_CAN_RX_VEHICLE_DOOR_ALL            0x09
#define OP_CAN_RX_VEHICLE_DOOR_FL              0x0A
#define OP_CAN_RX_VEHICLE_DOOR_FR              0x0B
#define OP_CAN_RX_VEHICLE_DOOR_RL              0x0C
#define OP_CAN_RX_VEHICLE_DOOR_RR              0x0D
#define OP_CAN_RX_VEHICLE_DOOR_BAG        	0x0E
#define OP_CAN_RX_VEHICLE_DOOR_ENGINE       0x0F

#define OP_CAN_RX_VEHICLE_WIPER_FRONT       0x10
#define OP_CAN_RX_VEHICLE_WIPER_REAR         0x11

#define OP_CAN_RX_VEHICLE_RMIR_LEFT            0x12
#define OP_CAN_RX_VEHICLE_RMIR_RIGHT          0x13

#define OP_CAN_RX_VEHICLE_CRUISE		          0X14
#define OP_CAN_RX_VEHICLE_MAINTAIN		   0X15
#define OP_CAN_RX_VEHICLE_AVM			   0X16
#define OP_CAN_RX_VEHICLE_SEARCH			   0X17
#define OP_CAN_RX_TBOX_REQTUID			   0x18
#define OP_CAN_RX_TBOX_REGACK			   0x19
#define OP_CAN_RX_BLIND_INOUT			   0x1a
#define OP_CAN_RX_VEHICLE_Seat			   0x1f
#define OP_CAN_RX_VEHICLE_Recover		   0x1e
#define OP_CAN_RX_VEHICLE_AvmSlip		   0x1b
#define OP_CAN_RX_VEHICLE_SetAmp		   0x1c	



#define OP_CAN_RX_FAC_SWITCH			 	0x40	/* Front AC switch on/off command */
#define OP_CAN_RX_RAC_SWITCH			 0x41	/* Rear AC switch on/off command */
#define OP_CAN_RX_FLAC_TEMP_ADJ		 	0x42	/* adjust Front Left AC temperature value: up/down 1 unit */
#define OP_CAN_RX_FRAC_TEMP_ADJ		 	0x43	/* adjust Front right AC temperature value: up/down 1 unit */
#define OP_CAN_RX_RAC_TEMP_ADJ		 	0x44	/* adjust rear AC temperature value: up/down 1 unit */
#define OP_CAN_RX_FAC_WIND_MODE			0x45	/* Front AC wind mode setting */
#define OP_CAN_RX_RAC_WIND_MODE			0x46 /* rear AC wind mode setting */
#define OP_CAN_RX_FAC_WIND_LEVEL_ADJ		0x47	/* Front AC wind level adjust: up/down 1 unit */
#define OP_CAN_RX_RAC_WIND_LEVEL_ADJ	0x48	/* rear AC wind level adjust: up/down 1 unit */

#define OP_CAN_RX_AC_REF_SWTICH			0x49	/*  AC refrigeration  switch on/off command */
#define OP_CAN_RX_ACF_AUTO_SET		       0x4a	/* AC F AUTO mode setting */
#define OP_CAN_RX_AC_CIRCLE_MODE  		0x4b	/* AC Circle mode setting */
#define OP_CAN_RX_AC_WIND_REGION		0x4c	/* AC wind region setting */
#define OP_CAN_RX_AC_FRONT_DEFROST          0x4d	/* AC front automatic defrost switch on/off */
#define OP_CAN_RX_AC_REAR_DEFROST		0x4e	/* AC rear automatic defrost switch on/off */
#define OP_CAN_RX_AC_GLASS_HEAT		       0x4f	/* AC glass heat  switch on/off */
#define OP_CAN_RX_AC_ECO_MODE		       0x50/* AC ECO mode  switch on/off */
#define OP_CAN_RX_AC_SENSOR		              0x51	/* AC Air sensor sensitivity */
#define OP_CAN_RX_AC_FILTER_SWITCH		0x52	/* AC Pollen filter switch on/off  */
#define OP_CAN_RX_FLAC_SEATHEAT		       0x53	/* AC Front left seat heat */
#define OP_CAN_RX_FRAC_SEATHEAT		       0x54	/* AC Front right seat heat */
#define OP_CAN_RX_RAC_SEATHEAT			0x55	/* ACRear seat heat  */
#define OP_CAN_RX_AC_WIND_AUTOCTL		0x56	/*Auto Wind Control Setting */
#define OP_CAN_RX_ACR_AUTO_SET		       0x58	/* AC R AUTO mode setting */

#define OP_CAN_RX_ACR_FAC_SWITCH			 	0x5D	/*ACR Front AC switch on/off command */
#define OP_CAN_RX_ACR_FLAC_TEMP_ADJ		 	0x5E	/*ACR adjust Front Left AC temperature value: up/down 1 unit */
#define OP_CAN_RX_ACR_FAC_WIND_MODE			0x5F	/*ACR Front AC wind mode setting */
#define OP_CAN_RX_ACR_FAC_WIND_LEVEL_ADJ		0x60	/*ACR Front AC wind level adjust: up/down 1 unit */
#define OP_CAN_RX_ACR_AC_CIRCLE_MODE  		0x61	/*ACR AC Circle mode setting */
#define OP_CAN_RX_ACR_AC_FRONT_DEFROST          0x62	/* ACR AC front automatic defrost switch on/off */
#define OP_CAN_RX_ACR_OPEN_AVM          0x63
#define OP_CAN_RX_ACR_RESET		       0xA0	/* AC reset	 */
#define OP_CAN_RX_LIGHT_OFF_DELAY	0x26
#define OP_CAN_RX_TURN_BLINK_TIMES	0x27
#define OP_CAN_RX_KEY_DOOR_UNLOCK_MODE 0x28
#define OP_CAN_RX_DRIVE_DOOR_LOCK	0x29
#define OP_CAN_RX_PARK_DOOR_UNLOCK	0x2A

#define OP_CAN_RX_ACC_OBJ_ENABLE		0x2C	//目标提示音
#define OP_CAN_RX_FCW_ENABLE			0X2D	//前碰撞预警
#define OP_CAN_RX_AUTO_BRAKE_ENABLE	0x2E	//前碰撞缓解
#define OP_CAN_RX_BSD_LCA_ENABLE		0x2F	//并线辅助
#define OP_CAN_RX_CTA_ENABLE			0x31	//倒车横向预警
#define OP_CAN_RX_RCW_ENABLE			0x32	//后追尾预警
#define OP_CAN_RX_LDW_SENSITIVITY		0x33	//灵敏度
#define OP_CAN_RX_SLA_SWITCH			0x34	//限速标示识别
#define OP_CAN_RX_HMA_ENABLE			0x35	//自动远光灯
#define OP_CAN_RX_DRIVE_LIGHT_ENABLE	0x36	//行车灯

/*CAM part transmit message to CAN */
/*Vehicle control part transmit message to CAN */
#define OMS_CAN_RX_VEHICLE	 LMS_CAN_RX_VEHICLE
/*NAVI part transmit message to CAN */
#define OMS_CAN_RX_NAVI 		 LMS_CAN_RX_NAVI
/*DTV part transmit message to CAN */
#define OMS_CAN_RX_DTV		 LMS_CAN_RX_DTV
/*MEDIA part transmit message to CAN */
#define OMS_CAN_RX_MEDIA 		 LMS_CAN_RX_MEDIA

/*CAN transmit message To HMI */
/*CAN->HMI operation GID */

#define LMS_CAN_TX_SYS                             0X60  /*Reserved.*/
#define LMS_CAN_TX_CAR                             0X61  /*Vehicle all information*/
#define LMS_CAN_TX_AC                               0X62  /*Vehicle AC information*/
#define LMS_CAN_TX_RADAR                        0X63  /*Vehicle Radar information*/
#define LMS_CAN_TX_TPMS                          0X64  /*Vehicle TPMS information*/
#define LMS_CAN_TX_OBD                            0X65  /*Vehicle OBD information*/
#define LMS_CAN_TX_DTV                            0X66  /*Vehicle DTV information*/
#define LMS_CAN_TX_KCP					0x67 /*keyboard control panel information */

/*CAN->HMI operation SID */

/*LMS_CAN_TX_CAR: SID definition */					
#define OP_CAN_TX_EOL						0x01	/*End of Line config data */
#define OP_CAN_TX_CAR_LIGHT				0X02	/*Car Light information */
#define OP_CAN_TX_CAR_WIPER				0X03	/*Car wiper information */
#define OP_CAN_TX_CAR_WINDOW				0X04	/*Car Window information */
#define OP_CAN_TX_CAR_DOOR				0X05	/*Car Door information */
#define OP_CAN_TX_CAR_SEAT				0X06	/*Car Seat information */
#define OP_CAN_TX_CAR_RMIRROR				0X07/*Car Rear Mirror information */
#define OP_CAN_TX_CAR_MAINTAIN			0X08	/*Car Maintain information */
#define OP_CAN_TX_ECU_STATE				0X09	/*ECU State information */
#define OP_CAN_TX_CAR_TBOX				0X0a	/*Car TBOX information */
#define OP_CAN_TX_CAR_ANGLE				0X0b	/*Car Angle information */
#define OP_CAN_TX_CAR_SPEED				0X0c/*Car Speed information */
#define OP_CAN_TX_CAR_SYS					0X0d	/*Car System information */
#define OP_CAN_TX_CAR_PEPS				0X0e  /*Car PEPS information */
#define OP_CAN_TX_CAR_ECO					0x0f	 /* vehicle ECO data */
#define OP_CAN_TX_CAR_VIN					0x10	/* vehicle VIN data */
#define OP_CAN_TX_TBOX_TUID				0x11 /*TBOX TUID data */
#define OP_CAN_TX_TBOX_PHONE				0x12 /*Tbox user register telephone */
#define OP_CAN_TX_AC_FRONT				0X13/*Front AC information */
#define OP_CAN_TX_AC_REAR					0X14/*Rrar AC information */
#define OP_CAN_TX_AC_OUTTEMP				0X15/*Outside Temperature information */
#define OP_CAN_TX_AC_SEATHEAT				0X16/*Seat heat information */
#define OP_CAN_TX_RADAR_STATE				0X17/*Radar State information */
#define OP_CAN_TX_RADAR_DATA			        0X18/*Radar Data information */
#define OP_CAN_TX_TPMS_DATA			        0X19/*TPMS Data information */
#define OP_CAN_TX_DTV_STATE			        0X1a/*DTV STATE information */
#define OP_CAN_TX_DTV_LIST			        	0X1b/*DTV LIST information */
#define OP_CAN_TX_DTV_CAST			        0X1c/*DTV CAST information */
#define OP_CAN_TX_DTV_CA			               0X1d/*DTV CA Card information */
#define OP_CAN_TX_DTV_VER					0x1e/*DTV Version information */
#define OP_CAN_TX_KCP_VER					0x1f/*KCP version inforamtion */
#define OP_CAN_TX_AVM_INFO				0x23/*AVM information*/
#define OP_CAN_TX_FUEL_LEVEL				0x24/*FUEL Level information*/
#define OP_CAN_TX_CAR_ODO					0x21/*Vehicle Odometer information*/
#define OP_CAN_TX_DOOR_LOCK_INFO			0x25/*DOOR LOCK INFO*/
#define OP_CAN_TX_CAN_PM_DATA			0x26/*CAN PM INFO*/



#define OP_CAN_TX_ACC_CONTROL_DATA		0x27/*CAN ACC INFO*/
#define OP_CAN_TX_FCW_DATA				0x28/*CAN FCW INFO*/
#define OP_CAN_TX_RCW_DATA				0x29/*CAN RCW INFO*/
#define OP_CAN_ROAD_ASSISTANT				0x2A/*CAN ROAD ASSISTANT*/



#define OP_CAN_TX_PRJ_SPCL					0xff
/*LMS_CAN_TX_SYS: SID definition */
#define OP_CAN_TX_CAN_KNOB				0x01	/*canbus keyboard knob information */
#define OP_CAN_TX_PM_REQ					0x02	/*CAN send PM information to HMI */

/*-----------NEXT define no used------------------*/
#define OP_CAN_TX_CAN_STATE				0X00	/*CAN module state: APU comm associate */
#define OP_CAN_TX_SYNC_CLK				0x04/* sync clock ticks data */
#define OP_CAN_TX_CAR_BSD					0X09	/*Car BSD information */
#define OP_CAN_TX_CAR_PAC					0X0A	/*Car Parking information */
#define OP_CAN_TX_CAR_AVM					0X0E	/*Car AVM information */
#define OP_CAM_TX_KCP_KEYBOARD_TEST       0x02/*keyboard test*/
/*CAN module Send message to HMI */
#define OMS_CAN_TX_SYS				        	LMS_CAN_TX_SYS	
#define OMS_CAN_TX_CAR				 	LMS_CAN_TX_CAR	
#define OMS_CAN_TX_AC				        	LMS_CAN_TX_AC
#define OMS_CAN_TX_RADAR			        	LMS_CAN_TX_RADAR
#define OMS_CAN_TX_TPMS			        	LMS_CAN_TX_TPMS	
#define OMS_CAN_TX_OBD			        	LMS_CAN_TX_OBD	
#define OMS_CAN_TX_DTV			        	LMS_CAN_TX_DTV
#define OMS_CAN_TX_KCP					LMS_CAN_TX_KCP



#endif

