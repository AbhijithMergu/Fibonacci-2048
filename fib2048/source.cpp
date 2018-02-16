#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

struct player
{
	char* name;
	char* date;
	int n;
	int moves;
};

int fibN(int n)
/*Calculates the nth fibonacci number.*/
{
	if (n == 1 || n == 2) return n - 1;
	else return fibN(n - 2) + fibN(n - 1);
}

int* returnFibSeries()
{
	int* fib = (int*)malloc(35 * sizeof(int));
	for (int i = 0; i < 35; i++)
	{
		fib[i] = fibN(i + 1);
	}
	return fib;

}

char* presentDate()
{
	time_t t;
	struct tm *tmp;
	char MY_TIME[15];

	time(&t);

	tmp = localtime(&t);

	strftime(MY_TIME, sizeof(MY_TIME), "%d-%b-%Y", tmp);

	int len = strlen(MY_TIME);
	char* date = (char*)malloc((len + 1)*sizeof(char));

	for (int i = 0; i<len; i++)
	{
		date[i] = MY_TIME[i];
	}
	date[len] = '\0';
	return date;
}

int number_of_lines(FILE *file_pointer)
{
	int count = 0;
	char c;
	for (c = getc(file_pointer); c != EOF; c = getc(file_pointer)){
		if (c == '\n')
		{
			count = count + 1;
		}
	}
	fseek(file_pointer, 0, SEEK_SET);
	return count;
}

int mergeCheck(int a, int b, int* fib)
/*Checks if the passed two numbers could be merged.*/
{
	int i;
	if (a == 1 && (b == 1 || b == 2)) return 1;
	for (i = 1; i <= 33; i++)
	{
		if (fib[i] == a) break;
	}
	//	if (i == 19) return 0;
	if (i > 1) if (fib[i - 1] == b) return 1;
	if (fib[i + 1] == b) return 1;
	return 0;
}

void arrayDisplay(int** arr, int n)
/*Prints the array to the console*/
{
	printf("\n\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i][j] == 0)
				printf("     ***  ");

			else
				printf("%8d  ", arr[i][j]);
		}
		printf("\n\n");
	}
}

bool hasEmptySpaces(int** arr, int n)
{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i][j] == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool rowMovesAvailable(int** arr, int len,int* fib)
{
	bool flag = false;
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - 1; j++)
		{
			if (mergeCheck(arr[i][j], arr[i][j+1], fib)==1)
				return true;
		}
	}
	return false;
}

bool colMovesAvailable(int** arr, int len, int* fib)
{
	bool flag = false;
	for (int j = 0; j < len; j++)
	{
		for (int i = 0; i < len - 1; i++)
		{
			if (mergeCheck(arr[i][j], arr[i + 1][j], fib)==1)
				return true;
		}
	}
	return false;
}

bool movesAvailable(int** arr, int len,int* fib)
{
	if (hasEmptySpaces(arr, len)) return true;
	else
	{
		if (rowMovesAvailable(arr, len, fib) || colMovesAvailable(arr, len, fib))
			return true;
	}
	return false;
}

bool gameWon(int** arr, int n)
{
	int max = fibN(2*n*n );
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n;j++)
			if (arr[i][j] >= max)
			{
				return true;
			}
	}
	return false;
}

void initialFillTwo1s(int** arr, int n)
/*initially fills two 1s at random places*/
{
	int i1, j1, i2, j2;
	i1 = rand() % n;
	j1 = rand() % n;
	do
	{
		i2 = rand() % n;
		j2 = rand() % n;
	} while (i2 == i1 && j2 == j1);

	arr[i1][j1] = 1;
	arr[i2][j2] = 1;
}

void fillArrayRadom1(int** arr, int n)
{
	int i, j;
	do
	{
		i = rand() % n;
		j = rand() % n;
	} while (arr[i][j] != 0);

	arr[i][j] = 1;
}

bool pushRowElementsRight(int** arr, int len)
/*Used to push all the elements to the right*/
{
	bool flag = false;
	for (int k = 0; k<len; k++)
	{
		for (int i = len - 2; i >= 0; i--)
		{
			int j = i;
			while (j<len - 1 && arr[k][j + 1] == 0&&arr[k][j]!=0)
			{
				arr[k][j + 1] = arr[k][j];
				arr[k][j] = 0;
				j++;
				flag = true;
			}
		}
	}
	return flag;
}

