#include "stdio.h"
#include "stdlib.h"

void turn_90_matrix(char** s,int n,char** output){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            output[j][n-i-1] = s[i][j];
        }
    }
}
void reflect_in_y(char** s,int n,char** output){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            output[i][n-j-1] = s[i][j];
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    char** s = (char**)malloc(n*sizeof(char*));
    for(int i=0;i<n;i++){
        s[i] = (char*)malloc(n*sizeof(char));
    }
    char** output = (char**)malloc(n*sizeof(char*));
    for(int i=0;i<n;i++){
        output[i] = (char*)malloc(n*sizeof(char));
    }
    char** cpr = (char**)malloc(n*sizeof(char*));
    for(int i=0;i<n;i++){
        cpr[i] = (char*)malloc(n*sizeof(char));
    }
    char** temp = (char**)malloc(n*sizeof(char*));
    for(int i=0;i<n;i++){
        temp[i] = (char*)malloc(n*sizeof(char));
    }
    char** temp2 = (char**)malloc(n*sizeof(char*));
    for(int i=0;i<n;i++){
        temp2[i] = (char*)malloc(n*sizeof(char));
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf(" %c",&s[i][j]); 
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf(" %c",&cpr[i][j]); 
        }
    }
    
    
    turn_90_matrix(s,n,output);

    int founded = 1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(output[i][j] != cpr[i][j] && founded != 0){
                founded = 0;
                break;
            }
        }
    }
    if(founded == 1){printf("1\n"); return 0;} 

    founded = 1; 
    turn_90_matrix(output,n,temp);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(temp[i][j] != cpr[i][j] && founded != 0){
                founded = 0;
                break;
            }
        }
    }
    if(founded == 1){printf("2\n"); return 0;} 

    founded = 1;  
    turn_90_matrix(temp,n,temp2);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(temp2[i][j] != cpr[i][j] && founded != 0){
                founded = 0;
                break;
            }
        }
    }
    if(founded == 1){printf("3\n"); return 0;} 

    founded = 1;  
    reflect_in_y(s,n,output);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(output[i][j] != cpr[i][j] && founded != 0){
                founded = 0;
                break;
            }
        }
    }
    if(founded == 1){printf("4\n"); return 0;} 
    founded = 1; 
    turn_90_matrix(output,n,temp);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(temp[i][j] != cpr[i][j] && founded != 0){
                founded = 0;
                break;
            }
        }
    }
    if(founded == 1){printf("5\n"); return 0;}

    founded = 1; 
    turn_90_matrix(temp,n,temp2);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(temp2[i][j] != cpr[i][j] && founded != 0){
                founded = 0;
                break;
            }
        }
    }
    if(founded == 1){printf("5\n"); return 0;}  

    founded = 1;  
    turn_90_matrix(temp2,n,temp);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(temp[i][j] != cpr[i][j] && founded != 0){
                founded = 0;
                break;
            }
        }
    }
    if(founded == 1){printf("5\n"); return 0;} 
    founded = 1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(s[i][j] != cpr[i][j] && founded != 0){
                founded = 0;
                break;
            }
        }
    }
    if(founded == 1) {printf("6\n"); return 0;} 
    printf("7\n"); 
    return 0;  
}