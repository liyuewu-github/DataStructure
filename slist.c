#include <stdio.h>
#include <stdlib.h>

/*，，，
矩阵转圈，动态规划，*/

#define NULL ((void *)0)

/* 单链表 */
typedef struct S_List
{
	unsigned int uiValue;
	struct S_List *pstNext;
}S_LIST_S;

/* 链表插入 */
S_LIST_S * SLIST_Insert(S_LIST_S *pstSList, unsigned int uiValue)
{
	S_LIST_S *pstSList_New;
	S_LIST_S *pstSList_Iter;

	pstSList_New = malloc(sizeof(S_LIST_S));
	if (!pstSList_New)
		return;

	pstSList_New->uiValue = uiValue;
	pstSList_New->pstNext = NULL;

	if (!pstSList) /* 链表第一个节点 */
	{
		pstSList = pstSList_New;
		return pstSList;
	}

	pstSList_Iter = pstSList;
	while (pstSList_Iter->pstNext)
	{
		pstSList_Iter = pstSList_Iter->pstNext;
	}
	
	pstSList_Iter->pstNext = pstSList_New;

	return pstSList;
}

/* 查找链表 */
S_LIST_S * SLIST_Find(S_LIST_S *pstSList, unsigned int uiValue)
{
	while (pstSList)
	{	
		if (pstSList->uiValue == uiValue)
			return pstSList;
		pstSList = pstSList->pstNext;
	}

	return NULL;
}

/* 链表长度 */
unsigned int SLIST_Len(S_LIST_S *pstSList)
{
	unsigned int uiLen = 0;
	while (pstSList)
	{	
		uiLen++;
		pstSList = pstSList->pstNext;
	}

	return uiLen;
}

/* 打印链表 */
void SLIST_Dump(S_LIST_S *pstSList)
{
	while (pstSList)
	{
		printf("%d \n", pstSList->uiValue);
		pstSList = pstSList->pstNext;
	}
}


/* 链表反转-非递归 */
S_LIST_S *SLIST_Reverse_NoRecursive(S_LIST_S *pstSList)
{
	S_LIST_S *pstSList_Rev = NULL;
	S_LIST_S *pstSList_Cur;
	S_LIST_S *pstSList_Next;

	pstSList_Cur = pstSList;

	while (pstSList_Cur)
	{
		pstSList_Next = pstSList_Cur->pstNext; /* 先记录当前节点的下一个节点，后面会被覆盖 */
		pstSList_Cur->pstNext = pstSList_Rev; /* 当前节点pstNext指向其前一个节点，即反转 */
		pstSList_Rev = pstSList_Cur; /* 当前节点作为下一轮的前一个节点 */
		pstSList_Cur = pstSList_Next; /* 当前节点pstNext作为下一轮的当前节点，继续遍历直至到链表尾 */
	}

	return pstSList_Rev;
}

/* 链表反转-递归 */
S_LIST_S *SLIST_Reverse_Recursive(S_LIST_S *pstSList)
{	
	if (!pstSList)
		return NULL;
	SLIST_Reverse_Recursive(pstSList->pstNext);
	printf("value %d \n", pstSList->uiValue);
}

/* 链表有没有环 */
int SLIST_IsRing(S_LIST_S *pstSList, S_LIST_S **ppstSList_Ring)
{
	S_LIST_S *pstSList_Fast = pstSList;
	S_LIST_S *pstSList_Slow = pstSList;
	*ppstSList_Ring = NULL;

	if ((!pstSList) || (!pstSList->pstNext)) /* 空链表和只有一个元素的链表不会有环 */
		return 0;

	while (pstSList_Slow && pstSList_Fast->pstNext) /* 能走到尾结点说明没环 */
	{
		pstSList_Fast = pstSList_Fast->pstNext->pstNext;
		pstSList_Slow = pstSList_Slow->pstNext;
		if (pstSList_Slow == pstSList_Fast)
		{
			*ppstSList_Ring = pstSList_Slow;
			return 1;
		}
	}
	return 0;
}

/* 链表是否相交 */
int SLIST_IsCross(S_LIST_S *pstSListA, S_LIST_S *pstSListB)
{
	if ((!pstSListA) || (!pstSListB))
		return 0;

	while (pstSListA->pstNext)
		pstSListA = pstSListA->pstNext;

	while(pstSListB->pstNext)
		pstSListB = pstSListB->pstNext;

	if (pstSListA == pstSListB) /* 如果两个单链表相交，则尾节点是一样的 */
		return 1;

	return 0;
}

