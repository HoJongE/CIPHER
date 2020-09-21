#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<stdlib.h>
#define NO 5

void generate_key();
void Encryption(FILE* key);
void Decryption(FILE* key);
int printMenu();
// x, y ��ǥ�� �Է¹޾� cmd â Ŀ���� �̵��ϴ� �Լ� ����� CUI ������ ���� ���
void gotoxy(int x, int y) { 
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main(void) {
	int menu=0;
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
			printf("�޴��� ��Ȯ�� �Է����ּ���!");
		}
		fclose(key);
	}
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
void generate_key(){
	FILE* key = fopen("key.txt", "w");
	char a[26] = "abcdefghijklmnopqrstuvwxyz";
	char key_string[53] = "0";
	int i = 0;
	int j = 26;
	int ran = 0;

	//key_string 0~25 �ε����� ���ĺ� ������� �Է�
	for (i = 0;i < 26;i++) {
		key_string[i] = a[i];
	}
	//key_string 26~51 �ε����� ���� ���ĺ� ����
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
	printf("\nŰ�� ���� �Ϸ�.\n\n");
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
	//���� ������ �б�
	while (!feof(fp)) {
		fgets(plaintext[a], 100, fp);
		while (plaintext[a][i] != '\0') {
			for (j = 0;j < 26;j++) {
				//key_string�� ���� �򹮿� �ش��ϴ� ��ȣ�� �迭 ����
				if (plaintext[a][i] == key_string[j]) {
					ciphertext[a][i] = key_string[j + 26];
				}
				//���� �������� �״�� ��ȣ���� ����
				else if (plaintext[a][i] == ' ') {
					ciphertext[a][i] = plaintext[a][i];
				}
			}
			i++;
		}
		fprintf(fp1,"%s\n", ciphertext[a]);
		a++;
		i = 0;
	}
	fclose(fp);
	fclose(fp1);
	printf("\n��ȣȭ �Ϸ�.\n\n");
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
	//���� ������ �б�
	while (!feof(fp1)) {
		fgets(ciphertext[a], 100, fp1);
		while (ciphertext[a][i] != '\0') {
			for (j = 26;j < 52;j++) {
				//key_string�� ���� ��ȣ���� �ش��ϴ� �� �迭 ����
				if (ciphertext[a][i] == key_string[j]) {
					plaintext[a][i] = key_string[j - 26];
				}
				//��ȣ���� �������� �״�� �򹮿� ����
				else if (ciphertext[a][i] == ' ') {
					plaintext[a][i] = ciphertext[a][i];
				}
			}
			i++;
		}
		fprintf(fp, "%s\n", plaintext[a]);
		a++;
		i = 0;
	}
	fclose(fp);
	fclose(fp1);
	printf("\n��ȣȭ �Ϸ�.\n\n");
	Sleep(2000);	
}