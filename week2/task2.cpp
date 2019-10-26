#include <stack>
#include <iostream>
using namespace std;

class MinStack
{
    stack<int> regular_stack;
    stack<int> min_elem_stack;

public:
    void push(int value)
    {
        regular_stack.push(value);

        if( min_elem_stack.empty() )
        {
            min_elem_stack.push(value);
        }
        else if (!min_elem_stack.empty())
        {
            if(value <= min_elem_stack.top() )
            {
                min_elem_stack.push(value);
            }
        }

    }

    void pop()
    {
        int top_value = regular_stack.top();

        if(top_value == min_elem_stack.top())
        {
            min_elem_stack.pop();
        }

        regular_stack.pop();
    }

    int top()
    {
        return regular_stack.top();
    }

    int min_elem()
    {
        if(min_elem_stack.empty())
            return -1;

        return min_elem_stack.top();
    }

};


int main()
{

    MinStack ms;
    ms.push(10);
    ms.push(1);
    ms.push(2);
    ms.push(1);
    
    ms.pop();
    cout<<ms.min_elem()<<endl;

    
    ms.pop();
    cout<<ms.min_elem()<<endl;
    
    ms.pop();
    cout<<ms.min_elem()<<endl;

    return 0;
}