bool pushRowElementsLeft(int** arr, int len)
/*Used to push all the elements to the left when left button is pressed*/
{
	bool flag = false;
	for (int k = 0; k<len; k++)
	{

		for (int i = 1; i < len; i++)
		{
			int j = i;
			while (j>0 && arr[k][j - 1] == 0&&arr[k][j]!=0)
			{
				flag = true;
				arr[k][j - 1] = arr[k][j];
				arr[k][j] = 0;
				j--;
			}
		}
	}
	return flag;
}

bool pushElementsUp(int** arr, int len)
/*Used to push all the elements to the top*/
{
	bool flag = false;
	for (int j = 0; j < len; j++)
	{
		for (int i = 1; i < len; i++)
		{
			int k = i;
			while (k>0 && arr[k - 1][j] == 0&&arr[k][j]!=0)
			{
				flag = true;
				arr[k - 1][j] = arr[k][j];
				arr[k][j] = 0;
				k--;
			}
		}
	}
	return flag;
}

bool pushElementsDown(int** arr, int len)
/*Used to push all the elements of the row down*/
{
	bool flag = false;
	for (int j = 0; j < len; j++)
	{
		for (int i = len - 2; i >= 0; i--)
		{
			int k = i;
			while (k < len - 1 && arr[k + 1][j] == 0&&arr[k][j]!=0)
			{
				flag = true;
				arr[k + 1][j] = arr[k][j];
				arr[k][j] = 0;
				k++;
			}
		}
	}
	return flag;
}

void LchangeArray(int* arr, int i, int len, int x)
/*Changes the array and merges the elements to the left, if the merge condition satisfies.*/
{
	arr[i] = arr[i] + arr[i + 1];

	for (int j = i + 1; j < len-1; j++)
	{
		arr[j] = arr[j + 1];
	}
	arr[x] = 0;
	return;

}

void RchangeArray(int* arr, int i, int x)
/*Changes the array and merges the elements to the left, if the merge condition satisfies.*/
{
	arr[i] = arr[i] + arr[i - 1];

	for (int j = i - 1; j > 0; j--)
	{
		arr[j] = arr[j - 1];
	}
	arr[x] = 0;
	return;

}

void UchangeArray(int** arr, int i,int j, int len)
{
	arr[i][j] = arr[i][j] + arr[i + 1][j];
	for (int k = i+1; k < len-1;k++)
	{
		arr[k][j] = arr[k + 1][j];
	}
	arr[len - 1][j] = 0;
}

void BchangeArray(int** arr, int i, int j, int len)
{
	arr[i][j] = arr[i][j] + arr[i - 1][j];

	for (int k = i - 1; k > 0; k--)
	{
		arr[k][j] = arr[k - 1][j];
	}
	arr[0][j] = 0;
}

bool LeftRowMerge(int* row, int len, int* fib)
/*Checks for the merge condition in the elements of the row and calls the changearray to change the elements if the conditions
are satisfied. This is the method which gets called when user presses button for left*/
{
	int x=len-1;
	bool flag = false;
	for (int i = 0; i < len - 1; i++)
	{
		if (mergeCheck(row[i], row[i + 1], fib) == 1)
		{
			LchangeArray(row, i,len, x);
			flag = true;
		
		}

	}
	return flag;
}

bool RightRowmerge(int* row, int len, int* fib)
/*Checks for the merge condition in the row and calls the changearray to change the elements if the conditions
are satisfied. This is the method which gets called when user presses button for right*/
{
	int x = 0;
	bool flag = false;
	for (int i = len - 1; i > 0; i--)
	{
		if (mergeCheck(row[i], row[i - 1], fib) == 1)
		{
			RchangeArray(row, i, x);
			flag = true;
			
		}
	}
	return flag;
}

bool UpColMerge(int** arr, int len, int j, int* fib)
{ 
	bool flag = false;

	for (int i = 0; i < len - 1; i++)
	{
		if (mergeCheck(arr[i][j], arr[i + 1][j], fib) == 1)
		{
			UchangeArray(arr, i, j, len);
			flag = true;
		}
	}
	return true; 
}

