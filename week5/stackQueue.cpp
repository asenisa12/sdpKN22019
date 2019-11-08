#include <stack>
#include <iostream>
using namespace std;


// Task1
class Queue
{
    stack<int> s1, s2;
public:

    //ads element at the end
    void enQueue(int x)
    {
        while(!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }

        s1.push(x);

        while(!s2.empty())
        {
            s1.push(s2.top());
            s2.pop();
        }
    }

    //gets element from the front
    int deQueue()
    {
        if(s1.empty())
        {
            cout<<"empty queue"<<endl;
            exit(1);
        }
        
        int x = s1.top();
        s1.pop();
        return x;
    }

};

int main()
{
    Queue q; 
    q.enQueue(1); 
    q.enQueue(2); 
    q.enQueue(3); 
  
    cout << q.deQueue() << '\n'; 
    cout << q.deQueue() << '\n'; 
    cout << q.deQueue() << '\n'; 

    return 0;
}