/* 找到链表倒数第K个节点 */
S_LIST_S *SLIST_Find_K(S_LIST_S *pstSList, unsigned int uiK)
{
	S_LIST_S *pstFast = pstSList;
	S_LIST_S *pstSlow = pstSList;

	if(!pstSList)
		return NULL;

	while(pstFast->pstNext)
	{
		if(--uiK > 0)
			pstFast = pstFast->pstNext;
		pstFast = pstFast->pstNext;
		pstSlow = pstSlow->pstNext;
	}

	return pstSlow;
}

/* 链表删除重复元素 */
S_LIST_S * SLIST_Delete_Repect(S_LIST_S *pstSList)
{
	unsigned char aucList[1000] = {0};
	unsigned int uiValue;
	S_LIST_S *pstPrev;
	S_LIST_S *pstIter;
	
	if (!pstSList)
		return NULL;
	pstIter = pstSList;
	while (pstIter->pstNext)
	{
		uiValue = pstIter->uiValue;
		if (aucList[uiValue] > 0)
		{
			#ifdef DEBUG
			printf("value rep %d pre value %d\n",uiValue,pstPrev->uiValue);
			#endif
			free(pstPrev->pstNext);
			pstPrev->pstNext = pstPrev->pstNext->pstNext;
		}
		
		pstPrev = pstIter;
		pstIter = pstIter->pstNext;
		aucList[uiValue]++;
	}

	return pstSList;
}


//#define LIST_CROSS_TEST
#define LIST_REVERSE_TEST
void main(void)
{
	unsigned int auiList[] = {1,3,7,5,7,9};
	unsigned int uiLen = sizeof(auiList)/sizeof(unsigned int);
	S_LIST_S *pstSList = NULL;
	int i;

	for (i = 0; i < uiLen; i++)
		pstSList = SLIST_Insert(pstSList, auiList[i]);
	
#ifdef LIST_REVERSE_TEST
	SLIST_Dump(pstSList);
	pstSList = SLIST_Reverse_NoRecursive(pstSList);
	SLIST_Dump(pstSList);
#endif

#ifdef LIST_K_TEST
	S_LIST_S * pstNodeK = SLIST_Find_K(pstSList, 3);
	printf("K %d\n", pstNodeK->uiValue);
#endif

#ifdef LIST_REPECT_TEST
	SLIST_Dump(pstSList);
	pstSList = SLIST_Delete_Repect(pstSList);
	SLIST_Dump(pstSList);
#endif

#ifdef LIST_RING_TEST
	S_LIST_S *pstSList_Ring;
	int iIsRing = SLIST_IsRing(pstSList,&pstSList_Ring);
	printf("isRing %d %p\n",iIsRing,pstSList_Ring);

	S_LIST_S * pstNode = SLIST_Find(pstSList,  3);
	S_LIST_S * pstIter = pstSList;
	while ( pstIter->pstNext)
		pstIter = pstIter->pstNext;
	pstIter->pstNext = pstNode;

	iIsRing = SLIST_IsRing(pstSList,&pstSList_Ring);
	if (iIsRing)
	{
		printf("isRing %d %d %d\n",iIsRing,pstSList_Ring->pstNext->uiValue,pstNode->uiValue);
	}
#endif

#ifdef LIST_CROSS_TEST
	unsigned int auiListB[] = {2,4,6,8};
	unsigned int auiListC[] = {1,2,3};
	unsigned int uiLenB = sizeof(auiListB)/sizeof(unsigned int);
	unsigned int uiLenC = sizeof(auiListC)/sizeof(unsigned int);
	S_LIST_S *pstSListB = NULL;
	S_LIST_S *pstSListC = NULL;
	int iIsCross;
	
	for (i = 0; i < uiLenB; i++)
		pstSListB = SLIST_Insert(pstSListB, auiListB[i]);

	for (i = 0; i < uiLenC; i++)
		pstSListC = SLIST_Insert(pstSListC, auiListC[i]);

	iIsCross = SLIST_IsCross(pstSListB, pstSListC);
	printf("isCross %d\n",iIsCross);
	
	S_LIST_S * pstIter = pstSListB;
	while ( pstIter->pstNext)
		pstIter = pstIter->pstNext;
	pstIter->pstNext = pstSList;

	pstIter = pstSListC;
	while ( pstIter->pstNext)
		pstIter = pstIter->pstNext;
	pstIter->pstNext = pstSList;

	iIsCross = SLIST_IsCross(pstSListB, pstSListC);
	printf("isCross %d\n",iIsCross);
#endif
	
	return;
}




