#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <utility>

#define vertexRequireTime 1
#define edgeRequireTime 2
#define infinite 100000

using namespace std;

struct Graph {
	char vertex;
	list<Graph*> edge;

	Graph(char vertex) :vertex(vertex) {}
	Graph(ifstream& input) {
		input >> vertex;
	}
	Graph() {}
};
pair<char, int>* Dijkstra_Algorithm(list<Graph> city, Graph startLocation);
int main(void) {
	ifstream ifp("meeting.inp");
	int N; ifp >> N;
	Graph location1(ifp), location2(ifp), location3(ifp);
	list<Graph> city;

	city.push_back(location1), city.push_back(location2), city.push_back(location3);

	for (int i = 0; i < N; i++) {
		char vertex; ifp >> vertex;
		list<Graph>::iterator vertexIter = find_if(city.begin(), city.end(), [=](Graph iter) {
			return iter.vertex == vertex;
		});
		if (vertexIter == city.end()) {
			city.emplace_back(vertex);
			advance(vertexIter, -1);
		}
		while (ifp >> vertex && vertex != '$') {
			list<Graph>::iterator nearVertexIter = find_if(city.begin(), city.end(), [=](Graph iter) {
				return iter.vertex == vertex;
			});
			if (nearVertexIter == city.end()) {
				city.emplace_back(vertex);
				advance(nearVertexIter, -1);
			}
			vertexIter->edge.push_back(&(*nearVertexIter));
		}
	}ifp.close();

	city.sort([](Graph A, Graph B) {
		return A.vertex < B.vertex;
	});
	pair<char, int>* location1RoutingTable = Dijkstra_Algorithm(city, location1); //location1���� �ٸ� �������� �Ÿ��� ����� ǥ
	pair<char, int>* location2RoutingTable = Dijkstra_Algorithm(city, location2); //location2���� �ٸ� �������� �Ÿ��� ����� ǥ
	pair<char, int>* location3RoutingTable = Dijkstra_Algorithm(city, location3); //location3���� �ٸ� �������� �Ÿ��� ����� ǥ
	//RoutingTable�� ���ĺ� ������ ���� �Ǿ� ����.
	char location;
	int leastTime = infinite;
	int i = 0;
	for (const Graph iter : city) {
		int time =0;
		if (location1RoutingTable[i].second > time)
			time = location1RoutingTable[i].second;
		if (location2RoutingTable[i].second > time)
			time = location2RoutingTable[i].second;
		if (location3RoutingTable[i].second > time)
			time = location3RoutingTable[i].second;
		if (time < leastTime) {
			leastTime = time;
			location = iter.vertex;
		}
		i++;
	}
	ofstream ofp("meeting.out");
	ofp << location << endl << leastTime;
	ofp.close();
	delete[] location1RoutingTable;
	delete[] location2RoutingTable;
	delete[] location3RoutingTable;

	return 0;
}

pair<char, int>* Dijkstra_Algorithm(list<Graph> city, Graph startLocation) { //���ͽ�Ʈ�� �˰��� ����.
	struct myclass {
		bool operator()(pair<Graph, int> arr1, pair<Graph, int> arr2) { // �Ÿ��� ª�� ���� �տ�, ������� ���ĺ� ������ ������ ������ ����.
			if (arr1.second != arr2.second)
				return (arr1.second < arr2.second);
			else
				return (arr1.first.vertex < arr2.first.vertex);
		}
	}myobject;
	list<pair<Graph, int>> arr;
	for (Graph& iter : city) { // �ڱ��ڽű����� �Ÿ��� 0 �������� ������.
		if (iter.vertex == startLocation.vertex)
			arr.emplace_back(iter, 0);
		else
			arr.emplace_back(iter, infinite);
	}
	arr.sort(myobject);
	for (pair<Graph, int> iter : arr) {
		for (Graph* edges : (iter.first.edge)) {
			list<pair<Graph, int>>::iterator edgeIter = find_if(arr.begin(), arr.end(), [=](pair<Graph, int> node) {
				return node.first.vertex == edges->vertex;
			});
			if (iter.first.vertex != arr.front().first.vertex)
				edgeIter->second = edgeIter->second < iter.second + (vertexRequireTime + edgeRequireTime) ? edgeIter->second : iter.second + (vertexRequireTime + edgeRequireTime);
			else
				edgeIter->second = edgeIter->second < iter.second + (vertexRequireTime) ? edgeIter->second : iter.second + (vertexRequireTime);
			arr.sort(myobject);  // �Ÿ� ���� ����-> ������ ������ ����.
		}
	}
	arr.sort([](pair<Graph, int> arr1, pair<Graph, int> arr2) {
		return arr1.first.vertex < arr2.first.vertex;
	});
	pair<char, int>* routingTable = new pair<char, int>[city.size()];

	int i = 0;
	for (pair<Graph, int> iter : arr) {
		routingTable[i].first = iter.first.vertex;
		routingTable[i].second = iter.second;
		i++;
	}
	return routingTable;
}
