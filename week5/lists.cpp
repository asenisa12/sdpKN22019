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

// Task 2 a)
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

// Task 2 b)
// this method is more useful for singly linked list
void reverseListWithStack(Node *&first)
{
    stack<Node*> s;
    Node *current = first;
    while(current != nullptr)
    {
        s.push(current);
        current = current->next;
    }

    first = s.top();
    s.pop();
    first->prev = nullptr;
    current = first;

    while(!s.empty())
    {
        current->next = s.top();
        current->next->prev = current;
        current = current->next;
        s.pop();
    }
    current->next = nullptr;
}

// erases element from list and returns the next one
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

// Task3 a) *1
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

// erase() method for Iterator
// it removes the element at the current position 
// and returns iterator to the next one
Iterator erase(const Iterator &it)
{
    Node *new_ptr = erase(it.current);
    
    return Iterator(new_ptr);
}

// Iterator to the end of the list
Iterator end()
{
    return Iterator(nullptr);
}

// Task 3 a) *2
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
            ++it;
        }   
    }
}

// Task 3 b)
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
        else ++it;
    }
}

// prints the elements from list
void printList(Node *first)
{
    Node *current = first;
    cout << "[ ";
    while(current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;

    }
    cout << " ]" << endl;
}

// deletes all elements from list
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

    // reverseList(first);
    // reverseListWithStack(first);
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
