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
		tree* iter = this;
		while (iter != nullptr && iter->word != word) {
			if (iter->word > word)
				iter = iter->left;
			else if (iter->word < word)
				iter = iter->right;
		}// find
		if (!iter)
			return; // not exist.
		else if (iter == this) {

		}
		else {

		}

		
	}


};
/*
tree* find_max(tree* node) {
	if (!node)
		return nullptr;
	if (node->right == nullptr)
		return node;
	else
		return find_max(node->right);

}
tree* find_min(tree* node) {
	if (!node)
		return nullptr;
	if (node->left == nullptr)
		return node;
	else
		return find_min(node->left);
}
tree* find_data(tree* node, string word) {
	if (!node)
		return nullptr;
	if (node->word == word)
		return node;
	else if (node->word > word) {
		return find_data(node->left, word);
	}
	else { // node->word < word
		return find_data(node->right, word);
	}
}
tree* upperNode(tree* node, tree* target) {
	if (node->left == target || node->right == target)
		return node;
	else {
		if (node->word > target->word)
			return upperNode(node->left, target);
		else
			return upperNode(node->right, target);
	}

}
void addData(string word, tree* node, int depth = 0) {
	depth++;
	if (!node) {
		node = new tree(word, depth);
		return;
	}
	if (node->word == word) {
		return;
	}
	else if (node->word < word) { // right
		if (node->right == nullptr) {
			node->right = new tree(word, depth);
		}
		else
			addData(word, node->right, depth);
	}
	else { // left
		if (node->left == nullptr) {
			node->left = new tree(word, depth);
		}
		else
			addData(word, node->left, depth);
	}
}
void deleteData(string word , tree* node) {
	tree* iter = find_data(node, word);
	if (!iter)
		return;

	if (iter->left != nullptr) {
		tree* iterMax = find_max(iter->left);
		if (iterMax->right != nullptr) {
			iterMax->word = iterMax->right->word;
			delete iterMax->right;
			iterMax->right = nullptr;
		}
		else {

		}
	}
	

}
*/
int main(void) {
	tree* BST = nullptr;
	if (BST == nullptr)
		BST = new tree("phone");

	BST->addData("banana");
	BST->addData("chip");
	
	delete BST;
	return 0;
}