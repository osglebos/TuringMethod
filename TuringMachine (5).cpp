#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <iostream>

char *ConvertFromDecemaToDuo(int first)
{
	if (first == 1)
	{
		char *tmp_arr = new char[2];
		tmp_arr[0] = '1';
		tmp_arr[1] = 0;
		return tmp_arr;
	}

	int len = first;
	char *tmp_arr = new char[len];
	int i = 0;
	for (i = 0; i < len; i++)
	{
		tmp_arr[i] = '0' + first % 2;
		if (first < 1)break;
		first /= 2;
	}
	tmp_arr[i] = 0;
	len = i;
	char *arr = new char[len];
	for (int k = 0, j = len - 1; k < len; k++, j--)
		arr[k] = tmp_arr[j];
	arr[len] = 0;
	return arr;
}

int LenOfTape(char *arr)
{
	int sum = 0;
	for (int i = 0; arr[i] != 0; i++)
		sum++;
	return sum;
}

char *ConvertFromDecemaToTape(int first)
{
	char *number_duo = ConvertFromDecemaToDuo(first);
	int i, len = LenOfTape(number_duo) + 4;
	char *arr = new char[len];
	for (i = 0; i < len; i++)
		if ((i > 1) && (i < len-4+2)) arr[i] = number_duo[i-2];
		else arr[i] = 'e';

	arr[len - 1] = 0;

	return arr;
}

void PrintTape(char *arr, int len, int k)
{
	for (int i = 0; i < len; i++)
		printf("%3i", i);
	printf("\n");
	for (int i = 0; i < len; i++)
		printf("%3c", arr[i]);
	printf("\n");
	for (int i = 0; i < k; i++) printf("   ");
	printf("  ^\n");
}

char *add_one_turing(char *arr, int len, int start)
{
	char comands[3][3][4] = {
		{"00R", "01R", "1eL"},
		{"21L", "10L", "21L"},
		{"20L", "21L", "2eL"}
	};
	char comand = '0';
	int k = 0;
	for (k = start; k < len && k >= 0;)
	{
		int x = 0, y = 0, z = 0;

		if (arr[k] == '0') x = 0;
		else if (arr[k] == '1') x = 1;
		else if (arr[k] == 'e') x = 2;
		else break;

		if (comand == '0') y = 0;
		else if (comand == '1') y = 1;
		else if (comand == '2') y = 2;
		else break;

		printf("\nLenta : \n");
		PrintTape(arr, len, k);
		printf("Comanda : q%s\n", comands[y][x]);

		comand = comands[y][x][0];
		arr[k] = comands[y][x][1];

		if (comands[y][x][2] == 'R') k++;
		else if (comands[y][x][2] == 'L') k--;
	}
	printf("\nLenta : \n");
	PrintTape(arr, len, k);
	return arr;
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	int first = 0;
	printf("Введите первое число для сложения: ");
	scanf("%i", &first);

	
	char *tape = ConvertFromDecemaToTape(first);
	printf("%s\n", tape);
	add_one_turing(tape, LenOfTape(tape), 2);
	system("pause");
	return 0;
}