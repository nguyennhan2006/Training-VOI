#include <iostream>
#include <vector>
#include <stack>
#define pil pair<int, long long> 
#define se second
#define fi first
using namespace std;
const int N = 1e5 + 7;
vector<pair<int, int>> G[N];
int n, S[N], V[N], top, savetop[N];
pil save[N];
long long dp[N];
pil st[N];
stack<pil> DQ;
bool bad(pil L1, pil L2, pil L3)
{
    long double x1 = (long double) (L3.se - L1.se) / (L1.fi - L3.fi);
    long double x2 = (long double) (L2.se - L1.se) / (L1.fi - L2.fi);
    return (x1 <= x2);
}

long long check(int id, int x){
    return (1LL * st[id].fi * x + st[id].se);
}

long long Get(int x){
    long long res = check(0, x);
    int l = 0, r = top;
    if (top > 0)
    while (l <= r){
        int mid = (l + r) / 2;
        if (check(mid, x) >= check(mid + 1, x))
            res = min(res, check(mid + 1, x)), l = mid + 1;
        else
            r = mid - 1; 
    }
    return res;
}

int newtop(int a, long long b){
    if (top < 1) return top;
    int l = 0, r = top, res = top;
    while (l <= r){
        int mid = (l + r) >> 1;
        if (mid == top || bad(st[mid], st[mid + 1], make_pair(a, b)))
            res = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    return res;
}

void DFS(int u, int p, int pre){
    dp[u] = Get(V[u]) + S[u] + 1LL * pre * V[u];
    savetop[u] = top;
    top = newtop(-pre, dp[u]);
    ++top;
    save[u] = st[top];
    st[top] = make_pair(-pre, dp[u]);
    for (auto x : G[u])
    if (x.fi != p)
    {
        DFS(x.fi, u, pre + x.se);
    }
    st[top] = save[u];
    top = savetop[u];
}

int main(){
    freopen("nhap.inp", "r", stdin);
    freopen("xuat.out", "w", stdout);
    freopen("error.err", "w", stderr);
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n;
    for (int i = 1; i < n; ++i){
        int u, v, d;
        cin >> u >> v >> d;
        G[u].push_back({v, d});
        G[v].push_back({u, d});
    }

    for (int i = 1; i < n; ++i)
        cin >> S[i + 1] >> V[i + 1];
    st[0] = make_pair(0, 0);
    for (auto x : G[1])
    DFS(x.fi, 1, x.se);
    for (int i = 2; i <= n; ++i)
        cout << dp[i] << " ";
}