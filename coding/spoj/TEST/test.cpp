#include <iostream>
using namespace std;

int main() {
	for(;;) {
		int i;
		cin>> i;
		if (!cin.eof()) {
			if(i == 42) {
				break;
			}
			cout<<i<<endl;
		} else {
			break;
		}
	}
	return 0;
}
