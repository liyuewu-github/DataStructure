#include <stdio.h>
#include <stdlib.h>

/* 
����ı�ʾ������(TRAW, TCOL)     - (BRAW, BCOL)     ���Ͻ�-���½�
����Ԫ�صı�ʾ������(RAW, COL)     */

/* ��ӡ���� */
void MatrixPrint(int * apMatrix [ ], int m, int n)
{
	int iR,iC;

	for (iR = 0; iR < m; ++iR)
	{
		for (iC = 0; iC < n; ++iC)
		{
			printf("%d ",apMatrix[iR][iC]);
		}
		printf("\n ");
	}
}


/* ����תȦ��ӡ */
/* ���룺
   1  2  3  4  
   5  6   7  8
   9  10  11  12
  13  14  15  16
�����  1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10*/
void Matrix_CirclePrint(int* apMatrix[], int iR, int iC)
{
	int iTopR, iTopC;   /*���Ͻ�����*/
	int iBotR, iBotC;   /*���½�����*/
	int i,j,m,n;
	
	iTopR = iTopC = 0;
	iBotR = iR -1;
	iBotC = iC - 1;
	
	while ((iTopR<=iBotR) && (iTopC<=iBotC))
	{
		/* ���ɣ���ӡһ��������У���ӡһ��������� */
		if (iTopR == iBotR)  /* һ�� */
		{
			for (i = iTopC; i <= iBotC; i++)
			{
				printf("%d ",apMatrix[iTopR][i]);
			}
		}
		else if (iTopC == iBotC)   /* һ�� */
		{
			for (i = iTopR; i <= iBotR; i++)
			{
				printf("%d ",apMatrix[i][iTopC]);
			}
		}
		else /* ���ж��� */
		{
			for (i = iTopC; i < iBotC; i++) /* �����ӡ�У������һ��Ԫ�أ���Ϊ������ʼ */
			{
				printf("%d ",apMatrix[iTopR][i]);
			}
			for (j = iTopR; j < iBotR; j++) /* �����ӡ�У������һ��Ԫ�أ���Ϊ������ʼ */
			{
				printf("%d ",apMatrix[j][iBotC]);
			}
			for (m = i; m > iTopC; m--) /* �����ӡ�У������һ��Ԫ�أ���Ϊ������ʼ */
			{
				printf("%d ",apMatrix[iBotR][m]);
			}
			for (n = j; n > iTopR; n--) /* �����ӡ�У�һȦ���� */
			{
				printf("%d ",apMatrix[n][iTopC]);
			}
		}
		
		/* ��һȦ */
		iTopR++;
		iTopC++;
		iBotR--;
		iBotC--;		
	}
	printf("\n ");

}

/* �����ξ���˳ʱ����ת90�� */
/* 
���룺
   1  2  3  4  
   5  6   7  8
   9  10  11  12
  13  14  15  16
�����
   13  9   5  1
   14  10  6  2
   15  11  7  3
   16  12  8  4*/
 /* ���⵽��������ת��һ���滻1->4;4->16;16->13;13->1; ����Ϊ�л���Ԫ�ظ��� */
int ** Matrix_Rorate(int * apMatrix [ ], int iR, int iC)
{
	int iTopR, iTopC;   /*���Ͻ�����*/
	int iBotR, iBotC;   /*���½�����*/
	int iTime;   /*��ת����*/
	int iTmp;
	int **ppM;
	int i;
	ppM = malloc(iR * sizeof(int));
	for (i = 0; i < iR; ++i)
	{
		ppM[i] = apMatrix[i];
	}

	iTopR = iTopC = 0;
	iBotR = iR -1;
	iBotC = iC - 1;

	while (iTopR<iBotR)
	{
		iTime = iBotR - iTopR; /* ��ת�������л��е�Ԫ�ظ��� */
		for (i = 0; i < iTime; ++i)
		{
			iTmp = apMatrix[iTopR][iTopC+i];
			apMatrix[iTopR][iTopC+i] = apMatrix[iBotR-i][iTopC]; /*13->1*/
			apMatrix[iBotR-i][iTopC] = apMatrix[iBotR][iBotC-i]; /*16->13*/
			apMatrix[iBotR][iBotC-i] = apMatrix[iTopR+i][iBotC]; /*4->16*/
			apMatrix[iTopR+i][iBotC] = iTmp; /*1->4*/
		}

		/* ��һȦ */
		iTopR++;
		iTopC++;
		iBotR--;
		iBotC--;		
	}

	return ppM;
}

/* ��֮�����δ�ӡ���� */
/* 
���룺
   1  2  3  4  
   5  6   7  8
   9  10  11  12
  13  14  15  16
�����1 2 5 9 6 3 4 7 10 13 14 11 8 12 15 16*/
void Matrix_SnakePrint(int* apMatrix[], int iR, int iC)
{
	int iTopR, iTopC;   /*���Ͻ�����*/
	int iBotR, iBotC;   /*���½�����*/
	int iRev;    /*�۵���ӡ*/
	int i,j;

	iTopR = iTopC = 0;
	iBotR = iBotC = 0;
	iRev = 0;

	/* ���ɣ�
	1������û���ף�б��������(iTopR, iTopC++)��β����(iBotR++, iBotC)
	2���е��ף�б��β����(iBotR, iBotC++)
	3���е��ף�б��������(iTopR++, iTopC)*/
	while (iTopR <= iR)
	{
		if (iRev) /* ���´�ӡ����++����-- */
		{
			for (i = iTopR,j=iTopC; i < iBotR+1; i++,j--)
			{
				printf("%d ",apMatrix[i][j]);
			}
		}
		else /* ���ϴ�ӡ����--����++ */
		{
			for (i = iBotR,j=iBotC; j < iTopC+1; i--,j++)
			{
				printf("%d ",apMatrix[i][j]);
			}
		}

		if (iTopC == iC-1) /* ��ӡ�������һ�У��к����� */
		{
			iTopR++;
		}
		else /* ���������һ�У��к����� */
		{
			iTopC++;
		}

		if (iBotR==iR-1) /* ��ӡ�������һ�У��к����� */
		{
			iBotC++;
		}
		else /* ���������һ�У��к����� */
		{
			iBotR++;
		}
		
		iRev = !iRev;
	}
	printf("\n ");
	return;
}


int main()
{
	int aM[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
	int *pM[4] = {aM[0],aM[1],aM[2],aM[3]};
	int **ppM;

	printf("--Circle Print--\n");
	Matrix_CirclePrint(pM, 4, 4);

	printf("--Snake Print--\n");
	Matrix_SnakePrint(pM, 4, 4);

	printf("--Rorate Print--\n");
	printf("input:\n ");
	MatrixPrint(pM, 4, 4);

	ppM = Matrix_Rorate(pM, 4, 4);

	printf("output:\n ");
	MatrixPrint(pM, 4, 4);



	return 0;
}




