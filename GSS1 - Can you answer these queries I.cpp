#include<bits/stdc++.h>

using namespace std;

struct treenode{
    int data,data1,left,right,flag;
};

treenode segtree[400010];
int a[100010];

void build(int node,int start,int end)
{
	if(start == end)
	{
		segtree[node].data = a[start];
        segtree[node].data1 = a[start];
        segtree[node].left = 0;
        segtree[node].right = 0;
        segtree[node].flag = true;
		return;
	}

	int mid = (start+end)/2;

	build(2*node,start,mid);
	build(2*node+1,mid+1,end);

	int x,y,z;
    x = segtree[2*node].data;
    y = segtree[2*node+1].data;
    z = x+y+segtree[2*node].right+segtree[2*node+1].left;

    if(z >= x && z >= y)
    {
        segtree[node].data = z;
        segtree[node].left = segtree[2*node].left;
        segtree[node].right = segtree[2*node+1].right;
    }
    else if(y >= x)
    {
        segtree[node].data = y;
        segtree[node].left = segtree[2*node].data1 + segtree[2*node+1].left;
        segtree[node].right = segtree[2*node+1].right;
    }
    else
    {
        segtree[node].data = x;
        segtree[node].right = segtree[2*node+1].data1 + segtree[2*node].right;
        segtree[node].left = segtree[2*node].left;
    }

    segtree[node].data1 = segtree[2*node].data1 + segtree[2*node+1].data1;
    segtree[node].flag = true;
}

treenode query(int node, int start, int end, int left, int right)
{
    treenode p = {0,0,0,0,false};

	int mid = (start+end)/2;

	if(left > end || start > right)
	{
        p.flag = false;
        return p;
    }
	else if(left <= start && right >= end)
		return segtree[node];
	else
    {
        treenode p1,p2;
        p1 = query(2*node,start,mid,left,right);
        p2 = query(2*node+1,mid+1,end,left,right);

        if(p1.flag && p2.flag)
        {
            int x,y,z;
            x = p1.data;
            y = p2.data;
            z = x+y+p1.right+p2.left;

            if(z >= x && z >= y)
            {
                p.data = z;
                p.left = p1.left;
                p.right = p2.right;
            }
            else if(y >= x)
            {
                p.data = y;
                p.left = p1.data1 + p2.left;
                p.right = p2.right;
            }
            else
            {
                p.data = x;
                p.right = p2.data1 + p1.right;
                p.left = p1.left;
            }

            p.data1 = p1.data1 + p2.data1;
            p.flag = true;

            return p;
        }
        else if(p1.flag == true)
            return p1;
        else
            return p2;
    }
}
int main()
{
	int n;
	cin >> n;

	for(int i=0;i<n;i++)
		cin >> a[i];

	build(1,0,n-1);

    int q;
    cin >> q;

	while(q--)
	{
		int x,y;
		cin >> x >> y;
		treenode p = query(1,0,n-1,x-1,y-1);

        if(p.flag == true)
            cout << p.data << endl;
	}
}