#include <stdio.h>
int main()
{
    int year;
    scanf("%d", &year);
    if (1582<= year && year <= 2020)
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
            printf("1");
        else
            printf("0");
    else printf("Not a valid year");
    return 0;
}