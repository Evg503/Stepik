#include <iostream>
#include <string>
#include <stack>

using namespace std;

string s;
struct CharIndex
{
    char c;
    int idx;
};

stack<CharIndex> st;

int check()
{
    for(int i = 0; i<s.size(); ++i)
    {
        char c = 0;
        switch(s[i]){
            case '(':
            case '[':
            case '{':
                st.push({s[i], i});
                continue;
            case ')':
                c = '(';
                break;
            case ']':
                c = '[';
                break;
            case '}':
                c= '{';
                break;
            default:
                continue;
        }

        if (st.empty()) return i+1;
        if (st.top().c != c) return i+1;
        st.pop();
    }
    if(!st.empty()) return st.top().idx+1;
    return 0;
}

void test()
{
     struct {string s; int answer;} cases[] = 
     { 

         {"[]", 0},
         {"{}", 0},
         {"()", 0},
         {"{}[]", 0},
         {"[()]", 0},
         {"{[]}()", 0},
         {"foo(bar)", 0},

         {"{", 1},
         {"{[}", 3},
         {"foo(bar[i)", 10},
         
    };

    for(auto& i:cases)
    {
        s=i.s;
        stack<CharIndex> tmp;
        swap(st, tmp);
        cout << "Check:\"" << i.s << "\" \tExpected:" << i.answer << " Return: " << check() <<endl;
    }
}

int main()
{
      //test();
      cin >> s;
      int i = check();
      if(i == 0)
        cout << "Success";
      else
          cout << i;
}
