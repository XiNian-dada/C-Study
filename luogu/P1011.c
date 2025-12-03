#include <stdio.h>

int main() {
    int a, n, m, x;
    scanf("%d %d %d %d", &a, &n, &m, &x);
    
    for(int t = 0; ;t++){
        int up1 = a,up2 = t;
        int people = a;
        for(int i = 2; i < n; i++){
            if(i == 2){
                people = a;
            }else{
                int new_up = up1 + up2;    
                int new_down = up2;
                people = people + new_up - new_down;
                up1 = up2;
                up2 = new_up;
            }
        }
        if(people == m){
            up1 = a,up2 = t;
            people = a;
            for(int i = 2; i <= x; i++){
                if(i == 2){
                    people = a;
                }else{
                    int new_up = up1 + up2;    
                    int new_down = up2;
                    people = people + new_up - new_down;
                    up1 = up2;
                    up2 = new_up;
                }
            }
            printf("%d\n", people);
            return 0;
        }
    }
}