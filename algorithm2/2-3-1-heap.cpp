#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int n;
vector<int> A;

inline int parent(int i){return (i-1)/2;}
inline int left(int i){return 2*i+1;}
inline int right(int i){return 2*i+2;}

template <typename F>
void siftup(int i, F swapbyindex)
{
    while(i>0 && A[parent(i)] < A[i])
    {
        swapbyindex(parent(i), i);
        i = parent(i);
    }
}

template <typename F>
void siftdown(int i, F swapbyindex)
{
    int mIndex = i;
    do{
    i = mIndex;
    int l = left(i);
    int r = right(i);
    if (l<n && A[l] < A[mIndex])
        mIndex = l;
    if (r<n && A[r] < A[mIndex])
        mIndex = r;
    if (i != mIndex)
        swapbyindex(i, mIndex);
    } while (i != mIndex);
}


int main()
{
    cin >> n;
    A.resize(n);
    for(int i = 0; i < n; ++i)
        cin >> A[i];

    stringstream out;
    int count = 0;
    for (int i =n/2-1; i>=0; --i)
        siftdown(i,[&out, &count](int i1, int i2){
            out << i1 << ' ' << i2 << endl;
            ++count;
            swap(A[i1], A[i2]);
            });
    
    cout << count << endl;
    cout << out.str();

}