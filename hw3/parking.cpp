#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

class parking_lot{
private:
    int numofParking;
	int sizeofArea;
	vector<int> car;

public:
    parking_lot(int _size){
		car.resize(_size, 0);
		numofParking = 0;
		sizeofArea = _size;

    }
    void checkSize(void);
    void inout(int carNumber);
    void print(void) const;
    void writedata(std::ofstream& _out);
};

int k, n;

int main(void){

    std::ifstream infile;
    infile.open("parking.inp");

    infile >> k;
    infile >> n;

    int *num = new int[n];
    for(int i = 0; i <n; i++)
        infile >> num[i];
    infile.close();

    class parking_lot exhibition(k);

    for(int i = 0; i< n; i++){
		if (num[i] > 0) {
			exhibition.checkSize();
			exhibition.inout(num[i]);
		}
		else {
			exhibition.inout(num[i]);
			exhibition.checkSize();
		}

    }

    exhibition.print();

	std::ofstream outfile;
    outfile.open("parking.out");
    exhibition.writedata(outfile);
	outfile.close();

	delete[] num;

    return 0;
}

void parking_lot::checkSize() {
	if(numofParking == sizeofArea)
	{
		car.resize((car.size() * 2), 0);
		sizeofArea *= 2;
	}
	else if (numofParking <= (sizeofArea / 3.0)) {

		if (sizeofArea > k) {
			for (vector<int>::iterator iter = car.begin(); iter != car.end();) {
				if (*iter == 0) {
					car.erase(iter);
					iter = car.begin();
				}
				else {
					iter++;
				}
			}
			car.resize((sizeofArea / 2), 0);
			sizeofArea /= 2;

		}
	}
}
void parking_lot::inout(int carNumber) {
	if (carNumber > 0) {
		for (vector<int>::iterator iter = car.begin(); iter != car.end(); iter++) {
			if (*iter == 0) {
				*iter = carNumber;
				numofParking += 1;
				break;
			}
		}
	}
	else if (carNumber < 0) {
		for (vector<int>::iterator iter = car.begin(); iter != car.end(); iter++) {
			if (*iter == (-carNumber)) {
				*iter = 0;
				numofParking -= 1;
				break;
			}
		}
	}
}
void parking_lot::print(void) const {
	int i = 0;
	for (vector<int>::const_iterator iter = car.begin(); iter != car.end(); iter++) {
		if (*iter != 0) {
			std::cout << i+1 << " " << *iter << std::endl;
		}
		i++;
	}
}

void parking_lot::writedata(std::ofstream& _out) {
	int i = 0;
	for (vector<int>::const_iterator iter = car.begin(); iter != car.end(); iter++) {
		if (*iter != 0) {
			_out << i+1 << " " << *iter << std::endl;
		}
		i++;
	}
}
