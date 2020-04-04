#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;

	while(t--) {
		int n;
		string s;

		cin >> n >> s; 
		string a = "", b = ""; 

		bool done = false; 

		for(int i = 0; i < n; i++) {
			if(s[i] == '2' && !done) {
				a += '1'; 
				b += '1'; 
			}
			else if(s[i] == '2' && done) {
				a += '0'; 
				b += '2'; 
			}
			else if(s[i] == '1' && !done) {
				a += '1'; 
				b += '0'; 
				done = true; 
			}
			else if(s[i] == '1' && done) {
				a += '0'; 
				b += '1'; 
			}
			else if(s[i] == '0') {
				a += '0'; 
				b += '0'; 
			}
		}

		cout << a << endl; 
		cout << b << endl;
	}

	return 0; 
}