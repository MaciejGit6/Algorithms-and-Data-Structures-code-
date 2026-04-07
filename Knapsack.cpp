#include<iostream>
#include<iomanip>
#include<algorithm>
#include <vector>
#include <cstdio>
#include <time.h>
#include <math.h>
using namespace std;

const int MAX = 4000;
int itemSize[MAX]; 
int itemValue[MAX];

//auxiliary function
void printTable(int ** A, int n, int W)
{
	for (int i = 0; i <= n; i++)
	{
		for (int j=0; j<=W ; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << "******************************\n";
}

// function allocating memory for amn int table of size (n+1) x (W+1)
void allocate_memory_for_matrix(int** &A, int n, int W)
{
	A = new int* [n+1];
	for(int i=0; i<=n; i++)
	{
		A[i] = new int[W+1];
	}		
}

// function freeing memory taken by a table of size (n+1) x (W+1)
void free_memory_for_matrix(int** A, int n)
{
	for (int i=0;i<=n;i++)
	{
		delete [] A[i];
	}
	delete [] A;
}


void solve(int* weights, int * Worth, int ** A, int n, int W)
{
	
	/* write all the necessary code here */

	//n is numberofItems
	//W is max Capacity
	//s I changed to weights
	// v changed to Worth now

	for (int itemNum = 0; itemNum <= n; itemNum++) {
		for (int currentWeight = 0; currentWeight <= W; currentWeight++) {
			if (itemNum == 0 || currentWeight == 0) {
				A[itemNum][currentWeight] = 0;
			}
			else if (weights[itemNum-1] <= currentWeight) {
				A[itemNum][currentWeight] = max(Worth[itemNum - 1] + A[itemNum - 1][currentWeight - weights[itemNum -1]], A[itemNum - 1][currentWeight]);
			}
			else
				A[itemNum][currentWeight] = A[itemNum - 1][currentWeight];

			
		}
	}

}



int main()
{
	int z,n,W;
	cin >> z;
	while(z)
	{		
		cin >> n >> W;
		int ** tab;
		allocate_memory_for_matrix(tab,n,W);
		for(int i=0; i<n; i++)
		{
			cin >> itemSize[i];
		}
		for(int i=0; i<n; i++)
		{
			cin >> itemValue[i];
		}
		solve(itemSize,itemValue, tab, n, W);
		cout << tab[n][W] << "\n";
		free_memory_for_matrix(tab,n);
		z--;
	}
		
}
