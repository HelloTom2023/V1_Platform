/***********************( Copyright infomation )********************************
 * FILE      :
 * INFOMATIN :
 * VERSION   : v00
 * DATA      : 22/03, 2013
 * AUTHOR    : yangyan
 *
 * UPDATE    :
 * ---------------------------------------------
 *   | INFOMATION
 *   | VERSION
 *   | AUTHOR
 *   -------------------------------------------
 *     |  ......
 *     |  
 ******************************************************************************/

#define _MAIN_C_
#include "..\config\inc.h"

#if _COMPILER_ == _RENESAS_CUBE_
extern unsigned long _S_romp;
#endif
void main(void)
{   
  	//PMC6H6 = 0;
	//P6H6 = 1;
	//PM6H6 = 0;
    #if _COMPILER_ == _RENESAS_CUBE_
    _rcopy(&_S_romp, -1);
    #endif
#ifndef D_CODE_FOR_JX
    cpu_io_init();
#endif
    cpu_init();

    DI();

    OS_Init();
	
	l_tMediaCB.uDevFlag.field.bUpData = 0;

    /*creat all task*/
    /*Task which not be stoped when PM OFF */
	(void)PM_TaskCreate();
	(void)HMI_TaskCreate(); 

    /*Task whitch will be stoped when PM OFF */
	(void)CANbus_TaskCreate();
	(void)MDI_TaskCreate();
	I2C_TaskCreate();
	(void)EEP_TaskCreate();
	(void)SRC_TaskCreate();
	(void)AUD_TaskCreate();
	(void)VID_TaskCreate();
	(void)Mult_Function_TaskCreate();
   
    cpu_wdt_start();
    EI();
    core_printf(_T("System Start,long:%d,int:%d ",sizeof(long),sizeof(int)));
    core_printf(_T("double:%d,float:%d,byte:%d\n",sizeof(double),sizeof(float),sizeof(char)));
    
    OS_TaskSchedule();
    
}