bool BottomColMerge(int** arr, int len, int j, int* fib)
{
	bool flag = false;
	for (int i = len - 1; i > 0; i--)
	{
		if (mergeCheck(arr[i][j], arr[i - 1][j], fib) == 1)
		{
			BchangeArray(arr, i, j, len);
			flag = true;
		}
	}
	return flag;
}

bool LMerge(int** arr, int len, int* fib)
{
	bool flag = false;
	if (pushRowElementsLeft(arr, len))flag = true;
	for (int i = 0; i < len; i++)
	{
		if (LeftRowMerge(arr[i], len, fib))
			flag = true;
	}
	return flag;
}

bool RMerge(int** arr, int len, int* fib)
{

	bool flag = false;
	if (pushRowElementsRight(arr, len)) flag = true;
	for (int i = 0; i < len; i++)
	{
		if (RightRowmerge(arr[i], len, fib))
		{
			flag = true;
		}
	}
	return flag;
}

bool UMerge(int** arr, int len, int* fib)
{
	bool flag = false;
	if (pushElementsUp(arr, len))flag = true;
	for (int i = 0; i < len; i++)
	{
		if (UpColMerge(arr, len, i, fib))
			flag = true;
	}
	return flag;
}

bool BMerge(int** arr, int len, int* fib)
{
	bool flag = false;
	if (pushElementsDown(arr, len)) flag = true;
	for (int i = 0; i < len; i++)
	{
		if (BottomColMerge(arr, len, i, fib))
			flag = true;
	}
	return flag;
}

void displayFinal(int moveCount, int type)
{
	system("cls");
	if (type == 1)
	{
		printf("\n\nYou have won with %d moves\n\n", moveCount);
	}
	else if (type == 2)
	{
		printf("\n\nYou have lost with %d moves \n\n", moveCount);
	}
}

void takeUserInput(int** arr, int n,int* fib,int* moveCount)
{

	char ch;
	int flag = 0;
	do{
		
			ch = _getch();
			
			if (ch == 'H' || ch == 'W' || ch == 'w')
			{
				if (UMerge(arr, n, fib) && hasEmptySpaces(arr, n))
				{
					fillArrayRadom1(arr, n);
					*moveCount=*moveCount+1;
				}
				
				flag = 1;
			}
				
			else    if (ch == 'P' || ch == 'S' || ch == 's')
			{
				if (BMerge(arr,n,fib)&&hasEmptySpaces(arr,n))
				{
					fillArrayRadom1(arr, n);
					*moveCount = *moveCount + 1;
				}
				flag = 1;
			}
			
			else    if (ch == 'M' || ch == 'D' || ch == 'd')
			{
				if(RMerge(arr, n,fib)&&hasEmptySpaces(arr,n))
				{
					fillArrayRadom1(arr, n);
					*moveCount = *moveCount + 1;
				}
				flag = 1;
			}
		
			else   if (ch == 'K' || ch == 'A' || ch == 'a')
			{
				if(LMerge(arr, n,fib)&&hasEmptySpaces(arr,n))
				{
					fillArrayRadom1(arr, n);
					*moveCount = *moveCount + 1;
				}
				flag = 1;
			}
		
	} while (flag!=1);
}

void saveWinnerDetails(char* name,int moveCount,int n)
{
	FILE* fp = fopen("leaderboard.txt", "a");
	char* date = presentDate();
	fprintf(fp, "%s,%s,%d,%d\n", date, name, n, moveCount);
	fclose(fp);
}

