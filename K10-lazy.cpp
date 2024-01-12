#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int BASE = 1 << 20;

struct PlusTree {
    vector<ll> lazy;
    vector<ll> sum;
    vector<ll> m;

    PlusTree() : lazy(2 * BASE), sum(2 * BASE), m(2 * BASE) {}

    void add(int node, int len, ll val) {
        lazy[node] += val;
        sum[node] += val * len;
        m[node] += val;
    }

    void push(int node, int len) {
        if (lazy[node] == 0) return;
        add(2 * node, len / 2, lazy[node]);
        add(2 * node + 1, len / 2, lazy[node]);
        lazy[node] = 0;
    }

    void update(int node, int l, int r, int a, int b, ll val) {
        if (a <= l && r <= b) {
            add(node, r - l + 1, val);
            return;
        }

        push(node, r - l + 1);

        int mid = (l + r) / 2;
        if (a <= mid) update(2 * node, l, mid, a, b, val);
        if (b > mid) update(2 * node + 1, mid + 1, r, a, b, val);
        sum[node] = sum[2 * node] + sum[2 * node + 1];
        m[node] = max(m[2 * node], m[2 * node + 1]);
    }

    ll querySum(int node, int l, int r, int a, int b) {
        if (a <= l && r <= b)
            return sum[node];

        push(node, r - l + 1);

        int mid = (l + r) / 2;
        ll res = 0;
        if (a <= mid) res += querySum(2 * node, l, mid, a, b);
        if (b >= mid) res += querySum(2 * node + 1, mid + 1, r, a, b);

        return res;
    }

    ll queryMax(int node, int l, int r, int a, int b) {
        if (a <= l && r <= b)
            return m[node];

        push(node, r - l + 1);

        int mid = (l + r) / 2;
        ll res = -1e18;
        if (a <= mid) res = max(res, queryMax(2 * node, l, mid, a, b));
        if (b > mid) res = max(res, queryMax(2 * node + 1, mid + 1, r, a, b));

        return res;
    }

};

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int z;
    cin >> z;

    PlusTree tree;

    while (z --> 0) {
        string op;
        cin >> op;

        if (op == "update") {
            int a, b;
            ll val;
            cin >> a >> b >> val;
            tree.update(1, 1, BASE, a, b, val);
        }
        else if (op == "query") {
            int a, b;
            cin >> a >> b;
            cout << tree.queryMax(1, 1, BASE, a, b) << '\n';
        }
    }

    return 0;
}
