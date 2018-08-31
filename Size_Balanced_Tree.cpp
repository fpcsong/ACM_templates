//https://vjudge.net/contest/21629#problem/B
/*
ID:fpcsong1
LANG:C++
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;
#define ABS(x) (x) > 0 ? (x) : (-(x))
#define lowbit(x) (x) & (-x)
const int MAXN = 2000010;
struct sbt
{
    int val, sz;
    int ch[2];
    void Init()
    {
        ch[0] = ch[1] = 0;
        sz = 1;
    }
} tree[MAXN];
int tot, root;
void push_down(int x)
{
    //
}
inline void push_up(const int &x)
{
    tree[x].sz = tree[tree[x].ch[0]].sz + tree[tree[x].ch[1]].sz + 1;
}
void rotate(int &x, int flag) // 0 left 1 right
{
    int y = tree[x].ch[!flag];
    tree[x].ch[!flag] = tree[y].ch[flag];
    tree[y].ch[flag] = x;
    push_up(x);
    push_up(y);
    x = y;
}
void maintain(int &x, int flag)
{

    if (tree[tree[tree[x].ch[flag]].ch[flag]].sz > tree[tree[x].ch[!flag]].sz)
        rotate(x, !flag);
    else if (tree[tree[tree[x].ch[flag]].ch[!flag]].sz > tree[tree[x].ch[!flag]].sz)
        rotate(tree[x].ch[flag], flag), rotate(x, !flag);
    else
        return;
    maintain(tree[x].ch[0], 0);
    maintain(tree[x].ch[1], 1);
    maintain(x, 0);
    maintain(x, 1);
}
void Insert(int &x, int val)
{
    if (x == 0)
    {
        x = ++tot;
        tree[x].Init();
        tree[x].val = val;
    }
    else
    {
        tree[x].sz++;
        if (val < tree[x].val)
            Insert(tree[x].ch[0], val);
        else
            Insert(tree[x].ch[1], val);
        maintain(x, val >= tree[x].val);
    }
}
int get_Kth(int x, int k)
{
    if (tree[tree[x].ch[0]].sz >= k)
        return get_Kth(tree[x].ch[0], k);
    else if (k > tree[tree[x].ch[0]].sz + 1)
        return get_Kth(tree[x].ch[1], k - tree[tree[x].ch[0]].sz - 1);
    return tree[x].val;
}
int getMin(int x)
{
    while (tree[x].ch[0])
        x = tree[x].ch[0];
    return x;
}
int Del()
{
    int temp = root;
    if (tree[temp].ch[0] == 0)
    {

        root = tree[root].ch[1];
        return tree[temp].val;
    }
    while (tree[tree[temp].ch[0]].ch[0])
    {
        tree[temp].sz--;
        temp = tree[temp].ch[0];
    }
    tree[temp].sz--;
    int ret = tree[tree[temp].ch[0]].val;
    tree[temp].ch[0] = tree[tree[temp].ch[0]].ch[1];
    return ret;
}
int main()
{
    int base;
    int u;
    char option[3];
    int n, Min;
    while (~scanf("%d%d", &n, &Min))
    {
        tot = root = 0;
        base = 0;
        int ans = 0;
        while (n--)
        {
            scanf("%s", option);
            if (option[0] == 'I')
            {
                scanf("%d", &u);
                if (u >= Min)
                    Insert(root, u - base);
                // printf ("%d\n", tree[root].sz);
            }
            if (option[0] == 'S')
            {
                scanf("%d", &u);
                base -= u;
                while (root != 0 && tree[getMin(root)].val + base < Min)
                {
                    Del();
                    ans++;
                }
            }
            if (option[0] == 'A')
            {
                scanf("%d", &u);
                base += u;
            }
            if (option[0] == 'F')
            {
                scanf("%d", &u);
                if (root != 0 && u <= tree[root].sz)
                    printf("%d\n", get_Kth(root, tree[root].sz + 1 - u) + base);
                else
                    puts("-1");
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}