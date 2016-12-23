#include <string.h>
int main()
{
    char s1[100],s2[100];
    strcpy(s1,"hello"); /* copy "hello" into s1 */
    strcpy(s2,s1);      /* copy s1 into s2 */
    return 0;
}