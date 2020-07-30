#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define IN
#define OUT
#define INOUT

#define HASH_OK   0
#define HASH_NOMEM 1

#define NULL ((void *)0)

//#define HASH_TRACE
#define HASH_BUFLEN 20480

/* HASH冲突域链表节点 */
typedef struct tagHASH_LIST
{
	unsigned int uiValue;
	struct tagHASH_LIST *pHashList;
}HASH_LIST_S;

/* HASH表 */
typedef struct tagHASH_TABLE
{
	unsigned int uiTableSize;  /* HASH表大小  */
	unsigned int (*pFunHash)(const void *);     /* HASH算法  */
	unsigned int (*pFunCmp)(unsigned int uiKey, unsigned int uiOldKey);    /* HASH冲突域值比较  */
	HASH_LIST_S **ppHashList;     /* HASH数组链表    */
}HASH_TABLE_S;

/* HASH表创建 */
HASH_TABLE_S * HASH_Create(
	IN unsigned int uiTableSize, 
	IN unsigned int (*pFunHash)(const void *), 
	IN unsigned int (*pFunCmp)(unsigned int uiKey, unsigned int uiOldKey))
{
	HASH_TABLE_S *pstHashTable;
	unsigned int i;

	pstHashTable = malloc(sizeof(HASH_TABLE_S));
	if (NULL == pstHashTable)
	{
		return NULL;
	}

	pstHashTable->ppHashList = malloc(sizeof(HASH_LIST_S) * uiTableSize);
	if (NULL == pstHashTable->ppHashList)
	{
		free(pstHashTable);
		return NULL;
	}
	memset(pstHashTable->ppHashList, 0, sizeof(HASH_LIST_S) * uiTableSize);
	pstHashTable->uiTableSize = uiTableSize;
	pstHashTable->pFunHash = pFunHash;
	pstHashTable->pFunCmp = pFunCmp;

	return pstHashTable;
}

/* HASH表查找 */
HASH_LIST_S *HASH_Find( IN HASH_TABLE_S *pstHashTable, IN unsigned int uiKey)
{
	HASH_LIST_S *pstHashFind;
	unsigned int uiHashIndex;

	uiHashIndex = pstHashTable->pFunHash((void *)&uiKey);
	pstHashFind = pstHashTable->ppHashList[uiHashIndex];

	while(pstHashFind)
	{
		if(pstHashFind->uiValue == uiKey)
		{
			break;
		}
		pstHashFind = pstHashFind->pHashList;
	}

	return pstHashFind;
}

/* HASH表插入 */
unsigned int HASH_Insert( IN HASH_TABLE_S *pstHashTable, IN unsigned int uiKey)
{
	HASH_LIST_S *pstHashFind;
	HASH_LIST_S *pstNewHashNode;
	HASH_LIST_S *pstHashCmp;
	unsigned int uiHashIndex;

	pstHashFind = HASH_Find(pstHashTable, uiKey);
	if (NULL == pstHashFind)
	{
		pstNewHashNode = malloc(sizeof(HASH_LIST_S));
		if (NULL == pstNewHashNode)
		{
			return HASH_NOMEM;
		}
		uiHashIndex = pstHashTable->pFunHash((void *)&uiKey);
		pstNewHashNode->uiValue = uiKey;

		pstHashCmp = pstHashTable->ppHashList[uiHashIndex];

		while(pstHashCmp)
		{
			if (pstHashTable->pFunCmp(uiKey, pstHashCmp->uiValue ))
			{
				break;
			}
			pstHashCmp = pstHashCmp->pHashList;
		}
		
		if (NULL == pstHashCmp) /* 当前节点为冲突域中的最大值或者最小值 */
		{
			pstNewHashNode->pHashList = pstHashTable->ppHashList[uiHashIndex];
			pstHashTable->ppHashList[uiHashIndex] = pstNewHashNode;
		}
		else  /* 当前节点为冲突域中的中间值，插入pstHashCmp之后 */
		{
			pstNewHashNode->pHashList = pstHashCmp->pHashList;
			pstHashCmp->pHashList = pstNewHashNode;
		}
		#ifdef HASH_TRACE
		printf("Key %d index %d head %p node %p nextnode %p\n",uiKey, uiHashIndex,
			pstHashTable->ppHashList[uiHashIndex],pstNewHashNode, pstNewHashNode->pHashList);
		#endif
	}
	#ifdef HASH_TRACE
	else
	{
		printf("The Key %d is repect\n",uiKey);
	}
	#endif
	return HASH_OK;
}

/* HASH表删除 */
void HASH_Destroy(IN HASH_TABLE_S * pstHashTable)
{
	HASH_LIST_S *pstHashScan;
	unsigned int uiHashIndex;

	for (uiHashIndex = 0; uiHashIndex < pstHashTable->uiTableSize; uiHashIndex++)
	{
		pstHashScan = pstHashTable->ppHashList[uiHashIndex];

		while(pstHashScan)
		{
			free(pstHashScan);
			pstHashScan = pstHashScan->pHashList;
		}
	}
	free(pstHashTable->ppHashList);
	free(pstHashTable);
	return;
}


/* HASH表打印 */
unsigned int HASH_Dump( IN HASH_TABLE_S *pstHashTable )
{
	HASH_LIST_S *pstHashScan;
	unsigned int uiHashIndex;
	char * pcBuf;
	unsigned int uiLen = 0;

	pcBuf = (char * )malloc(HASH_BUFLEN);
	if (NULL == pcBuf)
	{
		return HASH_NOMEM;
	}

	for (uiHashIndex = 0; uiHashIndex < pstHashTable->uiTableSize; uiHashIndex++)
	{
		uiLen += snprintf((pcBuf+uiLen), (HASH_BUFLEN-uiLen), "----------------HASH INDEX %u----------------\n", uiHashIndex);
		pstHashScan = pstHashTable->ppHashList[uiHashIndex];

		while(pstHashScan)
		{
			uiLen += snprintf((pcBuf+uiLen), (HASH_BUFLEN-uiLen), "node %p value %u\n", pstHashScan, pstHashScan->uiValue);
			pstHashScan = pstHashScan->pHashList;
		}
	}

	printf("%s", pcBuf);
	free(pcBuf);
}


#define __TEST_PROCESS__

#define HASHTEST_MOD   5
#define HASHTEST_SIZE  20

unsigned int HASH(const void * pKey)
{
	return (*(unsigned int *)pKey/HASHTEST_MOD);
}

unsigned int Cmp(unsigned int uiKey, unsigned int uiOldKey)
{
	return (uiKey < uiOldKey ? 1 : 0);
}

void main()
{
	HASH_TABLE_S * pstHashTest;
	int i;
	pstHashTest = HASH_Create(HASHTEST_SIZE, HASH,Cmp);
	if (NULL == pstHashTest)
	{
		return;
	}
	for (i=0;i<100;i++)
		HASH_Insert(pstHashTest, i);

	HASH_Insert(pstHashTest, 17);
	HASH_Insert(pstHashTest, 15);
	HASH_Insert(pstHashTest, 16);

	HASH_Dump(pstHashTest);
	HASH_Destroy(pstHashTest);
	return;
}


#ifdef __cplusplus
}
#endif
