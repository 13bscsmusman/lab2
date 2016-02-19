
#include "Header.h"

#define MAX 2
#define MIN 1

int row = 8;
int col = 8;

int main()
{
	vector<vector<int>> A;
	vector<vector<int>> B;



	int x = 0;
	if (col > row){
		x = col;
		A.resize(col, vector<int>(col, 0));
		B.resize(col, vector<int>(col, 0));
	}
	else{
		x = row;
		A.resize(row, vector<int>(row, 0));
		B.resize(row, vector<int>(row, 0));
	}
	srand(time(NULL));

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			A[i][j] = (rand() % ((MAX - MIN) + 1)) + MIN;
			B[i][j] = (rand() % ((MAX - MIN) + 1)) + MIN;

		}

	}
	
	cout << "matrix A:" << endl;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < x; j++) {
			cout<<A[i][j]<<" ";
		}
		cout << endl;
	}

	cout << "matrix B:" << endl;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < x; j++) {
			cout << B[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "Iterative Multiplication Result:" << endl;
	vector<vector<int>> iterResult;
	iterResult=multiply_Iter(A, B);
	print(iterResult);
	cout << endl << "Strassen Multiplication Result:" << endl;
	vector<vector<int>> strassenResult;
	strassenResult = strassen(A, B);
	print(strassenResult);

	unitTest(iterResult, strassenResult);
	system("pause");
	return 0;
}
