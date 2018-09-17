#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class syslog{
private:
    int d;
    vector <int> t;
public:
    syslog(){ d =0; }
    void input_d(int _d);
    void input_t(int _t);
    int getD(void) const;
    int getT(int index) const;
    int getIndexT(int num) const;
    int countT(void) const;
    void printAll(void) const;
};
class dtime{
private:
    int d_start;
    int d_end;
    int t_start;
    int t_end;
public:
    dtime(int _d_start,int  _d_end,int _t_start,int _t_end){
    d_start = _d_start;
    d_end = _d_end;
    t_start = _t_start;
    t_end = _t_end;
    }
    void setTime(int ds,int  ts,int de,int te){
    d_start = ds;
    d_end = de;
    t_start = ts;
    t_end = te;
    }
    dtime() {
    d_start = 0;
    d_end = 0;
    t_start = 0;
    t_end = 0;
    }
    int getDstart(void) const;
    int getDend(void) const;
    int getTstart(void) const;
    int getTend(void) const;
    void printAll(void) const;
};

void readLog(ifstream &in, syslog data[], int _sizeD);
void readLog(ifstream &in, dtime data[], int _sizeinp);
int countTime(int ds, int de, int ts, int te, const syslog* data, int dataSize); //d start t start, d end ..
int main(void)
{
    //input syslog.txt
    ifstream inLog;
    inLog.open("syslog.txt");
    int sizeLog=0;
    inLog >> sizeLog;

    syslog* serverData;
    serverData = new syslog[sizeLog];
    readLog(inLog, serverData, sizeLog);
    inLog.close();

    //input log.inp
    inLog.open("log.inp");
	int sizeinp = 0;
    inLog >> sizeinp;

    dtime* inTime;
inTime = new dtime[sizeinp];
readLog(inLog, inTime, sizeinp);
inLog.close();

//find result
int *result = new int[sizeinp];
for (int i = 0; i < sizeinp; i++)
	result[i] = countTime(inTime[i].getDstart(), inTime[i].getDend(), inTime[i].getTstart(), inTime[i].getTend(), serverData, sizeLog);

//write log.out

ofstream outLog;
outLog.open("log.out");
for (int i = 0; i < sizeinp; i++)
	outLog << result[i] << endl;
outLog.close();

delete[] serverData;
delete[] inTime;
delete[] result;



return 0;

}

void syslog::input_d(int _d) { d = _d; }
void syslog::input_t(int _t) { t.push_back(_t); }
int syslog::getD(void) const { return d; }
int syslog::countT(void) const { return t.size(); }
void syslog::printAll(void) const {
	cout << d << " ";
	for (vector<int>::const_iterator i = t.begin(); i < t.end(); i++)
		cout << *i << " ";
	cout << endl;
	return;
}
int syslog::getT(int index) const { return t.at(index); }
int syslog::getIndexT(int num) const {
	int index = 0;
	vector<int>::const_iterator i = t.begin();
	while (i < t.end() && *i != num) {
		index++;
		i++;
	}
	if (index == t.size())
		index = -1;
	return index;
}
void readLog(ifstream &in, syslog data[], int _sizeD)
{
	for (int i = 0; i < _sizeD; i++)
	{
		int num;
		in >> num;
		data[i].input_d(num);

		while (true) {
			in >> num;
			if (num == 0)
				break;
			else
				data[i].input_t(num);
		}
	}

}
void readLog(ifstream &in, dtime data[], int _sizeinp)
{
	int ds, ts, de, te; //d start t start, d end ..
	for (int i = 0; i < _sizeinp; i++) {
		in >> ds;
		in >> ts;
		in >> de;
		in >> te;
		data[i].setTime(ds, ts, de, te);
	}
}
int dtime::getDstart(void) const { return d_start; }
int dtime::getDend(void) const { return d_end; }
int dtime::getTstart(void) const { return t_start; }
int dtime::getTend(void) const { return t_end; }
void dtime::printAll(void) const {
	cout << d_start << " " << t_start << " " << d_end << " " << t_end << endl;
}

