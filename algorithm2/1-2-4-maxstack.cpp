#include <iostream>
#include <string>
#include <stack>

using namespace std;

int n;

struct Value
{   
    int v;
    int mx;
};

stack<Value> st;

int main()
{
    cin >> n;
    string cmd;
    int arg;
    int mx = -1;
    for (int i = 0; i<n; ++i)
    {

        cin >> cmd;
        if (cmd == "push")
        {
            cin >> arg;
            mx = max(mx, arg);
            st.push({arg, mx});
        }
        else if (cmd == "pop")
        {
            st.pop();
            mx=st.top().mx;
        
        }
        else 
         cout << mx << endl;
    }


}
/*
6
push 7
push 1
push 7
max
pop
max


5
push 1
push 2
max
pop
max
*/