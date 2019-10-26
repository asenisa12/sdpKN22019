#include <list>
#include <iostream>
using namespace std;


list<int> sum_lists(list<int> &l1, list<int> &l2)
{
    list<int> sumList;
    list<int>::iterator it1 = l1.begin();
    auto it2 = l2.begin();
    int carry = 0;

    while(it1 != l1.end() || it2 != l2.end())
    {
        int num1 = (it1 != l1.end())? (*it1) : 0;
        int num2 = (it2 != l1.end())? (*it2) : 0;

        int sum = num1 + num2 + carry;

        sumList.push_back(sum % 10);
        carry = sum / 10;

        it1++;
        it2++;
    }
    return sumList;
}


int main()
{

    list<int> l1({7,1,6});
    list<int> l2({5,9,2});

    auto sum = sum_lists(l1,l2);

    for(auto &e: sum)
    {
        cout<< e<< endl;
    }
    

    return 0;
}