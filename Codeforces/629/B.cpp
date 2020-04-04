#include <iostream>
using namespace std;

#define ll long long

int binary_search(ll n, ll k) {
	ll low = 0, high = n-2, ans = (n-2); 

	while(low <= high) {
		ll mid = (low+high)/2 ;

		if( (mid + (mid*(mid+1))/2 + 1)  >= k) {
			ans = mid; 
			high = mid-1; 
		}	
		else {
			low = mid+1; 
		}
	}

	return ans; 
}

int main() {
	int t; 
	cin >> t; 

	while(t--) {
		ll n, k; 
		cin >> n >> k;

		ll ans = binary_search(n, k); 
		ll val = ans + (ans*(ans+1))/2 + 1; 

		for(int i=1; i<=n; i++) {
			if(i == (n-ans-1)) {
				cout << 'b'; 
			}
			else if(i == (n-ans)+(val-k)) {
				cout << 'b'; 
			}
			else {
				cout << 'a'; 
			}
		}
		cout << endl; 
	}

	return 0; 
}