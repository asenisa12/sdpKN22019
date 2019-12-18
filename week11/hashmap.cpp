#include <iostream>
#include <vector>
#include <functional>
using namespace std;

template<typename T>
class HashMap
{
    vector<T*> table;

    function<int(const char*)> hash;


public: 
    HashMap(int size, const function<int(const char*)> &_hash)
        :table(size, nullptr), hash(_hash)
    {}

    T& operator[](const char* key)
    {
        int id = hash(key);
        
        if(id > table.size())
        {
            table.resize(table.size() + id + 1, nullptr);
        }

        if(table[id] == nullptr)
        {
            table[id] = new T();
        }

        return *table[id];
    }

    typedef typename vector<T*>::iterator table_it;
    class Iterator
    {
        table_it current;
        vector<T*> *table_ref;
    public:

        Iterator(const table_it& _curr,  vector<T*>  *_table_ref)
            :current(_curr), table_ref(_table_ref)
        {}
        //prefix
        Iterator& operator++() 
        { 
            while(++current != table_ref->end())
            {
                if(*current != nullptr)
                {
                    break;
                }
            }
            return *this; 
        } 

        bool operator!=(const Iterator& other)
        {
            return current != other.current;
        }

        const T& operator*() 
        {
            return *(*current); 
        }
    };

    Iterator begin()
    {
        table_it it = table.begin();
        while(it != table.end())
        {
            if(*it != nullptr)
            {
                break;
            }
            ++it;
        }
        return Iterator(it, &table);
    }

    Iterator end()
    {
        return Iterator(table.end(),&table);
    }

};

int hash_func1(const char* key)
{
    unsigned int hash = 0;
    int size = 1;
	int c;

	while (c = *key++)
    {
        size++;
	    hash += c;
    }

	return hash % size;
}



int main()
{

    HashMap<string> hm(40, hash_func1);

    hm["John"] = "Smith";

    hm["Boj2o"] = "Borisov";
    HashMap<string>::Iterator it = hm.begin();

    hm["Bojko"] = "Borisov";

    while(it!= hm.end())
    {
        cout<<*it<<endl;
        ++it;
    }


    return 0;
}
