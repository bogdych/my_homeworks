#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>	
#include "HashTable.h"

const long int sizeOfTable = 1000;

long hashFunction(char * str) {
	long len = strlen(str);
	long sum = 171;
	for (long j = 0; j < len; j++) {
		sum = abs(sum * 171 + str[j]) % sizeOfTable;
	}
	return sum;
}

void main() {
	HashTable * hashTable = createHashTable(sizeOfTable, hashFunction);

	FILE *file = fopen("file.txt", "r");
	char *str = realloc(NULL, sizeof(char)*0);
	char ch;
	size_t size = 16;
	size_t len = 0;
	char flag = 0;

	clock_t startTime;
	clock_t endTime;
	double operatingTime;

	startTime = clock();
	while (EOF != (ch = fgetc(file))) {
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
			if (!flag) {
				flag = !flag;
				str = calloc(size, sizeof(char));
				if (!str) {
					printf("Something goes wrong! (Couldn't write word)\n");
					exit(0);
				}
			}
			str[len++] = ch;
			if (len == size) {
				str = realloc(str, sizeof(char) * (size += 16));
				if (!str) {
					printf("Something goes wrong! (Couldn't write word)\n");
					exit(0);
				}
			}
		}
		else {
			if (flag) {
				flag = !flag;
				str[len++] = '\0';
				str = realloc(str, sizeof(char) * len);
				len = 0;
				size = 16;
				if (!insertData(hashTable, str, 1)) {
					printf("Something goes wrong! (Couldn't add word in hash table)\n");
					exit(0);
				}
			}
		}
	}
	endTime = clock();
	fclose(file);
	operatingTime = ((double)(endTime - startTime) / CLOCKS_PER_SEC  * 1000);
	printHashTableStats(hashTable);
	printf("Operating time (ms): %.0f\n", operatingTime);
	freeHashTable(hashTable);
}