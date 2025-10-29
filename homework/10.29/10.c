#include <stdio.h>
int is_leap(int year){
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0){
        return 1;
    }
    else{
        return 0;
    }
}
int days_in_month(int month,int is_leap){
    switch(month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            if (is_leap == 1){
                return 29;
            } else{
                return 28;
            }
    }
}

int main(){
    int year[100],months[100],days[100];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf ("%d %d %d", &year[i], &months[i], &days[i]);
    }
    for (int i = 0; i < n; i++){
        int temp_year = year[i];
        int days_sum = days[i];
        int is_leap_year = is_leap(temp_year);
        for (int j = 1; j < months[i]; j++){
            days_sum += days_in_month(j,is_leap_year);
            
        }
    printf("%d\n", days_sum);
    }
}