#include <fstream>
#include <list>
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
		if (this->left == nullptr && this->right == nullptr)
		{ }
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
			if (iter->word > word)
				iter = iter->left;
			else if (iter->word < word)
				iter = iter->right;
			else
				return; // already exist.
		}

		iter = new tree(word, upperIter->depth + 1);
		if (upperIter->word > word)
			upperIter->left = iter;
		else if (upperIter->word < word) {
			upperIter->right = iter;
		}
	}
	void deleteData(string word) {
		tree* upperNode = nullptr;
		tree* deleteNode = this;
		while (deleteNode != nullptr && deleteNode->word != word) {
			upperNode = deleteNode;
			if (deleteNode->word > word)
				deleteNode = deleteNode->left;
			else if (deleteNode->word < word)
				deleteNode = deleteNode->right;
		} // find node -> 찾으면 deleteNode에, 상위노드는 upperNode.
		
		if (!deleteNode)
			return; // not exist.
		
		if (deleteNode->left == nullptr && deleteNode->right == nullptr) {
			delete deleteNode;
			if (upperNode->word > word)
				upperNode->left = nullptr;
			else if (upperNode->word < word)
				upperNode->right = nullptr;
		}
		else if (deleteNode->left != nullptr) {
			tree* iter = deleteNode->left;
			while (iter->right != nullptr) {
				upperNode = iter;
				iter = iter->right;
			} // 왼쪽부트리의 최대값 찾기
			deleteNode->word = iter->word; // 기존값을 지우고 최대값으로 교체.

			if (iter->left)
				upperNode->right = iter->left;
			else
				upperNode->right = iter;
			delete iter;
		}
		else { //deleteNode->right != nullptr
			tree* iter = deleteNode->right;
			while (iter->left != nullptr) {
				upperNode = iter;
				iter = iter->left;
			} // 오른쪽부트리의 최소값 찾기
			deleteNode->word = iter->word; // 기존값을 지우고 최소값으로 교체.

			if (iter->right)
				upperNode->left = iter->right;
			else
				upperNode->left = iter;
			delete iter;
		}
	}
};

int main(void) {
	tree* BST = nullptr;
	if (BST == nullptr)
		BST = new tree("phone");

	BST->addData("banana");
	BST->addData("chip");
	
	delete BST;
	return 0;
}