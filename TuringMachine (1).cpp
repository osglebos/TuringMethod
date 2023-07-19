#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;
enum COLOR { RED, BLACK };

struct RBTree {
	int Data;
	RBTree *Left;
	RBTree *Right;
	RBTree *Parent;
	COLOR color;
};

#define NIL &list           /* all leafs are sentinels */
RBTree list = { 0, NIL, NIL, 0, BLACK };
HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);

void Insert_Node(RBTree** Node, int Data);
void Insert_Fixup(RBTree** Node, RBTree* New_Node);
void Rotate_Left(RBTree** Node, RBTree *Current);
void Rotate_Right(RBTree** Node, RBTree *Current);

//�������� ������-������� ������
void Make_RBTree(RBTree** Node, int n) {
	int Data;
	while (n > 0) {
		cout << "������� �������� ";
		cin >> Data;
		Insert_Node(Node, Data);
		n--;
	}
}

//���������� ���� � ������-������ ������
void Insert_Node(RBTree** Node, int Data) {
	RBTree **Curent, *Parent, *New_Node;
	Curent = Node;
	Parent = NIL;
	// ����� ��������������
	while (*Curent != NIL) {
		Parent = (*Curent);
		Curent = Data < (*Curent)->Data ? &((*Curent)->Left) : &((*Curent)->Right);
	}
	// �������� ������ ����
	New_Node = new RBTree();
	New_Node->Data = Data;
	New_Node->Parent = Parent;
	New_Node->Left = NIL;
	New_Node->Right = NIL;
	New_Node->color = RED;
	// ������� �������� � ������
	if (Parent != NIL) {
		if (Data < Parent->Data) Parent->Left = New_Node;
		else Parent->Right = New_Node;
	}
	else (*Curent) = New_Node;
	Insert_Fixup(Node, New_Node);
}

// ��������� ������� ������ ����� ������� ������ ��������
void Insert_Fixup(RBTree** Node, RBTree* New_Node) {
	RBTree* Current = New_Node;
	// �������� ������� ������
	while (Current != *(Node) && Current->Parent->color == RED) {
		// ���� ���� ���������
		if (Current->Parent == Current->Parent->Parent->Left) {
			RBTree *ptr = Current->Parent->Parent->Right;
			if (ptr->color == RED) {
				Current->Parent->color = BLACK;
				ptr->color = BLACK;
				Current->Parent->Parent->color = RED;
				Current = Current->Parent->Parent;
			}
			else {
				if (Current == Current->Parent->Right) {
					// ������� Current ����� ��������
					Current = Current->Parent;
					Rotate_Left(Node, Current);
				}
				// ����������� � ���������
				Current->Parent->color = BLACK;
				Current->Parent->Parent->color = RED;
				Rotate_Right(Node, Current->Parent->Parent);
			}
		}
		else {
			RBTree *ptr = Current->Parent->Parent->Left;
			if (ptr->color == RED) {
				Current->Parent->color = BLACK;
				ptr->color = BLACK;
				Current->Parent->Parent->color = RED;
				Current = Current->Parent->Parent;
			}
			else {
				if (Current == Current->Parent->Left) {
					Current = Current->Parent;
					Rotate_Right(Node, Current);
				}
				Current->Parent->color = BLACK;
				Current->Parent->Parent->color = RED;
				Rotate_Left(Node, Current->Parent->Parent);
			}
		}
	}
	(*Node)->color = BLACK;
}
//������� ���� Current �����
void Rotate_Left(RBTree** Node, RBTree *Current) {
	RBTree *ptr = Current->Right;
	Current->Right = ptr->Left;
	if (ptr->Left != NIL) ptr->Left->Parent = Current;
	if (ptr != NIL) ptr->Parent = Current->Parent;
	if (Current->Parent != NIL) {
		if (Current == Current->Parent->Left)
			Current->Parent->Left = ptr;
		else
			Current->Parent->Right = ptr;
	}
	else {
		(*Node) = ptr;
	}
	ptr->Left = Current;
	if (Current != NIL) Current->Parent = ptr;
}

//������� ���� Current ������
void Rotate_Right(RBTree** Node, RBTree *Current) {
	RBTree *ptr = Current->Left;
	Current->Left = ptr->Right;
	if (ptr->Right != NIL) ptr->Right->Parent = Current;
	if (ptr != NIL) ptr->Parent = Current->Parent;
	if (Current->Parent != NIL) {
		if (Current == Current->Parent->Right)
			Current->Parent->Right = ptr;
		else
			Current->Parent->Left = ptr;
	}
	else {
		(*Node) = ptr;
	}
	ptr->Right = Current;
	if (Current != NIL) Current->Parent = ptr;
}

//������ ������-������� ������
void Print_RBTree(RBTree* Node, int l) {

	int i;
	if (Node != NIL) {
		Print_RBTree(Node->Right, l + 1);
		for (i = 0; i < l; i++) cout << "    ";
		if (Node->color == RED) SetConsoleTextAttribute(hStd, FOREGROUND_RED);
		else SetConsoleTextAttribute(hStd, FOREGROUND_INTENSITY);
		_cprintf("%4ld", Node->Data);
		Print_RBTree(Node->Left, l + 1);
	}
	else cout << endl;

	SetConsoleTextAttribute(hStd, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

//������������ ������, ���������� ��� ������-������ ������
void Delete_RBTree(RBTree* Node) {
	if (Node != NIL) {
		Delete_RBTree(Node->Left);
		Delete_RBTree(Node->Right);
		delete(Node);
	}
}

#define SIZE 10
RBTree *GenerateTree(void)
{
	RBTree *T = NIL;
	printf("Generating RBTree: \n");
	int a[SIZE] = { 1, 9, 13, 16, 19, 10, 6, 25, 15, 11 };
	for (int i = 0; i < SIZE; i++)
		Insert_Node(&T, a[i]);
	Print_RBTree(T, 0);
	return T;
}

int main(void)
{
	RBTree *root = GenerateTree();
	printf("\n-----------------------------\nAdding new number 12\n");
	Insert_Node(&root, 12);
	Print_RBTree(root, 0);
	printf("\n-----------------------------\n");
	Delete_RBTree(root);
	system("pause");
	return 0;
}
