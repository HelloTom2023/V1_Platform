#ifndef _INC_H_
#define _INC_H_


#include "stdlib.h"
#include "stdarg.h"
#include "stdio.h"
#include "math.h"


#include "..\config\type.h"


#include "..\config\config.h"



#include "..\hw\mcu\mcu.h"
#include "..\hw\mcu\mcu_io.h"
#include "..\api\printf.h"

#include "..\kernel\msg_def.h"
#include "..\kernel\core.h"


#include "..\i2c\i2c.h"


#include "..\power\power.h"



#include "..\media\media_driver.h"
#include "..\media\media.h"
#include "..\media\media_user.h"

#include "..\eeprom\eeprom.h"

#include "..\sys\sys_core.h"
#include "..\sys\sys_app.h"
#include "..\sys\sys_user.h"

#include "..\sys\sys.h"

#include "..\hmi\hmi.h"
#include "..\hmi\key_def.h"
#include "..\hmi\key.h"

#include "..\Audio\Dsp_def.h"
#include "..\Audio\Audio_Public.h"
#ifdef D_AUDIO_ASP_HERO
#include "..\Hero\Hero_Audio_Private.h"
#include "..\Hero\Hero_Tuner_Private.h"
#include "..\Hero\Hero_Drv.h"
#include "..\Hero\Hero_Func.h"
#include "..\Hero\Hero_Ctl.h"
#endif//D_AUDIO_ASP_HERO



#include "..\Dirana3\Dirana3_ABB_E7A1.h"
#include "..\Dirana3\Dirana3_Drv.h"
#include "..\Dirana3\Dirana3_Func.h"
#include "..\Audio\Audio_Func.h"
#include "..\Audio\Task_Audio.h"
#include "..\Audio\Audio_Api.h"
#include "..\Audio\Audio_Link.h"
#include "..\Audio\Amp\Amp_Drv.h"
//#include "..\Comm\Comm.h"
#include "..\Tuner\Tuner_Public.h"
#include "..\Tuner\Task_Tuner.h"
#include "..\Tuner\Tuner_MidLayer.h"
#include "..\Tuner\Tuner_LinkLayer.h"
#ifdef D_TUNER_MODULE_HERO
#include "..\Tuner\Tuner_Nxp6638.h"
#endif//D_TUNER_MODULE_HERO
#include "..\Video\Task_Video.h"
#ifdef D_VIDEO_SWITCH_FMS6501
#include "..\Video\Video_Fms6501.h"
#endif//#ifdef D_VIDEO_SWITCH_FMS6501
#ifdef D_VIDEO_SWITCH_TW8836
#include "..\Video\tw8836\Tw8836_Drv.h"
#include "..\Video\tw8836\Tw8836_Ctrl.h"
#include "..\Video\tw8836\Tw8836_Upgrade.h"
//#include "..\Video\tw8836\Tw8836_OSD.h"
#include "..\I2c\SoftI2c.h"
#endif

#include "..\Rds\Rds_Public.h"
#include "..\Rds\Rds_Func.h"

#include "..\Tmc\Tef700x_Drv.h"
#include "..\Tmc\Tef700x_Func.h"
#include "..\Tmc\Tmc_Ctl.h"

#include "..\CAN\CAN_BuildIn\CANbus.h"
#include "..\Mult_Function\Mult_Function.h"//lkm20140321_edit
#include "..\FCT\FCT_Task.h"   //__dhb+
//#include "..\TW8836\tw8836.h"
#include "..\Test\TestCase.h"

#include "..\Video\NJM2246.h"
#include "..\Audio\74HC4053.h"

#endif


