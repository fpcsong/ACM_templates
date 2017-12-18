//传统自上而下的线段树
//poj3468
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e7 + 10;
struct node
{
    int l, r;
    long long ad, sum; //lazy
} tree[maxn];
int posmap[maxn]; //保存原始数据对应的节点，这样单点更新的时候可以少一次树上的递归
void pushup(int rt)
{
    tree[rt].sum = tree[rt << 1].sum + tree[rt << 1 | 1].sum;
}
void pushdown(int rt)
{
    if (tree[rt].ad != 0)
    {
        int m = tree[rt].l + tree[rt].r >> 1;
        tree[rt << 1].ad += tree[rt].ad;
        tree[rt << 1 | 1].ad += tree[rt].ad;
        tree[rt << 1].sum += (long long )(m - tree[rt].l + 1) * tree[rt].ad;
        tree[rt << 1 | 1].sum += (long long )(tree[rt].r - m) * tree[rt].ad;
        tree[rt].ad = 0;
    }
}
void build(int rt, int l, int r)
{
    tree[rt].l = l;
    tree[rt].r = r;
    if (l == r)
    {
        // tree[rt].sum = 1; //这里给出原始数据
        scanf("%I64d", &tree[rt].sum);
        posmap[l] = rt;
        return;
    }
    int mid = l + r >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}
//单点更新
// 在原始序列的pos位置上修改，add==1为直接修改，add==0为加减
void updatex(int pos, int val, int add)
{
    int rt = posmap[pos];
    if (add == 1)
        tree[rt].sum = val;
    else
        tree[rt].sum += val;
    rt >>= 1;
    while (rt != 1)
    {
        pushup(rt);
        rt >>= 1;
    }
}
//区间更新，这里只写更新问题，不写染色问题，染色的话就是初始值都为空，
//将初始值一起作为一次更新，这个标记是替代关系，不是叠加关系
void updatelr(int rt, int l, int r, int val)
{
    if (l <= tree[rt].l && r >= tree[rt].r)
    {
        tree[rt].ad += val;
        tree[rt].sum += (long long)(tree[rt].r - tree[rt].l + 1) * val;
        return;
    }
    pushdown(rt);
    int m = tree[rt].l + tree[rt].r >> 1;
    if (l <= m)
        updatelr(rt << 1, l, min(m, r), val);
    if (r > m)
        updatelr(rt << 1 | 1, max(m + 1, l), r, val);
    pushup(rt);
}
//查询区间和
long long query(int rt, int l, int r)
{
    if (l <= tree[rt].l && r >= tree[rt].r)
    {
        return tree[rt].sum;
    }
    // cout << "??? " << rt<< endl;
    pushdown(rt);
    int m = tree[rt].l + tree[rt].r >> 1;
    long long ret = 0;
    if (l <= m)
        ret += query(rt << 1, l, min(m, r));
    if (r > m)
        ret += query(rt << 1 | 1, max(m + 1, l), r);
    return ret;
}
int main()
{
    int m, n;
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    while (m--)
    {
        char s[5];
        int a, b, c;
        scanf("%s", s);
        // cout << s << endl;
        if (s[0] == 'Q')
        {
            scanf("%d%d", &a, &b);
            printf("%I64d\n", query(1, a, b));
        }
        else
        {
            scanf("%d%d%d", &a, &b, &c);
            updatelr(1, a, b, c);
        }
    }
    return 0;
}
