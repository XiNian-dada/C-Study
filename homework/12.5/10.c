#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "ctype.h"
/*
 * 题目描述：纪念日时间差计算
 * 
 * 难度：简单
 * 
 * 输入：
 * - 第1行：4个整数 start_month start_day start_hour start_minute
 *   表示开始时间的月、日、时、分
 * - 第2行：4个整数 end_month end_day end_hour end_minute
 *   表示结束时间的月、日、时、分
 * 
 * 输出：
 * - 一个整数：两个时间节点之间相差的分钟数
 * 
 * 条件：
 * 1. 第一行的时间早于第二行的时间
 * 2. 时间表示均合法
 * 3. 小时按照24小时制表示
 * 4. 时间均在2024年内
 * 5. 需要计算开始时间到结束时间的时间差（分钟数）
 * 
 * 2024年月份天数：
 * 1月：31天
 * 2月：29天（2024年是闰年）
 * 3月：31天
 * 4月：30天
 * 5月：31天
 * 6月：30天
 * 7月：31天
 * 8月：31天
 * 9月：30天
 * 10月：31天
 * 11月：30天
 * 12月：31天
 * 
 * 计算方法：
 * 1. 将两个时间都转换为从2024年1月1日00:00开始的分钟数
 * 2. 计算两个时间的分钟数差值
 * 
 * 转换步骤：
 * 总分钟数 = (累计天数)×24×60 + 小时×60 + 分钟
 * 累计天数 = 之前月份的总天数 + 当前日期-1（因为1月1日是第0天）
 * 
 * 示例1：
 * 输入:
 * 4 1 21 21
 * 4 1 21 22
 * 输出:
 * 1
 * 
 * 解释:
 * 同一天内，小时相同，分钟差1分钟
 * 
 * 示例2：
 * 输入:
 * 6 30 23 49
 * 7 1 6 30
 * 输出:
 * 401
 * 
 * 解释:
 * 6月30日23:49到7月1日6:30
 * 6月30日剩余时间：23:49到24:00 = 11分钟
 * 7月1日时间：0:00到6:30 = 390分钟
 * 总计：11 + 390 = 401分钟
 * 
 * 验证：
 * 6月30日23:49到7月1日0:00：11分钟
 * 7月1日0:00到6:30：6×60+30=390分钟
 * 总计：401分钟
 * 
 * 约束：
 * - 时间均在2024年内
 * - 开始时间早于结束时间
 * - 需要处理跨天、跨月的情况
 * - 不需要考虑秒
 * - 结果为正整数
 * 
 * 实现提示：
 * 1. 定义月份天数数组：int days[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31}
 * 2. 计算每个时间从1月1日开始的累计天数
 * 3. 转换为分钟数比较
 * 4. 使用long long避免溢出
 */
int how_many_days_in_month(int month){
    switch(month){
        case 0: return 0;
        case 1: return 31;
        case 2: return 29 + how_many_days_in_month(month-1);
        case 3: return 31 + how_many_days_in_month(month-1);
        case 4: return 30 + how_many_days_in_month(month-1);
        case 5: return 31 + how_many_days_in_month(month-1);
        case 6: return 30 + how_many_days_in_month(month-1);
        case 7: return 31 + how_many_days_in_month(month-1);
        case 8: return 31 + how_many_days_in_month(month-1);
        case 9: return 30 + how_many_days_in_month(month-1);
        case 10: return 31 + how_many_days_in_month(month-1);
        case 11: return 30 + how_many_days_in_month(month-1);
        case 12: return 31 + how_many_days_in_month(month-1);
    } 
}
int trans_into_min(int month,int day,int hour,int minutes){
    int days = day + how_many_days_in_month(month-1);
    return days * 24 * 60 + hour * 60 + minutes;
}
int main(){
    int month,day,hour,minutes;
    int all_min_1 = 0;
    int all_min_2 = 0;
    scanf("%d %d %d %d",&month,&day,&hour,&minutes);
    all_min_1 = trans_into_min(month,day,hour,minutes);
    scanf("%d %d %d %d",&month,&day,&hour,&minutes);
    all_min_2 = trans_into_min(month,day,hour,minutes);
    printf("%d",abs(all_min_1 - all_min_2));

}

