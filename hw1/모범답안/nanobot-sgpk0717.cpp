#include <iostream>
#include <fstream>

using namespace std;

void print(int** m, int x, int y) {
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j)
			cout << m[i][j] << '\t';
		cout << endl;
	}
}

int main(void)
{
	int nx, ny,tx,ty, ti;

	ifstream s1("nanobot.inp");

	if (!s1.is_open()) {
		cerr << "Input Error." << endl;
		return -1;
	}

	s1 >> nx >> ny;
	s1 >> tx >> ty;
	s1 >> ti;

	s1.close();

	int** m = new int*[nx];
	for (int i = 0; i < nx; ++i)
		m[i] = new int[ny];

	int* xx = new int[nx*ny];
	int* yy = new int[nx*ny];

	for (int i = 0; i < nx; ++i)
		for (int j = 0; j < ny; ++j)
			m[i][j] = 0;

	int dx = 0, dy = 1;
	int x = 0, y = 0;
	for (int i = 1; i <= nx * ny; ++i) {
		m[x][y] = i;
		xx[i] = x;
		yy[i] = y;
		if (!((x + dx<nx) && (x + dx >= 0) && (y + dy < ny) && (y + dy >= 0)) || (m[x + dx][y + dy] != 0)) {
			if (dx == 0 && dy == 1) {
				dx = 1; dy = 0;
			}
			else if (dx == 1 && dy == 0) {
				dx = 0; dy = -1;
			}
			else if (dx == 0 && dy == -1) {
				dx = -1; dy = 0;
			}
			else if (dx == -1 && dy == 0) {
				dx = 0; dy = 1;
			}
		}
		x += dx;
		y += dy;
	}

	ofstream s2("nanobot.out");
	if (!s2.is_open()) {
		cerr << "Output Error." << endl;
		return -1;
	}
	s2 << m[tx-1][ty-1] << endl << xx[ti]+1 << ' ' << yy[ti]+1;

	s2.close();	

	return 0;
}
