#include <stdio.h>

void other() {
    printf("Other\n");
}

void input() {
    printf("Input\n");
    int a[1] = {1};
    printf("main  = 0x%x or %i \n", &main,  &main);
    printf("input = 0x%x or %i \n", &input, &input);
    printf("other = 0x%x or %i \n", &other, &other);
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("a[%d] = 0x%x (%d)\n", i, a[i], a[i]);
    }
    int value;
    scanf("%d %d", &n, &value);
    a[n] = value;
}

int main() {
    printf("Main\n");
    input();

    return 0;
}

