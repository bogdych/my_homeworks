#include <stdio.h>
#include <string.h>

long long int getValue(char *str) {
	long long int value = 0;
	long long int length = strlen(str);
	for (long long int i = 0; i < length; i++) {
		value = value + (str[i] - '0') * (1 << length - i - 1);
	}
	return value;
}

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
	char *string;

	printf("Enter a:\n");
	string = inputString(stdin);
	long long int a = getValue(string);
	free(string);

	printf("Enter b:\n");
	string = inputString(stdin);
	long long int b = getValue(string);
	free(string);

	if (a > b) {
		printf("a > b\n");
	}
	else if (a == b) {
		printf("a = b\n");
	}
	else {
		printf("a < b\n");
	}
	return 0;
}