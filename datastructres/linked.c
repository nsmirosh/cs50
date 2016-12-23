#include <stdio.h>
#include <stdlib.h>



typedef struct _node {
	int value;
	struct _node *next;
} node;


node* head = NULL;

int main()
{
	void insertFirst(int valueToInsert);
	node* delete(int valueToRemove);
	void traverse();
	node* deleteFirst();
	node* find(int valueToFind);
	int length();

	insertFirst(5);
	insertFirst(8);
	insertFirst(10);
	insertFirst(99);
	insertFirst(20);
	insertFirst(55);


	printf("after insertion!\n");


	traverse();
	printf("length = %i\n", length());


	printf("after insertion!\n");



	node *deletedFirst = deleteFirst();
	printf("deletedFirst value = %i\n", deletedFirst -> value);

	node *deleted = delete(99);
	printf("deleted value = %i\n", deleted -> value);

	traverse();


	node* valueToFind = find(324);

	if (valueToFind == NULL) {
		printf("value not found\n");
	}

	node* valueToFind1 = find(20);
	printf("valueToFind = %i\n", valueToFind1 -> value);

}


void insertFirst(int valueToInsert) {


	node * toInsert = malloc(sizeof(node));

	if (toInsert == NULL) {
		printf("crap!\n");
		return;
	}

	toInsert -> value  = valueToInsert;
	toInsert -> next = head;
	head = toInsert;
}

node * deleteFirst() {
	node *temp = head;
	head = head -> next;
	return temp;
}


node* find(int valueToFind) {

	node* current = head;

	// if the start is null then nothing to do here
	if (current == NULL) {
		return NULL;
	}

	while (current -> value != valueToFind) {
		//if it is last node
		if (current -> next == NULL) {
			return NULL;
		}
		else {
			current = current -> next;
		}
	}

	return current;

}

node* delete(int valueToRemove) {

	node* current = head;
	node* previous = NULL;

	if (current == NULL) {
		return NULL;
	}

	while (current -> value != valueToRemove) {
		//if it is last node
		if (current -> next == NULL) {
			return NULL;
		}
		else {
			previous  = current;
			current = current -> next;
		}
	}

	if (current == head) {
		head = head -> next;
	}
	else {
		previous -> next = current -> next;
	}

	return current;
}




void traverse() {
	node* traversalPointer = head;
	printf("[");
	while (traversalPointer != NULL) {
		printf("%i, ", traversalPointer -> value);
		traversalPointer = traversalPointer -> next;

	}
	printf("]\n");
}


int length() {
	int length = 0;

	for  (node* traversalPointer = head; traversalPointer != NULL; traversalPointer = traversalPointer -> next, length++);
	return length;
}