int countTime(int ds, int de, int ts, int te, const syslog* data, int dataSize)
{
	int result = 0;
	int _ds = 0, _de = 0;
	bool ds_boundary, de_boundary;
	for (int i = 0; i < dataSize; i++) {
		if (ds > data[i].getD()) {
			if (i + 1 != dataSize) {
				if (data[i + 1].getD() > ds){ // i+1 > ds > i
					_ds = i + 1;
					ds_boundary = false;
					break;
				}
			}
			else if (i + 1 == dataSize) {
				_ds = i+1;
				ds_boundary = false;
				break;
			}

		}
		else if (ds == data[i].getD()) {
			if (i + 1 != dataSize) {
				if (data[i + 1].getD() > ds) { // i+1 > ds = i
					_ds = i;
					ds_boundary = true;
					break;
				}
			}
			else if (i + 1 == dataSize) {
				_ds = i;
				ds_boundary = true;
				break;
			}
		}
		else if (ds < data[i].getD()) {
			if (i == 0) {
				_ds = i;
				ds_boundary = false;
				break;
			}
		}
    }

	for (int i = 0; i < dataSize; i++) {
		if (de > data[i].getD()) {
			if (i + 1 != dataSize) {
				if (data[i + 1].getD() > de) { // i+1 > de > i
					_de = i;
					de_boundary = false;
					break;
				}
			}
			else if (i + 1 == dataSize) { // d가 254까지 있을떄 de가 255인 경우
				_de = i;
				de_boundary = false;
				break;
			}
		}
		else if (de == data[i].getD()) {
			if (i + 1 != dataSize) {
				if (data[i + 1].getD() > de) { // i+1 > de = i
					_de = i;
					de_boundary = true;
					break;
				}
			}
			else if (i + 1 == dataSize) {  // de = i 이고 마지막 d.
				_de = i;
				de_boundary = true;
				break;
			}
		}
		else if (de < data[i].getD()) {
			if (i == 0) {
				_de = -1;
				de_boundary = false;
				break;
			}
		}
	}

	if ((ds_boundary == false) && (de_boundary == false)) {
		if (_ds != _de) {
			for (int i = _ds; i < _de + 1; i++) {
				result += data[i].countT();
			}
		}
		else if (_ds == _de) {
			result += data[_ds].countT();
		}
	}
	else if ((ds_boundary == false) && (de_boundary == true)) {
		if ((ds != de)) {
			for (int i = _ds; i < _de; i++) {
				result += data[i].countT();
			}
			for (int i = 0; i < data[_de].countT(); i++)
				if (te >= data[_de].getT(i))
					result++;
		}
		else { //ds == de
			for (int i = 0; i < data[_de].countT(); i++)
				if (te >= data[_de].getT(i))
					result++;
		}
	}
	else if ((ds_boundary == true) && (de_boundary == false)) {
		if (ds != de) {
			for (int i = _ds + 1; i < _de + 1; i++) {
				result += data[i].countT();
			}
			int num = 0;
			for (int i = 0; i < data[_ds].countT(); i++)
				if (ts > data[_ds].getT(i))
					num++;
			result += (data[_ds].countT() - num);
		}
		else { //ds == de
			int num = 0;
			for (int i = 0; i < data[_ds].countT(); i++)
				if (ts > data[_ds].getT(i))
					num++;
			result += (data[_ds].countT() - num);
		}
	}
	else if ((ds_boundary == true) && (de_boundary == true)) {
		for (int i = _ds+1; i < _de; i++) {
			result += data[i].countT();
		}

		int num = 0;
		if (_de != _ds) {
			for (int i = 0; i < data[_ds].countT(); i++)
				if (ts > data[_ds].getT(i))
					num++;
			result += (data[_ds].countT() - num);

			for (int i = 0; i < data[_de].countT(); i++)
				if (te >= data[_de].getT(i))
					result++;
		}
		else { //_de ==_ds
			for (int i = 0; i < data[_de].countT(); i++)
				if ((ts <= data[_de].getT(i)) && (data[_de].getT(i)) <= te)
					result++;
		}
	}

    return result;
}
