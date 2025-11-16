#include "stdio.h"
#include "stdlib.h"

int checkndprint(int w, int l) {
    // 11分制正确结束条件：至少一人达到11分且分差≥2
    if ((w >= 11 || l >= 11) && abs(w - l) >= 2) {
        printf("%d:%d\n", w, l);
        return 1;
    }
    return 0;
}

int checkndprint21(int w, int l) {
    // 21分制正确结束条件：至少一人达到21分且分差≥2
    if ((w >= 21 || l >= 21) && abs(w - l) >= 2) {
        printf("%d:%d\n", w, l);
        return 1;
    }
    return 0;
}
void process_11(char list[], int start_pos, int len) {
    int i = start_pos;
    int w = 0, l = 0;
    
    while (i < len) {
        if (list[i] == 'W') {
            w++;
            i++;
            if (checkndprint(w, l)) {
                w = 0;
                l = 0;
            }
        }
        else if (list[i] == 'L') {
            l++;
            i++;
            if (checkndprint(w, l)) {
                w = 0;
                l = 0;
            }
        }
        else {
            i++; // 跳过非法字符
        }
    }
    // 输出最后一局未结束的比赛比分
    printf("%d:%d\n", w, l);
}

void process_21(char list[], int start_pos, int len) {
    int i = start_pos;
    int w = 0, l = 0;
    
    while (i < len) {
        if (list[i] == 'W') {
            w++;
            i++;
            if (checkndprint21(w, l)) {
                w = 0;
                l = 0;
            }
        }
        else if (list[i] == 'L') {
            l++;
            i++;
            if (checkndprint21(w, l)) {
                w = 0;
                l = 0;
            }
        }
        else {
            i++; // 跳过非法字符
        }
    }
    // 输出最后一局未结束的比赛比分
    printf("%d:%d\n", w, l);
}

int main() {
    char list[2502];
    int index = 0;
    
    while (1) {
        char c = getchar();
        if (c == EOF) {  // 添加EOF检查
            break;
        }
        if (c == '\n') {
            continue;
        }
        if (c == 'E') {
            break;
        }
        if (c == 'W' || c == 'L') {
            if (index < 2501) {  // 添加数组边界检查
                list[index++] = c;
            }
        }
    }
    
    process_11(list, 0, index);
    printf("\n");
    process_21(list, 0, index);
    
    return 0;
}