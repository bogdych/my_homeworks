#include <stdio.h>
#include <stdlib.h>

char *inputString(FILE* fp){
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
    char ch;
    printf("Enter the string: ");
    string = inputString(stdin);
    printf("Enter the symbol: ");
    scanf("%c", &ch);
    char *sym1 = string;
    char *sym2 = sym1;
    while (*sym1 != '\0') {
        if (*sym1 == ch) {
            sym2 = sym1;
            while (*sym2 != '\0') {
                *sym2 = *(sym2 + 1);
                sym2++;
            }
        }
        else {
            sym1++;
        }
    }
    printf("%s\n", string);
    return 0;
}