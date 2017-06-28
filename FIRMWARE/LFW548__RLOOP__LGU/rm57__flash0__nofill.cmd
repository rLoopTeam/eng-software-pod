
/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
/* ONLY USE FLASH BANK 0, DO NOT FILL THE REST OF THE FLASH*/

--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */

MEMORY
{
    VECTORS (X)  : origin=0x00000000 length=0x00000020
    FIRMWARE_LFW   : origin=0x00000020 length=0x00000004 fill=0x00000000
    FIRMWARE_MAJOR : origin=0x00000024 length=0x00000004 fill=0x00000000
    FIRMWARE_MINOR : origin=0x00000028 length=0x00000004 fill=0x00000000
    FLASH0  (RX)  : origin=0x0000002C length=0x001FFFD0
    FLASH1  (RX) : origin=0x00200000 length=0x00200000
    STACKS  (RW) : origin=0x08000000 length=0x00003000
    RAM     (RW) : origin=0x08003000 length=0x0007CFFF

}


/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
    .intvecs : {} > VECTORS
	.lfwFirmware   :  {} > FIRMWARE_LFW
    .majorFirmware :  {} > FIRMWARE_MAJOR
    .minorFirmware :  {} > FIRMWARE_MINOR
	.text    align(8) : {} > FLASH0
    .const   align(8) : {} > FLASH0
    .cinit   align(8) : {} > FLASH0
    .pinit   align(8) : {} > FLASH0
    .bss     : {} > RAM
    .data    : {} > RAM
	.sysmem  : {} > RAM
	

}


