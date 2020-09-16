#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<Windows.h>
#define NO 5

void generate_key(FILE* key);
void Encryption(FILE* key);
void Decryption(FILE* key);
int printMenu();
// x, y 좌표를 입력받아 cmd 창 커서를 이동하는 함수 깔끔한 CUI 구성을 위해 사용
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
			printf("메뉴를 정확히 입력해주세요!");
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
	printf("|메뉴를 선택해주세요|\n");
	printf("---------------------\n");

	printf("1: key 생성 2: 암호화 3: 복호화 4:프로그램 종료\n");
	printf("메뉴: ");
	scanf("%d", &menu);

	if (menu <= 4 && menu >= 1)
		return menu;
	else
		return NO;
}
void generate_key(FILE* key){}
void Encryption(FILE* key){}
void Decryption(FILE* key){}