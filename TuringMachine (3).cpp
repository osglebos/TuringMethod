#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <iostream>

char *ConvertFromDecemaToUno(int x)
{
	char *arr = new char[2 * (x + 1) + 3];

	for (int i = 0; i < 2 * (x + 1) + 3; i++)
		if ((i > 0) && (i < x + 2)) arr[i] = '1';
		else arr[i] = 'e';

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

char *copy_turing(char *arr, int len, int start)
{
	char comands[4][4][4] = {
		{"01L", "10R", "0*L", "2eR"},
		{"---", "11R", "2*R", "2*R"},
		{"---", "21R", "---", "31L"},
		{"00R", "31L", "3*L", "---"}
	};
	char comand = '0';
	for (int k = start; k < len && k >= 0;)
	{
		int x = 0, y = 0, z = 0;

		if (arr[k] == '0') x = 0;
		else if (arr[k] == '1') x = 1;
		else if (arr[k] == '*') x = 2;
		else if (arr[k] == 'e') x = 3;
		else break;

		if (comand == '0') y = 0;
		else if (comand == '1') y = 1;
		else if (comand == '2') y = 2;
		else if (comand == '3') y = 3;
		else break;

		printf("\nLenta : \n");
		PrintTape(arr, len, k);
		printf("Comanda : q%s\n", comands[y][x]);

		comand = comands[y][x][0];
		arr[k] = comands[y][x][1];

		if (comands[y][x][2] == 'R') k++;
		else if (comands[y][x][2] == 'L') k--;
	}
	return arr;
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	int first = 0;
	printf("Введите количество единиц которое надо скопировать: ");
	scanf("%i", &first);

	copy_turing(ConvertFromDecemaToUno(first), 2 * (first + 1) + 3, 1);
	system("pause");
	return 0;
}