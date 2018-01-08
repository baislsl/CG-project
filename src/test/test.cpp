#include <iostream>
#include <random>
#include <map>

using namespace std;

int main(){
	std::map<int ,std::vector<int> > gg;

	auto g = gg[0];
	std::cout << g.size();
}