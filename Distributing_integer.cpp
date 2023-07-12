#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int N = 2e5 + 7, base = 257, MOD = 1e9 + 7;

int n;
vector<int> G[N];
long long ans, Size[N], Dp[N], pw[N], KQ[N];

long long lt(long long a, long long b){
    a %= MOD;
    if (b == 0) return 1;
    if (b == 1) return a;
    if (b % 2 == 0)
        return lt(a * a, b / 2);
    else
        return lt(a * a, b / 2) * a % MOD;
}

void calcsize(int u, int p){
    Size[u] = 1;
    for (auto x : G[u])
    if (x != p)
    {
        calcsize(x, u);
        Size[u] += Size[x];
    }
}

void calcdp(int u, int p){
    Dp[u] = pw[Size[u] - 1];
    for (auto x : G[u])
    if (x != p)
    {
        calcdp(x, u);
        Dp[u] *= Dp[x], Dp[u] %= MOD;
        Dp[u] *= lt(pw[Size[x]], MOD - 2), Dp[u] %= MOD;
    }
}

long long Divi(long long a, long long b){
    return a = (a * lt(b, MOD - 2)) % MOD;
}
long long mul(long long a, long long b){
    return a = (a * b) % MOD;
 }

void hoan_doi(int u, int x){
    Dp[u] = Divi(Dp[u], pw[Size[u] - 1]);
    Dp[u] = Divi(Dp[u], Divi(Dp[x], pw[Size[x]]));
    Size[u] -= Size[x];
    Dp[u] = mul(Dp[u], pw[Size[u] - 1]);

    Dp[x] = Divi (Dp[x], pw[Size[x] - 1]);
    Size[x] += Size[u];
    Dp[x] = mul(Dp[x], pw[Size[x] - 1]);
    Dp[x] = mul(Dp[x], Divi(Dp[u], pw[Size[u]]));
}
void dfs(int u, int p){
   // ans = max(ans, Dp[u]);
    KQ[u] = Dp[u];
    for (auto x : G[u])
    if (x != p){
        hoan_doi(u, x);
        dfs(x, u);
        hoan_doi(x, u);
    }
}

int main(){
    freopen("nhap.inp", "r", stdin);
    freopen("xuat.out", "w", stdout);
    freopen("error.err", "w", stderr);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n;
    pw[0] = 1;
    for (int i = 1; i <= n; ++i)
        pw[i] = pw[i - 1] * i, pw[i] %= MOD;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    calcsize(1, 1);
    calcdp(1, 1);
    dfs(1, 1);
    for (int i = 1; i <= n; ++i) cout << KQ[i] << "\n";

}
