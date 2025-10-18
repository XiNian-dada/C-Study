#include <stdio.h>
struct student{
    int id;
    double score_1;
    double score_2;
};
int main() {
    int x;
    struct student student[1000];
    scanf("%d", &x);
    for (int i = 1 ; i <= x; i++){
        scanf("%d %lf %lf", &student[i].id, &student[i].score_1, &student[i].score_2);
    }
    for (int i = 1; i <= x; i++){
        if ((student[i].score_1*7 + student[i].score_2*3)>=800 && (student[i].score_2+student[i].score_1)>140){
            printf("%s\n","Excellent");
        }else {
            printf("%s\n","Not excellent");
        }
    }
}

