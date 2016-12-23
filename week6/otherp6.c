
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{


	typedef struct
	{
		char name[21];
		char city[21];
		char phone[21];
		char *comment;
	} Addr;
	Addr *s;
	char comm[100];

	s = (Addr *)malloc(sizeof(Addr));
	gets(s->name, 20);
	gets(s->city, 20);
	gets( s->phone, 20);
	gets(comm, 100);
	s->comment =
	    (char *)malloc(sizeof(char[strlen(comm) + 1]));
	strcpy(s->comment, comm);
}