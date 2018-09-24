/**********************************************************
 * @file        Tw8836_Upgrade.h
 * @purpose    8836 Upgrade
 * @version    0.01
 * @date        2015.07.25
 * @author    XL
 * @brief
 ***********************************************************
 *     History:
 *  <write/modify>        <time>        <version >    <desc>
 *  Deefisher.Lyu          02.Feb.2013        v0.01        created
 *
  **********************************************************/
#ifndef Tw8836_Upgrade_H
#define Tw8836_Upgrade_H

#ifdef Tw8836_Upgrade
#define EXTERN
#else
#define EXTERN extern
#endif

#define UPGRADE_INIT 0
#define UPGRADE_DATA 1
#define UPGRADE_END 2

EXTERN uint8_t Tw8836_HoldMcu(void);
EXTERN uint8_t TW8836_SpiWriteEnable(uint8_t flag);
EXTERN uint8_t Tw8836_BlockErase(void);
EXTERN uint8_t TW8836_WriteInFlash(void);

EXTERN void Tw8836_UpgradeInit(void);
EXTERN void Tw8836_UpgradeProcess(void);
EXTERN void Tw8836_SetUpgradeStatus(uint8_t tStatus);
	
#undef EXTERN
#if D_DEBUG_8836_Upgrade&& D_PRINT_EN
#define Upgrade8836_printf(x)  x
#else
#define Upgrade8836_printf(x)
#endif
#endif
