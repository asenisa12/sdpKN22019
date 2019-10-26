#include <iostream>
#include <vector>
using namespace std;

class DoubleStack
{
    vector<int> _data;//stores the stacks
    int _top1, _top2;

    void shift(int start)
    {
        _data.resize(_data.size() + 1);
        for(int i = _data.size() - 2; i >= start; i--)
        {
            _data[i + 1] = _data[i];
        }
        _top2++;
    }

public:
    DoubleStack(int default_size)
        :_data(default_size),
         _top1(-1), _top2(default_size)
        {}

    void push1(int value)
    {
        if(_top1 + 1 == _top2)
        {
            shift(_top1 + 1);
        }
        ++_top1;
        _data[_top1] = value;
    }

    void push2(int value)
    {
        if(_top2 - 1 == _top1)
        {
            shift(_top2);
        }
        _top2--;
        _data[_top2] = value;
    }

    int top1()
    {
        if(_top1 > -1)
            return _data[_top1];
        else return -1;
    }

    int top2()
    {
        if(_top2 > -1)
            return _data[_top2];
        else return -1;
    }

    int pop1()
    {
        if(_top1 >= 0)
        {
            int val = _data[_top1];
            _top1--;
            return val;
        }
        return -1;
    }

    int pop2()
    {
        if(_top2 <= _data.size() - 1)
        {
            int val = _data[_top2];
            _top2++;
            return val;

        }
        return -1;
    }

};


int main()
{
    DoubleStack ds(4);

    for(int i = 0; i<5; i++)
    {
        ds.push1(i);
    }
    for(int i = 1; i<5; i++)
    {
        ds.push2(i*10);
    }

    for(int i = 0; i<6; i++)
    {
        cout<<ds.pop1()<<endl;
    }

    cout<<"\n";
    for(int i = 0; i<6; i++)
    {
        cout<<ds.pop2()<<endl;
    }




    return 0;
}