#include <stdio.h>
#include <string.h>
int main()
{
    char s1[100],s2[100];
     gets(s1);
    gets(s2);
    if (strcmp(s1,s2)==0)
        printf("equal\n");
    else if (strcmp(s1,s2)<0)
        printf("s1 less than s2\n");
    else
        printf("s1 greater than s2\n");
    return 0;
}