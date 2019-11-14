#include <iostream>
#include <array>
#include  <utility>
using namespace std;

struct Node
{
    Node *next;
    int data;

    Node(int data_)
        :data(data_), next(nullptr)
    {}
} *first;



class Iterator
{
protected:
    Node *_current;
public:
    Iterator(Node *current = nullptr) :_current(current)
    {}

    //prefix
    Iterator& operator++() 
    { 
        if (_current) 
            _current = _current->next; 
        return *this; 
    } 

    bool operator!=(const Iterator& other)
    {
        return _current != other._current;
    }

    const int& operator*() 
    {
        return _current->data; 
    }

};



// task1
class SkipIterator : public Iterator
{
    int _N;
public:
    SkipIterator(int N, Node *current = nullptr) 
    :Iterator(current), _N(N)
    {}

    //prefix
    SkipIterator& operator++() 
    { 
        while(_current)
        {
            _current = _current->next; 

            if(_current!=nullptr && _current->data <= _N)
                break;
        }
        return *this; 
    } 

};


//task 2
class DeleteIterator : public Iterator
{
    Node *&_first;
public:
    DeleteIterator(Node *&first, Node *current = nullptr) 
    :Iterator(current),_first(first)
    {}

    //prefix
    DeleteIterator& operator++() 
    { 
        if(_current)    
        {
            if(_current == _first)
                _first = _current->next;

            Node *old = _current;
            _current = _current->next;
            
            delete old;
        }

        return *this; 
    } 
};


Iterator begin()
{
    return Iterator(first);
}

Iterator end()
{
    return Iterator(nullptr);
}

void printList()
{
    for (Iterator it = begin(); it != end(); ++it)
    {
        cout<<(*it)<<" ";
    }
    cout<<endl;
}


SkipIterator begin_skip_it(int N)
{
    return SkipIterator(N,first);
}


DeleteIterator begin_del_it()
{
    return DeleteIterator(first, first);
}


// task 2
template <class Iter>
class Sequence
{
    public:
        Sequence (const Iter &b, 
                  const Iter &e):_begin(b), _end (e){}

        Iter begin()
        {
            return _begin;
        }
        Iter end()
        {
            return _end;
        }
    private:
        Iter _begin;
        Iter _end;
};


//task3 a)
class IndexIterator : public Iterator
{
    int _index;
public:
    IndexIterator(int index, const Iterator &it) 
    :Iterator(it), _index(index)
    {}

    IndexIterator(int index, Node *current = nullptr) 
    :Iterator(current), _index(index)
    {}
    //prefix
    Iterator& operator++() 
    { 
        if (_current){
            _index++;
            _current = _current->next; 
        }
        return *this; 
    } 

    pair<int, Iterator> operator*() 
    {
        return make_pair(_index, Iterator(_current)); 
    }
};

Sequence<IndexIterator> addIndex(Sequence<Iterator> s)
{
    IndexIterator begin_it(0, s.begin());
    IndexIterator end_it(0, s.end());
    return Sequence<IndexIterator>(begin_it,end_it);
}

// task 3 b)
class AppendIterator : public Iterator
{
    bool _first_sequnce;
    Iterator _first_end;
    Iterator _second_start;

public:
    AppendIterator(Iterator first_start, Iterator first_end,
        Iterator second_start)
        :Iterator(first_start), _second_start(second_start),
        _first_end(first_end), _first_sequnce(true)
    {}

    AppendIterator(Iterator first_start)
    :Iterator(first_start), _first_sequnce(false)
    {}

    AppendIterator& operator++() 
    {
        Iterator::operator++();
        if(_first_sequnce)
        {
            if ( !((Iterator)*this != _first_end))
            {
                Iterator::operator=(_second_start);
                _first_sequnce = false;
            }
        }
          
        return *this; 
    } 

    bool operator!=(const AppendIterator& other)
    {
        return _current != other._current && 
            _first_sequnce ==  other._first_sequnce || 
            _first_sequnce !=  other._first_sequnce;
    }    

};

Sequence<AppendIterator> append(Sequence<Iterator> s1, Sequence<Iterator> s2)
{

    AppendIterator begin_it(s1.begin(), s1.end(), s2.begin());
    AppendIterator end_it(s2.end());

    return Sequence<AppendIterator>(begin_it,end_it);
}



int main()
{
    // int input_arr[] = {2,6,7,3,2,12,15,2,4};
       int input_arr[] = {0,1,2,3,4,5,6,7,8};
    first = new Node(input_arr[0]);
    Node *current = first;
    for(size_t i = 1; i < 9; i++)
    {
        current->next = new Node(input_arr[i]);
        current = current->next;
    }
   
    // cout<<"\nSkipIterator output: \n";
    // for (SkipIterator it = begin_skip_it(5); it != end(); ++it)
    // {
    //     cout<<(*it)<<" ";
    // }
    // cout<<endl;


    // cout<<"\nDeleteIterator output: \n";
    // for (DeleteIterator it = begin_del_it(); it != end(); ++it)
    // {
    //     cout<<(*it)<<" ";
    // }
    // cout<<endl;
    // cout<<"After DeleteIterator output: \n";
    // printList();

    cout<<"\nSequence output: \n";
    Sequence<Iterator> s(begin(), end());
    for(auto &elem : s)
    {
        cout<<elem<<" ";
    }
    cout<<endl;

    cout<<"\nIndexed Sequence output: \n";
    Iterator it1 = begin();
    Iterator it2 = begin();
    for(size_t i = 0; i < 2; i++, ++it1);
    for(size_t i = 0; i < 7; i++, ++it2);


    for(auto elem : addIndex(Sequence<Iterator>(it1, it2)))
    {
        cout<<elem.first << ":" << *(elem.second) <<" ";
    }
    cout<<endl;



    Sequence<Iterator> sapp1(begin(), it2);
    for(auto &elem : sapp1)
    {
        cout<<elem<<" ";
    }
    cout<<endl;
    Sequence<Iterator> sapp2(it1, end());

    for(auto &elem : sapp2)
    {
        cout<<elem<<" ";
    }
    cout<<endl;
    cout<<"\nAppendIterator output: \n";
    for(auto &elem : append(sapp1, sapp2))
    {
        cout<<elem<<" ";
    }
    cout<<endl;



    return 0;
}