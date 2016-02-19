#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>



using namespace std;


vector<vector<int>> multiply_Iter(vector<vector<int>> A, vector<vector<int>> B)
{
	int rows = A.size();
	int cols = A[0].size();
	int dimZ = B[0].size();

	vector<vector<int>> answer;
	answer.resize(rows, vector<int>(dimZ, 0));
	for (int i = 0; i < rows; i++)
	for (int j = 0; j < dimZ; j++) {
		int sum = 0;
		for (int k = 0; k < cols; k++)
			sum = sum + (A[i][k] * B[k][j]);
		answer[i][j] = sum;
	}
	return answer;
}

void print(vector<vector<int>> answer)
{
	int rows = answer.size();
	int cols = answer[0].size();
	cout << "\n";
	for (int i = 0; i < rows; i++) {
		cout << "[";
		for (int j = 0; j < cols; j++) {
			if (j == cols - 1)
				cout << answer[i][j];
			else
				cout << answer[i][j] << " ";
		}
		cout << "]\n";
	}
	cout << "\n";
}

vector<vector<int>> sum(vector<vector<int>> A, vector<vector<int>> B) {

	int n = A.size();
	vector<vector<int>> result;
	result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = A[i][j] + B[i][j];
		}
	}
	return result;
}

vector<vector<int>> sub(vector<vector<int>> A, vector<vector<int>> B) {

	int n = A.size();
	vector<vector<int>> result;
	result.resize(n, vector<int>(n, 0));
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = A[i][j] - B[i][j];
		}
	}
	return result;
}

vector<vector<int>> strassen(vector<vector<int>> A, vector<vector<int>> B) {

	int n = A.size();

	vector<vector<int>> answer;
	answer.resize(n, vector<int>(n, 0));

	if (n == 1) {
		answer[0][0] = A[0][0] * B[0][0];
		return answer;
	}
	else {
		vector<vector<int>> a11, a12, a21, a22;//making separate matrics
		vector<vector<int>> b11, b12, b21, b22;
		vector<vector<int>> c11, c12, c21, c22;
		vector<vector<int>> p1, p2, p3, p4, p5, p6, p7;

		a11.resize(n / 2, vector<int>(n / 2, 0));
		a12.resize(n / 2, vector<int>(n / 2, 0));
		a21.resize(n / 2, vector<int>(n / 2, 0));
		a22.resize(n / 2, vector<int>(n / 2, 0));

		b11.resize(n / 2, vector<int>(n / 2, 0));
		b12.resize(n / 2, vector<int>(n / 2, 0));
		b21.resize(n / 2, vector<int>(n / 2, 0));
		b22.resize(n / 2, vector<int>(n / 2, 0));

		c11.resize(n / 2, vector<int>(n / 2, 0));
		c12.resize(n / 2, vector<int>(n / 2, 0));
		c21.resize(n / 2, vector<int>(n / 2, 0));
		c22.resize(n / 2, vector<int>(n / 2, 0));

		p1.resize(n / 2, vector<int>(n / 2, 0));
		p2.resize(n / 2, vector<int>(n / 2, 0));
		p3.resize(n / 2, vector<int>(n / 2, 0));
		p4.resize(n / 2, vector<int>(n / 2, 0));
		p5.resize(n / 2, vector<int>(n / 2, 0));
		p6.resize(n / 2, vector<int>(n / 2, 0));
		p7.resize(n / 2, vector<int>(n / 2, 0));

		vector<vector<int>> aResult;
		vector<vector<int>> bResult;
		aResult.resize(n / 2, vector<int>(n / 2, 0));
		bResult.resize(n / 2, vector<int>(n / 2, 0));


		int i, j;

		//dividing the matrices in 4 sub-matrices:
		for (i = 0; i < n / 2; i++) {
			for (j = 0; j < n / 2; j++) {
				a11[i][j] = A[i][j];
				a12[i][j] = A[i][j + n / 2];
				a21[i][j] = A[i + n / 2][j];
				a22[i][j] = A[i + n / 2][j + n / 2];

				b11[i][j] = B[i][j];
				b12[i][j] = B[i][j + n / 2];
				b21[i][j] = B[i + n / 2][j];
				b22[i][j] = B[i + n / 2][j + n / 2];
			}
		}

		aResult = sum(a11, a22); 
		bResult = sum(b11, b22); 
		p1 = strassen(aResult, bResult); 

		aResult = sum(a21, a22); 
		p2 = strassen(aResult, b11); 

		bResult = sub(b12, b22); 
		p3 = strassen(a11, bResult); 

		bResult = sub(b21, b11); 
		p4 = strassen(a22, bResult); 

		aResult = sum(a11, a12); 
		p5 = strassen(aResult, b22); 

		aResult = sub(a21, a11); 
		bResult = sum(b11, b12); 
		p6 = strassen(aResult, bResult); 

		aResult = sub(a12, a22); 
		bResult = sum(b21, b22); 
		p7 = strassen(aResult, bResult); 


		c12 = sum(p3, p5); 
		c21 = sum(p2, p4); 

		aResult = sum(p1, p4); 
		bResult = sum(aResult, p7); 
		c11 = sub(bResult, p5); 

		aResult = sum(p1, p3); 
		bResult = sum(aResult, p6); 
		c22 = sub(bResult, p2); 

		// Grouping the results obtained in a single matrix
		for (i = 0; i < n / 2; i++) {
			for (j = 0; j < n / 2; j++) {
				answer[i][j] = c11[i][j];
				answer[i][j + n / 2] = c12[i][j];
				answer[i + n / 2][j] = c21[i][j];
				answer[i + n / 2][j + n / 2] = c22[i][j];
			}
		}
	}
	return answer;
}

bool check(vector<vector<int>> A, vector<vector<int>> B){
	for (size_t i = 0; i < A.size(); i++)
	{
		for (size_t j = 0; j < A[0].size(); j++)
		{
			if (A[i][j] != B[i][j]){
				return false;

			}
		}
	}
	return true;



}
void unitTest(vector<vector<int>> A, vector<vector<int>> B){
	if (check(A, B)){
		cout << endl << "Unit test passed"<<endl;
	}
	else
		cout << endl << "Unit test failed"<<endl;

}
