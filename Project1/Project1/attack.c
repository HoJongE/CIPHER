#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
void Decryption(FILE*,int num);
void predictKey(char[],char[]);
void generate_key(char[],char[],char[],char[],char[],int);
void generate_testfile(char real[]) {
	FILE* fp = fopen("ciphertext.txt", "w");
	int num = 30;
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < num; j++)
			fprintf(fp, "%c",real[i]);
		fprintf(fp, "\n");
		num--;
	}
}
int main(void) {
	FILE* fp = fopen("ciphertext.txt", "r");
	char frequency_real[26] = "etaoinshrdlcumwfgypbvkjxqz";
	int frequency_fake[26] = { 0 };//��ȣ�� �󵵼� �迭
	int* pfrequency_fake[26] = { 0 };//���� ���Ŀ� ����� �迭
	char frequency[26];
	char ciphertext[1000][100] = { "\0" };
	int a = 0;
	int i = 0, j = 0;
	
	srand(time(NULL));
	//���� �����鼭 �󵵼� üũ
	printf("��ȣ�� :\n");
	if (fp == NULL) {
		printf("���� ���� ����!");
		return -1;
	}
	while (!feof(fp)) {
		fgets(ciphertext[a], 100, fp);
		printf("%s", ciphertext[a]);
		while (ciphertext[a][i] != '\0') {
			if (ciphertext[a][i]>='a'&&ciphertext[a][i]<='z') {
				frequency_fake[ciphertext[a][i++] - 'a']++;
			}
			else i++;
		}
		i = 0;
		a++;
	}

	//���� ������ �迭�� ���� ���� �ʱ� ����
	for (i = 0;i < 26;i++) {
		pfrequency_fake[i] = frequency_fake + i;//�� ������ �޸� �ּҸ� ������ ����
	}

	//���� ���� �˰������� ���� ����
	for (i = 0;i < 25;i++) {
		for (j = 0;j < 26 - i - 1;j++) {
			if (*(pfrequency_fake[j]) < * (pfrequency_fake[j + 1])) {
				int* temp = pfrequency_fake[j];
				pfrequency_fake[j] = pfrequency_fake[j+1];
				pfrequency_fake[j+1] = temp;
			}
		}
	}

	//�󵵼� �������� ���
	printf("�󵵼� :\n");
	for (i = 0;i < 26;i++) {
		j = pfrequency_fake[i] - frequency_fake;
		frequency[i] = j + 'a';
		printf("%c %d\n", j + 'a', frequency_fake[j]);
	}
	predictKey(frequency,frequency_real);
	fclose(fp);
	return 0;
}
void randomShuffle(char group[],int length) {
	char temp;
	int randIndex1;
	int randIndex2;
	for (int i = 0; i < length; i++) {
		randIndex1 = rand() % length;
		randIndex2 = rand() % length;
		temp = group[randIndex1];
		group[randIndex1] = group[randIndex2];
		group[randIndex2] = temp;
	}
}
//�� ���� �������� 10���� Ű ����
void predictKey(char frequency[26],char frequency_real[26]) {
	FILE* key = NULL;
	
	int i = 0;
	char group1[3];
	char group2[6];
	char group3[6];
	char group4[11];

	for (int j = 0; j < 3; j++)
		group1[j] = frequency[i++];
	for (int j = 0; j < 6; j++) {
		group2[j] = frequency[i];
		group3[j] = frequency[i + 6];
		i++;
	}
	i += 6;
	for (int j = 0; j < 11; j++)
		group4[j] = frequency[i++];
	
	for (int j = 0; j < 26; j++)
		printf("%c ", frequency[j]);
	for (int x = 0; x < 11; x++) {
		generate_key(frequency_real, group1, group2, group3, group4, x + 1);
		randomShuffle(group1, 3);
		randomShuffle(group2, 6);
		randomShuffle(group3, 6);
		randomShuffle(group4, 11);
	}
}

void generate_key(char frequency_real[],char group1[],char group2[],char group3[],char group4[],int num) {
	FILE* key = NULL;
	char fileName[30] = "key0.txt";
	char a[26] = "abcdefghijklmnopqrstuvwxyz";
	char key_string[53] = "0";
	int i = 0;
	
	int ran = 0;

	//key_string 0~25 �ε����� ���ĺ� ������� �Է�
	for (i = 0; i < 26; i++) {
		key_string[i] = a[i];
	}
	i = 0;
	//key_string 26~51 �ε����� ���� ���ĺ� ����
	for (int j=0; j < 3; j++,i++) 
		key_string[frequency_real[i] - 'a' + 26] = group1[j];
	for (int j = 0; j < 6; j++, i++)
		key_string[frequency_real[i] - 'a' + 26] = group2[j];
	for (int j = 0; j < 6; j++, i++)
		key_string[frequency_real[i] - 'a' + 26] = group3[j];
	for (int j = 0; j < 11; j++, i++)
		key_string[frequency_real[i] - 'a' + 26] = group4[j];
	fileName[3] = num + '0';
	key_string[52] = '\0';
	key = fopen(fileName, "w");
	fprintf(key, "%s\n", key_string);
	printf("\nŰ�� ���� �Ϸ�.\n");
	fclose(key);
	Decryption(fileName, num);
}
void Decryption(char keyname[],int num) {
	char plainname[30] = "plaintext0.txt";
	FILE* fp  = fopen(keyname, "r");
	FILE* fp1 = fopen("ciphertext.txt", "r");
	FILE* fp2 = NULL;
	char key_string[53] = "\0";
	char plaintext[1000][100] = { "\0" };
	char ciphertext[1000][100] = { "\0" };
	int i = 0;
	int j = 0;
	int a = 0;
	if (fp1 == NULL||fp==NULL)
		return;
	plainname[9] = num + '0';
	fp2 = fopen(plainname, "w");
	fscanf(fp, "%s\n", key_string);
	printf("\nkey_string :\n%s\n", key_string);
	//���� ������ �б�
	while (!feof(fp1)) {
		fgets(ciphertext[a], 100, fp1);
		while (ciphertext[a][i] != '\0') {
			//key_string�� ���� ��ȣ���� �ش��ϴ� �� �迭 ����
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
		fprintf(fp2, "%s", plaintext[a]);
		a++;
		i = 0;
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	printf("��ȣȭ �Ϸ�.\n");
}