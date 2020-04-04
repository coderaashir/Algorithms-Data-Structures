#include <iostream> 
#include <vector> 
using namespace std;

int main() {
	int n;
	cin >> n;

	while(n--) {
		int a, b;
		cin >> a >> b;
		
		if(a%b) {
			cout << (((b*(a/b + 1))) - a) << endl;  
		}
		else {
			cout << 0 << endl; 
		}
	}

	return 0; 
}