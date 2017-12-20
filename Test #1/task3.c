#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("fl", "r");
    char ch = fgetc(file);
    char flag = 0;
    char fl1 = 0;
    char fl2 = 0;
    while (ch != EOF) {
        if ((ch == '"') && (flag == 0 || flag == 1) && !fl2) {
            fl1 = !fl1;
            flag = 0;
        }
        else if ((ch == 0x27) && (flag == 0 || flag == 1) && !fl1) {
            fl2 = !fl2;
            flag = 0;
        }
        else if (ch == '/' && (flag == 0 || flag == 1) && !fl1 && !fl2 ){ //Перевод в активное или предактивное состояние
            flag++;
        }
        else {
            switch (flag) {
                case 1:
                    flag = 0;
                    break;
                //Если в состоянии 2, то комментарий только начинает выводиться, и нужно перед символом добавить два слеша
                case 2:
                    printf("//%c", ch);
                    flag = 3;
                    break;
                //Если в состоянии 3, то комментарий уже выводится, и можно просто напечатать символ
                case 3:
                    printf("%c", ch);
            }
            if (ch == '\n') {
                flag = 0;
            }
        }
        ch = fgetc(file);
    }
    return 0;
}
    