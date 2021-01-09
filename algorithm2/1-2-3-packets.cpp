#include <iostream>
#include <vector>
#include <deque>

using namespace std;
constexpr bool debug = false;

struct Packet 
{
    int arrival; 
    int duration;
    int start;
};

int size, n;

vector<Packet> packets;

deque<int> queue;
void simulate()
{
    int idx = 0;
    int time = packets[idx].arrival;
    int busytime = time;

    auto exec = [&time, &busytime]()
    {
        while(busytime <= time && !queue.empty())
        {
            int curr = queue.front();
            queue.pop_front();
            packets[curr].start = busytime = max(busytime, packets[curr].arrival);
            busytime += packets[curr].duration;
            if (debug) cout << "exec packet:" << curr << "-(" <<packets[curr].arrival<<", "<<packets[curr].duration
              <<") interval:("<<packets[curr].start<<", "<<(packets[curr].start+packets[curr].duration)<<")\n";

        }
    };
    do{
        while(packets[idx].arrival == time && idx < n)
        {
            if(queue.size() < size-int(busytime>time))
            {
                queue.push_back(idx); // in queue
                if (debug)cout << "queue packet:" << idx << "-(" <<packets[idx].arrival<<", "<<packets[idx].duration<<")\n";
            }
            else
            {
                packets[idx].start = -1;  //drop
                if (debug) cout << "drop packet:" << idx << "-(" <<packets[idx].arrival<<", "<<packets[idx].duration<<")\n";
            }
            ++idx;
            if(packets[queue.front()].duration ==0) exec();
        }
        time = idx<n?packets[idx].arrival:2000000000; // next packet time
        if (debug) cout <<"next packege time " << time << endl;
        exec();
    }while (idx < n);

}

void load()
{
    cin >> size >> n;
    packets.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        int a, d;
        cin >> a >> d;
        packets.push_back({a, d, -2});
    }
}

void output()
{
    int idx = 0;
    for(auto& p:packets)
        if (debug) cout<<idx++<<":" << p.start<<endl;
        else cout << p.start<<endl;
}
void test1()
{
    size = 1;
    n = 1;
    auto name = " s=1  (0 0)"s;
    packets = { {0, 0, -2}};
    int expected[] = {0};
    simulate();
    for (int i = 0; i < n; ++i)
        if(packets[i].start != expected[i])
            cout << "Error in ["<<name<<"] " <<i<<":" << packets[i].start <<"!="<< expected[i]<<endl;
}
void test2()
{
    size = 1;
    n = 2;
    auto name = " drop s=1  (0 1) (1 1)"s;
    packets = { 
        {0, 1, -2},
        {0, 1, -2},
    };
    int expected[] = {0, -1};
    simulate();
    for (int i = 0; i < n; ++i)
        if(packets[i].start != expected[i])
            cout << "Error in ["<<name<<"] " <<i<<":" << packets[i].start <<"!="<< expected[i]<<endl;
}
void test3()
{
    size = 1;
    n = 2;
    auto name = " Ok s=1  (0 1) (1 1)"s;
    packets = { 
        {0, 1, -2},
        {1, 1, -2},
    };
    int expected[] = {0, 1};
    simulate();
    for (int i = 0; i < n; ++i)
        if(packets[i].start != expected[i])
            cout << "Error in ["<<name<<"] " <<i<<":" << packets[i].start <<"!="<< expected[i]<<endl;
}

void test4()
{
    size = 2;
    n = 8;
    auto name = " fast packet "s;
    packets = { 
        {0, 0, -2},
        {0, 0, -2},
        {0, 0, -2},
        {1, 1, -2},
        {1, 0, -2},
        {1, 0, -2},
        {1, 2, -2},
        {1, 3, -2},
    };
    int expected[] = {0, 0, 0, 1, 2, -1, -1, -1};
    simulate();
    for (int i = 0; i < n; ++i)
        if(packets[i].start != expected[i])
            cout << "Error in ["<<name<<"] " <<i<<":" << packets[i].start <<"!="<< expected[i]<<endl;
}
void test5()
{
    size = 2;
    n = 4;
    auto name = " waiting"s;
    packets = { 
        {0, 0, -2},
        {2, 1, -2},
        {4, 1, -2},
        {6, 1, -2},
    };
    int expected[] = {0, 2, 4, 6};
    simulate();
    for (int i = 0; i < n; ++i)
        if(packets[i].start != expected[i])
            cout << "Error in ["<<name<<"] " <<i<<":" << packets[i].start <<"!="<< expected[i]<<endl;
}

void test6()
{
    size = 2;
    n = 4;
    auto name = " long exec with get and drop pakets"s;
    packets = { 
        {0, 5, -2},
        {2, 1, -2},
        {4, 1, -2},
        {6, 1, -2},
    };
    int expected[] = {0, 5, -1, 6};
    simulate();
    for (int i = 0; i < n; ++i)
        if(packets[i].start != expected[i])
            cout << "Error in ["<<name<<"] " <<i<<":" << packets[i].start <<"!="<< expected[i]<<endl;
}
void test()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}
int main()
{
    if (debug) 
    {
        test();
        return 0;
    }
    load();
    if (n>0) 
        simulate();
    output();
}