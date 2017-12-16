#include <stdio.h>

int strlen(char *s) {
	char *n = s;
	while (*n)
		n++;
	return n - s;
}

void strcpy(char *dst, char *src) {
	while (*dst++ = *src++) 
		;
	*dst = '\0';
}

char *strcat(char *dst, char *src) {
    char *res = dst;
    while (*dst)
        dst++;
    while (*dst++ = *src++)
        ;
    *dst = '\0';
    return res;
}


int strcmr(char *s1, char *s2) {
	while (!(*s1 - *s2) && *s1++ && *s2++) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

int main() {
	return 0;
}
