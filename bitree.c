#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* �������������������󹫹��ڵ� */
#define NULL ((void *)0)

/* ������ */
typedef struct BiTreeNode{
	unsigned int uiValue;
	struct BiTreeNode *pstLeft;
	struct BiTreeNode *pstRight;
}BITREE_NODE_S;


#define RECURSIVE

/* �ݹ鹹�������� */
BITREE_NODE_S *BITREE_Create_recursive(BITREE_NODE_S *pstTreeRoot, BITREE_NODE_S *pstTreeNode)
{
	if (!pstTreeRoot) /*��ֹ���� */
		pstTreeRoot = pstTreeNode;
	else if (pstTreeNode->uiValue < pstTreeRoot->uiValue ) /* ������ */
		pstTreeRoot->pstLeft = BITREE_Create_recursive(pstTreeRoot->pstLeft, pstTreeNode);
	else /* ������ */
		pstTreeRoot->pstRight = BITREE_Create_recursive(pstTreeRoot->pstRight,pstTreeNode);

	return pstTreeRoot;
}

/* �������������� */
BITREE_NODE_S *BITREE_Create_iteration(BITREE_NODE_S *pstTreeRoot, BITREE_NODE_S *pstTreeNode)
{


	return pstTreeRoot;
}


/* ������� */
void BITREE_Pre_Foreach(BITREE_NODE_S *pstTreeRoot)
{
	if (! pstTreeRoot)
		return;
	printf(" value %u \r\n", pstTreeRoot->uiValue);
	BITREE_Pre_Foreach(pstTreeRoot->pstLeft);
	BITREE_Pre_Foreach(pstTreeRoot->pstRight);
}

/* ������� */
void BITREE_Mid_Foreach(BITREE_NODE_S *pstTreeRoot)
{
	if (!pstTreeRoot)
		return;
	BITREE_Mid_Foreach(pstTreeRoot->pstLeft);
	printf(" value %u \r\n", pstTreeRoot->uiValue);
	BITREE_Mid_Foreach(pstTreeRoot->pstRight);
}

/* ������� */
void BITREE_Post_Foreach(BITREE_NODE_S *pstTreeRoot)
{
	if (!pstTreeRoot)
		return;
	BITREE_Post_Foreach(pstTreeRoot->pstLeft);
	BITREE_Post_Foreach(pstTreeRoot->pstRight);
	printf(" value %u \r\n", pstTreeRoot->uiValue);
}

#define __ITERATION__

/* ������ջ */
#define STACK_LEN  1024
typedef struct BiTree_Stack{
	BITREE_NODE_S *pastBiTreeRoot[STACK_LEN];
	unsigned int uiTop;
}BITREE_STACK_S;

BITREE_STACK_S g_stBiTree_Stack;


/* ��ʼ��������ջ */
void BITREE_NODE_Stack_Init(void)
{
	g_stBiTree_Stack.uiTop = 0;
	return;
}

/* ������ջ�Ƿ�Ϊ�� */
int BITREE_NODE_Stack_IsEmpty(void)
{
	return (g_stBiTree_Stack.uiTop == 0);
}

/* ��������ջ */
void BITREE_NODE_Stack_Push(BITREE_NODE_S *pstBiTreeNode)
{
	g_stBiTree_Stack.pastBiTreeRoot[g_stBiTree_Stack.uiTop++] = pstBiTreeNode;
	return;
}

/* ��������ջ */
BITREE_NODE_S *BITREE_NODE_Stack_Pop(void)
{
	return g_stBiTree_Stack.pastBiTreeRoot[--g_stBiTree_Stack.uiTop] ;
}

/* ������� */
void BITREE_Pre_Foreach_NoRecursive(BITREE_NODE_S *pstTreeRoot)
{
	BITREE_NODE_S *pstForeach;
	
	pstForeach = pstTreeRoot;
	
	BITREE_NODE_Stack_Init();
	while ((pstForeach) || (!BITREE_NODE_Stack_IsEmpty()))
	{
		while (pstForeach)
		{
			printf(" value %u \r\n", pstForeach->uiValue);
			BITREE_NODE_Stack_Push(pstForeach);  /* ��ڵ���ջ */
			pstForeach = pstForeach->pstLeft;
		}
		if (!BITREE_NODE_Stack_IsEmpty())
		{
			pstForeach = BITREE_NODE_Stack_Pop(); /* ��ڵ��ջ���ӵ׵������ҽڵ� */
			pstForeach = pstForeach->pstRight;
		}
	}

}

