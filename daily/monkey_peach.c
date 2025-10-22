#include <stdio.h>
/*
说是吉吉国王第一天让毛毛去摘了一些桃子，但是吉吉胃口大开，每天要吃一半才能
填满它的大卫带，然后黑心的资本家吉吉每天只给毛毛一个桃子
到了第N天，吉吉发现桃子只剩下一个了

求 第一天毛毛摘了多少桃子*/ 
int main (){
    int N;
    int total_peach = 1;
    scanf("%d", &N);
    for (int i =1;i < N; i++){
        total_peach = (total_peach +1)*2;
    }
    printf("%d", total_peach);
}