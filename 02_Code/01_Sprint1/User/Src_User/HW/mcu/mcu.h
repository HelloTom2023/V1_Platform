

#if (_CPU_TYPE_ == _V850_upd3355_) || (_CPU_TYPE_ == _V850_upd3365_) 
#include "upd70f33x5\v850.h"


#define ENTER_CRITICAL()
#define EXIT_CRITICAL()

#define cpu_wdt_start     v850_wdt2_init
#define cpu_init          v850_init
#define cpu_io_init       v850_io_init
#define cpu_wdt_reset     v850_wdt2_reset
#define cpu_lowpower      v850_enter_lp_mode
#define cpu_sleep         v850_sleep
#define cpu_awake         v850_awake

#define cpu_putc          v850_putc 

#endif
