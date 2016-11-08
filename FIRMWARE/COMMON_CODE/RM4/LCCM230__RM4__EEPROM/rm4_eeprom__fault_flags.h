#ifndef _LCCM230__00__FAULT_FLAGS_H_
#define _LCCM230__00__FAULT_FLAGS_H_
/*
 * @fault_index
 * 00
 * 
 * @brief
 * EEPROM Not Init 
 * 
 * The EEPROM module has not been initted before a call was made to the module. 
 *  This is a critical fault as there has been some program sequence problem 
 * during power on reset. 
*/
#define C_LCCM230__CORE__FAULT_INDEX__00				0x00000000U
#define C_LCCM230__CORE__FAULT_INDEX_MASK__00			0x00000001U

/*
 * @fault_index
 * 01
 * 
 * @brief
 * Erase sector fail. 
 * 
 * An attempt to erase a sector was made prior to writing data.  The erase 
 * sector module returned a fault. 
*/
#define C_LCCM230__CORE__FAULT_INDEX__01				0x00000001U
#define C_LCCM230__CORE__FAULT_INDEX_MASK__01			0x00000002U

/*
 * @fault_index
 * 02
 * 
 * @brief
 * Write Buffer Fail 
 * 
 * An attempt to write the data back to the buffer failed.  The data has not 
 * been written. 
*/
#define C_LCCM230__CORE__FAULT_INDEX__02				0x00000002U
#define C_LCCM230__CORE__FAULT_INDEX_MASK__02			0x00000004U

/*
 * @fault_index
 * 03
 * 
 * @brief
 * Read attempt beyond range of buffer 
 * 
 * A Read attempt was made which is beyond the range of the data buffer.  
 * The calculated index was outside the range of the buffer, increase the 
 * buffer size or check the program logic. 
*/
#define C_LCCM230__CORE__FAULT_INDEX__03				0x00000003U
#define C_LCCM230__CORE__FAULT_INDEX_MASK__03			0x00000008U

#endif //#ifndef _LCCM230__FAULT_FLAGS_H_

