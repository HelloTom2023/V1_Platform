#   Copyright (C) NEC Electronics Corporation  2002, 2003
#   All rights reserved by NEC Electronics Corporation. This program must be used solely
#   for the purpose for which it was furnished by NEC Electronics Corporation . No part
#   of this program may be reproduced or disclosed to others, in any form,
#   without the prior written permission of NEC Electronics Corporation .
#
#   crtE.s -  start up module for ca850(V850E)
#
# DESCRIPTIONS:
#      This assembly program is a sample of start-up module for ca850(V850E).
#    If you modified this program, you must assemble this file, and
#    locate a given directory.
#
#    Unless -G is specified, sections are located as the following.
#
#                  |        :        |
#                  |        :        |
#           tp -> -+-----------------+ __start     __tp_TEXT
#                  |  start up       |
#                  |---------------- |
#   text section   |                 |
#                  | user program    |
#                  |                 |
#                  |-----------------|
#                  | library         |
#                 -+-----------------+ 
#                  |        :        |
#                  |        :        |
#                 -+-----------------+ __argc
#                  |      0          |
#                  |---------------- | __argv
#   data section   |    #.L16        |
#                  |---------------- | .L16
#                  | 0x0,0x0,0x0,0x0 |
#                 -+-----------------+               
#                  |                 |
#   sdata section  |                 |
#                  |                 |
#            gp-> -+-----------------+             __ssbss
#                  |                 |
#   sbss section   |                 |
#                  |                 |
#                  +-----------------+ __stack     __esbss     __sbss
#                  | stack area      |
#   bss section    |                 |
#                  |  0x200 bytes    |
#            sp-> -+-----------------+ __stack + STACKSIZE     __ebss
#
#=============================================================================
#-----------------------------------------------------------------------------
#    register mode
#-----------------------------------------------------------------------------
    .option reg_mode 5 5  
#    .option reg_mode 7 7  

#-----------------------------------------------------------------------------
#    special symbols
#-----------------------------------------------------------------------------    
    .extern __tp_TEXT, 4
    .extern __gp_DATA, 4
    .extern __ep_DATA, 4
    .extern __ssbss, 4
    .extern __esbss, 4
    .extern __sbss, 4
    .extern __ebss, 4
    .extern __sstack, 4
    .extern __estack, 4

#-----------------------------------------------------------------------------
#     C program main function
#-----------------------------------------------------------------------------
    .extern    _main
    .extern    _CLOCK_Init
    .extern    _SystemInit

#-----------------------------------------------------------------------------
#    for argv
#-----------------------------------------------------------------------------
#    .data
#    .size    __argc, 4
#    .align    4
#__argc:
#    .word    0
#    .size    __argv, 4
#__argv:
#    .word    #.L16
#.L16:
#    .byte    0
#    .byte    0
#    .byte    0
#    .byte    0

#-----------------------------------------------------------------------------
#    dummy data declaration for creating sbss section
#-----------------------------------------------------------------------------
    .sbss
    .lcomm    __sbss_dummy, 0, 0

#-----------------------------------------------------------------------------
#    system stack
#-----------------------------------------------------------------------------
    .set    STACKSIZE, 0x800
    .section ".stack",bss
    .lcomm    __stack, STACKSIZE, 4

#-----------------------------------------------------------------------------
#    RESET handler
#-----------------------------------------------------------------------------
    .section   "RESET", text
    jr      __start
    .section   "INTCB1T", text
    reti
    .section   "INTCB1R", text
    reti
#-----------------------------------------------------------------------------
#    start up
#        pointers:  tp - text pointer
#               gp - global pointer
#               sp - stack pointer
#               ep - element pointer
#        mask reg:  r20 - 0xff
#               r21 - 0xffff
#    exit status is set to r10
#-----------------------------------------------------------------------------
    .text
    .align    4
    .globl    __start
    .globl    _reset_vec
    .globl    _iap_reboot_entry
    .globl    __exit
    .globl    __startend
    .extern    ___PROLOG_TABLE
__start:

    jr    _reset_vec            -- call main function
__exit:
    halt                        -- end of program

    .section "iap_reboot_text.text", text
    .align    4
_iap_reboot_entry:
    nop
    nop
    nop
    nop

    
    .section "app_text.text", text
    .align    4
    
_reset_vec:
    mov        #__tp_TEXT, tp        -- set tp register
    mov        #__gp_DATA, gp        -- set gp register offset
    add        tp, gp                -- set gp register
    mov        #__stack+STACKSIZE, sp    -- set sp register
    mov        #__ep_DATA, ep        -- set ep register
    -- Init some io
    clr1    0x03,PDLL
    clr1    0x03,PMDLL
    clr1    0x03,PDLL
    -- on-chip debug mode
    mov        1, r11
    st.b    r11, PRCMD[r0]
    st.b    r11, OCDM[r0]

    -- system wait control
    mov        0x11, r10
    st.b    r10, VSWC[r0]

#
    .option nowarning
    mov        0xff,   r20        -- set mask register
    mov        0xffff, r21        -- set mask register
    .option warning
#
    mov        #__ssbss, r13        -- clear sbss section
    mov        #__esbss, r12
    cmp        r12, r13
    jnl        .L11
.L12:
    st.w    r0, [r13]
    add        4, r13
    cmp        r12, r13
    jl        .L12
.L11:
    mov        #__sstack, r13        -- clear bss section
    mov        #__estack, r12
    cmp        r12, r13
    jnl        .L14
.L15:
    st.w    r0, [r13]
    add        4, r13
    cmp        r12, r13
    jl        .L15
.L14:
    mov     #___PROLOG_TABLE, r12    -- for prologue/epilogue runtime
    ldsr    r12, 20            -- set CTBP (CALLT base pointer)

    
    jarl    _main,lp            -- call main function
    jr      _iap_reboot_entry   -- call iap_reboot_entry

__startend: 

