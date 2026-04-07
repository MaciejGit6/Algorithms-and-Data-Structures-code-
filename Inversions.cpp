#include <iostream>
#include <vector>
using namespace std;



int merge(vector<int>& arr, int left, int mid, int right) {
    int h = 0;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    
    vector<int> L(n1), R(n2);

    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
            h += (n1 - i);
        }
        k++;
    }

    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    return h;
}


int mergeSort(vector<int>& arr, int left, int right) {

    if (left >= right)
        return 0;

    int mid = left + (right - left) / 2;
    int a = mergeSort(arr, left, mid);
    int b = mergeSort(arr, mid + 1, right);
    return merge(arr, left, mid, right) + a + b;
}

int main() {
    
    vector<int> arr = {1, 4, 2, 5, 3 ,9, 10, 8, 7 ,6  };
    int n = arr.size();

    
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
    cout << mergeSort(arr, 0, n - 1) << endl;

    return 0;
}