/* ������� */
void BITREE_Mid_Foreach_NoRecursive(BITREE_NODE_S *pstTreeRoot)
{
	BITREE_NODE_S *pstForeach;
	pstForeach = pstTreeRoot;

	BITREE_NODE_Stack_Init();
	while ((pstForeach) || (!BITREE_NODE_Stack_IsEmpty()))
	{
		while (pstForeach)
		{
			BITREE_NODE_Stack_Push(pstForeach); /* ���ڵ����ڵ���ջ */
			pstForeach = pstForeach->pstLeft;
		}
		if (!BITREE_NODE_Stack_IsEmpty())
		{
			pstForeach = BITREE_NODE_Stack_Pop();  /* ��ڵ㣬���ڵ㣬�ҽڵ����γ�ջ */
			printf("value %d\n", pstForeach->uiValue);
			pstForeach = pstForeach->pstRight;  /* �ҽڵ���ջ */
		}
	}
	
}

/* ������� */
void BITREE_Post_Foreach_NoRecursive(BITREE_NODE_S *pstTreeRoot)
{
	BITREE_NODE_S *pstForeach;
	pstForeach = pstTreeRoot;

	BITREE_NODE_Stack_Init();

	while (pstForeach)
	{
		BITREE_NODE_Stack_Push(pstForeach); /* ��ڵ���ջ */
		pstForeach = pstForeach->pstLeft;
	}
	
	while ( !BITREE_NODE_Stack_IsEmpty())
	{
		pstForeach = BITREE_NODE_Stack_Pop(); 
		printf("value %d\n", pstForeach->uiValue);
		
		if(pstForeach->pstRight)
			BITREE_NODE_Stack_Push(pstForeach->pstRight); /* �ҽڵ�����ջ�����ջ */
		if(pstForeach->pstLeft)
			BITREE_NODE_Stack_Push(pstForeach->pstLeft);
	}
}

/* ��α��� */
/* ���������� */
#define QUEUE_LEN  1024
typedef struct BiTree_Node_Queue{
	BITREE_NODE_S *pstQueue[QUEUE_LEN];
	unsigned int uiFront;
	unsigned int uiRear;
}BITREE_NODE_QUEUE;

BITREE_NODE_QUEUE g_stBiTree_Queue;

void BITREE_NODE_QUEUE_INIT(void)
{
	g_stBiTree_Queue.uiFront = 0;
	g_stBiTree_Queue.uiRear = 0 ;
	return;
}

void BITREE_NODE_Queue_Enq(BITREE_NODE_S *pstTreeRoot)
{
	g_stBiTree_Queue.pstQueue[++g_stBiTree_Queue.uiRear] = pstTreeRoot;
	return;
}
BITREE_NODE_S *BITREE_NODE_Queue_Deq(void)
{
	return g_stBiTree_Queue.pstQueue[++g_stBiTree_Queue.uiFront] ;
}

int BITREE_NODE_Queue_IsEmp()
{
	return (g_stBiTree_Queue.uiFront == g_stBiTree_Queue.uiRear);
}


void BITREE_Layer_Foreach(BITREE_NODE_S *pstTreeRoot)
{
	BITREE_NODE_S *pstTmp;
	
	BITREE_NODE_Queue_Enq(pstTreeRoot);
	while(!BITREE_NODE_Queue_IsEmp())
	{
		pstTmp = BITREE_NODE_Queue_Deq();
		printf("value %d\n",pstTmp->uiValue);

		if (pstTmp->pstLeft)
			BITREE_NODE_Queue_Enq(pstTmp->pstLeft);
		if (pstTmp->pstRight)
			BITREE_NODE_Queue_Enq(pstTmp->pstRight);
	}
	return;
}

/* ������� */
unsigned int BITREE_Depth(BITREE_NODE_S *pstTreeRoot)
{
	unsigned int uiLeftDepth, uiRightDepth;
	if (!pstTreeRoot)
		return 0;
	uiLeftDepth = BITREE_Depth(pstTreeRoot->pstLeft);
	uiRightDepth = BITREE_Depth(pstTreeRoot->pstRight);
	return 1+(uiLeftDepth > uiRightDepth ? uiLeftDepth : uiRightDepth);
}

