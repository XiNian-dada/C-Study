#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[3];
    int result = 0;
    
    scanf("%d %d %d", &arr[0], &arr[1], &arr[2]);
    int* first_ptr = arr;
    for (int i = 0; i<3 ;i++){
        int temp = 1;
        for (int j = 0 ; j<3 ;j++){
            temp = temp * *first_ptr;
        }
        first_ptr++;
        result = result + temp;
    }
    printf("%d",result);
}