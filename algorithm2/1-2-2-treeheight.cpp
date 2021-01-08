#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <map>

using namespace std;

int n;
vector<int> parents;
multimap<int, int> children;
int start = -1;

int res;

void load()
{   
    cin >> n;
    parents.resize(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> parents[i];
        children.emplace(parents[i], i);
        if (parents[i] == -1)
            start = i;
    }
}

int h(int root)
{
    int size = 1;
    for(auto i = find(begin(parents), end(parents), root); 
            i!= end(parents); 
            i=find(i+1, end(parents), root))
    {
        int pos = i-begin(parents);
        size = max(size, h(pos)+1);
    }
    return size;
}
int h2(int root)
{
    int size = 1;
    auto range = children.equal_range(root);
    for(auto i = range.first; i!= range.second; ++i)
    {
        size = max(size, h2(i->second)+1);
    }
    return size;
}

void simple()
{
   res =  h(start);
}
void over_children()
{
   res =  h2(start);
}

void output()
{
    cout << res;
}

int  main()
{
    load();
    over_children();
    output();

}

