#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node;

typedef struct LinkedList {
	size_t length;	
	Node * head;
} LinkedList;

LinkedList * createLinkedList() {
	LinkedList * list = (LinkedList *)calloc(1, sizeof(LinkedList));
	if (list) {
		list->length = 0;
		list->head = NULL;
		return list;
	}
	else {
		return NULL;
	}
}

Node * createNode(int value) {
	Node * node = (Node *)calloc(1, sizeof(Node));
	if (node) {
		node->value = value;
		node->next = NULL;
		return node;
	}
	else {
		return NULL;
	}
}

int insertToBeginning(LinkedList * list, int value) {
	if (list) {
		Node * node = createNode(value);
		if (node) {
			node->next = list->head;
			list->head = node;
			list->length++;
			return 1;
		}
		else {
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int insertToEnd(LinkedList * list, int value) {
	if (list) {
		Node * node = createNode(value);
		if (node) {
			if (list->head) {
				Node * lastNode = list->head;
				while (lastNode->next != NULL) {
					lastNode = lastNode->next;
				}
				lastNode->next = node;
				list->length++;
				return 1;
			}
			else {
				list->head = node;
				list->length++;
			}
		}
		else {
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int insertAfterIndex(LinkedList * list, int value, size_t index) {
	if (list) {
		if (index <= list->length) {
			Node * node = createNode(value);
			if (node) {
				Node * currentNode = list->head;
				for (int i = 1; i < index; i++) {
					currentNode = currentNode->next;
				}
				node->next = currentNode->next;
				currentNode->next = node;
				list->length++;
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int insertAfterPointer(LinkedList * list, int value, Node * prevNode) {
	if (list) {
		Node * currentNode = list->head;
		Node * node = createNode(value);
		if (node) {
			while (currentNode) {
				if (currentNode == prevNode) {
					node = currentNode->next;
					currentNode->next = node;
					list->length++;
					return 1;
				}
			}
			return 0;
		}
		else {
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

size_t deleteElementByValue(LinkedList * list, int value) {
	if (list) {
		Node * currentNode = list->head;
		Node * prevNode = list->head;
		size_t count = 0;
		while (currentNode) {
			if (currentNode->value == value) {
				if (currentNode == list->head) {
					list->head = currentNode->next;
					free(currentNode);
					currentNode = list->head;
				}
				else {
					prevNode->next = currentNode->next;
					free(currentNode);
					currentNode = prevNode->next;
				}
				list->length--;
				count++;
			}
			else {
				prevNode = currentNode;
				currentNode = currentNode->next;
			}
		}
		return count;
	}
	else
	{
		return 0;
	}
}

int deleteElementByIndex(LinkedList * list, size_t index) {
	if (list) {
		if (index <= list->length && index > 0) {
			size_t currentIndex = 1;
			Node * currentNode = list->head;
			Node * prevNode = list->head;
			while (currentIndex != index) {
				prevNode = currentNode;
				currentNode = currentNode->next;
				currentIndex++;
			}
			if (index == 1) {
				list->head = currentNode->next;
			}
			else {
				prevNode->next = currentNode->next;
			}
			free(currentNode);
			list->length--;
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

void printLinkedList(LinkedList * list) {
	if (list) {
		if (list->head) {
			Node * currentNode = list->head;
			size_t index = 1;
			while (currentNode) {
				printf("%zu. %d\n", index, currentNode->value);
				index++;
				currentNode = currentNode->next;
			}
		}
		else {
			printf("Sorry, but list doesn't have nodes.\n");
		}
	}
	else
	{
		printf("List doesn't exist.\n");
	}
}

void deleteList(LinkedList ** list) {
	if (*list) {
		Node * currentNode = (*list)->head;
		Node * prevNode;
		while (currentNode) {
			prevNode = currentNode;
			currentNode = currentNode->next;
			free(prevNode);
		}
		free(*list);
		*list = NULL;
	}
}

void freeLinkedList(LinkedList * list) {
	if (list) {
		Node * currentNode = list->head;
		while (currentNode) {
			list->head = currentNode->next;
			free(currentNode);
			currentNode = list->head;
		}
	}
}

void reverseLinkedList(LinkedList * list) {
	if (list) {
		if (list->head->next) {
			Node * currentNode = list->head;
			Node * nextNode = currentNode->next;
			Node * prevNode = NULL;
			while (nextNode) {
				currentNode->next = prevNode;
				prevNode = currentNode;
				currentNode = nextNode;
				nextNode = nextNode->next;
			}
			currentNode->next = prevNode;
			list->head = currentNode;
		}
	}
}

int loopLinkedList(LinkedList * list, size_t index) {
	if (list) {
		if (index < list->length + 1 && index > 0) {
			Node * currentNode = list->head;
			size_t	currentIndex = 1;
			Node * beginningOfLoop = NULL;
			while (currentNode->next) {
				if (currentIndex == index) {
					beginningOfLoop = currentNode;
				}
				else {
					currentIndex++;
				}
				currentNode = currentNode->next;
			}

			if (beginningOfLoop) {
				currentNode->next = beginningOfLoop;
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int isLooped(LinkedList * list) {
	if (list) {
		Node * runner1 = list->head;
		Node * runner2 = list->head;
		int flag = 0;
		while (1) {
			if (!runner1) {
				return 0;
				break;
			}
			else {
				if (runner1 == runner2) {
					if (flag == 1) {
						return 1;
						break;
					}
					else {
						flag++;
					}
				}
				runner1 = runner1->next;
				if (!runner1) {
					return 0;
					break;
				}
				else {
					runner1 = runner1->next;
				}
				runner2 = runner2->next;
			}
		}
	}
}

void breakLoop(LinkedList * list) {
	if (list) {
		Node * currentNode = list->head;
		size_t currentIndex = 1;
		while (currentIndex != list->length) {
			currentIndex++;
			currentNode = currentNode->next;
		}
		currentNode->next = NULL;
	}
}