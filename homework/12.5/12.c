#include "stdio.h"
#include "stdlib.h"
#include "string.h"


int push_in_end_of_list(int *list, int size) {
    for(int i = 0; i < size; i++) {
        if(list[i] == -1) {
            return i;
        }
    }
    return size;
}

void insert_in_start_of_list(int *list, int size, int value) {
    for(int i = size - 1; i > 0; i--) {
        list[i] = list[i - 1];
    }
    list[0] = value;
}

void remove_start_of_list(int *list, int size) {
    for(int i = 0; i < size - 1; i++) {
        list[i] = list[i + 1];
    }
    list[size - 1] = -1;
}

void remove_end_of_list(int *list, int size) {
    for(int i = size - 1; i >= 0; i--) {
        if(list[i] != -1) {
            list[i] = -1;
            break;
        }
    }
}

int main() {
    int list[10000];
    for(int i = 0; i < 10000; i++) {
        list[i] = -1;
    }
    
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        int input;
        scanf("%d", &input);
        
        if(input == 1) {
            int value;
            scanf("%d", &value);
            int pos = push_in_end_of_list(list, 10000);
            if(pos < 10000) {
                list[pos] = value;
            }
        } else if(input == 2) {
            int value;
            scanf("%d", &value);
            insert_in_start_of_list(list, 10000, value);
        } else if(input == 3) {
            remove_start_of_list(list, 10000);
        } else if(input == 4) {
            remove_end_of_list(list, 10000);
        } else if(input == 5) {
            for(int j = 0; j < 10000; j++) {
                if(list[j] != -1) {
                    printf("%d\n", list[j]);
                    break;
                }
            }
        }
    }
    
    return 0;
}