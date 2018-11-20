#include <bits/stdc++.h>

using namespace std;

typedef struct Node
{
	string name;
	vector<Node *>child;
	int depth = 0;
	int child_cnt = 0;
}Node;

Node *newNode(string name)
{
	Node *temp = new Node;
	temp->name = name;
	return temp;
}

vector<Node*> find_Leaves(Node *node) {
	deque<Node *> leaf;
	vector<Node *> vec;
	if (node->child.size() == 0) {
		return vec;
	}
	for (int i = 0; i < node->child.size(); i++) {
		leaf.push_back(node->child[i]);
	}
	while (leaf.size() != 0) {
		Node * n = leaf.front();
		if (n->child.size() == 0) vec.push_back(n);
		else {
			for (int j = 0; j < n->child.size(); j++) {
				leaf.push_back(n->child[j]);
			}
		}
		leaf.pop_front();
	}
	return vec;
}

vector<Node*> find_depth(Node *node) {
	deque<Node *> leaf;

	for (int i = 0; i < node->child.size(); i++) {
		node->child[i]->depth++;
		leaf.push_back(node->child[i]);
	}
	while (leaf.size() != 0) {
		Node *n = leaf.front();
		if (n->child.size() != 0) {
			for (int j = 0; j < n->child.size(); j++) {
				n->child[j]->depth = n->depth + 1;
				leaf.push_back(n->child[j]);
			}
		}
		else {
			for (int j = 0; j < n->child.size(); j++) {
				n->child[j]->depth = n->depth + 1;
			}
		}
		leaf.pop_front();
	}
}

void find_Child(Node *node) {
	deque<Node *> leaf;
	int cnt = 0;
	if (node->child.size() == 0) {
		return;
	}

	for (int i = 0; i < node->child.size(); i++) {
		leaf.push_back(node->child[i]);
		cnt++;
	}
	while (leaf.size() != 0) {
		Node * n = leaf.front();
		if (n->child.size() == 0) {

		}
		else {
			for (int j = 0; j < n->child.size(); j++) {
				leaf.push_back(n->child[j]);
				cnt++;
			}
		}
		leaf.pop_front();
	}
	node->child_cnt = cnt;
}

bool CompareNode(Node *a, Node *b)
{
	if (a->child_cnt > b->child_cnt) {
		return true;
	}
	else if (a->child_cnt == b->child_cnt) {
		if (a->depth < b->depth) {
			return true;
		}
		else if (a->depth == b->depth) {
			if ((a->name).compare(b->name) < 0) {
				return true;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

int main()
{
	ifstream in("org.inp");
	ofstream out("org.out");

	int N;
	in >> N;

	vector<Node *> nodeList;

	for (int i = 0; i < N - 1; i++) {
		string boss;
		string person;
		in >> person >> boss;
		if (i == 0) {
			Node * n1 = newNode(boss);
			Node * n2 = newNode(person);
			nodeList.push_back(n1);
			nodeList.push_back(n2);
			n1->child.push_back(n2);
		}
		else {
			Node *n1;
			Node* n2;
			bool chk1 = false;
			bool chk2 = false;
			for (int j = 0; j < nodeList.size(); j++) {
				if (nodeList[j]->name == person) {
					chk1 = true;
					n1 = nodeList[j];
				}
				else if (nodeList[j]->name == boss) {
					chk2 = true;
					n2 = nodeList[j];
				}
			}
			if (chk1 == false) {
				n1 = newNode(person);
				nodeList.push_back(n1);
			}
			if (chk2 == false) {
				n2 = newNode(boss);
				nodeList.push_back(n2);
			}
			n2->child.push_back(n1);
		}
	}
	Node * root;
	for (int i = 0; i < nodeList.size(); i++) {
		find_Child(nodeList[i]);
		if (nodeList[i]->child_cnt == (nodeList.size() - 1)) {
			root = nodeList[i];
		}
	}
	find_depth(root);
	sort(nodeList.begin(), nodeList.end(), CompareNode);
	for (int i = 0; i < nodeList.size(); i++) {
		out << nodeList[i]->name << " ";
	}

	in.close();
	out.close();
}