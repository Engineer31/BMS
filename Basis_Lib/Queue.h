#ifndef __QUEUE_H
#define __QUEUE_H

struct _QueueStruct
{
    U8 *Data;
    U32 Length, Start, Count;	  //count 数据个数，Length 总长度 Start数据初始位置
};
typedef struct _QueueStruct QueueStruct;

extern void QueueInit( QueueStruct *Obj, U32 Length);
extern void QueueClear( QueueStruct *Obj);
extern void QueueFree( QueueStruct *Obj);
extern bool BytesEnqueue(QueueStruct *q, byte *data, U16 length);
extern bool ByteDequeue(QueueStruct *q, byte *data);
extern U8 QueueInsert( QueueStruct *Obj, U8 c);
extern Bool QueueFetch(QueueStruct *Obj, U8 *data);
extern U8 QueueRead( QueueStruct *Obj, U32 Num);
extern U16 QueueToArray(QueueStruct *Obj, U8 *data);

#define QUEUE_LENGTH	26
struct _FQueueStruct
{
    F32 *Data;
    U16 Start;
};
typedef struct _FQueueStruct FQueueStruct;

extern U8 FQueueInsert( FQueueStruct *Obj, F32 c);
extern U8 FQueueReplace(FQueueStruct *Obj, F32 c, U16 Num);
extern F32 FQueueRead( FQueueStruct *Obj, U16 Num);
extern U8 FQueueDataInit(FQueueStruct *Obj, F32 c);
struct _LQueueStruct
{
    S32 *Data;
    U16 Start;
};
typedef struct _LQueueStruct LQueueStruct;

extern U8 LQueueInsert( LQueueStruct *Obj, S32 c);
extern U8 LQueueReplace(LQueueStruct *Obj, S32 c, U16 Num);
extern S32 LQueueRead( LQueueStruct *Obj, U16 Num);
#endif
