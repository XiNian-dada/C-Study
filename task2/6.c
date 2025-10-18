#include <stdio.h>
int main() { 
    char list_0_1[4]={'X','X','X','\0'};
    char list_0_2[4]={'X','.','X','\0'};
    char list_0_3[4]={'X','.','X','\0'};
    char list_0_4[4]={'X','.','X','\0'};
    char list_0_5[4]={'X','X','X','\0'};

    char list_1_1[4]={'.','.','X','\0'};
    char list_1_2[4]={'.','.','X','\0'};
    char list_1_3[4]={'.','.','X','\0'};
    char list_1_4[4]={'.','.','X','\0'};
    char list_1_5[4]={'.','.','X','\0'};

    char list_2_1[4]={'X','X','X','\0'};
    char list_2_2[4]={'.','.','X','\0'};
    char list_2_3[4]={'X','X','X','\0'};
    char list_2_4[4]={'X','.','.','\0'};
    char list_2_5[4]={'X','X','X','\0'};

    char list_3_1[4]={'X','X','X','\0'};
    char list_3_2[4]={'.','.','X','\0'};
    char list_3_3[4]={'X','X','X','\0'};
    char list_3_4[4]={'.','.','X','\0'};
    char list_3_5[4]={'X','X','X','\0'};

    char list_4_1[4]={'X','.','X','\0'};
    char list_4_2[4]={'X','.','X','\0'};
    char list_4_3[4]={'X','X','X','\0'};
    char list_4_4[4]={'.','.','X','\0'};
    char list_4_5[4]={'.','.','X','\0'};

    char list_5_1[4]={'X','X','X','\0'};
    char list_5_2[4]={'X','.','.','\0'};
    char list_5_3[4]={'X','X','X','\0'};
    char list_5_4[4]={'.','.','X','\0'};
    char list_5_5[4]={'X','X','X','\0'};

    char list_6_1[4]={'X','X','X','\0'};
    char list_6_2[4]={'X','.','.','\0'};
    char list_6_3[4]={'X','X','X','\0'};
    char list_6_4[4]={'X','.','X','\0'};
    char list_6_5[4]={'X','X','X','\0'};

    char list_7_1[4]={'X','X','X','\0'};
    char list_7_2[4]={'.','.','X','\0'};
    char list_7_3[4]={'.','.','X','\0'};
    char list_7_4[4]={'.','.','X','\0'};
    char list_7_5[4]={'.','.','X','\0'};

    char list_9_1[4]={'X','X','X','\0'};
    char list_9_2[4]={'X','.','X','\0'};
    char list_9_3[4]={'X','X','X','\0'};
    char list_9_4[4]={'.','.','X','\0'};
    char list_9_5[4]={'X','X','X','\0'};

    char list_8_1[4]={'X','X','X','\0'};
    char list_8_2[4]={'X','.','X','\0'};
    char list_8_3[4]={'X','X','X','\0'};
    char list_8_4[4]={'X','.','X','\0'};
    char list_8_5[4]={'X','X','X','\0'};
    
    int n;
    scanf("%d",&n);
    
    char input[100];
    scanf("%s", input);
    
    for(int row = 0; row < 5; row++) {
        for(int i = 0; i < n; i++) {
            char digit = input[i];
            switch(digit) {
                case '0':
                    if(row == 0) printf("%s", list_0_1);
                    else if(row == 1) printf("%s", list_0_2);
                    else if(row == 2) printf("%s", list_0_3);
                    else if(row == 3) printf("%s", list_0_4);
                    else if(row == 4) printf("%s", list_0_5);
                    break;
                case '1':
                    if(row == 0) printf("%s", list_1_1);
                    else if(row == 1) printf("%s", list_1_2);
                    else if(row == 2) printf("%s", list_1_3);
                    else if(row == 3) printf("%s", list_1_4);
                    else if(row == 4) printf("%s", list_1_5);
                    break;
                case '2':
                    if(row == 0) printf("%s", list_2_1);
                    else if(row == 1) printf("%s", list_2_2);
                    else if(row == 2) printf("%s", list_2_3);
                    else if(row == 3) printf("%s", list_2_4);
                    else if(row == 4) printf("%s", list_2_5);
                    break;
                case '3':
                    if(row == 0) printf("%s", list_3_1);
                    else if(row == 1) printf("%s", list_3_2);
                    else if(row == 2) printf("%s", list_3_3);
                    else if(row == 3) printf("%s", list_3_4);
                    else if(row == 4) printf("%s", list_3_5);
                    break;
                case '4':
                    if(row == 0) printf("%s", list_4_1);
                    else if(row == 1) printf("%s", list_4_2);
                    else if(row == 2) printf("%s", list_4_3);
                    else if(row == 3) printf("%s", list_4_4);
                    else if(row == 4) printf("%s", list_4_5);
                    break;
                case '5':
                    if(row == 0) printf("%s", list_5_1);
                    else if(row == 1) printf("%s", list_5_2);
                    else if(row == 2) printf("%s", list_5_3);
                    else if(row == 3) printf("%s", list_5_4);
                    else if(row == 4) printf("%s", list_5_5);
                    break;
                case '6':
                    if(row == 0) printf("%s", list_6_1);
                    else if(row == 1) printf("%s", list_6_2);
                    else if(row == 2) printf("%s", list_6_3);
                    else if(row == 3) printf("%s", list_6_4);
                    else if(row == 4) printf("%s", list_6_5);
                    break;
                case '7':
                    if(row == 0) printf("%s", list_7_1);
                    else if(row == 1) printf("%s", list_7_2);
                    else if(row == 2) printf("%s", list_7_3);
                    else if(row == 3) printf("%s", list_7_4);
                    else if(row == 4) printf("%s", list_7_5);
                    break;
                case '8':
                    if(row == 0) printf("%s", list_8_1);
                    else if(row == 1) printf("%s", list_8_2);
                    else if(row == 2) printf("%s", list_8_3);
                    else if(row == 3) printf("%s", list_8_4);
                    else if(row == 4) printf("%s", list_8_5);
                    break;
                case '9':
                    if(row == 0) printf("%s", list_9_1);
                    else if(row == 1) printf("%s", list_9_2);
                    else if(row == 2) printf("%s", list_9_3);
                    else if(row == 3) printf("%s", list_9_4);
                    else if(row == 4) printf("%s", list_9_5);
                    break;
            }
            
            if(i < n - 1) {
                printf(".");
            }
        }
        printf("\n");
    }
}