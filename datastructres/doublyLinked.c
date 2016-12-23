#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct _node {
	int value;
	struct _node *next;
	struct _node *prev;
} node;


node* head = NULL;
node* last = NULL;
node* current = NULL;




int main()
{
	void insertFirst(int valueToInsert);
	void insertLast(int valueToInsert);
	bool insertAfter(int key, int newValue);


	node* delete(int valueToRemove);
	void printForward();
	void printBackward();

	node* deleteFirst();
	node* deleteLast();

	node* find(int valueToFind);
	int length();

	insertFirst(5);
	insertFirst(8);
	insertFirst(10);
	insertFirst(99);
	insertFirst(20);
	insertFirst(55);


	printBackward();

	printForward();


	insertLast(135);
	insertLast(255);

	printForward();

	deleteFirst();


	printForward();

	deleteLast();

	printForward();

	delete(99);

	printForward();
	delete(20);

	delete(135);
	printForward();

	insertAfter(10, 99999);

	printForward();

	printf("last element = %i\n", last -> value);


	insertAfter(5, 8000);



	printForward();












}


bool isEmpty() {
	return head == NULL;
}


void insertFirst(int valueToInsert) {
	node * toInsert = (node*) malloc(sizeof(node));

	if (toInsert == NULL) {
		printf("crap!\n");
		return;
	}

	toInsert -> value  = valueToInsert;
	toInsert -> prev = NULL;

	if (isEmpty()) {
		last = toInsert;
	}
	else {
		head -> prev = toInsert;
	}
	toInsert -> next = head;
	head = toInsert;
}


void insertLast(int valueToInsert) {
	node * toInsert = (node*) malloc(sizeof(node));

	if (toInsert == NULL) {
		printf("crap!\n");
		return;
	}

	toInsert -> value  = valueToInsert;
	toInsert -> next = NULL;

	if (isEmpty()) {
		head = toInsert;
	}
	else {
		last -> next = toInsert;
	}
	toInsert -> prev = last;
	last = toInsert;
}

void printForward() {
	node* traversalPointer = head;
	printf("[");
	while (traversalPointer != NULL) {
		printf("%i, ", traversalPointer -> value);
		traversalPointer = traversalPointer -> next;

	}
	printf("]\n");
}

void printBackward() {
	node* traversalPointer = last;
	printf("[");
	while (traversalPointer != NULL) {
		printf("%i, ", traversalPointer -> value);
		traversalPointer = traversalPointer -> prev;

	}
	printf("]\n");
}

node* deleteFirst() {
	node *temp = head;
	if (head -> next == NULL) {
		//if it was the only link
		last = NULL;
	}
	else {
		head -> next -> prev = NULL;
	}
	head = head -> next;
	return temp;
}

node* deleteLast() {
	node *temp = head;
	if (last -> prev == NULL) {
		//if it was the only link
		head = NULL;
	}
	else {
		last -> prev -> next = NULL;
	}
	last = last -> prev;
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

node* delete(int key) {

	node* current = head;
	// node* previous = NULL;

	if (current == NULL) {
		return NULL;
	}

	while (current -> value != key) {
		//if it is last node
		if (current -> next == NULL) {
			return NULL;
		}
		else {
			// previous  = current;
			current = current -> next;
		}
	}

	//found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      current->prev->next = current->next;
   }    

   if(current == last) {
      //change last to point to prev link
      last = current->prev;
   } else {
      current->next->prev = current->prev;
   }


	return current;
}

bool insertAfter(int key, int newValue) {

	//if list is empty
	if (head == NULL) {
		return false;
	}

	node* current = head;

	while (current -> value != key) {
		//if it is last node
		if (current -> next == NULL) {
			return false;
		}
		else {
			current = current -> next;
		}
	}

	node* toInsert = (node*) malloc(sizeof(node));

	if (toInsert == NULL) {
		printf("crap!\n");
		return false;
	}
	toInsert -> value = newValue;


	if (current == last) {

		toInsert -> next = NULL;
		last = toInsert;
	}
	else {
		toInsert -> next = current -> next;
		current -> next -> prev = toInsert;
	}

	toInsert -> prev = current;
	current -> next = toInsert;
	return true;
}


int length() {
	int length = 0;

	for  (node* traversalPointer = head; traversalPointer != NULL; traversalPointer = traversalPointer -> next, length++);
	return length;
}



