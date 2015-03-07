/* ---------------------------------------------------------------------------------------------------
[FILE NAME]:      < common_macro.h >
[AUTHOR(S)]:      < Mohamed AbdelRaouf >
[DATE CREATED]:   < Mon 12/29/2014 >
[DESCRIPTION]:    < the file contains some common macros that are used to deal with hardware >
------------------------------------------------------------------------------------------------------- */

#ifndef COMMON_MACRO_H_
#define COMMON_MACRO_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT_NUM) ( REG = REG | (1<<BIT_NUM) )

/* clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT_NUM) ( REG = REG & (~(1<<BIT_NUM)) )

/* check if any bit is set in any register and return true if yes  */
#define BIT_IS_SET(REG,BIT_NUM) ( REG & (1<<BIT_NUM) )

/* check if any bit is clear in any register and return true if yes  */
#define BIT_IS_CLEAR(REG,BIT_NUM) ( !(REG & (1<<BIT_NUM)) )

#endif /* COMMON_MACRO_H_ */
