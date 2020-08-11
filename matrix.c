#include <stdio.h>
#include <stdlib.h>

/* 
矩阵的表示方法：(TRAW, TCOL)     - (BRAW, BCOL)     左上角-右下角
矩阵元素的表示方法：(RAW, COL)     */

/* 打印矩阵 */
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


/* 矩阵转圈打印 */
/* 输入：
   1  2  3  4  
   5  6   7  8
   9  10  11  12
  13  14  15  16
输出：  1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10*/
void Matrix_CirclePrint(int* apMatrix[], int iR, int iC)
{
	int iTopR, iTopC;   /*左上角坐标*/
	int iBotR, iBotC;   /*右下角坐标*/
	int i,j,m,n;
	
	iTopR = iTopC = 0;
	iBotR = iR -1;
	iBotC = iC - 1;
	
	while ((iTopR<=iBotR) && (iTopC<=iBotC))
	{
		/* 规律：打印一行则遍历列，打印一列则遍历行 */
		if (iTopR == iBotR)  /* 一行 */
		{
			for (i = iTopC; i <= iBotC; i++)
			{
				printf("%d ",apMatrix[iTopR][i]);
			}
		}
		else if (iTopC == iBotC)   /* 一列 */
		{
			for (i = iTopR; i <= iBotR; i++)
			{
				printf("%d ",apMatrix[i][iTopC]);
			}
		}
		else /* 多行多列 */
		{
			for (i = iTopC; i < iBotC; i++) /* 正向打印行，留最后一个元素，作为下列起始 */
			{
				printf("%d ",apMatrix[iTopR][i]);
			}
			for (j = iTopR; j < iBotR; j++) /* 正向打印列，留最后一个元素，作为下行起始 */
			{
				printf("%d ",apMatrix[j][iBotC]);
			}
			for (m = i; m > iTopC; m--) /* 逆向打印行，留最后一个元素，作为下列起始 */
			{
				printf("%d ",apMatrix[iBotR][m]);
			}
			for (n = j; n > iTopR; n--) /* 逆向打印列，一圈结束 */
			{
				printf("%d ",apMatrix[n][iTopC]);
			}
		}
		
		/* 下一圈 */
		iTopR++;
		iTopC++;
		iBotR--;
		iBotC--;		
	}
	printf("\n ");

}

/* 正方形矩阵顺时针旋转90度 */
/* 
输入：
   1  2  3  4  
   5  6   7  8
   9  10  11  12
  13  14  15  16
输出：
   13  9   5  1
   14  10  6  2
   15  11  7  3
   16  12  8  4*/
 /* 由外到内依次旋转，一轮替换1->4;4->16;16->13;13->1; 轮数为行或列元素个数 */
int ** Matrix_Rorate(int * apMatrix [ ], int iR, int iC)
{
	int iTopR, iTopC;   /*左上角坐标*/
	int iBotR, iBotC;   /*右下角坐标*/
	int iTime;   /*旋转次数*/
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
		iTime = iBotR - iTopR; /* 旋转次数即行或列的元素个数 */
		for (i = 0; i < iTime; ++i)
		{
			iTmp = apMatrix[iTopR][iTopC+i];
			apMatrix[iTopR][iTopC+i] = apMatrix[iBotR-i][iTopC]; /*13->1*/
			apMatrix[iBotR-i][iTopC] = apMatrix[iBotR][iBotC-i]; /*16->13*/
			apMatrix[iBotR][iBotC-i] = apMatrix[iTopR+i][iBotC]; /*4->16*/
			apMatrix[iTopR+i][iBotC] = iTmp; /*1->4*/
		}

		/* 下一圈 */
		iTopR++;
		iTopC++;
		iBotR--;
		iBotC--;		
	}

	return ppM;
}

/* “之”字形打印矩阵 */
/* 
输入：
   1  2  3  4  
   5  6   7  8
   9  10  11  12
  13  14  15  16
输出：1 2 5 9 6 3 4 7 10 13 14 11 8 12 15 16*/
void Matrix_SnakePrint(int* apMatrix[], int iR, int iC)
{
	int iTopR, iTopC;   /*左上角坐标*/
	int iBotR, iBotC;   /*右下角坐标*/
	int iRev;    /*折叠打印*/
	int i,j;

	iTopR = iTopC = 0;
	iBotR = iBotC = 0;
	iRev = 0;

	/* 规律：
	1、行列没到底，斜线首坐标(iTopR, iTopC++)，尾坐标(iBotR++, iBotC)
	2、行到底，斜线尾坐标(iBotR, iBotC++)
	3、列到底，斜线首坐标(iTopR++, iTopC)*/
	while (iTopR <= iR)
	{
		if (iRev) /* 向下打印，行++，列-- */
		{
			for (i = iTopR,j=iTopC; i < iBotR+1; i++,j--)
			{
				printf("%d ",apMatrix[i][j]);
			}
		}
		else /* 向上打印，行--，列++ */
		{
			for (i = iBotR,j=iBotC; j < iTopC+1; i--,j++)
			{
				printf("%d ",apMatrix[i][j]);
			}
		}

		if (iTopC == iC-1) /* 打印到了最后一列，行号下移 */
		{
			iTopR++;
		}
		else /* 不到了最后一列，列号下移 */
		{
			iTopC++;
		}

		if (iBotR==iR-1) /* 打印到了最后一行，列号下移 */
		{
			iBotC++;
		}
		else /* 不到了最后一行，行号下移 */
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




