#include "LinkedList.h"
#include <stdlib.h>

#define CREATE 1
#define INBEGIN 2
#define INEND 3
#define INAFTER 4
#define DBYVALUE 5
#define DBYINDEX 6
#define PRINT 7
#define FREE 8
#define REVERSE 9
#define LOOP 10
#define ISLOOPED 11
#define BREAKELOOP 12
#define EXIT 0

void main() {
	printf("1.  Create list\n");
	printf("2.  Insert to the beginning\n");
	printf("3.  Insert to the end\n");
	printf("4.  Insert after index\n");
	printf("5.  Delete by value\n");
	printf("6.  Delete by index\n");
	printf("7.  Print nodes' values\n");
	printf("8.  Free list\n");
	printf("9.  Reverse list\n");
	printf("10. Loop list\n");
	printf("11. Is list looped\n");
	printf("12. Break loop-\n");
	printf("0. Exit\n\n\n");
	unsigned int command;
	int value;
	size_t index;
	LinkedList * list = NULL;
	int x;
	while (1) {
		printf("Enter command:\n");
		x = scanf("%d", &command);
		if (x && command >= 0 && command <= 12) {
			switch (command)
			{
			case CREATE:
				if (!list) {
					list = createLinkedList();
					if (list) {
						printf("List was created!\n");
					}
					else {
						printf("List wasn't created! :(\n");
					}
				}
				else {
					printf("List already created\n");
				}
				break;
			case EXIT:
				freeLinkedList(list);
				free(list);
				exit(0);
				break;
			default:
				if (list) {
					switch (command)
					{
					case INBEGIN:
						printf("Enter value:\n");
						scanf("%d", &value);
						if (insertToBeginning(list, value)) {
							printf("The node was successfully added to the beginning.\n");
						}
						else {
							printf("The node wasn't inserted in the beginning.\n");
						}
						break;


					case INEND:
						printf("Enter value:\n");
						scanf("%d", &value);
						if (insertToEnd(list, value)) {
							printf("The node was successfully added to the end.\n");
						}
						else {
							printf("The node wasn't inserted in the end.\n");
						}
						break;


					case INAFTER: {
						printf("Enter index:\n");
						scanf("%zu", &index);
						printf("Enter value:\n");
						scanf("%d", &value);
						if (insertAfterIndex(list, value, index)) {
							printf("The node was successfully inserted after %zu element.\n", index);
						}
						else {
							printf("The node wasn't added to the end.\n");
						}
						break;
					}


					case DBYVALUE:
						if (list->head) {
							printf("Enter value:\n");
							scanf("%d", &value);
							size_t count = deleteElementByValue(list, value);
							if (count) {
								printf("%zu element%s successfully deleted.\n", count, (count == 1) ? " was" : "s were");
							}
							else {
								printf("Nothing was deleted.\n");
							}
						}
						else {
							printf("Nothing to delete.\n");
						}
						break;


					case DBYINDEX:
						if (list->head) {
							printf("Enter index:\n");
							scanf("%zu", &index);
							if (!deleteElementByIndex(list, index)) {
								printf("Wrong index.\n");
							}
						}
						else {
							printf("Nothing to delete.\n");
						}
						break;


					case PRINT:
						printLinkedList(list);
						break;


					case FREE:
						freeLinkedList(list);
						printf("List was freed.\n");
						break;


					case REVERSE:
						if (list->head) {
							reverseLinkedList(list);
							printf("List was reversed.\n");
							break;
						}
						else {
							printf("Nothing to reverse.\n");
						}


					case LOOP:
						if (list->head) {
							printf("Enter index of beginnig of loop\n");
							scanf("%zu", &index);
							if (loopLinkedList(list, index)) {
								printf("Loop was created in the node with index %zu.\n", index);
							}
							else {
								printf("Loop wasn't created.\n");
							}
						}
						else {
							printf("Nothing to loop");
						}
						break;


					case ISLOOPED:
						if (list->head) {
							if (isLooped(list)) {
								printf("List is looped.\n");
							}
							else {
								printf("List isn't looped.\n");
							}
						}
						else {
							printf("Nothing to check.\n");
						}
						break;


					case BREAKELOOP:
						if (list->head) {
							breakLoop(list);
							printf("Loop was broken.\n");
						}
					}
				}
				else {
					printf("You can't interact with the list if it doesn't exist. Create it for beginning.\n");
				}
			}
		}
		else {
			while ((x = getchar()) != EOF && x != '\n');
			printf("Incorrect input.\n");
		}
		printf("\n\n");
	}
}