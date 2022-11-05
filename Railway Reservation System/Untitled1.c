#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

int n, a[100000];

void solve() {
	cin >> n ;
	for(int i=0; i<n; ++i)
		cin >> a[i];
	sort(a, a+n);
	int ans=0;
	for(int i=0; i<n; ++i)
	{
	  int count=0;
	  for(i=1;i<n;i++)
	  {
	    if(a[i]==a[i+1])
	    count++;
	  }
	  for(i=1;i<=n;i++)
	  {
	    if(a[i]==a[i+1])
	       ans=ans+count*(i+1);
	    else
	    ans=ans+i+1;
	  }
	}

	}
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t, i=1;
	cin >> t;
	while(t--) {
		cout << "Case #" << i << ": ";
		solve();
		++i;
	}
}
