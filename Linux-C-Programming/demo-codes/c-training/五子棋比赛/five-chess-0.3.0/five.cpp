// five.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* define chessboard size */
#define ROW  10
#define COL  10

/* define how many chess win */
#define N  5

/* define chessboard using matrix */
int chessboard[ROW][COL] = { {0} };

int thinkboard1[ROW][COL] = { {0} };

int thinkboard2[ROW][COL] = { {0} };		// player 2 value table
int thinkboard3[ROW][COL] = { {0} };		// player 1 value table

/* define two ID */
#define PLAYER1		1
#define PLAYER2		2
#define EMPTY		0

/* clear board */
void clear(int board[ROW][COL])
{
	int i, j;
	for (i = 0; i < ROW; i++) 
		for (j = 0; j < COL; j++) 
			board[i][j] = 0;
}

/* display chessboard using printf */
void print(int board[ROW][COL])
{
	int i, j;

	printf("\n");
	printf("  ");
	for (j = 0; j < COL; j++)
		printf(" %d", j);
	printf("\n");

	printf(" -");
	for (j = 0; j < COL; j++)
		printf(" -");
	printf("\n");

	for (i = 0; i < ROW; i++) {
		printf("%d| ", i);
		for (j = 0; j < COL; j++) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* get the max valuable position */
int get_max_value(int thinkboard[ROW][COL], int * x, int * y)
{
	int i, j;
	int max = 0;
	int cur;

	for (i = 0; i < ROW; i++) 
	{
		for (j = 0; j < COL; j++) 
		{
			cur = thinkboard[i][j];

			if (cur > max)
			{
				max = cur;
				*x = i;
				*y = j;
			}
		}
	}

	return max;
}

/* get user input */
int get(int *x, int *y)
{
	scanf("%d %d", x, y);
	return 0;
}

int think1(void)
{
	int i, j;

	for (i = 0; i < ROW; i++) 
		for (j = 0; j < COL; j++) 
		{
			if (chessboard[i][j] == PLAYER1)
			{
				thinkboard1[i+1][j] += 1;
				thinkboard1[i-1][j] += 1;
				thinkboard1[i][j+1] += 1;
				thinkboard1[i][j-1] += 1;
				thinkboard1[i+1][j+1] += 1;
				thinkboard1[i+1][j-1] += 1;
				thinkboard1[i-1][j+1] += 1;
				thinkboard1[i-1][j-1] += 1;
			}
		}

	for (i = 0; i < ROW; i++) 
	{
		for (j = 0; j < COL; j++) 
			/* if this pos is not empty */
			if (chessboard[i][j] != EMPTY)
				thinkboard1[i][j] = 0;
	}

	return 0;
}

/* test (x, y) is valid before put chess */
int onboard(int x, int y)
{
	if (x >= ROW || x < 0)
		return 0;
	if (y >= COL || y < 0)
		return 0;

	return 1;
}

/* calc whose(player) value */
int value(int x, int y, int player)
{
	int i = 0, j = 0, k = 0;
	int counter = 0;
	int who;
	int nx, ny;		// next x y

	int value = 0;		// return value

	int other;

	/* define who is player, and who is other */
	if (player == PLAYER1)
		other = PLAYER2;
	else
		other = PLAYER1;

	// get the current person
	who = chessboard[x][y];
	if (who != EMPTY)	// this pos is full!
		return 0;	

	// right, down, right_down, left_down, and with other opposite 4 directions
	int dirx[8] = { 0, 1, 1,  1,  0, -1, -1, -1 };
	int diry[8] = { 1, 0, 1, -1, -1,  0, -1,  1 };

	// 4 directions
	for (i = 0; i < 4; i++) 
	{
		// for example: N = 5;  j = 1(1+3), 2(2+2), 3(3+1) 
		for (j = 1; j <= N-1-1; j++) 
		{
			nx = x;
			ny = y;
			counter = 0;

			for (k = 1; k <= j; k++)	
			{
				// count how many our chess in this 4 directions
				nx += dirx[i];
				ny += diry[i];

				// if (nx, ny) is out of board, then break;
				// if (nx, ny) is PLAYER1's chess, then break;
				if (!onboard(nx, ny) || chessboard[nx][ny] == player)
				{
					counter = 0;
					break;
				}
				
				// if (nx, ny) is EMPTY, then add 0;
				if (chessboard[nx][ny] == EMPTY)
					continue;

				// if (nx, ny) is PLAYER2, then add 1;
				if (chessboard[nx][ny] == other)
					counter += 1;		
			}

			nx = x;
			ny = y;

			for (k = 1; k <= N-j-1; k++)
			{
				// count how many our chess in this 4 directions
				nx += dirx[i+4];
				ny += diry[i+4];

				// if (nx, ny) is out of board, then break;
				// if (nx, ny) is PLAYER1's chess, then break;
				if (!onboard(nx, ny) || chessboard[nx][ny] == player)
				{
					counter = 0;
					break;
				}
				
				// if (nx, ny) is EMPTY, then add 0;
				if (chessboard[nx][ny] == EMPTY)
					continue;

				// if (nx, ny) is PLAYER2, then add 1;
				if (chessboard[nx][ny] == other)
					counter += 1;
			}

			// this is very near victory!
			if (counter == N - 1)
				value += 100;
			else
				value += counter;
		}
	}

	// 8 directions
	for (i = 0; i < 8; i++) 
	{
		nx = x;
		ny = y;
		counter = 0;
		for (j = 1; j < N; j++) 
		{
			// count how many our chess in this 4 directions
			nx += dirx[i];
			ny += diry[i];

			// if (nx, ny) is out of board, then break;
			// if (nx, ny) is PLAYER1's chess, then break;
			if (!onboard(nx, ny) || chessboard[nx][ny] == player)
			{
				counter = 0;
				break;
			}
			
			// if (nx, ny) is EMPTY, then add 0;
			if (chessboard[nx][ny] == EMPTY)
				continue;

			// if (nx, ny) is PLAYER2, then add 1;
			if (chessboard[nx][ny] == other)
				counter += 1;			
		}

		// this is very near victory!
		if (counter == N - 1)
			value += 100;
		else
			if (counter == N - 2)
				value += 50;
			else
				value += counter;
	}

	return value;
}

int think2(void)
{
	int i, j;
	for (i = 0; i < ROW; i++) 
		for (j = 0; j < COL; j++) 
			thinkboard2[i][j] = value(i, j, PLAYER2);

	return 0;
}

int think3(void)
{
	int i, j;
	for (i = 0; i < ROW; i++) 
		for (j = 0; j < COL; j++) 
			thinkboard3[i][j] = value(i, j, PLAYER1);

	return 0;
}

/* machine think a good place */
int think(int *x, int *y)
{
	int max_value1;
	int max_value2;		// player 2 value table
	int max_value3;		// player 1 value table

	clear(thinkboard1);
	think1();
	/* get the max value position (x,y) */
	max_value1 = get_max_value(thinkboard1, x, y);
	print(thinkboard1);
	printf("Player 2's think1 pos is (%d, %d), max value=%d \n\n", *x, *y, max_value1);

	clear(thinkboard2);
	think2();
	/* get the max value position (x,y) */
	max_value2 = get_max_value(thinkboard2, x, y);
	print(thinkboard2);
	printf("Player 2's think2 pos is (%d, %d), max value=%d \n\n", *x, *y, max_value2);

	clear(thinkboard3);
	think3();
	/* get the max value position (x,y) */
	max_value3 = get_max_value(thinkboard3, x, y);
	print(thinkboard3);
	printf("Player 2's think3 pos is (%d, %d), max value=%d \n\n", *x, *y, max_value3);

//	getchar();
	print(chessboard);
	printf("player %d: ", 2);
	scanf("%d %d", x, y);
	return 0;
}

/* put chess in chessboard(x, y) */
int put(int x, int y, int who)
{
	chessboard[x][y] = who;
	return 1;
}

/* check if (x, y) is empty */
int empty(int x, int y)
{
	if (chessboard[x][y] == 0)
		return 1;
	return 0;
}

/* test (x, y) is valid before put chess */
int test(int x, int y)
{
	if (x >= ROW || x < 0)
		return 0;
	if (y >= COL || y < 0)
		return 0;
	if (empty(x, y))
		return 1;
	return 0;
}


int check(int x, int y)
{
	int i = 0, j = 0;
	int counter = 1;
	int who;
	int nx, ny;		// next x y

	// right, down, right_down, left_down
	int dirx[4] = { 0, 1, 1, 1 };
	int diry[4] = { 1, 0, 1, -1 };

	// get the current person
	who = chessboard[x][y];
	if (who == 0)
		return 0;

	// 4 directions
	for (i = 0; i < 4; i++) 
	{
		nx = x;
		ny = y;
		counter = 1;
		for (j = 1; j < N; j++) 
		{
			nx += dirx[i];
			ny += diry[i];
			if (chessboard[nx][ny] == who)
				counter++;
		}
		if (counter == N) 
		{
			printf("check ok!  %d %d -> dir(%d) \n", x, y, i);
			return 1;
		}
	}
	return 0;
}

/* check if someone wins */
int find(void)
{
	int i, j;
	for (i = 0; i < ROW; i++) 
	{
		for (j = 0; j < COL; j++) 
		{
			if (check(i, j))
				return 1;
		}
	}
	return 0;
}


int main(int argc, char *argv[])
{
	int x, y;
	int step = 0;
	int who;
	printf("Hello, FIVE CHESS PLAYER!\nReady to go? GO!\n");

	print(chessboard);
	printf("you can input 4 4 to put a chess on board\n");

	while (1) 
	{
		who = step % 2 + 1;
		printf("player %d: ", who);
		if (who == 1)
			get(&x, &y);
		else
		{
			think(&x, &y);
		}

		if (test(x, y)) 
		{
			put(x, y, who);
			print(chessboard);
			step++;
			if (find()) 
			{
				printf("Congratulations, player %d win! \n", who);
				return 0;
			}
		}
		else
			printf("%d %d is not permitted! please reinput.\n\n", x, y);
	}
	return 0;
}
