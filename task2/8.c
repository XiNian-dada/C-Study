#include <stdio.h>
int main() {
    char input;
    int alphabet[26] = {0};
    int max = 0;
    while (scanf("%c", &input) != EOF){
        switch (input){
            case 'A':
                 alphabet[0]++;
                 break;
            case 'B':
                 alphabet[1]++;
                 break;
            case 'C':
                 alphabet[2]++;
                 break;
            case 'D':
                 alphabet[3]++;
                 break;
            case 'E':
                 alphabet[4]++;
                 break;
            case 'F':
                 alphabet[5]++;
                 break;
            case 'G':
                 alphabet[6]++;
                 break;
            case 'H':
                 alphabet[7]++;
                 break;
            case 'I':
                 alphabet[8]++;
                 break;
            case 'J':
                 alphabet[9]++;
                 break;
            case 'K':
                 alphabet[10]++;
                 break;
            case 'L':
                 alphabet[11]++;
                 break;
            case 'M':
                 alphabet[12]++;
                 break;
            case 'N':
                 alphabet[13]++;
                 break;
            case 'O':
                 alphabet[14]++;
                 break;
            case 'P':
                 alphabet[15]++;
                 break;
            case 'Q':
                 alphabet[16]++;
                 break;
            case 'R':
                 alphabet[17]++;
                 break;
            case 'S':
                 alphabet[18]++;
                 break;
            case 'T':
                 alphabet[19]++;
                 break;
            case 'U':
                 alphabet[20]++;
                 break;
            case 'V':
                 alphabet[21]++;
                 break;
            case 'W':
                 alphabet[22]++;
                 break;
            case 'X':
                 alphabet[23]++;
                 break;
            case 'Y':
                 alphabet[24]++;
                 break;
            case 'Z':
                 alphabet[25]++;
                 break;
        }
    }
    
    for (int i = 0; i < 26; i++){
        if (alphabet[i] > max){
            max = alphabet[i];
        }
    }


    for (int i = max; i > 0; i--) {
        for (int j = 0; j < 26; j++) {
            if (alphabet[j] >= i) {
                printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    
    for (int i = 0; i < 26; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    return 0;
}