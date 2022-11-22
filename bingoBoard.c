#include <stdio.h>
#include "bingoBoard.h"

#define BINGONUM_HOLE -1


static int bingoBoard[N_SIZE][N_SIZE];
static int numberStatus[N_SIZE*N_SIZE];


void bingo_init(void)
{
	int i, j;
	int cnt = 1;
	
	for (i=0;i<N_SIZE;i++)
		for (j=0;j<N_SIZE;j++)
		{
			if (cnt == 15)
			{
				bingoBoard[i][j] = BINGONUM_HOLE;
				numberStatus[cnt-1] = BINGONUM_HOLE;
				
				cnt++;
			}
			else
			{
				numberStatus[cnt-1] = i*N_SIZE + j;
				bingoBoard[i][j] = cnt++;
			}
		}
}

/*
void bingo_init(void)
{
	int i, j, k;
	int randNum;
	int maxNum = N_SIZE*N_SIZE;
	
	for (i=0;i<N_SIZE;i++) {
		for (j=0;j=N_SIZE;j++) {
			randNum = 0 - maxNum - 1 중 임의의 값 생성 
			
			for (k=0;k<N_SIZE;k++) {
				if (numberStatus[k]가 아직 할당이 안됨)
				{
					if (randNum == 0) {
					break;
					}
					else
					{
						randNum--;
					}
				}
			}
			bingoBoard의 i번째 행, j번째 옆에 k+1 값 할당;
			numberStatus[k] = N_SIZE*i+j;
			maxNum 값 하나 줄임;
		}
	}
}
*/

void bingo_printBoard(void)
{
	int i, j;
	printf("===================================\n");
	for (i=0;i<N_SIZE;i++) {
		for (j=0;j<N_SIZE;j++)
		{
			if (bingoBoard[i][j] == BINGONUM_HOLE)
				printf("X\t");
			else
				printf("%i\t", bingoBoard[i][j]);
		}
		printf("\n");
	}
	printf("===================================\n\n");
}


void bingo_inputNum(int sel)
{
	int i, j;
	i = numberStatus[sel-1]/N_SIZE;
	j = numberStatus[sel-1]%N_SIZE;
	bingoBoard[i][j] = BINGONUM_HOLE;
}


int bingo_checkNum(int selNum)
{
	if ( numberStatus[selNum-1] == BINGONUM_HOLE )
		return BINGO_NUMSTATUS_ABSENT;
		
	return BINGO_NUMSTATUS_PRESENT;
}


int bingo_countCompletedLine(void)
{
	int i, j;
	int cnt = 0;
	int checkBingo;
	
	//check row
	for (i=0;i<N_SIZE;i++) {
		checkBingo = 1;
		for (j=0;j<N_SIZE;j++) {
			if (bingoBoard[i][j] > 0) {
				checkBingo = 0;
				break;
			}
		}
		if (checkBingo == 1) {
				cnt++;
		}
	}

	//check col
	for (j=0;j<N_SIZE;j++) {
		checkBingo = 1;
		for (i=0;i<N_SIZE;i++) {
			if (bingoBoard[i][j] > 0) {
				checkBingo = 0;
				break;
			}
		}
		if (checkBingo == 1) {
			cnt++;
		}
	}
	
	//check diagonal
	checkBingo = 1;
	for (i=0;i<N_SIZE;i++) {
		if (bingoBoard[i][i] > 0) {
			checkBingo = 0;
			break;
		}
	}
	if (checkBingo == 1) {
		cnt ++;
	}
	
	checkBingo = 1;
	for (i=0;i<N_SIZE;i++)
	{
		if (bingoBoard[i][N_SIZE-i-1] > 0)
		{
			checkBingo = 0;
			break;
		}
	}
	if (checkBingo == 1) {
		cnt ++;
	}
	
	return cnt;
}
