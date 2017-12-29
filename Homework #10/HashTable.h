#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef void(*iterateFunc)(char *, long);
typedef long(*hashFunc)(int size, char *);

typedef struct Node {
	char *key;
	long value;
	struct Node *next;
} Node;

typedef struct LinkedList {
	size_t length;
	Node * head;
} LinkedList;

typedef struct HashTable {
	LinkedList ** table;
	size_t size;
	hashFunc hash;
	size_t amount;
} HashTable;

Node * createNode(char *key, long value) {
	Node * node = (Node *)calloc(1, sizeof(Node));
	if (node) {
		node->key = key;
		node->value = value;
		node->next = NULL;
		return node;
	}
	else {
		return NULL;
	}
}

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

Node * getNodeByKey(LinkedList * list, char *key) {
	if (list) {
		Node * currNode = list->head;
		while (currNode) {
			if (!strcmp(key, currNode->key)) {
				return currNode;
			}
			else {
				currNode = currNode->next;
			}
		}
		return NULL;		
	}
	return NULL;
}

long getValueByKey(LinkedList * list, char *key) {
	if (list) {
		Node * currNode = list->head;
		while (currNode) {
			if (!strcmp(currNode->key, key)) {
				return currNode->value;
			}
			else {
				currNode = currNode->next;
			}
		}
		return 0;
	}
	return 0;
}

int insertToEnd(LinkedList * list, char *key, long value) {
	Node * node = createNode(key, value);
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

void freeLinkedList(LinkedList * list) {
	if (list) {
		Node * currNode = list->head;
		while (currNode) {
			list->head = currNode->next;
			free(currNode->key);
			free(currNode);
			currNode = list->head;
		}
	}
}

HashTable * createHashTable(size_t size, hashFunc hashFunction) {
	HashTable * hashTable = (HashTable *)calloc(1, sizeof(HashTable));
	if (hashTable) {
		hashTable->table = (LinkedList **)calloc(size, sizeof(LinkedList *));
		if (hashTable->table) {
			for (size_t i = 0; i < size; i++) {
				hashTable->table[i] = createLinkedList();
				if (!hashTable->table[i]) {
					return NULL;
				}
			}
			hashTable->size = size;
			hashTable->hash = hashFunction;
			hashTable->amount = 0;
			return hashTable;
		}
		else {
			return NULL;
		}
	}
	else {
		return NULL;
	}
}

void clearHashTable(HashTable * hashTable) {
	if (hashTable) {
		if (hashTable->table) {
			for (size_t i = 0; i < hashTable->amount; i++) {
				freeLinkedList(hashTable->table[i]);
			}
		}
	}
}

void freeHashTable(HashTable * hashTable) {
	if (hashTable) {
		if (hashTable->table) {
			for (size_t i = 0; i < hashTable->size; i++) {
				freeLinkedList(hashTable->table[i]);
				free(hashTable->table[i]);
			}
			free(hashTable->table);
		}
		free(hashTable);
	}
}

int insertData(HashTable * hashTable, char *key, long value) {
	long hash = hashTable->hash(hashTable->size, key);
	Node * node = getNodeByKey(hashTable->table[hash], key);
	if (node) {
		node->value += value;
		free(key);
		return 1;
	}
	else {
		if (insertToEnd(hashTable->table[hash], key, value)) {
			hashTable->amount++;
			return 1;
		}
		else {
			return 0;
		}
	}
}

long getValue(HashTable * hashTable, char *key) {
	if (hashTable) {
		long hash = hashTable->hash(hashTable->size, key);
		return getValueByKey(hashTable->table[hash], key);
	}
}

void iterate(HashTable * hashTable, iterateFunc iterateFunction) {
	if (hashTable) {
		if (hashTable->table) {
			for (size_t i = 0; i < hashTable->size; i++) {
				if (hashTable->table[i]) {
					Node * currNode = hashTable->table[i]->head;
					while (currNode) {
						iterateFunction(currNode->key, currNode->value);
						currNode = currNode->next;
					}
				}
			}
		}
	}
}

long maxListLength(HashTable * hashTable) {
	long max = 0;
	for (long i = 0; i < hashTable->size; i++) {
		if (hashTable->table[i]->length > max) {
			max = hashTable->table[i]->length;
		}
	}
	return max;
}

long minListLength(HashTable * hashTable) {
	long min = 0;
	if (hashTable->size > 0) {
		min = hashTable->amount;
		for (long i = 0; i < hashTable->size; i++) {
			if ((hashTable->table[i]->length < min) && (hashTable->table[i]->length > 0)) {
				min = hashTable->table[i]->length;
			}
		}
	}
	return min;
}

long numOfEmptyLists(HashTable * hashTable) {
	long num = 0;
	for (long i = 0; i < hashTable->size; i++) {
		if (!hashTable->table[i]->length) {
			num++;
		}
	}
	return num;
}

long numOfNotEmptyLists(HashTable * hashTable) {
	long num = 0;
	for (long i = 0; i < hashTable->size; i++) {
		if (hashTable->table[i]->length) {
			num++;
		}
	}
	return num;
}

char * mostFrequentKey(HashTable * hashTable) {
	if (hashTable) {
		if (hashTable->table) {
			if (hashTable->amount > 0) {
				long max = 0;
				char *fKey = NULL;
				for (size_t i = 0; i < hashTable->size; i++) {
					if (hashTable->table[i]->head) {
						Node * currNode = hashTable->table[i]->head;
						while (currNode) {
							if (currNode->value > max) {
								max = currNode->value;
								fKey = currNode->key;
							}
							currNode = currNode->next;
						}
					}
				}
				return fKey;
			}
			return NULL;
		}
		return NULL;
	}
	return NULL;
}

void printHashTableStats(HashTable * hashTable) {
	printf("Size: %li \n", hashTable->size);
	printf("Num of keys: %li \n", hashTable->amount);
	printf("Num of empty lists: %li \n", numOfEmptyLists(hashTable));
	printf("Num of not empty lists: %li \n", numOfNotEmptyLists(hashTable));
	printf("Max list length: %li \n", maxListLength(hashTable));
	printf("Min list length: %li \n", minListLength(hashTable));
	printf("Average list length: %lf \n", (double)hashTable->amount / (double)numOfNotEmptyLists(hashTable));
	char *mfk = mostFrequentKey(hashTable);
	printf("Most frequent word: %s\n", mfk);
}