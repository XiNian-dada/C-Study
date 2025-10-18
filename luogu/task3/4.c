/*
4. P1068 [NOIP 2009 普及组] 分数线划定
https://www.luogu.com.cn/problem/P1068
*/
#include <stdio.h>

typedef struct{
    int id;
    int score;
} Student;

int main(){
    int n;
    int temp;
    int entered_num;
    
    scanf("%d %d", &n,&temp);
    entered_num = (temp*15)/10 - 1;
    Student student[n];

    for (int i = 0; i<=n-1; i++){
        scanf("%d %d", &student[i].id, &student[i].score);
    }
    for(int i=0;i<n;i++){
        int max = i;
        for (int j = i+1;j<n;j++){
            if (student[j].score > student[max].score ||
            (student[j].score == student[max].score && student[j].id < student[max].id)){
                max = j;
            }
        }
        Student temp_student;
        temp_student = student[i];
        student[i] = student[max];
        student[max] = temp_student;

    }
    int score_cut = student[entered_num].score;
    int passed_num = 0; 
    for (int i = 0; i<n; i++){
        if (student[i].score >= score_cut){
            passed_num++;
        }
    }

    printf("%d %d\n",score_cut, passed_num);
    for (int i = 0; i<passed_num; i++){
        printf("%d %d\n", student[i].id, student[i].score);
    }


}