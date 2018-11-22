#include <fstream>
#include <string>
using namespace std;

class tree {
	string word;
	tree* left = nullptr;
	tree* right = nullptr;
	int depth = 1;
public:
	tree(string word, int depth = 1) : word(word), depth(depth) {}
	~tree() {
		if (this->left == nullptr && this->right == nullptr) { }
		else if (this->left != nullptr) {
			delete this->left;
			this->left = nullptr;
		}
		else { // this->right != nullptr
			delete this->right;
			this->left = nullptr;
		}
	}
	void addData(string word) {
		tree* upperIter = nullptr;
		tree* iter = this;
		while (iter != nullptr) {
			upperIter = iter;
			if (iter->word == word) {
				return; // already exist.
			}
			else if (iter->word > word)
				iter = iter->left;
			else if (iter->word < word)
				iter = iter->right;
			else
				exit(-1); 
		}

		iter = new tree(word, upperIter->depth + 1);
		if (upperIter->word > word)
			upperIter->left = iter;
		else if (upperIter->word < word) {
			upperIter->right = iter;
		}
	}
	bool deleteData(string word) {
	}

};

int main(void) {
	tree* BST = nullptr;
	
	ifstream ifp("bst.inp");
	ofstream ofp("bst.out");

	int N;
	string order;

	ifp >> N;

	for (int i = 0; i < N; i++) {
		ifp >> order;
		if (order == "+") {
			ifp >> order;
			if (BST == nullptr)
				BST = new tree(order);
			else
				BST->addData(order);
		}
		else if (order == "-") {
			ifp >> order;
			if (!BST->deleteData(order))
				BST = nullptr;
		}
		else if (order == "leaf") {
			
		}
		else if (order == "depth") {
			
			
		}
		else {
			exit(-1);
		}
	}
	delete BST;
	ifp.close();
	ofp.close();

	return 0;
}