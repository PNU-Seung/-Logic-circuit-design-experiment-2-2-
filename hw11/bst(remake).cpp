#include <fstream>
#include <string>
using namespace std;

class tree {
	string word;
	tree* left = nullptr;
	tree* right = nullptr;
	int depth;
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
	int getMaxDepth(int depth = 0) {
		if (!this)
			return depth;
		else {
			depth++;
			int leftMaxDepth = this->left->getMaxDepth(depth);
			int rightMaxDepth = this->right->getMaxDepth(depth);
			return leftMaxDepth > rightMaxDepth ? leftMaxDepth : rightMaxDepth;
		}
	}
	tree* findMax() {
		tree* max = this;
		while (max->right != nullptr)
			max = max->right;
		return max;
	}
	tree* findMin() {
		tree* min = this;
		while(min->left != nullptr)
			min = min->left;
		return min;
	}
	tree* addData(string word) {
		if (this == nullptr)
			return (new tree(word));
		tree* upperIter = nullptr;
		tree* iter = this;
		while (iter != nullptr) {
			upperIter = iter;
			if (iter->word == word) {
				return this; // already exist.
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
		return this;
	}
	tree* deleteData(tree* upperNode, string word) {
		if (this == nullptr)
			return nullptr;
		else if (this->word < word)
			this->right = this->right->deleteData(this, word);
		else if (this->word > word)
			this->left = this->left->deleteData(this, word);
		else { //this->word == word
			if (this->left || this->right) {
				tree* temp = nullptr;
				if (this->left) {
					temp = this->left->findMax();
					this->word = temp->word;
					this->left = this->left->deleteData(this, temp->word);
				}
				else {
					temp = this->right->findMin();
					this->word = temp->word;
					this->right = this->right->deleteData(this, temp->word);
				}
			}
			else { // leafNode;
				if (upperNode->left == this) upperNode->left = nullptr;
				if (upperNode->right == this) upperNode->right = nullptr;
				delete this;
				return nullptr;
			}
		}
		return this;
	}
	void printDepth(ofstream& out, int depth) {
		if (!this)
			return;
		if (this->depth == depth)
			out << word << " ";
		else {
			this->left->printDepth(out, depth);
			this->right->printDepth(out, depth);
		}
	}
	void printLeafNode(ofstream& out) {
		if (!this)
			return;
		else {
			if (this->left == nullptr && this->right == nullptr)
				out << this->word << " ";
			else {
					this->left->printLeafNode(out);
					this->right->printLeafNode(out);
			}
		}
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
			BST = BST->addData(order);
		}
		else if (order == "-") {
			ifp >> order;
			BST = BST->deleteData(BST, order);
		}
		else if (order == "leaf") {
			BST->printLeafNode(ofp);
			ofp << endl;
		}
		else if (order == "depth") {
			int N;
			ifp >> N;
			if (N > BST->getMaxDepth())
				ofp << "NO" << endl;
			else {
				BST->printDepth(ofp, N);
				ofp << endl;
			}
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