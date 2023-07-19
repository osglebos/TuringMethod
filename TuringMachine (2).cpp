#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <iostream>

char *ConvertFromDecemaToUno(int x)
{
	char *arr = new char[x+2];
	for (int i = 0; i < x+2; i++) arr[i] = '1';
	arr[x + 1] = 0;
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
	char *number_uno = ConvertFromDecemaToUno(first);
	int i, len = LenOfTape(number_uno) + 6 + first/2;
	char *arr = new char[len];
	for (i = 0; i < len; i++)
		if ((i > 0) && (i < first + 2)) arr[i] = number_uno[i - 1];
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

char *devide_turing(char *arr, int len, int start)
{
	char comands[9][3][4] = {
		{"00R", "01R", "3eR"}, 
		{"10L", "20L", "6eR"},
		{"---", "00R", "5eR"},
		{"---", "31R", "41L"},
		{"---", "41L", "1eL"},
		{"5eR", "51R", "5eR"},
		{"6eR", "61R", "7eR"},
		{"---", "71R", "8eL"},
		{"8eR", "8eR", "8eR"}
	};
	char comand = '0';
	for (int k = start; k < len && k >= 0;)
	{
		int x = 0, y = 0, z = 0;

		if (arr[k] == '0') x = 0;
		else if (arr[k] == '1') x = 1;
		else if (arr[k] == 'e') x = 2;
		else break;

		if (comand == '0') y = 0;
		else if (comand == '1') y = 1;
		else if (comand == '2') y = 2;
		else if (comand == '3') y = 3;
		else if (comand == '4') y = 4;
		else if (comand == '5') y = 5;
		else if (comand == '6') y = 6;
		else if (comand == '7') y = 7;
		else if (comand == '8') y = 8;
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
	printf("¬ведите делимое: ");
	scanf("%i", &first);

	char *tape = ConvertFromDecemaToTape(first);
	printf("%s\n", tape);
	devide_turing(tape, LenOfTape(tape), 2);
	system("pause");
	return 0;
}

