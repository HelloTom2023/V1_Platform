    .option reg_mode 5 5  
#    .option reg_mode 7 7 

    .extern __sno_init.bss, 4
    .extern __eno_init.bss, 4
    .extern __sno_init.data, 4
    .extern __eno_init.data, 4

    .extern __sno_init.data, 4
    .extern __eno_init.data, 4

    .section ".text", text
    .globl _OS_GetNoInitRamSectionAdd
    .globl _OS_ClearNoInitRamSectiont

    # Parameter: ulong *secStart,*secEnd 
    _OS_GetNoInitRamSectionAdd:
        #  Generate section start
        movhi   hi1 (#__sno_init.bss), zero, r10
        movea   lo  (#__sno_init.bss), r10, r10
         #  Generate section size 
        movhi   hi1 (#__eno_init.bss), zero, r11
        movea   lo  (#__eno_init.bss), r11, r11
        br _return_value
    
        
    _return_value:     
        st.w    r10, 0[r6]
        st.w    r11, 0[r7]
        jmp     [lp]

    _OS_ClearNoInitRamSectiont:
        mov        #__sno_init.bss, r13        -- clear sbss section
        mov        #__eno_init.bss, r12
        cmp        r12, r13
        jnl        .exit_clear
    .Clear:
        st.w    r0, [r13]
        add        4, r13
        cmp        r12, r13
        jl        .Clear
    .exit_clear:
        jmp     [lp]
        