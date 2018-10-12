#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <fstream>

// information_t : 고객id + 구매한 물건의 수
#define information_t pair<int,int>


using std::vector;
using std::pair;
using std::queue;
using std::make_pair;
queue<information_t> customer;
vector<queue<information_t>> calculator;

vector<queue<information_t>>::iterator selectCalculator(void);


int main(void) {
	int N, k;
	std::ifstream ifp("3.inp");
	std::ofstream ofp("shoppping.out");
	ifp >> N, ifp >> k;

	queue <information_t> _cal;
	for (int i = 0; i < k; i++)
		calculator.push_back(_cal);

	int customerID, customerOBJECT;
	while (ifp >> customerID && ifp >> customerOBJECT) {
		customer.push(make_pair(customerID, customerOBJECT));
	}
	ifp.close();
	while ( not(customer.empty()) ) {
		vector<queue<information_t>>::iterator iter = selectCalculator();
		if (iter->empty())
			iter->push(customer.front());
		else
			iter->push(make_pair(customer.front().first, customer.front().second+iter->back().second));
			// id + 이전까지의 물건 갯수 + 새로 추가되는 물건 갯수
		customer.pop();
	}
	int size = 0;
	int time = 0;
	for (vector<queue<information_t>>::reverse_iterator iter = calculator.rbegin(); iter != calculator.rend(); ++iter)
		if (iter->empty())
			size++;
	while (size != k) {
		for (vector<queue<information_t>>::reverse_iterator iter = calculator.rbegin(); iter != calculator.rend(); ++iter) {
			if (not(iter->empty())) {
				if ((iter->front().second) == time) {
					ofp << iter->front().first << std::endl;
					iter->pop();
				}
				if (iter->empty())
					size++;
			}
		}
		time++;
	}
	ofp.close();
	return 0;

}
vector<queue<information_t>>::iterator selectCalculator(void) {
	for (vector<queue<information_t>>::iterator iter = calculator.begin(); iter != calculator.end(); iter++) {
		if (iter->empty())
			return iter;
	}

	vector<queue<information_t>>::iterator freeCalculator = calculator.begin();
	for (vector<queue<information_t>>::iterator iter = calculator.begin()+1; iter != calculator.end(); iter++) {
		if (freeCalculator->back().second > iter->back().second)
			freeCalculator = iter;
	}
	return freeCalculator;
}