void sortDetails(struct player* arr,int len)
{
	int swap = 1;
	
	while (swap != 0)
	{
		swap = 0;
		for (int i = 0; i < len - 1; i++)
		{
			if (arr[i].moves > arr[i + 1].moves)
			{
				swap++;
				struct player temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
	}
}

struct player* loadWinnerDetails(int* len)
{
	FILE* fp = fopen("leaderboard.txt","r");
	int count = number_of_lines(fp);
	struct player* players = (struct player*) malloc(count*sizeof(struct player));

	*len = count;

	for (int i = 0; i < count; i++)
	{
		char* date = (char*)malloc(12 * sizeof(char));
		char* name = (char*)malloc(30 * sizeof(char));
		int moves=0;
		int n=0;
		fscanf(fp, "%[^,]s,%[^,]s,%d,%d\n", date, name, &moves, &n);
		fscanf(fp, "%[^,s]", name);

		players[i].date = date;
		players[i].name = name;
		players[i].moves = moves;
		players[i].n = n;

	}
	fclose(fp);
	sortDetails(players, count);
	return players;
}
/*
struct player* loadWinnerDetails(int* len)
{
	FILE* fp = fopen("leaderboard.txt", "r");
	int count = number_of_lines(fp);
	struct player* players = (struct player*) malloc(count*sizeof(struct player));
	
	*len = count;
	
	for (int i = 0; i < count; i++)
	{
		int index = 0;
		char c;
		char* date = (char*)malloc(12 * sizeof(char));
		while (1)
		{
			c = fgetc(fp);
			if (c == ',') break;
			date[index++] = c;
		}
		date[index] = '\0';

		players[i].date = date;
		index = 0;
		char* name = (char*)malloc(30 * sizeof(char));
		while (1)
		{
			c = fgetc(fp);
			if (c == ',') break;
			name[index++] = c;
		}
		name[index] = '\0';
		
		players[i].name = name;
		
		int n;
		c = getc(fp);
		if (c == '4')
			n = 4;
		else if (c == '2')
			n = 2;
		players[i].n = n;
		c = getc(fp);
		index = 0;
		char* moves = (char*)malloc(8 * sizeof(char));
		while (1)
		{
			c = fgetc(fp);
			if (c == '\n')
				break;
			moves[index++] = c;
		}
		moves[index] = '\0';
		int moveCount = atoi(moves);
		players[i].moves = moveCount;

	}
	fclose(fp);
	sortDetails(players, count);
	return players;

}
*/

void game()
{
	system("cls");
	printf("Enter your name : ");
	char* name = (char*)malloc(30 * sizeof(char));
	scanf("%s", name);
	system("cls");
	printf("SELECT GAME MODE:\n1.2X2\n2.4X4\n");
	int choice,n;
	printf("\nEnter your choice: ");
	while (1)
	{
		scanf("%d", &choice);
		if (choice == 1)
		{
			n = 2;
			break;
		}
		else if (choice == 2)
		{
			n = 4;
			break;
		}
		else
		{
			printf("wrong choice, try again!");
		}
	}
	

	int** arr;
	arr = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i <n; i++)
	{
		arr[i] = (int*)calloc(n, sizeof(int));
	}
	
	system("cls");
	initialFillTwo1s(arr, n);
	arrayDisplay(arr, n);
	int moveCount = 0;
	int* fib = returnFibSeries();
	while ((!gameWon(arr, n) && movesAvailable(arr, n, fib)))
	{
		takeUserInput(arr, n, fib, &moveCount);
		system("cls");
		arrayDisplay(arr, n);
	}
	if (gameWon(arr, n))
	{
		displayFinal(moveCount, 1);
		saveWinnerDetails(name, moveCount, n);
	}
	else
	{
		displayFinal(moveCount, 2);
	}


}

void leaderboard()
{
	system("cls");
	//printf("yyet to be updated");
	int count;
	struct player* winnerDetails = loadWinnerDetails(&count);
	printf("S.No      Date                Name            Board Moves\n");
	for (int i = 0; i < count; i++)
	{
		char nn[4];
		if (winnerDetails[i].n == 2)
		{
			nn[0] = '2';
			nn[1] = 'X';
			nn[2] = '2';
			nn[3] = '\0';
		}
		else
		{
			nn[0] = '4';
			nn[1] = 'X';
			nn[2] = '4';
			nn[3] = '\0';
		}
		printf("%-8d%-20s%-20s%-5s%-4d\n", i + 1, winnerDetails[i].date, winnerDetails[i].name, nn, winnerDetails[i].moves);

	}
}

void initialInput()
{
	printf("1. PLAY GAME\n2.VIEW LEADERBOARD\n");
	int choice;
	printf("\nEnter your choice: ");
	scanf("%d", &choice);
	if (choice == 1)
		game();
	else if (choice==2)
		leaderboard();
}

int main()
{
	initialInput();
	system("pause");
	return 0;
}