--/*
--*****************************************************************************
--*
--*  This device driver was created by Applilet2 for V850ES/Sx3
--*  32-Bit Single-Chip Microcontrollers
--*
--*  Copyright(C) NEC Electronics Corporation 2002 - 2013
--*  All rights reserved by NEC Electronics Corporation.
--*
--*  This program should be used on your own responsibility.
--*  NEC Electronics Corporation assumes no responsibility for any losses
--*  incurred by customers or third parties arising from the use of this file.
--*
--*  Filename :     inttab.s
--*  Abstract :    This file implements interrupt vector table.
--*  APIlib :    Applilet2 for V850ES/Sx3 V2.41 [28 Apr. 2008]
--*
--*  Device :    uPD70F3355
--*
--*  Compiler :    CA850
--*
--*  Creation date:    2013-3-27
--*  
--*****************************************************************************
--*/

--/*
--*****************************************************************************
--*  interrupt variable
--*****************************************************************************
--*/
    .option reg_mode 5 5  
#    .option reg_mode 7 7  

    .section "TRAP00", text            --TRAP instruction
    .globl    __trap00
__trap00:
    reti
    .section "TRAP10", text            --TRAP instruction
    .globl    __trap01
__trap01:
    reti
    .section "ILGOP", text            --ILGOP/DBG0 instruction



-- end of file
