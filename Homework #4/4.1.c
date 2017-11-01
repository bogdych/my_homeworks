#include <stdio.h>

int strlen(char *s) {
	int n;
	for (n = 0; *s != '\0'; s++) {
		n++;
	}
	return n;
}

void strcpy(char *dst, char *src) {
	int i = 0;
	while ((*(dst + i) = *(src + i)) != '\0') {
		i++;
	}
}

int main() {
	char a[5] = "hasd\0";
	char b[5] = "yqwe\0";
	strcpy(a, b);
	printf("%d\n", strlen("Hello, world!\0"));
	printf("%s\n", a);
	return 0;
}
