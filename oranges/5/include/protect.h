#ifndef	_ORANGES_PROTECT_H_
#define	_ORANGES_PROTECT_H_

/* 存储段描述符/系统段描述符 */
typedef struct s_descriptor	/* 共8个字节 */
{
  u16 limit_low;		/* Limit */
  u16 base_low;			/* Base */
  u8 base_mid;			/* Base */
  u8 attr1;			/* P(1) DPL(2) DT(1) TYPE(4) */
  u8 limit_hight_attr2;		/* G(1) D(1) O(1) AVL(1) LimitHigh(4) */
  u8 base_high;			/* Base */
}DESCRIPTOR;

/* 门描述符 */
typedef struct s_gate
{
	u16	offset_low;	/* Offset Low */
	u16	selector;	/* Selector */
	u8	dcount;		/* 该字段只在调用门描述符中有效。如果在利用
				   调用门调用子程序时引起特权级的转换和堆栈
				   的改变，需要将外层堆栈中的参数复制到内层
				   堆栈。该双字计数字段就是用于说明这种情况
				   发生时，要复制的双字参数的数量。*/
	u8	attr;		/* P(1) DPL(2) DT(1) TYPE(4) */
	u16	offset_high;	/* Offset High */
}GATE;

/* 中断向量 */
#define	INT_VECTOR_IRQ0			0x20
#define	INT_VECTOR_IRQ8			0x28

#endif	/* _ORANGES_PROTECT_H_ */
