#include <stdio.h>
#include <math.h>

int main ()
{
   double x, ret;
   x = 11524;
  
   /* finding value of log1010000 */
   ret = log10(x);
   printf("log10(%lf) = %lf\n", x, ret);
   
   return(0);
}