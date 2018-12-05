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
	char getVertex(void) const {
		return vertex;
	}
};
list<pair<Graph, int>> Dijkstra_Algorithm(list<Graph> city, Graph startLocation);
int main(void) {
	ifstream ifp("meeting.inp");
	int N; ifp >> N;
	Graph location1(ifp), location2(ifp), location3(ifp);
	list<Graph> city;

	city.push_back(location1), city.push_back(location2), city.push_back(location3);

	for (int i = 0; i < N; i++) {
		char vertex; ifp >> vertex;
		list<Graph>::iterator vertexIter = find_if(city.begin(), city.end(), [=](Graph iter) {
			return iter.getVertex() == vertex;
		});
		if (vertexIter == city.end()) {
			city.emplace_back(vertex);
			advance(vertexIter, -1);
		}
		while (ifp >> vertex && vertex != '$') {
			list<Graph>::iterator nearVertexIter = find_if(city.begin(), city.end(), [=](Graph iter) {
				return iter.getVertex() == vertex;
			});
			if (nearVertexIter == city.end()) {
				city.emplace_back(vertex);
				advance(nearVertexIter, -1);
			}
			vertexIter->edge.push_back(&(*nearVertexIter));
		}
	}
	ifp.close();
	// 그래프 입력 끝.
	city.sort([](Graph A, Graph B) {
		return A.vertex < B.vertex;
	});
	list<pair<Graph, int>> location1RoutingTable = Dijkstra_Algorithm(city, location1);
	list<pair<Graph, int>> location2RoutingTable = Dijkstra_Algorithm(city, location2);
	list<pair<Graph, int>> location3RoutingTable = Dijkstra_Algorithm(city, location3);

	char location;
	int leastTime = infinite;
	for (Graph iter : city) {
		int time = 0;
		for (pair<Graph, int> iter2 : location1RoutingTable)
			if (iter.vertex == iter2.first.vertex) {
				time = time < iter2.second ? iter2.second : time;
				break;
			}
		for (pair<Graph, int> iter2 : location2RoutingTable)
			if (iter.vertex == iter2.first.vertex) {
				time = time < iter2.second ? iter2.second : time;
				break;
			}
		for (pair<Graph, int> iter2 : location3RoutingTable)
			if (iter.vertex == iter2.first.vertex) {
				time = time < iter2.second ? iter2.second : time;
				break;
			}
		if (time < leastTime) {
			leastTime = time;
			location = iter.vertex;
		}
	}
	ofstream ofp("meeting.out");
	ofp << location << endl << leastTime;
	ofp.close();
	return 0;
}

list<pair<Graph, int>> Dijkstra_Algorithm(list<Graph> city, Graph startLocation) {
	struct myclass {
		bool operator() (pair<Graph, int> arr1, pair<Graph, int> arr2) {
			if (arr1.second != arr2.second)
				return (arr1.second < arr2.second);
			else
				return (arr1.first.vertex < arr2.first.vertex);
		}
	} myobject;

	list<pair<Graph, int>> arr;

	for (Graph& iter : city) {
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
				edgeIter->second = edgeIter->second < iter.second + (1 + 2) ? edgeIter->second : iter.second + (1 + 2);
			else
				edgeIter->second = edgeIter->second < iter.second + (1) ? edgeIter->second : iter.second + (1);
			arr.sort(myobject);
		}
	}
	arr.sort([](pair<Graph, int> arr1, pair<Graph, int> arr2) {
		return arr1.first.vertex < arr2.first.vertex;
	});
	return arr;

}
