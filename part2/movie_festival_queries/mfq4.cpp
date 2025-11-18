
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    const int MAXT = 1000000; // given in statement
    const int INF_TIME = MAXT + 5;
    
    vector<vector<int>> startsAt(MAXT + 2);
    int a,b;
    int maxSeenStart = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        // store movie by its start time
        if (a <= MAXT) {
            startsAt[a].push_back(b);
            maxSeenStart = max(maxSeenStart, a);
        }
    }
    
    // firstEnd[t] = end time of the first movie you would pick when arriving at time t
    vector<int> firstEnd(MAXT + 3, INF_TIME);
    priority_queue<int, vector<int>, greater<int>> minHeap; // store end times
    // process times descending so heap contains movies with start >= t
    for (int t = MAXT; t >= 1; --t) {
        for (int endTime : startsAt[t]) minHeap.push(endTime);
        if (!minHeap.empty()) firstEnd[t] = minHeap.top();
        else firstEnd[t] = INF_TIME;
    }
    firstEnd[INF_TIME] = INF_TIME; // sentinel (not strictly needed but safe)
    
    // Binary lifting: up[k][t] = time you end up after watching 2^k movies starting at t
    int LOG = 20; // enough because n <= 2e5 -> log2(n) < 18, 20 safe
    vector<vector<int>> up(LOG, vector<int>(MAXT + 3, INF_TIME));
    for (int t = 1; t <= MAXT+1; ++t) up[0][t] = firstEnd[t <= MAXT ? t : MAXT+1];
    // build
    for (int k = 1; k < LOG; ++k) {
        for (int t = 1; t <= MAXT+1; ++t) {
            int mid = up[k-1][t];
            if (mid <= MAXT+1) up[k][t] = up[k-1][ mid <= MAXT+1 ? mid : MAXT+1 ];
            else up[k][t] = INF_TIME;
        }
    }
    
    // answer queries
    for (int i = 0; i < q; ++i) {
        int L, R; cin >> L >> R;
        if (L > MAXT) { cout << 0 << '\n'; continue; }
        int cur = L;
        if (cur < 1) cur = 1;
        if (firstEnd[cur] > R) { cout << 0 << '\n'; continue; }
        int cnt = 0;
        for (int k = LOG-1; k >= 0; --k) {
            int nxt = up[k][cur];
            if (nxt <= R) {
                cnt += (1 << k);
                cur = nxt;
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}

