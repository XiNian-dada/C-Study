#include <stdio.h>
#include <stdlib.h>
#define ll long long
ll n,m,K;
ll A[100001],B[100001];
int cmp(const void* a, const void* b){
    return * (ll*)a - * (ll*)b;
}

ll count_pairs(ll target){
    ll count = 0;
    ll j = m-1;
    for (ll i = 0; i < n ; i++){
        while (j >= 0 && A[i] + B[j] > target){
            j--;
        }
        if (j >= 0){
            count += (j + 1);
        } else {
            break;
        }

    }return count;
}

int main()
{
    scanf ("%lld %lld %lld", &n, &m, &K);
    for (int i = 0; i < n; i++){
        scanf("%lld", &A[i]);
    }
    for (int i = 0; i < m; i++){
        scanf("%lld", &B[i]);
    }
    qsort(A, n, sizeof(ll),cmp);
    qsort(B, m, sizeof(ll),cmp);
    ll left = A[0] + B[0];
    ll right = A[n-1] + B[m-1];
    while (left < right){
        ll mid = (left + right) / 2;
        ll pairs = count_pairs (mid);
        if (pairs < K){
            left = mid + 1;
        }else {
            right = mid;
        }
    }
    printf("%lld", left);
    return 0;
}