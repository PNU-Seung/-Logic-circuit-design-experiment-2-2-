#include <bits/stdc++.h>

using namespace std;

class org {
private:
	org* boss = NULL;
	string name;
	int servant_count = 0;
	int height = 0; // root을 -1로 값을 부여함.
public:
	org(string name, org* boss) :name(name), boss(boss) {}
	org(string name) : name(name) {}

	void setBoss(org* boss) {
		this->boss = boss;
	}
	void setHeight(int height) {
		this->height = height;
	}
	string getName(void) const {
		return name;
	}
	int getServantCount(void) const {
		return servant_count;
	}
	int getHeight(void) const {
		return height;
	}
	friend int countHeight(const org* node, int height);
	friend void setServantCount(org* node);
};

void setServantCount(org* node) {
	org* iter = node->boss;
	while (iter != NULL) {
		iter->servant_count += 1;
		iter = iter->boss;
	}
}
int countHeight(const org* node, int height = 0) {
	height += 1;
	if (node->boss == NULL)
		return height*(-1);
	else
		return countHeight(node->boss, height);
}

int main(void) {
	ifstream ifp("org.inp");
	list<org> Organization;
	
	int N;
	ifp >> N;

	string name, boss_name;
	while (ifp >> name && ifp >> boss_name) {
		list<org>::iterator bossIter = std::find_if(Organization.begin(), Organization.end(), [=](org a) {return (a.getName() == boss_name); });
		list<org>::iterator nameIter = std::find_if(Organization.begin(), Organization.end(), [=](org a) {return (a.getName() == name); });
		if (nameIter == Organization.end()&& bossIter == Organization.end()) {
			Organization.emplace_back(boss_name);
			Organization.emplace_back(name, &(Organization.back()));
		}
		else if(nameIter != Organization.end() && bossIter == Organization.end()) {
			Organization.emplace_back(boss_name);
			nameIter->setBoss(&Organization.back());
		}
		else if (nameIter == Organization.end() && bossIter != Organization.end()) {
			Organization.emplace_back(name);
			Organization.back().setBoss(&(*bossIter));
		}
		else { //nameIter != Organization.end()&& bossIter != Organization.end()
			nameIter->setBoss(&(*bossIter));
		}
	}ifp.close();

	for (org& iter : Organization) {
		iter.setHeight(countHeight(&iter));
		setServantCount(&iter);
	}
	Organization.sort([](const org A, const org B) {
		if (A.getServantCount() != B.getServantCount())
			return (A.getServantCount() > B.getServantCount());
		else {
			if (A.getHeight() != B.getHeight())
				return (A.getHeight() > B.getHeight());
			else
				return (A.getName() < B.getName());
		}
	});
	ofstream ofp("org.out");
	for (const org iter : Organization) {
		ofp << iter.getName() << " ";
	}ofp.close();
	
	return 0;
}