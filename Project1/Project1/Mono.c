#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<Windows.h>
#define NO 5

void generate_key(FILE* key);
void Encryption(FILE* key);
void Decryption(FILE* key);
int printMenu();
// x, y ��ǥ�� �Է¹޾� cmd â Ŀ���� �̵��ϴ� �Լ� ����� CUI ������ ���� ���
void gotoxy(int x, int y) { 
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main(void) {
	FILE* key = fopen("key.txt", "w");
	int menu=0;
	

	if (key == NULL) {
		printf("FILE OPEN ERROR!\n");
		return NO;
	}

	while (menu!=4) {
		menu = printMenu();


		switch (menu) {
		case 1:
			generate_key(key);
			break;
		case 2:
			Encryption(key);
			break;
		case 3:
			Decryption(key);
			break;
		case 4:
			break;
		case 5:
			system("cls");
			printf("�޴��� ��Ȯ�� �Է����ּ���!");
		}
	}
	if(key!=NULL)
	fclose(key);

}


int printMenu() {
	int menu=0;
	boolean quit = FALSE;
	system("cls");
	printf("---------------------\n");
	printf("|�޴��� �������ּ���|\n");
	printf("---------------------\n");

	printf("1: key ���� 2: ��ȣȭ 3: ��ȣȭ 4:���α׷� ����\n");
	printf("�޴�: ");
	scanf("%d", &menu);

	if (menu <= 4 && menu >= 1)
		return menu;
	else
		return NO;
}
void generate_key(FILE* key){}
void Encryption(FILE* key){}
void Decryption(FILE* key){}