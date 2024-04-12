#include<bits/stdc++.h>
using namespace std;

constexpr int INF = 100;

map<int, int> brute(const vector<int> &items, int st = 0, int en = -1) {
    map<int, int> res;
    if (en == -1) en = items.size();

    int n = en - st;

    for(int mask = 0; mask < (1<<n); mask++) {
        int sum = 0, cnt = 0;
        for(int i = 0; i < n; i++) {
            if(mask & (1<<i)) {
                sum += items[i + st];
                cnt++;
            }
        }
        if(res.find(sum) == res.end()) res[sum] = cnt;
        else res[sum] = min(res[sum], cnt);
    }

    return res;
}

// x = a + b
// b = x - a

// void go(int cur, int sum, int cnt, const vector<int> &items) {
//     if(cur == items.size()) {
//         if(res.find(sum) == res.end()) res[sum] = cnt;
//         else res[sum] = min(res[sum], cnt);
//         return;
//     }

//     go(cur + 1, sum + items[cur], cnt + 1, items);
//     go(cur + 1, sum, cnt, items);
// }

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> items(n);

    for(int &x : items) cin >> x;


    // go(0, 0, 0, items);
    // brute(items);

    // while(q --> 0) {
    //     int x;
    //     cin >> x;

    //     if(res.find(x) == res.end()) cout << "NIE\n";
    //     else cout << res[x] << '\n';
    // }

    map<int, int> left  = brute(items, 0, (n + 1) / 2);
    map<int, int> right = brute(items, (n + 1) / 2);

    while(q --> 0) {
        int x;
        cin >> x;

        int res = INF;
        for (auto I: left) {
            if (right.count(x - I.first)) {
                res = min(res, I.second + right[x - I.first]);
            }
        }

        if (res == INF) cout << "NIE\n";
        else cout << res << "\n";
    }

    return 0;
}
