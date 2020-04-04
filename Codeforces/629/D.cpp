#include <iostream>
using namespace std;

int main () {
	int q; 
	cin >> q;

	while(q--) {
		int n;
		cin >> n;

		int arr[n+1]; 
		int col[n+1]; 

		for(int i=1; i<=n; i++) {
			cin >> arr[i]; 
		}

		col[1] = 0; 
		int hi = 0; 

		bool equal = true; 

		for(int i=2; i <= n; i++) {
			if(arr[i] != arr[i-1])
				equal = false; 
		}

		if(equal) {	
			for(int i=1; i<=n; i++)
				col[i] = 0; 
		}

		else if(n%2) {
			bool can_do = false; 

			for(int i=2; i<=n; i++) {
				if(arr[i] == arr[i-1])
					can_do = true; 
			}

			if(can_do) {
				bool done = false; 
				col[1] = 0; 

				for(int i=2; i<=n; i++) {
					if(arr[i] == arr[i-1] && !done) {
						done = true; 
						col[i] = col[i-1]; 
					}
					else {
						col[i] = !col[i-1]; 
					}
				}
			}
			else if (arr[1] == arr[n]) {
				col[1] = 0; 

				for(int i=2; i<=n; i++)
					col[i] = !col[i-1]; 
			}
			else {
				col[1] = 0; 

				for(int i=2; i<n; i++) {
					col[i] = !col[i-1]; 
				}

				col[n] = 2; 
			}	
		}

		else {
			col[1] = 0; 
			for(int i=2; i<=n; i++)
				col[i] = !col[i-1];
		}

		if(col[n] == 2) 
			cout << 3 << endl; 
		else if(equal)
			cout << 1 << endl; 
		else 
			cout << 2 << endl; 

		for(int i=1; i<=n; i++)
			cout << (col[i]+1) << " "; 

		cout << endl; 
	}	

	return 0; 
}