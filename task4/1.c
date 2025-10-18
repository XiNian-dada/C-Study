#include <stdio.h>
#include <stdlib.h>
#define ll long long
ll list[200001];
ll ans = 0;
ll N,C;
int cmp(const void* a, const void* b){
    return * (ll*)a - * (ll*)b;
}
ll lower_bound (ll target){
    ll left = 0 ,right = N;
    while (left < right){
        ll mid = (left + right) / 2;
        if (list[mid] >= target){
            right = mid;
        }else {
            left = mid + 1;
        }
    }return left;
}

ll upper_bound (ll target){
    ll left = 0 ,right = N;
    while (left < right){
        ll mid = (left + right) / 2;
        if (list[mid] > target){
            right = mid;
        }else {
            left = mid + 1;
        }
    }return left;
}
int main()
{
    scanf("%lld %lld", &N, &C);
    for (ll i = 0; i < N; i++)
    {
        scanf("%lld", &list[i]);
    }
    qsort(list, N, sizeof(ll),cmp);
    for (ll i = 0; i < N; i++){
        ll temp = list[i] + C;
        ans += upper_bound(temp) - lower_bound(temp);

    }
    printf("%lld", ans);
    return 0;
}