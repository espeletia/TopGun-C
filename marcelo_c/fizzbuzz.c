#include <stdio.h>



int main() {
    /* 
    print fizz if divisible by 3;
    print buzz if divisible by 5;
    print fizzbuzz if both;
    otherwise print the number;
    */

   for (int i = 1; i <= 100; i++)
   {
        if(i % 3 == 0 && i % 5 == 0)
            printf("fizzbuzz, ");
        else if(i % 3 == 0)
            printf("fizz, ");
        else if(i % 5 == 0)
            printf("buzz, ");
        else
            printf("%d, ", i);
        
   }
   

}