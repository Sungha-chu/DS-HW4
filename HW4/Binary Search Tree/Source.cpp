#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 10000
#define cut "%[^ ,\".?:();\t\n\r] %*[ ,\".?:();\t\n\r]"		//把正規運算是放在巨集
int countWords = 0;
int countNode = 0;

struct TREE {
	char Data[size];
	int count;
	TREE* left, * right;
};

TREE* NewNode(char* KeyWord) {
	TREE* temp = (TREE*)calloc(1, sizeof(TREE));
	strcpy(temp->Data, KeyWord);
	temp->count++;
	temp->left = temp->right = NULL;
	countNode++;
	return temp;
}

TREE* Add(TREE* Node, char* KeyWord) {
	if (Node == NULL) return NewNode(KeyWord);

	if (strcmp(KeyWord, Node->Data) < 0)
		Node->left = Add(Node->left, KeyWord);
	else if (strcmp(KeyWord, Node->Data) > 0)
		Node->right = Add(Node->right, KeyWord);
	else if (strcmp(KeyWord, Node->Data) == 0)
		Node->count++;
	return Node;
}

void Inorder(TREE* Root) {
	if (Root != NULL) {
		Inorder(Root->left);
		printf("%-8s\t\t出現%d次\n", Root->Data, Root->count);
		Inorder(Root->right);
	}
}

int countTall(TREE* Root) {
	if (Root == NULL)return  0;
	if (countTall(Root->left) > countTall(Root->right))return 1 + countTall(Root->left);
	else return 1 + countTall(Root->right);
}

TREE* dealFile(char* argv) {
	FILE* file = fopen(argv, "rb");
	TREE* root = NULL;
	char data[size] = { 0 };
	while (fscanf(file, cut, data) != EOF) {
		root = Add(root, data);
		countWords++;
	}
	fclose(file);
	return root;
}

void main(int argc, char* argv[]) {
	Inorder(dealFile(argv[1]));
	printf("\n總共%d個單字\n", countWords);
	printf("\n高%d，%d個節點\n", countTall(dealFile(argv[1])), countNode);
}