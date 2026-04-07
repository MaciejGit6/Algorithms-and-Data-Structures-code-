#include<iostream>
#include<iomanip>
#include<algorithm>
#include <vector>
#include <cstdio>
#include <time.h>
#include <math.h>
using namespace std;

const int MAX = 4000000;
//int sizeSlize[MAX];
//int gain[MAX][MAX];
//int sumSize[MAX][MAX];

void printTable(int ** A, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j=0; j<n; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << "******************************\n";
}

void allocate_memory_for_matrix(int** &A, int n)
{
	A =new int * [n];
	for(int i=0; i<n; i++)
	{
		A[i] = new int[n];
	}		
}

void free_memory_for_matrix(int** A, int n)
{
	for (int i=0;i<n;i++)
    delete [] A[i];
	delete [] A;
}


/*
 computes the sum of sizes of slices in the range [i:j]
 sum[i,j]: contains s[i] + s[(i+1) % n] + ... + s[(i+k) %n], where k is such that (i+k)%n = j
*/
void computeSumSize(int * s, int ** sum, int n)
{
	
	for (int i =0; i<n; i++)
	{
		sum[i][i] = s[i];
	}
	
	for(int num = 1; num < n; num++ )
	{
		for (int i = 0; i < n; i++)
		{
			sum[i][(i+num)%n] = sum[i][(i+num-1)%n] + s[(i+num)%n];
		}
	}
}

void computeGain(int* s, int** sum, int **gain , int n)
{
	/* write all the necessary code here */
	for (int i = 0; i < n; i++) {
		gain[i][i] = s[i];

	}
	for (int len = 2; len <= n; len++) {
		for (int i = 0; i < n; i++) {
			int j = (i + len - 1) % n;
			int next_i = (i + 1) % n;
			int prev_j = (j - 1 + n) % n;
			int takingL = s[i] + (sum[i][j] - s[i] - gain[next_i][j]);
			int takingR = s[j] + (sum[i][j] - s[j] - gain[i][prev_j]);
			gain[i][j] = max(takingL, takingR);
		}
	}
}


int z,n;
int ** sumSize;
int ** FPGain;
int * sliceSize;


int main()
{
	cin >> z;
	while(z)
	{
		cin >> n;
		sliceSize = new int[n];
		allocate_memory_for_matrix(sumSize,n);
		allocate_memory_for_matrix(FPGain,n);
		for(int i=0; i<n; i++)
		{
			cin >> sliceSize[i];
		}
		//printTable(tab,n);
		computeSumSize(sliceSize,sumSize,n);
		computeGain(sliceSize,sumSize,FPGain,n);
		//printTable(sumSize,n);
		//printTable(FPgain,n);
		int AliceGain = 0;
		for (int i=0; i < n; i++)
		{
			//cout << "FPGain[" << i << "][" << (i+n-1)%n << "]=" << FPgain[i][(i+n-1)%n] << "\n";
			if (FPGain[i][(i-1+n)%n] > AliceGain)
				AliceGain = FPGain[i][(i+n-1)%n];
		}
		cout << AliceGain <<"\n";
		free_memory_for_matrix(FPGain,n);
		free_memory_for_matrix(sumSize,n);
		delete [] sliceSize;
		z--;
	}		
}
