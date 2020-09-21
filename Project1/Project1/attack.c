#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

int main(void) {
	FILE* fp = fopen("ciphertext.txt", "r");
	char frequency_real[26] = "etaoinshrdlcumwfgypbvkjxqz";
	int frequency_fake[26] = { 0 };//��ȣ�� �󵵼� �迭
	int* pfrequency_fake[26] = { 0 };//���� ���Ŀ� ����� �迭
	char ciphertext[100][100] = { "\0" };
	int a = 0;
	int i = 0, j = 0;

	//���� �����鼭 �󵵼� üũ
	printf("��ȣ�� :\n");
	while (!feof(fp)) {
		fgets(ciphertext[a], 100, fp);
		printf("%s", ciphertext[a]);
		while (ciphertext[a][i] != '\0') {
			if (ciphertext[a][i] == ' ') {
				i++;
			}
			else {
				frequency_fake[ciphertext[a][i] - 'a']++;
				i++;
			}
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
		printf("%c %d\n", j + 'a', frequency_fake[j]);
	}
		
	fclose(fp);
	return 0;
}