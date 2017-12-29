#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *inputString(FILE* fp) {
	char *str;
	int ch;
	size_t size = 16;
	size_t len = 0;
	str = realloc(NULL, sizeof(char) * size);
	if (!str)
		return str;
	while (EOF != (ch = fgetc(fp)) && ch != '\n') {
		str[len++] = ch;
		if (len == size) {
			str = realloc(str, sizeof(char) * (size += 16));
			if (!str)
				return str;
		}
	}
	str[len++] = '\0';

	return realloc(str, sizeof(char) * len);
}

int main() {
	FILE *file1 = fopen("file", "r");
	FILE *file2 = fopen("file", "r");
	if (file1 != NULL && file2 != NULL) {
		char * str1;
		char * str2;
		char flag = 0;
		char nn;
		str1 = inputString(file1);
		while (str1 != EOF) {
			str2 = inputString(file2);
			while (str2 != EOF) {
				if (!strcmp(str1, str2)) {
					flag++;
					if (flag == 2) {
						break;
					}
				}
				free(str2);
				nn = fgetc(file2);
				if (nn == EOF) {
					str2 = nn;
				}
				else {
					str2 = inputString(file2);
				}
			}
			if (flag == 2) {
				fclose(file2);
				fopen("file", "r");
			}
			else {
				printf("%s\n", str1);
				free(str1);
				break;
			}
			nn = fgetc(file1);
			flag = 0;
			if (nn == EOF) {
				str1 = nn;
			}
			else {
				str1 = inputString(file1);
			}
		}
		fclose(file1);
		fclose(file2);
	}
	else {
		printf("Couldn't open file\n");
	}
	return 0;
}