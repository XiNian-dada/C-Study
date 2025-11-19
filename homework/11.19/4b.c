#include "stdio.h"
int main(){
    int n,m=2,al[2][1001],max[2]={0,0},min[2]={1000,1000};
    while(m--){scanf("%d",&n);
        for(int i=0;i<n;scanf("%d",&al[m][i++]));
        for(int i=0;i<n;max[m] = al[m][i]>max[m]?al[m][i]:max[m],min[m] = al[m][i]<min[m]?al[m][i]:min[m],i++);}
    printf("%d",(max[0]-min[1] > max[1]-min[0]?max[0]-min[1]:max[1]-min[0]) < 0 ? -((max[0]-min[1] > max[1]-min[0]?max[0]-min[1]:max[1]-min[0])):(max[0]-min[1] > max[1]-min[0]?max[0]-min[1]:max[1]-min[0]));
}