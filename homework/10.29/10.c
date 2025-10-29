#include <stdio.h>
/*
 * 题目描述：判断某个日期是该年第几天
 * 
 * 输入：
 * - 第1行: 整数n, 表示测试数据的组数
 * - 随后n行: 每行包含3个整数year, month, day, 以空格隔开
 * 
 * 输出：
 * - n行: 每行一个整数，表示该日期在当年中的第几天
 * 
 * 要求：
 * - 计算给定日期是该年的第几天
 * - 需要考虑闰年情况
 * 
 * 闰年规则：
 * - 能被4整除但不能被100整除的年份为闰年
 * - 能被400整除的年份为闰年
 * 
 * 示例：
 * 输入: 
 * 3
 * 2016 1 1
 * 2016 3 1
 * 2015 12 12
 * 输出:
 * 1
 * 61
 * 346
 * 
 * 解释:
 * 2016年1月1日: 第1天
 * 2016年3月1日: 31(1月) + 29(2月闰年) + 1(3月) = 61天
 * 2015年12月12日: 前11个月天数之和 + 12 = 346天
 * 
 * 约束：
 * - 输入日期保证合法有效
 * - 年份为合理范围
 */
int is_leap(int year){ //判断闰年方法
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0){
        return 1;
    }
    else{
        return 0;
    }
}
int days_in_month(int month,int is_leap){ //返回每个月的天数
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
        int days_sum = days[i]; //天数之和先等于这个月已过的天数
        int is_leap_year = is_leap(temp_year); //计算是否为闰年
        for (int j = 1; j < months[i]; j++){ //逐月相加
            days_sum += days_in_month(j,is_leap_year);
            
        }
    printf("%d\n", days_sum);
    }
}