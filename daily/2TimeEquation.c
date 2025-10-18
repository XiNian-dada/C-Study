#include <stdio.h>
#include <math.h>
/*

解一元二次方程ax^2 + bx + c = 0
输入a,b,c，输出方程的解

*/
int main(){
    double a,b,c,sq1,sq2,x1,x2,xb1,xb2;
    scanf("%lf %lf %lf",&a,&b,&c);
    if (a == 0 && b == 0 && c != 0){
        printf("Not An Equation");
        return 0;
    }
    else if (a == 0 && b == 0 && c ==0){
        printf("Zero Equation");
        return 0;
    }
    double delta = b*b - 4*a*c;
    if (a == 0 ){
        printf ("%.2f", -c/b);
        return 0;
    }
    else if (delta < 0){
        x1 = -b/(2*a);
        x2 = x1;
        sq1 = fabs(sqrt(-delta)/(2*a));
        printf("%.2f + %.2fi, %.2f - %.2fi", x1, sq1, x2, sq1);
    }
    else if (delta == 0){
        x1 = -b/(2*a);
        printf("%.2f", x1);
    }
    else if (delta > 0){
        x1 = (-b + sqrt(delta))/(2*a);
        x2 = (-b - sqrt(delta))/(2*a);
        printf("%.2f, %.2f", x1, x2);
    }
}