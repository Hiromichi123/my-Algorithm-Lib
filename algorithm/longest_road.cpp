// 在一个有向无环图上，求 1->n 最长路
#include<iostream>
#include<queue>
#include<vector>

// 初始化
vector<vector<pair<int, int>>> g(n+1);
vector<int> indeg(n+1);
while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    indeg[v] ++;
}

queue<int> que;
for(int i=1; i<=n; i++) {
    if(indeg[i] == 0) que.push(i);
}

// 拓扑 + dp
const int inf = INT_MIN/2;
vector<int> dp(n+1, inf);
dp[1]=0;
while(!que.empty()) {
    int u == que.front();
    for (auto [u, w] : g[u]) {
        que.pop();
        dp[v] = max(dp[v]. dp[u] + w);
        if(indeg[v] == 0) que.push(v);
    }
}
cout << (dp[n] == inf ? -1 : dp[n]) << '\n';

// 记忆化搜索
const int inf = INT_MIN/2;
vector<int> dp(n+1, inf);
dp[1] = 0;
auto dfs = [&](auto &self, int u) {
    if (dp[u] != inf) return dp[u];
    auto &res = dp[u];
    for (auto [v, w] : g[u]) {
        res = max(res, self(self, v) + w);
    }
    return res;
};
int ans = dfs(dfs, n);
