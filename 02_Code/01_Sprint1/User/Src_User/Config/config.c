
#define _CONFIG_C_
#include "..\config\inc.h"
////////////////////////////////////////////////////////////////////////////////
////代码风格 命名规则
/*

变量 尽量用自注释命名,不同单词首字母大写
     如 任务计时器:  TaskTimer
     g_  global   全局 
     l_  local    本地
     s_  static   静态
     
                  
     g_cX/g_iX/g_wX/g_bX  全局 char/int(short)/long/bool型变量
     g_uX/g_tX/g_eX/g_fx  全局 union/struct/enum型变量/函数型变量
     g_XX        全局一般变量
     gc_XX       全局const
     ga_XX       全局数组
     gp_XX       全局指针
     其他(lX_../sX_.. 同gX_..)
     caXX/ctXX/wpXX..      局部变量无前缀 直接以 类型+名字

函数: 函数本身自注释命名:如任务调度函数 TaskSchedule
     函数命名规则:
     模块名简写+函数自注释名
     如 OS_TaskSchedule
     函数名前不必带返回值类型前缀

结构命名规则:  结构类型+自注释名    (单词首字母大写)
结构类型定义:  结构类型+自注释定义名(全大写)
     eXX/tXX/uXX/fXX
     如
     typedef enum{
      
     }eTASK_STATE;  enum内部命名全大写

     typedef struct{
     
     }tTASK_BLOCK;

     typedef union{
     
     }uTASK_BUFF;
     struct,union内部命名采用局部变量命名规则

     typedef (void)(*fUSER_FUNC)(void)

宏定义命名:
D_       开头全大写   开关名
_XXX_    XX全大写     常量值
_XxxXxx  首字母大写   动作宏定义
XX_XX_XX 全大写，单词分隔开
*/
////////////////////////////////////////////////////////////////////////////////

//--------------------------------0123456789ABCEF0123456789ABCDEF-------------------  
/*
#ifdef  D_AMP_TDA75610
const char ga_cSoftwareVer[] = "MC_V8_S401_V1.28A_160119_01\x0";//15B+'\0'
#else
const char ga_cSoftwareVer[] = "MC_V8_S401_V1.28C_160707_02\x0";//15B+'\0'
#endif
*/
#ifndef R103_H15T_OVERSEAS
#ifndef D_AMP_TDA7388
const char ga_cSoftwareVer[] = "MC_V8_R103-H15T_V0.41A_170502\x0";//15B+'\0'
#else
const char ga_cSoftwareVer[] = "MC_V8_R103-H15T_V0.41C_170502\x0";//15B+'\0' // use TDA7388
#endif
#else  //海外版版本号
const char ga_cSoftwareVer[] = "MC_V8_R103-H15T_V0.41C_170502U\x0";//15B+'\0' // use TDA7388
#endif



#if _COMPILER_  == _IAR_EWV850_
#pragma    constseg = FLAG_VER
#elif _COMPILER_ == _RENESAS_CUBE_
    #pragma section const "iap_ver_const" begin
#endif
const char ga_cBootVer[8] = {'B','.','0','1','\0','\0','\0','\0'};
#if _COMPILER_ == _IAR_EWV850_
#pragma    constseg = default
#elif _COMPILER_ == _RENESAS_CUBE_
    #pragma section const "iap_ver_const" end
#endif


