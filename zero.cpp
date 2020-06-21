// zeronet.cpp: 定义应用程序的入口点。
//

#include "zeronet.h"
#include <memory>
#include <vector>
#include "container/List.h"
using namespace std;


int main()
{
	zeronet::List list;
	int a = 8;
	std::vector<int> test;
	test.push_back(0);
	test.push_back(1);
	list.append(8);
	list.append(test);
	std::cout << list.get<int>(0) << std::endl;
	test = list.get<std::vector<int>>(1);
	for (auto& t : test) {
		std::cout << t << std::endl;
	}
	return 0;
}
