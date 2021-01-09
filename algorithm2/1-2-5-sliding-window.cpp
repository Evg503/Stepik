#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int n;
int m;
vector<int> A;

int main()
{
    cin >> n;
    A.resize(n);
    for(int i = 0; i < n; ++i)
        cin >> A[i];
    cin >> m;
    deque<int> q;
    for(int i = 0; i < m-1; ++i)
    {
        while (!q.empty() && q.back()  < A[i])
	        q.pop_back();
        q.push_back (A[i]);
    }
    for(int i = m-1; i < n; ++i)
    {
        while (!q.empty() && q.back() < A[i])
	        q.pop_back();
        q.push_back (A[i]);
        cout << q.front() <<' ';
        if (!q.empty() && q.front() == A[i-m+1])
	        q.pop_front();
    }
}

/*
8
2 7 3 1 5 2 6 2
4

7 7 5 6 6

*/
/*
8
8 7 6 5 4 3 2 1
4

8 7 6 5 4 

*/
/*
8
1 2 3 4 5 6 7 8
4

4 5 6 7 8 

*/