/* ���Ĺ����ڵ� */
BITREE_NODE_S *BITREE_Get_Parent(BITREE_NODE_S *pstTreeRoot,BITREE_NODE_S *pstTreeNode1,BITREE_NODE_S *pstTreeNode2)
{
	if ((!pstTreeRoot) || (!pstTreeNode1) || (!pstTreeNode2))
	{
		return NULL;
	}

	if ((pstTreeRoot->uiValue < pstTreeNode1->uiValue) && (pstTreeRoot->uiValue < pstTreeNode2->uiValue))
	{
	    return BITREE_Get_Parent(pstTreeRoot->pstRight,pstTreeNode1,pstTreeNode2);
	}
	else if ((pstTreeRoot->uiValue > pstTreeNode1->uiValue) && (pstTreeRoot->uiValue > pstTreeNode2->uiValue))
	{
		return BITREE_Get_Parent(pstTreeRoot->pstLeft,pstTreeNode1,pstTreeNode2);
	}
	else
	{
		return pstTreeRoot;
	}

}

BITREE_NODE_S *BITREE_Get_Parent1(BITREE_NODE_S *pstTreeRoot,BITREE_NODE_S *pstTreeNode1,BITREE_NODE_S *pstTreeNode2)
{
	BITREE_NODE_S *pstLeft;
	BITREE_NODE_S *pstRight;

	if ((!pstTreeRoot) || (pstTreeRoot == pstTreeNode1) || (pstTreeRoot == pstTreeNode2))
	{
		return pstTreeRoot;
	}
	pstLeft = BITREE_Get_Parent1(pstTreeRoot->pstLeft,pstTreeNode1,pstTreeNode2);
	pstRight = BITREE_Get_Parent1(pstTreeRoot->pstRight,pstTreeNode1,pstTreeNode2);

	if (pstLeft==NULL && pstRight==NULL)
	{
	    return NULL;
	}
	else if (pstLeft!=NULL && pstRight==NULL)
	{
		return pstLeft;
	}
	else if (pstLeft==NULL && pstRight!=NULL)
	{
		return pstRight;
	}
	else
	{
		return pstTreeRoot;
	}

}


#define __TEST_CODE__

void main()
{
	BITREE_NODE_S *pstTNode;
	BITREE_NODE_S *pstTRoot = NULL;
	int i;
	int iArray[] = {5,7,3,4,2};
	BITREE_NODE_S *apstTNode[5];

	for (i=0;i<5;i++)
	{
		pstTNode = malloc(sizeof(BITREE_NODE_S));
		memset(pstTNode, 0, sizeof(BITREE_NODE_S));
		pstTNode->uiValue = iArray[i];
		apstTNode[i] = pstTNode;
		pstTRoot = BITREE_Create_recursive(pstTRoot, pstTNode);
	}

	//BITREE_Pre_Foreach(pstTRoot); /* ����ݹ� */
	//BITREE_Mid_Foreach(pstTRoot); /* ����ݹ� */
	BITREE_Post_Foreach(pstTRoot); /* ����ݹ� */

	printf("\n");
	
	BITREE_NODE_QUEUE_INIT();
	BITREE_Layer_Foreach(pstTRoot);

	BITREE_Pre_Foreach_NoRecursive(pstTRoot);  /* ����ǵݹ� */
	//BITREE_Mid_Foreach_NoRecursive(pstTRoot);  /* ����ǵݹ� */
	//BITREE_Post_Foreach_NoRecursive(pstTRoot);  /* ����ǵݹ� */
	
	printf("\ndepth %d \n", BITREE_Depth(pstTRoot));
	{
		BITREE_NODE_S *pstNode;
		BITREE_NODE_S *pstNode1;

		pstNode = BITREE_Get_Parent(pstTRoot,apstTNode[3],apstTNode[4]);
		printf("parent %d\n",pstNode->uiValue);
		pstNode1 = BITREE_Get_Parent1(pstTRoot,apstTNode[3],apstTNode[4]);
		printf("parent %d\n",pstNode1->uiValue);
	}

}





