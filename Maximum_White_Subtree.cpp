#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#define pil pair<int, long long> 
#define se second
#define fi first
using namespace std;
const int N = 1e5 + 7;
vector<int> G[N];
vector<long long> pre[N], suf[N];
int n, a[N], m;
long long dp[N], KQ[N];
long long lt(long long a, long long b){
    a %= m;
    if (b == 0) return 1;
    if (b == 1)
        return a;
    if (b & 1)
        return a * lt(a * a, b / 2) % m;
    return lt(a * a, b / 2);
}
int phi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n != 1) {
        res -= res / n;
    }
    return res;
}
void calcdp(int u, int p){
    dp[u] = 1;
    pre[u].resize(G[u].size() + 2), suf[u].resize(G[u].size() + 2);
    pre[u][0] = 1, suf[u][G[u].size() + 1] = 1;
    for (int i = 1; i <= G[u].size(); ++i){
        int x = G[u][i - 1];
        if (x != p)
        {
            calcdp(x, u);
            pre[u][i] = pre[u][i - 1] * (dp[x] + 1) % m;
            dp[u] = (dp[u] * (dp[x] + 1) % m);
        }
        else
            pre[u][i] = pre[u][i - 1];
    }
    for (int i = G[u].size(); i >= 1; --i){
        int x = G[u][i - 1];
        if (x != p)
        {
            suf[u][i] = suf[u][i + 1] * (dp[x] + 1) % m;
        }
        else
            suf[u][i] = suf[u][i + 1];
    }
    //cerr << u << " " << dp[u] << "\n";
}

long long save[N], save1[N];
void DFS(int u, int p){
    KQ[u] = dp[u];
    int cnt = 0;
    for (int i = 1; i <= G[u].size(); ++i)
    {
        int x = G[u][i - 1];
        if (x != p){
            long long res = pre[u][i - 1] * suf[u][i + 1] % m;
           // cerr << u << " " << i - 1 << " " << i + 1 << " " << pre[u][i - 1] << " " << suf[u][i + 1] << "\n";
            if (u != p)
                res *= dp[p] + 1, res %= m;
            save[u] = dp[u];
            dp[u] = res;
            save1[x] = dp[x];
            dp[x] *= res + 1;
            dp[x] %= m;
        //cout << u << " " << x << " " << dp[u] << " " << dp[x] << "\n";
            DFS(x, u);
            dp[x] = save1[x];
            dp[u] = save[u];
        //cout << u << " " << x << " " << dp[u] << " " << dp[x] << "\n";
        }
    }
}

int main(){
    freopen("nhap.inp", "r", stdin);
    freopen("xuat.out", "w", stdout);
    freopen("error.err", "w", stderr);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n >> m;//cout << phi(m) << "\n";
    //cerr << __gcd(2, m) * lt(2 / __gcd(2, m), phi(m) - 1) % m << "\n";
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    calcdp(1, 1);
    DFS(1, 1);
    for (int i = 1; i <= n; ++i) cout << KQ[i] << "\n";
}