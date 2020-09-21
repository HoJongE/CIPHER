#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

int main(void) {
	FILE* fp = fopen("ciphertext.txt", "r");
	char frequency_real[26] = "etaoinshrdlcumwfgypbvkjxqz";
	int frequency_fake[26] = { 0 };//암호문 빈도수 배열
	int* pfrequency_fake[26] = { 0 };//간접 정렬에 사용할 배열
	char ciphertext[100][100] = { "\0" };
	int a = 0;
	int i = 0, j = 0;

	//파일 읽으면서 빈도수 체크
	printf("암호문 :\n");
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

	//간접 정렬할 배열의 원소 값을 초기 설정
	for (i = 0;i < 26;i++) {
		pfrequency_fake[i] = frequency_fake + i;//각 원소의 메모리 주소를 값으로 설정
	}

	//버블 정렬 알고리즘으로 간접 정렬
	for (i = 0;i < 25;i++) {
		for (j = 0;j < 26 - i - 1;j++) {
			if (*(pfrequency_fake[j]) < * (pfrequency_fake[j + 1])) {
				int* temp = pfrequency_fake[j];
				pfrequency_fake[j] = pfrequency_fake[j+1];
				pfrequency_fake[j+1] = temp;
			}
		}
	}

	//빈도수 내림차순 출력
	printf("빈도수 :\n");
	for (i = 0;i < 26;i++) {
		j = pfrequency_fake[i] - frequency_fake;
		printf("%c %d\n", j + 'a', frequency_fake[j]);
	}
		
	fclose(fp);
	return 0;
}