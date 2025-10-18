/*
3. P1928 外星密码（可能有点难）
https://www.luogu.com.cn/problem/P1928
*/
#include <stdio.h>

char s[10000];
int pos = 0;
void unzip(){
    while (s[pos] != '\0'){
        if (s[pos] == '['){
            pos++;
            int repeat_times = 0;
            while (s[pos] >= '0' && s[pos] <= '9'){
                repeat_times = repeat_times * 10 + (s[pos] - '0');
                pos++;
            }
            int saved_pos = pos;
            for (int i=0;i<repeat_times;i++){
                pos = saved_pos;
                unzip();
            }

        }
        else if (s[pos] != ']' && s[pos] != '['){
            putchar(s[pos]);
            pos++;
        }
        else if (s[pos] == ']'){
            pos++;
            return;
        }
    }
}

int main(){

    scanf("%s", s);
    
    unzip();
    return 0;
}