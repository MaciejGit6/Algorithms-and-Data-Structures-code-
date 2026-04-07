#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

int compute(vector<int>& seq, int n)
{
    int jumps = 0;
    int current_end = 0;
    int farthest = 0;

    for (int i = 0; i < n; i++)
    {
        farthest = max(farthest, i + seq[i]);

        if (farthest >= n)
        {
            return jumps + 1;
        }

        if (i == current_end)
        {
            jumps++;
            current_end = farthest;
        }
    }
    return jumps;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int z;
    if (cin >> z)
    {
        while (z--)
        {
            int n;
            cin >> n;

            vector<int> seq(n);
            for (int i = 0; i < n; i++)
            {
                cin >> seq[i];
            }

            cout << compute(seq, n) << "\n";
        }
    }
    return 0;
}
