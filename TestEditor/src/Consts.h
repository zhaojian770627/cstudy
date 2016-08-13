// Consts.h

#ifndef CONSTS_
#define CONSTS_

enum Indent {		// 缩进方式
leftInd, centerInd, rightInd
};

enum ParKind {		// 段落类型
	script,
	table
};

#define MaxWordSize 32		// 最大字数
#define MaxRMargin	80		// 最大右边空
#define	BuffLines	84		// 缓冲区最大行数
#define MaxRows		32		// 网格最大行数
#define MaxCols		10		// 网格最大列数
#define MaxItem		32		// 网格项最大长度

#endif	CONSTS_
