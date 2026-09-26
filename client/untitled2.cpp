#include<bits/stdc++.h>
using namespace std;
#define int long long
mt19937 rnd(time(0));
int n,m,cnt,rt,a[1000200];
struct node{
	int l,r,sz,rk,val,sct,ssm,cnt;
} t[1000200];
void pushup(int rt){
	t[rt].sz=t[t[rt].l].sz+t[t[rt].r].sz+1;
	t[rt].ssm=t[t[rt].l].ssm+t[t[rt].r].ssm+t[rt].cnt*t[rt].val;
	t[rt].sct=t[t[rt].l].sct+t[t[rt].r].sct+t[rt].cnt;
}
void split(int rt,int k,int &l,int &r){
	if (rt==0){
		l=r=0;
		return ;
	} 
	if (t[rt].val<=k) {
		l=rt;
		split(t[rt].r,k,t[rt].r,r);
	}else {
		r=rt;
		split(t[rt].l,k,l,t[rt].l);
	}
	pushup(rt);
}
int merge(int x,int y){
	if (x==0 || y==0) return x+y;
	if (t[x].rk<t[y].rk){
		t[x].r=merge(t[x].r,y);
		pushup(x);
		return x;
	}
	t[y].l=merge(x,t[y].l);
	pushup(y);
	return y;
}
int nnd(int x){
	cnt++;
	t[cnt].l=0;
	t[cnt].r=0;
	t[cnt].rk=rnd();
	t[cnt].sz=1;
	t[cnt].val=x;
	t[cnt].sct=1;
	t[cnt].ssm=x;
	t[cnt].cnt=1;
	return cnt;
}
void insert(int x){
	int l,r,md;
	split(rt,x,l,r);
	split(l,x-1,l,md);
	if (md){
		t[md].cnt++;
		pushup(md);
		rt=merge(merge(l,md),r);
	}else rt=merge(merge(l,nnd(x)),r);
}
void del (int x){
	int l,r,m;
	split(rt,x,l,r);
	split(l,x-1,l,m);
	if (m){
		t[m].cnt--;
		if (t[m].cnt) pushup(m);
		else m=merge(t[m].l,t[m].r);
	}
	rt=merge(merge(l,m),r);
}
int query(int &rt,int x){
	int l,r;
	split(rt,x,l,r);
	int ans=(t[l].ssm+t[r].sct*x);
	rt=merge(l,r);
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	// cout.tie(0);
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	cout<<"--------\n|      |\n|      |\n|DOUBLE|\n|      |\n|      |\n--------\n";
	cout<<"   /\\\n  /[]\\\n   []\n";
	return 0;
}
