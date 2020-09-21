#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>

#define NO 5

void generate_key();
void Encryption(FILE* key);
void Decryption(FILE* key);
int printMenu();
// x, y 좌표를 입력받아 cmd 창 커서를 이동하는 함수 깔끔한 CUI 구성을 위해 사용
void gotoxy(int x, int y) { 
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main(void) {
	int menu=0;
	srand(time(NULL));
	while (menu!=4) {
		menu = printMenu();
		FILE* key = fopen("key.txt", "r");
		
		switch (menu) {
		case 1:
			generate_key();
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
		fclose(key);
	}
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
void generate_key(){
	FILE* key = fopen("key.txt", "w");
	char a[26] = "abcdefghijklmnopqrstuvwxyz";
	char key_string[53] = "0";
	int i = 0;
	int j = 26;
	int ran = 0;

	//key_string 0~25 인덱스에 알파벳 순서대로 입력
	for (i = 0;i < 26;i++) {
		key_string[i] = a[i];
	}
	//key_string 26~51 인덱스에 랜덤 알파벳 매핑
	while (j != 52) {
		ran = rand() % 26;
		if (a[ran] != '\0') {
			key_string[j] = a[ran];
			a[ran] = 0;
			j++;
		}
	}
	key_string[52] = '\0';
	fprintf(key, "%s\n", key_string);
	printf("\n키값 생성 완료.\n\n");
	Sleep(2000);
	fclose(key);
}
void Encryption(FILE* key){
	FILE* fp = fopen("plaintext.txt", "r");
	FILE* fp1 = fopen("ciphertext.txt", "w");
	char key_string[53] = "\0";
	char plaintext[100][100] = { "\0" };
	char ciphertext[100][100] = { "\0" };
	int i = 0;
	int j = 0;
	int a = 0;

	fscanf(key, "%s\n", key_string);
	printf("\nkey_string :\n%s\n", key_string);
	printf("원문 내용: ");
	//파일 끝까지 읽기
	while (!feof(fp)) {
		fgets(plaintext[a], 100, fp);
		printf("%s\n", plaintext[a]);
		while (plaintext[a][i] != '\0') {
				//key_string을 통해 평문에 해당하는 암호문 배열 생성
			if (plaintext[a][i]>='a'&&plaintext[a][i]<='z') {
				ciphertext[a][i] = key_string[plaintext[a][i]-'a' + 26];
			}	
			else
				ciphertext[a][i] = plaintext[a][i];
			i++;
		}
		fprintf(fp1,"%s\n", ciphertext[a]);
		a++;
		i = 0;
	}
	fclose(fp);
	fclose(fp1);
	printf("\n암호화 완료.\n\n");
	Sleep(2000);
}
void Decryption(FILE* key){
	FILE* fp = fopen("plaintext.txt", "w");
	FILE* fp1 = fopen("ciphertext.txt", "r");
	char key_string[53] = "\0";
	char plaintext[100][100] = { "\0" };
	char ciphertext[100][100] = { "\0" };
	int i = 0;
	int j = 0;
	int a = 0;
	
	fscanf(key, "%s\n", key_string);
	printf("\nkey_string :\n%s\n", key_string);
	//파일 끝까지 읽기
	while (!feof(fp1)) {
		fgets(ciphertext[a], 100, fp1);
		while (ciphertext[a][i] != '\0') {
				//key_string을 통해 암호문에 해당하는 평문 배열 생성
			if (ciphertext[a][i] >= 'a' && ciphertext[a][i] <= 'z') {
				for (int x = 0; x < 26; x++) {
					if (key_string[x + 26] == ciphertext[a][i])
						plaintext[a][i] = key_string[x];
				}
			}
				else  
					plaintext[a][i] = ciphertext[a][i];
			i++;
		}
		fprintf(fp, "%s\n", plaintext[a]);
		a++;
		i = 0;
	}
	fclose(fp);
	fclose(fp1);
	printf("\n복호화 완료.\n\n");
	Sleep(2000);	
}