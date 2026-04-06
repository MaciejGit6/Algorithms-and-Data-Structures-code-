#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

class DS
{
private:
    vector<int> heap;

    void search(int i, int x, int& k);

    
    void heapify(int index);

public:
    DS(vector<int>& inval);
    ~DS();
    bool compare(int k, int x);   
};

void DS::heapify(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int n = heap.size();

    if (left < n && heap[left] > heap[largest])
        largest = left;

    if (right < n && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapify(largest);
    }
}

void DS::search(int i, int x, int& k) {
    if (k <= 0 || i >= heap.size() || heap[i] < x) {
        return;
    }
    k--;
    search(2 * i + 1, x, k);
    search(2 * i + 2, x, k);
}

DS::DS(vector<int>& inval)
{
    
    heap = inval;

    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        heapify(i);
    }
};

DS::~DS()
{
};

bool DS::compare(int k, int x)
{
    if (k <= 0) return true;
    search(0, x, k);
    return k <= 0;
}

int main()
{
    int z;
    cin >> z;
    while (z)
    {
        int n, q;
        vector<int> val;
        cin >> n >> q;
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            val.push_back(x);
        }
        DS ds = DS(val);
        while (q)
        {
            int x, k;
            cin >> k >> x;
            if (ds.compare(k, x))
                cout << "YES\n";
            else
                cout << "NO\n";
            q--;
        }
        z--;
    }
    return 0;
}