#include <stdio.h>

const int NUM = 100;

int main() {
    long squad_sum = 0;
    long sum_squad = 0;
    for (int i = 1; i <= NUM; i++) {
        squad_sum += i;
        sum_squad += i*i;
    }
    printf("%li\n", squad_sum * squad_sum - sum_squad);
    return 0;
}