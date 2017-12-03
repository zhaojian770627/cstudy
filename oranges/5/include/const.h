#ifndef _ORANGES_CONST_H_
#define _ORANGES_CONST_H_

/* EXTERN is defined as extern except in global.c */
#define EXTERN extern

/* 函数原型 */
#define PUBLIC			/* PUBLIC is the opposite of PRIVATE */
#define PRIVATE static		/* PRIVATE x limits the scope of x */

/* 8259A interrupt controller ports. */
#define INT_M_CTL     0x20 /* I/O port for interrupt controller       <Master> */
#define INT_M_CTLMASK 0x21 /* setting bits in this port disables ints <Master> */
#define INT_S_CTL     0xA0 /* I/O port for second interrupt controller<Slave>  */
#define INT_S_CTLMASK 0xA1 /* setting bits in this port disables ints <Slave>  */
/* GDT和IDT中描述符的个数 */
#define GDT_SIZE 128
#define	IDT_SIZE 256

#endif	/* _ORANGES_CONST_H_ */
