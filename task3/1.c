#include <stdio.h>
#include <math.h>
void divide(int x){
    int y = (int ) log2(x);
    if (y == 1){
        printf("%s","2");
    }
    else if (y == 0){
        printf("%s","2(0)");
    }
    else{
        printf("%s", "2(");
        divide(y);
        printf(")");
    }
    if (x - pow(2,y) != 0){
        printf("+");
        divide(x - pow(2,y));
    }
}
int main() {
    int n;
    scanf ("%d", &n);
    divide(n);
    return 0;
}
