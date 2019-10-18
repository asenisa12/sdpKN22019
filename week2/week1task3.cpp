#include <iostream>
using namespace std;

class MidStack
{
    struct Node
    {
        Node *prev, *next;
        int value;
        Node(int value = 0)
            :prev(nullptr),value(value)
        {}
    };
    Node *top, *mid_element;

    int size;
    int mid_element_position;

    void delete_top()
    {
       if(top != nullptr)
        {
            Node* prev_top = top;
            top = prev_top->prev;

            delete prev_top;
        }
    }

public:
    MidStack() : top(nullptr), size(0) 
    {
    }

    ~MidStack()
    {
        while(top!=nullptr)
        {
            delete_top();
        }
    }

    void push(int value)
    {
        Node *new_node = new Node(value);

        if(top != nullptr)
        {
            int new_mid_element_pos = size;
            new_node->prev = top;
            top->next = new_node;
        }
        size++;
        top = new_node;
        
        if(top->prev == nullptr)
        {
            mid_element = top;
        }
        else if(size % 2 != 0)
        {
            mid_element = mid_element->next;
        }
    }


    int pop()
    {
        if(top == nullptr)
            return -1;

        size--;
        top = top->prev;
        if(top != nullptr)
        {
            if(size % 2 == 0)
            {
                mid_element = mid_element->prev;
            }

            return top->value;
        }

        mid_element = nullptr;
        return -1;
    }


    int findMiddle()
    {
        if(mid_element != nullptr)
            return mid_element->value;
        
        return -1;
    }

};

int main()
{

    MidStack ms;
    ms.push(1);
    ms.push(2);
    ms.push(3);
    ms.push(4);
    ms.push(5);
    cout<<ms.findMiddle()<<endl;
    cout<<"pop: "<<ms.pop()<<endl;
    cout<<"pop: "<<ms.pop()<<endl;
    cout<<"pop: "<<ms.pop()<<endl;
    cout<<"pop: "<<ms.pop()<<endl;
    cout<<"pop: "<<ms.pop()<<endl;
    cout<<"mid: " <<ms.findMiddle()<<endl;
    return 0;
}