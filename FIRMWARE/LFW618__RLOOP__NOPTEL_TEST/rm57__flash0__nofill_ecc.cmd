
/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
/* ONLY USE FLASH BANK 0, DO NOT FILL THE REST OF THE FLASH*/
/* ENABLE ECC*/
/* Per: http://processors.wiki.ti.com/index.php/LAUNCHXL2-570LC43-RM57L:_LinkerECCRecommendation*/

--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */

MEMORY
{
    VECTORS (X)  : origin=0x00000000 length=0x00000020  vfill = 0xffffffff
    FLASH0  (RX)  : origin=0x00000020 length=0x001FFFE0  vfill = 0xffffffff
    FLASH1  (RX) : origin=0x00200000 length=0x00200000  vfill = 0xffffffff
    STACKS  (RW) : origin=0x08000000 length=0x00003000
    RAM     (RW) : origin=0x08003000 length=0x0007CFFF

	ECC_VEC (R)  : origin=0xf0400000 length=0x4 ECC={ input_range=VECTORS }
    ECC_FLA0 (R) : origin=0xf0400000 + 0x4 length=0x3FFFC ECC={ input_range=FLASH0 }
    ECC_FLA1 (R) : origin=0xf0440000 length=0x40000 ECC={ input_range=FLASH1 }
}

ECC
{
   algo_name : address_mask = 0xfffffff8
   hamming_mask = R4
   parity_mask = 0x0c
   mirroring = F021
}

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
    .intvecs : {} > VECTORS
	.text    align(8) : {} > FLASH0
    .const   align(8) : {} > FLASH0
    .cinit   align(8) : {} > FLASH0
    .pinit   align(8) : {} > FLASH0
    .stack :{} > STACKS
    .bss     : {} > RAM
    .data    : {} > RAM
	.sysmem  : {} > RAM
	

}


