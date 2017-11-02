#include <stdio.h>

int strlen(char *s) {
	int n;
	for (n = 0; *s != '\0'; s++) {
		n++;
	}
	return n;
}

void strcpy(char *dst, char *src) {
	while ((*dst = *src) != '\0') {
		dst++;
		src++;
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
	while ((*s1 - *s2) == 0 && *s1 != '\0' && *s2 != '\0') {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

int main() {
	return 0;
}
