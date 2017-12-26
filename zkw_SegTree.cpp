//zkw 线段树
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int M;
const int N = 1e6 + 10;
int tree[N];
void build(int n)
{
    for (M = 1; M < n + 2; M <<= 1);

    for (int i = M + 1; i < M + n + 1; i++)
    {
        cin >> tree[i];
    }
    for (int i = M - 1; i >= 1; i--)
    {
        tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
}
int query(int s, int t)
{
    int ret = 0;
    for (s = s + M - 1, t = t + M + 1; s ^ t ^ 1; s >>= 1, t >>= 1)
    {
        if (~s & 1)
            ret += tree[s ^ 1];
        if (t & 1)
            ret += tree[t ^ 1];
    }
    return ret;
}
void modify(int pos, int val)
{
    tree[pos + M] += val;
    int t = pos + M;
    while (t > 1)
    {
        t >>= 1;
        tree[t] = tree[t << 1] + tree[t << 1 | 1];
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    build(n);
    for (int i = 0; i < m; i++)
    {
        int k;
        cin >> k;
        if (k == 1)
        {
            int a, b;
            cin >> a >> b;
            cout << query(a, b) << endl;
        }
        else
        {
            int a, b;
            cin >> a >> b;
            modify(a, b);
        }
    }
    return 0;
}