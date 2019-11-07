#include <iostream>
#include <list>
#include <stack>
using namespace std;



struct Node
{
    Node *next;
    Node *prev;
    int data;

    Node(int data_)
        :data(data_), next(nullptr), prev(nullptr)
    {}
};

void reverseList(Node *&first)
{
    Node *current = first;
    Node *last = first;

    while(current != nullptr)
    {
        Node *next = current->next;
        first->prev = current;
        current->next = first;

        first = current;
        current = next;
    }
    last->next = nullptr;
    first->prev = nullptr;
}

void reverseListWithStack(Node *&first)
{
    stack<Node*> s;
    Node *current = first;
    while(current != nullptr)
    {
        s.push(current);
        current = current->next;
    }

    Node *last = s.top();
    s.pop();
    last->next = nullptr;
    first = last;
    while(!s.empty())
    {
        Node *prev_first = first;
        first = s.top();
        first->next = prev_first;
        prev_first->prev = first;

        s.pop();
    }

    first->prev = nullptr;
}



Node* erase(Node *elem)
{
    Node *tmp = elem;
    elem = elem->next;

    if(elem != nullptr)
        elem->prev = tmp->prev;

    if(tmp->prev != nullptr)
        tmp->prev->next = elem;

    delete tmp; 

    return elem;
}


void remove_Nth_recursion(Node *elem, int N, int cnt)
{
    if(elem == nullptr)
        return;

    if(cnt == 0)
    {
        elem = erase(elem);
        cnt = N;
    }
    else
    {
        elem = elem->next;
    }
    
    remove_Nth_recursion(elem, N, cnt-1);    
}

class Iterator
{
    Node *current;
public:
    Iterator(Node *current_ = nullptr) :current(current_)
    {}

    //prefix
    Iterator& operator++() 
    { 
        if (current) 
            current = current->next; 
        return *this; 
    } 

    //postfix
    Iterator operator++(int)
    {
        Iterator it = *this;
        ++*this;
        return it;
    }

    bool operator!=(const Iterator& other)
    {
        return current != other.current;
    }

    const int& operator*() 
    {
        return current->data; 
    }
    friend Iterator erase(const Iterator &it);

};

Iterator erase(const Iterator &it)
{
    Node *new_ptr = erase(it.current);
    
    return Iterator(new_ptr);
}

Iterator end()
{
    return Iterator(nullptr);
}

void remove_Nth_iterator(Node *first, int N)
{
    Iterator it(first);
    
    int cnt = N;
    while(it != end())
    {
        if(cnt-- == 1)
        {
            it = erase(it);
            cnt = N;
        }
        else
        {
            it++;
        }   
    }
}

void remove_Nth_std_list(list<int> &l, int N)
{
    std::list<int>::iterator it = l.begin();
    int cnt = N;
    while (it != l.end())
    {
        if(cnt-- == 1)
        {
            it = l.erase(it);
            cnt = N;
        }
        else it++;
    }
}

void printList(Node *first)
{
    Node *current = first;
    while(current != nullptr)
    {
        cout << current->data << endl;
        current = current->next;

    }
}


void deleteList(Node *first)
{
    Node *current = first;
    while(current != nullptr)
    {
        Node *for_delete = current;
        current = current->next;
        delete for_delete;
    }
}



int main()
{

    Node *first = new Node(1);
    Node *current = first;
    
    for(int i = 2; i <= 25; i++)
    {
        current->next = new Node(i);
        current->next->prev = current;
        current = current->next;
    }
    // remove_Nth_recursion(first, 5, 4);
    // remove_Nth_iterator(first, 5);

    reverseListWithStack(first);
    printList(first);
    

    // list<int> l;
    // for(int i = 1; i <= 25; i++)
    // {
    //     l.push_back(i);
    // }
    // remove_Nth_std_list(l,5);
    // for(auto elem : l)
    // {
    //     cout<<elem<<endl;
    // }


    return 0;
}