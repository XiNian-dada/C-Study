#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "ctype.h"

typedef struct{
    char name[51];
    int score;
    int goal_diff;
} team;
team* teams;
int n;
/*
 * 题目描述：循环赛排名
 * 
 * 难度：困难-
 * 
 * 输入：
 * - 第1行：偶数n（2 ≤ n ≤ 1000），表示队伍数量
 * - 接下来n行：每行一个队伍名称（包含字母、数字和空格，长度≤50）
 * - 接下来n(n-1)/2行：每行表示一场比赛结果
 *   格式：name1-name2: score1-score2
 *   其中：在:,-前后可能有若干空格
 *   每场得分不超过100分
 * 
 * 输出：
 * - 输出获奖队伍的名称（名次在n/2及以内的队伍）
 * - 按名次从前到后输出
 * - 名次相同的队伍，按队名字典序输出
 * 
 * 排名规则：
 * 1. 获奖条件：名次 ≤ n/2（含）
 * 2. 排名依据（优先级从高到低）：
 *    a) 积分：胜3分，平1分，负0分
 *    b) 净得分：总得分 - 总失分
 *    c) 如果积分和净得分都相同，则名次相同
 * 3. 名次分配规则：
 *    - 第1名给排名最高的队伍
 *    - 如果某个名次有x支队伍并列，则跳过后续x-1个名次
 *    - 例如：第1名有1队，第2名有2队并列，则下一名次是第4名
 * 
 * 示例：
 * 输入:
 * 4
 * Team1
 * Team2
 * Team3
 * Team4
 * Team1-Team2:2-0
 * Team1-Team3:3-1
 * Team1-Team4:4-2
 * Team2-Team3:3-2
 * Team2-Team4:2-0
 * Team3-Team4:3-1
 * 输出:
 * Team1
 * Team2
 * 
 * 解释:
 * n=4，获奖名次：前2名（4/2=2）
 * 比赛结果：
 * Team1：胜3场，积分9，得分9，失分3，净得分6
 * Team2：胜2场负1场，积分6，得分5，失分4，净得分1
 * Team3：胜1场负2场，积分3，得分6，失分8，净得分-2
 * Team4：负3场，积分0，得分3，失分8，净得分-5
 * 
 * 排名：
 * 第1名：Team1（积分9）
 * 第2名：Team2（积分6）
 * Team3和Team4名次在2名以外，不获奖
 * 
 * 排序过程：
 * 1. 按积分降序
 * 2. 积分相同按净得分降序
 * 3. 积分和净得分都相同的队伍名次相同
 * 4. 计算实际名次，考虑并列情况
 * 5. 输出名次≤n/2的队伍
 * 6. 名次相同的队伍按字典序输出
 * 
 * 约束：
 * - n为偶数，2≤n≤1000
 * - 队名长度≤50，包含字母、数字、空格
 * - 比赛场次：n(n-1)/2 ≤ 约500,000
 * - 每场得分≤100
 * - 需要处理队名中的空格
 * - 输入格式可能有额外空格
 * 
 * 算法：
 * 1. 读取队伍信息，建立名称到索引的映射
 * 2. 初始化队伍数据：积分、总得分、总失分
 * 3. 解析每场比赛，更新两队数据
 * 4. 计算净得分 = 总得分 - 总失分
 * 5. 排序：先按积分降序，再按净得分降序
 * 6. 确定实际名次，考虑并列
 * 7. 输出名次≤n/2的队伍，名次相同的按字典序排序
 */
int cmp(const void* a, const void* b){ 
    int score1 = ((team*)a)->score;
    int score2 = ((team*)b)->score;
    int goal_diff_1 = ((team*)a)->goal_diff;
    int goal_diff_2 = ((team*)b)->goal_diff;
    if(score1 > score2){
        return -1;
    }else if(score1 < score2){
        return 1;
    }else if(score1 == score2){
        if(goal_diff_1 > goal_diff_2){
            return -1;
        }else if(goal_diff_1 < goal_diff_2){
            return 1;
        }
    }
    return strcmp(((team*)a)->name, ((team*)b)->name);
}


void remove_space(char* s){
    if (s == NULL) return;
    int len = strlen(s);
    while(len > 0 && isspace(s[len-1])) {
        s[--len] = '\0';
    }
    int start = 0;
    while(s[start] != '\0' && isspace(s[start])) {
        start++;
    }
    if(start > 0) {
        memmove(s, s + start, len - start + 1);
    }
}

void proc_team(char* s){ 
    int mode = 0;
    char* token = strtok(s, ":");
    char score_part[110];
    char team_part[110];
    
    while (token != NULL){
        if(mode == 0){
            strcpy(team_part, token);
            remove_space(team_part); 
            mode = 1;
        }else if(mode == 1){
            strcpy(score_part, token);
            remove_space(score_part);
        }
        token = strtok(NULL, ":");
    }

    char team_name_1[100];
    char team_name_2[100];
    int t_index = 0;
    
    char* team_token = strtok(team_part, "-");
    while(team_token != NULL){
        remove_space(team_token); 
        if(t_index == 0){
            strcpy(team_name_1, team_token);
            t_index = 1;
        }else if(t_index == 1){
            strcpy(team_name_2, team_token);
        }
        team_token = strtok(NULL, "-");
    }

    int score_index = 0;
    int score_1 = 0;
    int score_2 = 0;
    char* score_token = strtok(score_part, "-");
    while(score_token != NULL){
        if(score_index == 0){
            score_1 = atoi(score_token);
            score_index = 1;
        }else if(score_index == 1){
            score_2 = atoi(score_token);
        }
        score_token = strtok(NULL, "-");
    }

    int tscore_1 = 0;
    int tscore_2 = 0;
    if(score_1 - score_2 > 0){
        tscore_1 = 3;
        tscore_2 = 0;
    }else if(score_1 - score_2 == 0){
        tscore_1 = 1;
        tscore_2 = 1;
    }else if(score_1 - score_2 < 0){
        tscore_1 = 0;
        tscore_2 = 3;
    }
    for(int i = 0; i < n; i++){
        if(strcmp(team_name_1, teams[i].name) == 0){
            teams[i].goal_diff += (score_1 - score_2);
            teams[i].score += tscore_1;
        }else if(strcmp(team_name_2, teams[i].name) == 0){
            teams[i].score += tscore_2;
            teams[i].goal_diff += (score_2 - score_1);
        }
    }
}

int main(){
    scanf("%d", &n);
    
    teams = (team*)malloc(n * sizeof(team));
    for(int i = 0; i < n; i++){
        teams[i].score = 0;
        teams[i].goal_diff = 0;
        
        scanf(" %[^\n]", teams[i].name); 
    }

    int line_num = n * (n - 1) / 2;
    for(int i = 0; i < line_num; i++){
        char temp[1000];

        scanf(" %[^\n]", temp); 
        proc_team(temp);
    }
    
    qsort(teams, n, sizeof(team), cmp);
    


    int actual_rank = 1;
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            if (teams[i].score != teams[i-1].score || teams[i].goal_diff != teams[i-1].goal_diff) {
                actual_rank = i + 1;
            }
        }
        
        if (actual_rank <= n / 2) {
            printf("%s\n", teams[i].name);
        } else {
            break;
        }
    }

    free(teams); 
    return 0;
}