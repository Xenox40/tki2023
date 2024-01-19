#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int MAX_BASE = 1e3;
const int N = 1e6;


struct SumsPoint {
    int n, BASE;
    vector<LL> sum;
    vector<LL> arr;

    SumsPoint(int _n) {
        n = _n;
        BASE = sqrt(n);
        sum.resize(BASE + 5);
        arr.resize(n);
    }

    int block(int x) {
        return x / BASE;
    }

    void update(int x, LL v) {
        arr[x] += v;
        sum[block(x)] += v;
    }

    LL query(int a, int b) {
        int b1 = block(a), b2 = block(b);
        LL res = 0;

        if(b1 == b2) {
            for(int i = a;i <= b;++i)
                res += arr[i];
            return res;
        }

        while(block(a) == b1)
            res += arr[a++];
        while(block(b) == b2)
            res += arr[b--];

        for(int i = b1 + 1;i < b2;++i)
            res += sum[i];
        return res;
    }
};

struct Sums {
    int n, BASE;
    vector<LL> sum;
    vector<LL> m;
    vector<LL> arr;
    vector<LL> lazy;

    Sums(int _n) {
        n = _n;
        BASE = sqrt(n);
        sum.resize(BASE + 5);
        m.resize(BASE + 5);
        lazy.resize(BASE + 5);
        arr.resize(n);
    }

    int block(int x) {
        return x / BASE;
    }

    void update(int a, int b, LL v) {
        int b1 = block(a), b2 = block(b);

        if(b1 == b2) {
            for(int i = a;i <= b;++i) {
                arr[i] += v;
                sum[b1] += v;
            }
            a = b1 * BASE;
            b = a + BASE;
            m[b1] = 0;
            for(int i = a;i <= b && i < n;++i) {
                m[b1] = max(m[b1], arr[i]);
            }
            return;
        }

        while(block(a) == b1) {
            arr[a++] += v;
            sum[b1] += v;
            m[b1] = max(m[b1], arr[a-1]);
        }

        while(block(b) == b2) {
            arr[b--] += v;
            sum[b2] += v;
            m[b2] = max(m[b2], arr[b+1]);
        }

        for(int i = b1 + 1;i < b2;++i) {
            sum[i] += v * BASE;
            m[i] += v;
            lazy[i] += v;
        }

    }

    void push(int id) {
        if(lazy[id] == 0)   return;
        int a = id * BASE;
        int b = a + BASE;
        LL s = 0;

        m[id] = 0;
        for(int i = a;i < b && i < n;++i) {
            arr[i] += lazy[id];
            m[id] = max(m[id], arr[i]);
            s += arr[i];
        }
        assert(s == sum[id]);
        lazy[id] = 0;
    }

    LL querySum(int a, int b) {
        int b1 = block(a), b2 = block(b);
        LL res = 0;

        push(b1);
        push(b2);

        if(b1 == b2) {
            for(int i = a;i <= b;++i)
                res += arr[i];
            return res;
        }

        while(block(a) == b1)
            res += arr[a++];
        while(block(b) == b2)
            res += arr[b--];

        for(int i = b1 + 1;i < b2;++i)
            res += sum[i];
        return res;
    }
    LL queryMax(int a, int b) {
        int b1 = block(a), b2 = block(b);
        LL res = 0;

        push(b1);
        push(b2);

        if(b1 == b2) {
            for(int i = a;i <= b;++i)
                res = max(arr[i], res);
            return res;
        }

        while(block(a) == b1)
            res = max(res, arr[a++]);
        while(block(b) == b2)
            res = max(res, arr[b--]);

        for(int i = b1 + 1;i < b2;++i)
            res = max(res, m[i]);
        return res;
    }
};


int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m, q;

    cin >> n >> m >> q;

    Sums tree(n);
    // for(int i = 0;i < n;++i) {
    //     cin >> tree.arr[i];
    //     tree.sum[tree.block(i)] += tree.arr[i];
    // }

    while(q --> 0) {
        int a, b, v;
        cin >> a >> b >> v;
        --a;--b;

        int cur = tree.queryMax(a, b-1);
        // cout << a << " " << b << " " << cur << endl;
        if(cur + v <= m) {
            cout << "T\n";
            tree.update(a, b-1, v);
        }
        else {
            cout << "N\n";
        }
    }

    return 0;
}
