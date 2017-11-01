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

char *strcat(char *dst, char *src) {
	char *res;
	res = dst;
	while (*dst != '\0') {
		dst++;
	}
	while ((*dst = *src) != '\0') {
		dst++;
		src++;
	}
	return res;
}	

int strcmr(char *s1, char *s2) {
	int i = 0;
	while ((s1[i] - s2[i]) == 0 && s1[i] != '\0' && s2[i] != '\0') {
		i++;
	}
	return s1[i] - s2[i];
}

int main() {
	return 0;
}
