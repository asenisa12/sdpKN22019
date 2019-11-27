#include "node.h"

/***********************************************************************
  Задача 6. Да се дефинира шаблон на функция removesub, която приема
  два параметъра first и second — указатели към линейни едносвързани
  списъци. Функцията да изтрива от списъка с начало first
  последователно всички срещания на подсписъци, които съвпадат със
  списъка с начало second. Например, при списък first с елементи 1, 2,
  3, 3, 3, 4, 5, 3, 3, 6 и second с елементи 3, 3, first да се
  преобразува до списъка 1, 2, 3, 4, 5, 6.
************************************************************************/

/***********************************************************************
 РЕШЕНИЕ:
************************************************************************/

template <typename T>
void removesub(node<T>*& first, node<T>* second)
{
  node<T> *current = first;
  node<T> *prev = first;

  if(second == nullptr)
    return;

  while(current != nullptr)
  {
    if(current->data == second->data)
    {
      node<T> *cur_first = current;
      node<T> *cur_second = second;
      
      while(cur_first != nullptr && cur_second != nullptr)
      {
        if(cur_first->data != cur_second->data)
        {
          break;
        }
        cur_first = cur_first->next;
        cur_second = cur_second->next;
      }

      if(cur_second == nullptr)
      {
        if(current == first)
        {
          first = cur_first;
        }
        else
        {
          prev->next = cur_first;
        }
        
        while(current != cur_first)
        {
          node<T> *tmp = current;
          current = current->next;
          delete tmp;
        }
      }  
    }
    else
    {
      prev = current;
      current = current->next;
    }
  }
}

/***********************************************************************
 КРАЙ НА РЕШЕНИЕТО
************************************************************************/

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

/***********************************************************************
  РАЗКОМЕНТИРАЙТЕ СЛЕДВАЩИЯ РЕД, ЗА ДА ВКЛЮЧИТЕ ТЕСТОВЕТЕ
************************************************************************/
#include "prob6_tests.h"

int main ()
{
    // пускане на тестовете
    doctest::Context().run();
    return 0;
}
