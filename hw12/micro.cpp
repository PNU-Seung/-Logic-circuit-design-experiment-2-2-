#include <bits/stdc++.h>
using namespace std;
struct virus {
	string cell;
	virus* top = nullptr;
	virus* bottom = nullptr;
	virus* left = nullptr;
	virus* right = nullptr;
	bool checked = false;
};
bool isInSquare(int width, int height, int posx, int posy){
    if(0<= posx && posx <width && 0<= posy && posy < height)
        return true;
    else
        return false;
}
int checkSize(virus* cell){
    if(!cell)
        return 0;
    else{
        if(cell->checked == true)
            return 0;
        else{
            cell->checked = true;
            return 1+checkSize(cell->left)+checkSize(cell->right)+checkSize(cell->top)+checkSize(cell->bottom);
        }
    }
}

int main(void) {
	ifstream ifp("micro.inp");
    int N,M,k;
    ifp >> N >> M >>k;
	virus matrix[M][N];

	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			ifp >> matrix[i][j].cell;
ifp.close();

   for(int i=0;i<M;i++){
        for(int j=0; j<N;j++){
            if(matrix[i][j].cell == "#"){
               if(isInSquare(N,M,j-1,i) && matrix[i][j-1].cell == "#"){
                    matrix[i][j].left = &matrix[i][j-1];
                    matrix[i][j-1].right = &matrix[i][j];
                }
                if(isInSquare(N,M,j+1,i) && matrix[i][j+1].cell == "#"){
                    matrix[i][j+1].left = &matrix[i][j];
                    matrix[i][j].right = &matrix[i][j+1];
                }
                if(isInSquare(N,M,j,i-1) && matrix[i-1][j].cell == "#"){
                    matrix[i][j].top = &matrix[i-1][j];
                    matrix[i-1][j].bottom = &matrix[i][j];
                }
                if(isInSquare(N,M,j,i+1) && matrix[i+1][j].cell == "#"){
                    matrix[i+1][j].top = &matrix[i][j];
                    matrix[i][j].bottom = &matrix[i+1][j];
                }
            }
        }
    }
    int num;
    int virusCount = 0;
    int maxSize=0;
       for(int i=0; i<M ;i++){
        for(int j=0; j<N ;j++){
            num = checkSize(&matrix[i][j]);
            if(num >=k){
                virusCount +=1;
                maxSize = num>maxSize ? num : maxSize;
            }
        }
    }
    ofstream ofp("micro.out");
    ofp << virusCount <<" " << maxSize;
    ofp.close();

    return 0;
}
