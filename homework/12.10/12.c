#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "math.h"

int is_left_alpha(char* s){
    int founded_eq = 0;
    int founded_alpha = 0;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] == '='){
            founded_eq = 1;
            break;
        }
        if(isalpha(s[i])){
            founded_alpha = 1;
            break;
        }
    }
    return founded_alpha && !founded_eq;
}

int main(){
    qsort()
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        char input[15];
        memset(input, '\0', sizeof(input));
        scanf("%s", input);

        double constant = 0.0;
        double coeff = 0.0;
        int flag = 1;
        int re_pos = 1;

        for(int j = 0; j < strlen(input); j++){ 
            if(input[j] == '='){
                re_pos = -1;
                flag = 1;
            }
            if(input[j] == '-'){
                flag = -1;
            }
            else if(input[j] == '+'){
                flag = 1;
            }
            else if(isdigit(input[j]) || (j == 0 && input[j] == '-')){
                double num = 0.0;  
                int k = j; 
                if (k == 0 && input[k] == '-') {
                    flag = -1;
                    k++;
                } else if (k > 0 && input[k] == '-') {
                    k++;
                }

                while(k < strlen(input) && isdigit(input[k])){
                    num = num * 10.0 + (input[k] - '0');
                    k++;
                }
                
                if (num == 0.0) { 
                     j = (input[j] == '-') ? j : k - 1;
                     continue;
                }

                j = k - 1; 

                if(j + 1 < strlen(input) && isalpha(input[j+1])){
                    coeff += num * (double)flag * re_pos;
                    j++;
                }
                else{
                    constant += num * (double)flag * (-re_pos); 
                }
            }
            else if(isalpha(input[j] )){
                if(j > 0 && isdigit(input[j-1])) continue;
                
                coeff += 1.0 * (double)flag * re_pos;
            }
            

            if(isdigit(input[j]) || isalpha(input[j])) {
                 flag = 1;
            }
        }
        
        char alphabet = '\0';
        for(int j = 0; j < strlen(input); j++){
            if(isalpha(input[j])){
                alphabet = input[j];
                break;
            }
        }
        
        printf("%c=%.6lf\n", alphabet, constant / coeff);
    }
    return 0;
}