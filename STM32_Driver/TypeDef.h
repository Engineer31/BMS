#ifndef _TYPE_DEF_H
#define _TYPE_DEF_H


typedef	unsigned	char	Bool;
typedef	unsigned	char	bool;
typedef	unsigned	char	U8;
typedef	signed	char	S8;
typedef	unsigned	int	U32;
typedef	signed	int 	S32;
typedef	float			F32;
typedef	double		F64;
typedef	unsigned	short	U16;
typedef	signed	short	S16;
typedef	unsigned	long	long	U64;
typedef	signed	long	long	S64;
typedef unsigned char   	byte;

typedef S16             	Int16;
typedef S32            		Int32;
typedef U16    			Uint16;
typedef U32   			Uint32;
typedef U64 			Uint64;
typedef S64 			Int64;
typedef float           		Float32;
typedef double     		Float64;
typedef unsigned char   	Byte;


#define TRUE   1
#define FALSE  0

typedef void (*GetBytesFunc)(byte *data, U16 length);

typedef void (*GetIDBytesFunc)(byte ID, byte *data, U16 length);

typedef bool (*WriteFunc)(byte *data, U16 length);

#endif
