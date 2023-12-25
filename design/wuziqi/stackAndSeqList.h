#pragma once

#include <stdbool.h>
#include "class.h"

void StackChessInit(ST* ps);
void StackChessPush(ST* ps, Chess x);
Chess StackChessPop(ST* ps);
Chess StackChessTop(ST* ps);
bool StackChessEmpty(ST* ps);
void StackChessDestroy(ST* ps);
void StackChessPrint(ST* ps);
// 清空栈
void StackChessClear(ST* pStack);

void SeqListPrint(SL* ps);
void SeqListInit(SL* ps);
void SeqListDestroy(SL* ps);
void SeqListCheckCapacity(SL* sl);
void SeqListPushBack(SL* ps, SLDataType x);
void SeqListPopBack(SL* ps);
void SeqListPushFront(SL* ps, SLDataType x);
void SeqListPopFront(SL* ps);
void SeqListClear(SL* ps);