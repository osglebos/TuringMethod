#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <iostream>

#define SPACE 3

char commands[9][8] = {
"1<2",
"2?1,3",
"3C4",
"4>5",
"5?4,6",
"6C7",
"7>8",
"8?9,1",
"9O"
};

int* ConvertFromDecemaToUno(int first, int second)
{
	int* arr = new int[first + second + 3];

	for (int i = 0; i < first + 3 + second; i++)
		if ((i < first + 1) || ((i > first + 1) && (i < first + 3 + second)))arr[i] = 1;
		else arr[i] = 0;
	return arr;
}

int ConvertFromUnoToDecema(int* arr, int num)
{
	int sum = 0;
	for (int i = 0; i < num; i++)
		if (arr[i] == 1)sum++;
		else break;
	return sum;
}


char convert_to_sum(char* str, int start, int end)
{
	char sum = 0;
	for (int i = start; str[i] != 0 && i < end; i++) sum += str[i] - '0';
	return sum - 1;
}

int* substract_post(int* arr, int len, int start)
{
	int sum = 0;
	char prev_com = 0;
	for (int k = start; k < len && k >= 0;)
	{
		char command;
		if (prev_com < 9) command = commands[prev_com][1];
		else command = commands[prev_com][2];

		switch (command)
		{
		case '<':
			k--;
			if (prev_com < 9) prev_com = convert_to_sum(commands[prev_com], 2, 100);
			else prev_com = convert_to_sum(commands[prev_com], 3, 100);
			break;

		case '>':
			k++;
			if (prev_com < 9) prev_com = convert_to_sum(commands[prev_com], 2, 100);
			else prev_com = convert_to_sum(commands[prev_com], 3, 100);
			break;

		case '?':
		{
			char first = 0, second = 0;
			int i = 0;
			for (i = (prev_com < 9 ? 2 : 3); commands[prev_com][i] != ','; i++) first += commands[prev_com][i] - '0';
			i++;
			for (; commands[prev_com][i] != 0; i++) second += commands[prev_com][i] - '0';

			if (arr[k] == 0) prev_com = first - 1;
			else prev_com = second - 1;
		}
		break;

		case 'M':
			if (arr[k] != 1) arr[k] = 1;
			else command = 'O';
			if (prev_com < 9) prev_com = convert_to_sum(commands[prev_com], 2, 100);
			else prev_com = convert_to_sum(commands[prev_com], 3, 100);
			break;

		case 'C':
			if (arr[k] != 0) arr[k] = 0;
			else command = 'O';
			if (prev_com < 9) prev_com = convert_to_sum(commands[prev_com], 2, 100);
			else prev_com = convert_to_sum(commands[prev_com], 3, 100);
			break;
		}

		if (command == 'O') break;
	}
	return arr;
}

void PrintTape(int* arr, int first, int second)
{
	int len = first + second + 2 + 2 + 1;
	int left = -first - 1 - SPACE;
	int right = second + 2 + SPACE;
	for (int i = left; i < right; i++)
		printf("%3i", i);
	printf("\n");
	for (int i = left; i < right; i++)
		if ((i >= -first - 1) && (i <= second + 1)) printf("%3i", arr[i + first + 1]);
		else printf("%3i", 0);
	printf("\n\n");

}

int devision(int first, int second)
{
	int dev = 0;

	for (int tmp_size = first; tmp_size >= second; dev++)
	{
		int j = 0;
		int* tmp_arr = ConvertFromDecemaToUno(tmp_size, second);

		printf("%iое вычитание\n", dev + 1);
		PrintTape(tmp_arr, tmp_size, second);
		tmp_arr = substract_post(tmp_arr, tmp_size + second + 3, tmp_size + 1);
		printf("После вычитания\n");
		PrintTape(tmp_arr, tmp_size, second);
		printf("------------------\n\n");

		tmp_size = ConvertFromUnoToDecema(tmp_arr, tmp_size + 1);
		free(tmp_arr);
	}
	return dev;
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	int first = 0, second = 0;
	printf("Введите делимое: ");
	scanf("%i", &first);
	printf("Введите делитель: ");
	scanf("%i", &second);

	printf("\n");
	int res = devision(first, second);
	printf("Результат в унарной системе:\n");
	PrintTape(ConvertFromDecemaToUno(res, -1), res, -1);
	printf("Результат деления %i / %i = %i\n\n", first, second, res);

	system("pause");
	return 0;
}
