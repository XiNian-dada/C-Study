#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int is_leap_year(int year){ 
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
char* get_name(int month){
  switch(month){
    case 1: return "January";
    case 2: return "February";
    case 3: return "March";
    case 4: return "April";
    case 5: return "May";
    case 6: return "June";
    case 7: return "July";
    case 8: return "August";
    case 9: return "September";
    case 10: return "October";
    case 11: return "November";
    case 12: return "December";
  }
}
int get_days_in_month(int month,int year){
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
      return is_leap_year(year) ? 29 : 28; 
  }
}
int is_valid_in_type(int year,int month,int days){
  return year >= 2000 && year <= 2099 && month >= 1 && month <= 12 && days >= 1 && days <= get_days_in_month(month,year);
}
int get_days_since_1900(int year, int month, int days) {
    int total_days = 0;
    for (int i = 1900; i < year; i++) {
        total_days += is_leap_year(i) ? 366 : 365;
    }
    for (int i = 1; i < month; i++) {
        total_days += get_days_in_month(i, year);
    }
    total_days += days;
    return total_days;
}
int main(){
  int a,b,c;
  scanf("%d/%d/%d",&a,&b,&c);
  //YYMMDD
  int valid_1 = is_valid_in_type(a+2000,b,c);
  //MMDDYY
  int valid_2 = is_valid_in_type(c+2000,a,b);
  if(valid_1 && !valid_2){
    printf("%s %d, %d\n",get_name(b),c,a+2000);
  }else if(valid_2 && !valid_1){
    printf("%s %d, %d\n",get_name(a),b,c+2000);
  }else if(valid_1 == 1 && valid_2 == 1){
    if(a+2000 == c+2000 && b == a && c == b){
      printf("%s %d, %d\n",get_name(a),b,c+2000);
      return 0;
    }
    int day_1 = get_days_since_1900(a+2000,b,c);
    int day_2 = get_days_since_1900(c+2000,a,b);
    printf("%d",abs(day_1-day_2));
  }

}
