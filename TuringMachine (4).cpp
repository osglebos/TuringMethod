#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

void PrintTape(char *arr, int first, int second)
{
	int left = -first - 1;
	int right = second + 2;
	for (int i = left; i < right; i++)
		printf("%3i", i);
	printf("\n");

	for (int i = left; i < right; i++)
		printf("%3c", arr[i + first + 1]);
	printf("\n");
}

char *TuringProgramm(char *arr, int len, int first, int second)
{
	char comands[4][5][4] = {
		{"5aR", "2 E", "11R", "3bE", "2aR"},
		{"5bE", "21E", "2aL", "2aR", "1bL"},
		{"41L", "2aE", "5bR", "5aL", "41E"},
		{"41R", "2bE", "11L", "31L", "3 E"}
	};

	char comand = '3';
	for (int k = first; k < len && k >= 0;)
	{
		int x = 0, y = 0, z = 0;

		if (arr[k] == ' ') x = 0;
		else if (arr[k] == '1') x = 1;
		else if (arr[k] == 'a') x = 2;
		else if (arr[k] == 'b') x = 3;

		y = 0;
		switch (comand)
		{
		case '5': y += 1;
		case '4': y += 1;
		case '3': y += 1;
		case '2': y += 1;
		case '1': y += 0;
		}

		printf("\nLenta : \n");
		PrintTape(arr, first, second);
		printf("Comanda : q%s\n", comands[x][y]);

		comand = comands[x][y][0];
		arr[k] = comands[x][y][1];

		if (comands[y][x][2] == 'R') k++;
		else if (comands[y][x][2] == 'L') k--;
	}
	return arr;
}

int main(void)
{
	char *str = new char[9];

	char tmp[9] = {' ', '1', '1', '1', '1', 'b', ' ', ' ', ' ' };
	for (int i = 0; i < 9; i++)
		str[i] = tmp[i];
	TuringProgramm(str, 9, 5, 1);

	system("pause");
	return 0;
}