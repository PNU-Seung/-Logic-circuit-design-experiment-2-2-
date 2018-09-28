#include <iostream>
#include <fstream>

using namespace std;

int arr[1000][1000] = { 0 };

int main(void) {

	int sizeX, sizeY;
	int pos_x, pos_y;
	int number;

	ifstream in;
	in.open("nanobot.inp");
	if (in.is_open() != true) {
		cout << "File is not found!" << endl;
		return -1;
	}


	in >> sizeX;
	in >> sizeY;
	in >> pos_x;
	in >> pos_y;
	in >> number;

	in.close();

	/*
  1 22 21 20 19 18 17 16
  2 23 36 35 34 33 32 15
  3 24 37 38 39 40 31 14
  4 25 26 27 28 29 30 13
  5  6  7  8  9 10 11 12
	*/
	int increase =1;
	int X = 0, Y = -1, val = 0;

	int lenX = sizeX - 1 ; // 8 - 1
	int lenY = sizeY; //5

	while (1)
	{
		for (int i = 0; i < lenY; i++) // Y
		{
			val++;
			Y += increase;
			arr[Y][X] = val;
		}
		lenY -= 1;

		if (val == sizeX * sizeY)
			break;

		for (int i = 0; i < lenX; i++) // X
		{
			val++;
			X += increase;
			arr[Y][X] = val;
		}
		lenX -=1;
		increase *= (-1);

		if (val == sizeX * sizeY)
			break;
	}

	// search
	int resultNum = arr[(pos_y)-1][(pos_x)-1];
	int resultXpos = 0, resultYpos = 0;

	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++)
			if (number == arr[j][i])
			{
				resultXpos = i + 1;
				resultYpos = j + 1;
			}

	cout << resultNum << endl;
	cout << resultXpos << " " << resultYpos << endl;


	ofstream out;
	out.open("nanobot.out");
	out << resultNum << endl;
	out << resultXpos << " " << resultYpos << endl;

	out.close();
	/*
		for (int i = 0; i < 1000; i++)
			delete[] arr[i];
		delete[] arr;
	*/
	return 0;
}
