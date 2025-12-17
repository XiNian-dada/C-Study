#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// 使用 long long 应对 10^9 的力量值和 10^12 的总和
#define ll long long

// 结构体：存储连续子序列的和以及其起点和终点（0-based index）
typedef struct {
    ll sum;
    int l; // 左端点 (0-based)
    int r; // 右端点 (0-based)
} Segment;

// 计算 ll 类型的绝对值差
ll llabs_diff(ll a, ll b) {
    ll diff = a - b;
    // 使用三元运算符代替 if/else for a simple absolute value calculation
    return diff > 0 ? diff : -diff;
}

// qsort 比较函数：按 sum 字段升序排序
int compare_segments_by_sum(const void *a, const void *b) {
    ll val_a = ((Segment*)a)->sum;
    ll val_b = ((Segment*)b)->sum;
    
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

void solve() {
    int n;
    // 确保读取成功
    if (scanf("%d", &n) != 1 || n < 2) return; 

    // 1. 读取输入并计算前缀和 S
    ll *a = (ll*)malloc(n * sizeof(ll));
    ll *S = (ll*)malloc((n + 1) * sizeof(ll)); // S[i] = a[0]...a[i-1] 的和


    S[0] = 0;
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &a[i]) != 1) { /* Handle read error */ break; }
        S[i + 1] = S[i] + a[i];
    }
    
    // 2. 生成所有 O(N^2) 个连续子序列 Segment
    // 最大的可能数量：n*(n+1)/2
    int segment_count = n * (n + 1) / 2;
    Segment* All_Segments = (Segment*)malloc(segment_count * sizeof(Segment));

    int idx = 0;
    // 使用增量计算（前缀和）O(1) 获得区间和
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            All_Segments[idx].sum = S[r + 1] - S[l]; // Sum(a[l]...a[r])
            All_Segments[idx].l = l;
            All_Segments[idx].r = r;
            idx++;
        }
    }
    
    // 3. 复制数组并排序 O(N^2 log N)
    Segment* List_A = (Segment*)malloc(segment_count * sizeof(Segment));
    Segment* List_B = (Segment*)malloc(segment_count * sizeof(Segment));
    
    // 复制数据
    memcpy(List_A, All_Segments, segment_count * sizeof(Segment));
    memcpy(List_B, All_Segments, segment_count * sizeof(Segment));
    free(All_Segments); // 释放原始数组

    // 按照 sum 字段升序排序
    qsort(List_A, segment_count, sizeof(Segment), compare_segments_by_sum);
    qsort(List_B, segment_count, sizeof(Segment), compare_segments_by_sum);

    // 4. 双指针 O(N^2) 查找最小差距
    int ptr_A = 0;
    int ptr_B = 0;
    ll min_diff = LLONG_MAX;

    while (ptr_A < segment_count && ptr_B < segment_count) {
        Segment seg_A = List_A[ptr_A]; // 队伍一候选
        Segment seg_B = List_B[ptr_B]; // 队伍二候选
        
        ll W1 = seg_A.sum;
        ll W2 = seg_B.sum;
        
        // 核心：检查约束条件 r1 < l2 (队伍一必须在队伍二前面且不重叠)
        if (seg_A.r < seg_B.l) {
            // 约束满足：更新最小差距
            ll current_diff = llabs_diff(W1, W2);
            if (current_diff < min_diff) {
                min_diff = current_diff;
            }
            
            // 移动较小和的指针，试图让两个和更接近
            if (W1 < W2) {
                ptr_A++;
            } else {
                ptr_B++;
            }
        } else {
            // 约束不满足 (r1 >= l2)：队伍重叠或顺序错误。
            // 移动较小和的指针，这是继续逼近 W1=W2 的最优启发式方法。
            if (W1 < W2) {
                ptr_A++;
            } else {
                ptr_B++;
            }
        }
        
        // 优化：如果差距为 0，则可以直接退出
        if (min_diff == 0) break;
    }

    printf("%lld\n", min_diff);


}

int main() {
    // 禁用标准 C IO 和 C++ IO 的同步，提高 IO 速度（竞赛常用）
    // 在纯 C 环境中，只需确保使用 scanf/printf 即可
    solve();
    return 0;
}