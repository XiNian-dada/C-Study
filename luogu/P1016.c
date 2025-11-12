#include <stdio.h>

int main() {
    double S, C, L, P0;
    int N;
    
    scanf("%lf %lf %lf %lf %d", &S, &C, &L, &P0, &N);
    
    double D[7], P[7];
    
    // 读取加油站信息
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &D[i], &P[i]);
    }
    
    // 添加终点作为特殊加油站
    D[N] = S;
    P[N] = 0;
    N++;
    
    // 计算满油最远能行驶的距离
    double maxDist = C * L;
    
    // 当前状态
    double currentPosition = 0;
    double currentFuel = 0;
    double totalCost = 0;
    double currentPrice = P0;
    
    // 遍历每个加油站（包括终点）
    for (int i = 0; i < N; i++) {
        // 计算到下一个加油站的距离
        double distance = D[i] - currentPosition;
        
        // 检查能否到达下一个加油站
        if (distance > maxDist) {
            printf("No Solution\n");
            return 0;
        }
        
        // 如果当前油量不足以到达下一个加油站
        if (currentFuel * L < distance) {
            // 计算需要补充的油量
            double needFuel = distance / L - currentFuel;
            
            // 寻找范围内是否存在更便宜的加油站
            int cheaperStation = -1;
            for (int j = i; j < N && D[j] - currentPosition <= maxDist; j++) {
                if (P[j] < currentPrice) {
                    cheaperStation = j;
                    break;
                }
            }
            
            // 如果存在更便宜的加油站且能在该站之前到达
            if (cheaperStation != -1) {
                // 只加刚好能到达那个便宜加油站的油
                double fuelToCheaper = (D[cheaperStation] - currentPosition) / L - currentFuel;
                if (fuelToCheaper > 0) {
                    totalCost += fuelToCheaper * currentPrice;
                    currentFuel += fuelToCheaper;
                }
            } else {
                // 否则加满油
                totalCost += (C - currentFuel) * currentPrice;
                currentFuel = C;
            }
        }
        
        // 更新状态
        currentFuel -= distance / L;
        currentPosition = D[i];
        currentPrice = P[i];
    }
    
    printf("%.2f\n", totalCost);
    
    return 0;
}