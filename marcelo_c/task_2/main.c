#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int num;
    int numbers[1000];
    int count = 0;
    for (int i = 0; i < 1000; i++)
    {
        numbers[i] = 0;
    }
    while (scanf("%d;", &num) != EOF)
    {
        ++count;
        if (count >= 3 && count <= 9)
            numbers[num]++;
        if (count == 16)
        {
            count = 0;
        }
    }
    int max1 = 0, max2 = 0, max3 = 0;
    for (int i = 0; i < 1000; i++)
    {
        if (numbers[i] != 0){
            if(numbers[i] > numbers[max1]){
                max3 = max2;
                max2 = max1;
                max1 = i;
                
            }
            else if(numbers[i] > numbers[max2]){
                max3 = max2;
                max2 = i;
            }
            else if(numbers[i] > numbers[max3]){
                max3 = i;
            }
        }
    }
    printf("%d\n%d\n%d\n", max1, max2, max3);
}