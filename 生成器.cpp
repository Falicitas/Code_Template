#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));

int main(){
	//freopen("out.txt","w",stdout);
	for(int i=1;i<=1000;i++) printf("%d\n",(unsigned int)(-1) %10000);
	int n = 100,m = 200;
	printf("%d %d\n",n,m);
	for(int i=2; i<=n; i++){
		int x = rand() % (i-1) + 1;
		cout<<x<<" "<<i<<" "<<endl;
	}
}
