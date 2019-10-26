#include <iostream>


class MidStack
{
    struct Node
    {
        Node *prev;
        int value;
        Node()
            :prev(nullptr),value(0)
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
        if(top == nullptr)
        {
            top* = new Node();
            mid_element = top;
            size = 1;
        }
        else
        {
            size++;
            int new_mid_element_pos = size;
            Node *prev = top;
            top = new Node();
            top->prev = prev;


        }

    }




};

int main()
{
    return 0;
}