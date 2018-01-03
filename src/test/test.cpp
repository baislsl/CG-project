#include <iostream>
#include <random>

using namespace std;

int main(){
	std::uniform_int_distribution<int> u(0, 4);
	std::default_random_engine e(0);


	for(int i = 0 ; i< 40;i++){
		cout << u(e) << " ";
		if(i %10 == 0) cout << endl;
	}
}