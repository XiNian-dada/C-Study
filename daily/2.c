//判断艺人是否通过考验
//观众投票，谁大谁赢，一定为奇数，不存在相等
//评委评分，谁满分谁赢，0为投a,1为投b
#include <stdio.h>
int main()
{    
    int vote1,vote2,n1,n2,n3;
    scanf("%d %d\n%d %d %d", &vote1, &vote2, &n1, &n2, &n3);
    int total_n = n1 + n2 + n3;
    if (vote1 > vote2 || total_n == 0){
        printf("The winner is a: %d + %d", vote1, total_n);
    }else if (vote2 > vote1 || total_n == 3){
        printf("The winner is b: %d + %d", vote2, 3);
    }
    return 0;
}