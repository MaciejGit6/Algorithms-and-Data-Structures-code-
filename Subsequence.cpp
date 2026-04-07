#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;
 void printVector(vector<int>& v)
 {
	for (int i=0; i<v.size(); i++)
	{
		cout << v[i]<<" ";
	}
	cout <<"\n";	
 }

int compute(vector<int>& seq, int n)
{
	/* write all the necessary code here */
	if (n == 1) return 0;
	if (n == 2) return 0;
	if ( n == 3) return min(seq[0], min(seq[1], seq[2]));
	vector<int> dp(n);
	dp[0] = seq[0];
	dp[1] = seq[1];
	dp[2] = seq[2];
	for (int i = 3; i < n; i++){
		dp[i] = seq[i] + min(dp[i - 1], min(dp[i - 2], dp[i - 3]));
	}
	return min(dp[n-1], min(dp[n - 2], dp[n - 3]));

	return 0;
}

int main()
{
	vector<int> seq;	
	int z,n;
	cin >> z;
	while(z)
	{
		seq.clear();		
		cin >> n;
		for(int i=0; i<n; i++)
		{
			int x;
			cin >> x;
			seq.push_back(x);
		}
		int sol = compute(seq, n);
		cout << sol <<"\n";
		z--;
	}
	return 1;
}