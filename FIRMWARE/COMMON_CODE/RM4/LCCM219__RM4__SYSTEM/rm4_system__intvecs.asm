;-------------------------------------------------------------------------------
; sys_intvecs.asm
;
; (c) Texas Instruments 2009-2013, All rights reserved.
;

    .sect ".intvecs"
    .arm

;-------------------------------------------------------------------------------
; import reference for interrupt routines

    .ref _c_int00
    .ref _dabort
    
    .def resetEntry

;-------------------------------------------------------------------------------
; interrupt vectors

resetEntry
        b   _c_int00
undefEntry
        b   undefEntry
svcEntry
        b   svcEntry
;A typical reason for the prefetch abort is a double-bit ECC error.
;Do you enable ECC checking for the flash?
;If so, you do need to fill the entire available 3MB flash.
;Any unused flash needs to be filled with a value that could act as a trap if the CPU ever starts
;executing code fetched from those "unused" locations. One suggested value to use as a fill is 0xEEFF3300.
;Check the registers:
;CP15_AUX_INSTRUCTION_FAULT_STATUS
;CP15_AUX_INSTRUCTION_FAULT_ADDRESS
;Check the statck size
;http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0335a/Chdbadah.html
;You can use the following assembly function in your data abort ISR to see the error address. With the error address and other information (such as link register), you should be able to figure out what causes the abort.
;Read_DFSR:
;    MRC p15, #0, r0, c5, c0, #0
;    MOV     pc, r14
;
;Read_IFSR:
;    MRC p15, #0, r0, c5, c0, #1
;    MOV     pc, r14
;
;Read_DFAR:
;MRC p15, #0, r0, c6, c0, #0
;    MOV     pc, r14
;Read_IFAR:
;    MRC p15, #0, r0, c6, c0, #2
;    MOV     pc, r14

;CHECK YOUR CLOCK SPEED. WRONG CRYSTAL SETTINGS IN LOCALDEF WILL CAUSE DATA ABORTS!!!!

prefetchEntry
        b   prefetchEntry
        b   _dabort
reservedEntry
        b   reservedEntry
        ldr pc,[pc,#-0x1b0]
        ldr pc,[pc,#-0x1b0]

    
;-------------------------------------------------------------------------------
