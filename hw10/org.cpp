#include <fstream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

struct org {
	org* boss = NULL;
	string name;
	int servant_count = 0;
	int height = 0; // root을 -1로 값을 부여함.
public:
	org(string name, org* boss) :name(name), boss(boss) {}
	org(string name) : name(name) {}
};
int countHeight(const org* node, int height = 0) {
	height += 1;
	if (node->boss == NULL)
		return height * (-1);
	else
		return countHeight(node->boss, height);
}
void setServantCount(org* node) {
	org* iter = node->boss;
	while (iter != NULL) {
		iter->servant_count += 1;
		iter = iter->boss;
	}
}
int main(void) {
	ifstream ifp("org.inp");
	list<org> Organization;
	
	int N;
	ifp >> N;

	string name, boss_name;
	while (ifp >> name && ifp >> boss_name) {
		list<org>::iterator bossIter = std::find_if(Organization.begin(), Organization.end(), [=](org a) {return (a.name == boss_name); });
		list<org>::iterator nameIter = std::find_if(Organization.begin(), Organization.end(), [=](org a) {return (a.name == name); });
		if (nameIter == Organization.end()&& bossIter == Organization.end()) {
			Organization.emplace_back(boss_name);
			Organization.emplace_back(name, &(Organization.back()));
		}
		else if(nameIter != Organization.end() && bossIter == Organization.end()) {
			Organization.emplace_back(boss_name);
			nameIter->boss = &Organization.back();
		}
		else if (nameIter == Organization.end() && bossIter != Organization.end()) {
			Organization.emplace_back(name);
			Organization.back().boss = &(*bossIter);
		}
		else { //nameIter != Organization.end()&& bossIter != Organization.end()
			nameIter->boss= &(*bossIter);
		}
	}ifp.close();

	for (org& iter : Organization) {
		iter.height = countHeight(&iter);
		setServantCount(&iter);
	}
	Organization.sort([](const org A, const org B) {
		if (A.servant_count != B.servant_count)
			return (A.servant_count > B.servant_count);
		else {
			if (A.servant_count != B.servant_count)
				return (A.servant_count > B.servant_count);
			else
				return (A.name < B.name);
		}
	});
	ofstream ofp("org.out");
	for (const org iter : Organization) {
		ofp << iter.name << " ";
	}ofp.close();
	
	return 0;
}