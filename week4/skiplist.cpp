#include <iostream>
using namespace std;

class SkipList
{
    struct Node
    {
        Node *next;
        Node *skip;
        int data;
        Node(int _data)
            :data(_data), next(nullptr), skip(nullptr)
        {}
    }*first, *last, *last_skipping_node;

    int skip_amount; //how many elements we are skiping
    int size;

    Node *get_ith_node(int index)
    {
        Node *current = first;
        
        int i = 0;
        while(i + (skip_amount + 1) <= index)
        {
            cout<< "skip from " << i;
            current = current->skip;
            i += skip_amount + 1;
            cout<< " to " << i << ", ";
        }

        for(; i < index; i++)
        {
            current = current->next;
        }

        return current;

    }

    void add_skip_links()
    {
        Node *shortcut = first;
        Node *current = first;
        int count = 0;
        
        while(shortcut != nullptr)
        {
            shortcut = shortcut->next;
            
            if(++count > skip_amount)
            {
                current->skip = shortcut;
                current = current->next;
            }
        }
        
    }

    void deleteall()
    {
        Node *next = first;
        while(next != nullptr)
        {
            Node *current = next;
            next = next->next;
            delete current;
        }
    }

    void copy(const SkipList &other)
    {
        first = new Node(other.first->data);
        last = first;

        Node *other_node = other.first->next;
        while(other_node != nullptr)
        {
            last->next = new Node(other_node->data);
            last = last->next;
            other_node = other_node->next;
        }
        
        size = other.size;
        skip_amount = other.skip_amount;

        add_skip_links();
    }

public:
    SkipList(int _skip_amount = 5) :first(nullptr), last(nullptr),
        skip_amount(_skip_amount), size(0)
    {}

    SkipList& operator=(const SkipList &other)
    {
        if(this != &other)
        {
            deleteall();
            copy(other);
        }
    }

    SkipList(const SkipList &other)
    {
        copy(other);
    }

    ~SkipList()
    {
        deleteall();
    }

    void push_back(int data)
    {
        size++;
        if(last == nullptr)
        {
            first = new Node(data);
            last = first;
            last_skipping_node = first;

            return;
        }

        last->next = new Node(data);
        last = last->next;

        if (size >= skip_amount + 2)
        {
            last_skipping_node->skip = last;
            last_skipping_node = last_skipping_node->next;
        }

        int skip = skip_amount;
    }

    int& operator[](int index)
    {
        
        Node *ith_node = get_ith_node(index);
        return ith_node->data;
    }

    void insert_at(int index, int data)
    {
        if(index < 0 || index > size)
        {
            cout << "wrong index" << endl;
            return;
        }


        Node *new_node = new Node(data);
        if(index > 0)
        {
            Node *ith_node = get_ith_node(index - 1);
            cout<<endl;
            new_node->next =  ith_node->next;
            ith_node->next =  new_node;
        }
        else if(index == 0)
        {
            new_node->next = first;
            first = new_node;
        }
        size++;
        add_skip_links();
    }
};

int main()
{
    SkipList sll(2);

    for(size_t i = 0; i < 10; i++)
    {
        sll.push_back(i);
    }


    SkipList sll2 = sll;
    sll2.insert_at(0,100);
    sll2.insert_at(5,101);
    sll2.insert_at(12,110);

    for(size_t i = 0; i < 13; i++)
    {
        cout<<i<<"th: "<<sll2[i]<<endl;
    }
    
    return 0;
}