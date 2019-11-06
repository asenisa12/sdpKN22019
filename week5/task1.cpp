#include <iostream>
#include <list>
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


void erase(Node *&elem )
{
    Node *tmp = elem;
    elem = elem->next;

    if(elem != nullptr)
        elem->prev = tmp->prev;

    if(tmp->prev != nullptr)
    {
        tmp->prev->next = elem;
    }

    delete tmp; 
}
void remove_Nth_recursion(Node *elem, int N, int cnt)
{
    if(elem == nullptr)
        return;

    if(cnt == 0)
    {
        erase(elem);
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
    friend void erase(Iterator &it);

};

void erase(Iterator &it)
{
    erase(it.current);
}

Iterator end()
{
    return Iterator(nullptr);
}

void remove_Nth_iterator(Node *first, int N)
{
    Iterator it(first);
    
    int cnt = N-1;
    while(it!=end())
    {
        if(cnt-- == 0)
        {
            erase(it);
            cnt = N-1;
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
    int cnt = N-1;
    while (it != l.end())
    {
        if(cnt-- == 0)
        {
            std::list<int>::iterator prev = it++; 
            l.erase(prev);
            cnt = N-1;
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
    // printList(first);
    
    
    
    
    
    list<int> l;
    for(int i = 1; i <= 25; i++)
    {
        l.push_back(i);
    }
    // remove_Nth_std_list(l,5);
    // for(auto elem : l)
    // {
    //     cout<<elem<<endl;
    // }


    return 0;
}