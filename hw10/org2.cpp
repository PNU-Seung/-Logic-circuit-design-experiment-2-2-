#include <fstream>
#include <list>
#include <algorithm>
#include <string>
#include <iostream>
using std::list;
using std::ifstream;
using std::string;

class org {
private:
	list<org*> servant;
	string name;
	int depth = 1;
public:
	org(string name) :name(name) {}
	string getName() {
		return name;
	}
	void addServant(org* servant) {
		this->servant.push_back(servant);
	}

};

int main(void) {
	ifstream ifp("1.inp");
	list<org> Organization;

	int N;
	ifp >> N;

	string name, boss_name;
	while (ifp >> name && ifp >> boss_name) {
		list<org>::iterator iter = std::find_if(Organization.begin(), Organization.end(), [=](org a) {return (a.getName() == boss_name); });
		if (iter == Organization.end()) {
			Organization.emplace_back(boss_name);
			
		}
		else {
			
		}
	}
}