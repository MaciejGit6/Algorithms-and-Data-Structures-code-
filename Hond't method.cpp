#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comparison(int a, int b, const vector<int>& votes, const vector<int>& seats)
{

    int left = votes[a] * (seats[b] + 1);
    int right = votes[b] * (seats[a] + 1);

    if (left != right) return left > right; 


    return a < b;                           
}

void heapifyUp(vector<int>& heap, int i, const vector<int>& votes, const vector<int>& seats)
{
    while (i > 1) {
        int parent = i / 2;
        if (comparison(heap[parent], heap[i], votes, seats)) break;
        swap(heap[parent], heap[i]);

        i = parent;
    }
}

void heapifyDown(vector<int>& heap,  int heapSize, int start, const vector<int>& votes, const vector<int>& seats)
{
    int i = start;
    while (true) {
        int left = i * 2;

        int right = left + 1;
        int best = i;


        if (left <= heapSize && comparison(heap[left], heap[best], votes, seats))
            best = left;
        if (right <= heapSize && comparison(heap[right], heap[best], votes, seats))
            best = right;

        if (best == i) break;


        swap(heap[i], heap[best]);
        i = best;
    }
}

void buildHeap(vector<int>& heap, int& heapSize, const vector<int>& votes,  const vector<int>& seats)
{
    for (int i = heapSize / 2; i >= 1; --i)
        heapifyDown(heap, heapSize, i, votes, seats);
}

int pop(vector<int>& heap, int& heapSize, const vector<int>& votes,  const vector<int>& seats)
{
    int top = heap[1];
    heap[1] = heap[heapSize--];


    if (heapSize > 0)
        heapifyDown(heap, heapSize, 1, votes, seats);
    return top;
}

void insert(vector<int>& heap, int& heapSize, int party, const vector<int>& votes, const vector<int>& seats)
{
    heap[++heapSize] =  party;

    heapifyUp(heap, heapSize, votes, seats);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int z;
    if (!(cin >> z)) return 0;

    while (z--) {
        int n, s;
        cin >> n >> s;

        vector<int> votes(n + 1);

        vector<int> seats(n + 1, 0);

        for (int i = 1; i <= n; ++i)
            cin >> votes[i];

        vector<int> heap(n + 1);
        int heapSize = n;
        for (int i = 1; i <= n; ++i)
            heap[i] = i;

        buildHeap(heap, heapSize, votes, seats);

        for (int k = 0; k < s; ++k) {
            int p = pop(heap, heapSize, votes, seats);
            seats[p]++;
            insert(heap, heapSize, p, votes, seats);
        }

        for (int i = 1; i <= n; ++i) {
            if (i > 1) cout << ' ';
            cout << seats[i];
        }
        cout << '\n';
    }

    return 0;
}
