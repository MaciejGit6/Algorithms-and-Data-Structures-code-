#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Box
{
public:
	Box(int _x, int _y, int _h)
	{
		x = _x;
		y = _y;
		h = _h;
	}
	int x;
	int y;
	int h;

	bool operator<=(const Box& b)
	{
		if (x <= b.x && y <= b.y)
			return true;
		if (x <= b.y && y <= b.x)
			return true;
		return false;
	}

	friend std::ostream& operator<< (std::ostream& stream, const Box& b);

};

std::ostream& operator<<(std::ostream& stream, const Box& b)
{
	stream << b.x << "/" << b.y << "/" << b.h << "\n";
	return stream;
}

int getHighestTower(vector<Box>* boxes, vector<int>* highestTower)
{



	/*writa all necessary code here*/

	/*writa all necessary code here*/
	int n = boxes->size();
	int max = 0;
	vector<int> dp(n);
	for (int i = 0; i < n; i++) {
		dp[i] = (*boxes)[i].h;
		for (int j = 0; j < i; j++) {
			if ((*boxes)[i] <= (*boxes)[j]) {
				dp[i] = std::max(dp[i], (*boxes)[i].h + dp[j]);
			}

		}
		max = std::max(max, dp[i]);
	}
	return max;


}

void printBoxes(vector<Box>* boxes)
{
	cout << "\nBoxes:\n";
	for (int i = 0; i < boxes->size(); i++)
	{
		cout << (*boxes)[i];
	}
}

int main()
{
	vector<Box> boxes;
	vector<int> highestTower;

	int z, n;
	cin >> z;
	while (z)
	{
		boxes.clear();
		highestTower.clear();

		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int x, y, h;
			cin >> x >> y >> h;
			boxes.push_back(Box(x, y, h));
		}
		cout << getHighestTower(&boxes, &highestTower) << "\n";
		z--;

	}
	return 1;
}