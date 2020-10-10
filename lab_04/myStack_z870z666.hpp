
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;
template <typename Object>
class myStack
{  
private:
    int m_size;
    int m_campacity;
    Object *Stack_list;

public:

    
   
    myStack()
    {
        m_size = 0;
        m_campacity =10;
        Stack_list =  new Object[m_campacity];
    }

    ~myStack()
    {
        delete[] Stack_list;
        Stack_list = nullptr;
    }

    myStack(myStack &&rhs) : m_size{rhs.m_size}, m_campacity{rhs.m_campacity}, Stack_list{rhs.Stack_list}
    {
        rhs.m_size = 0;
        rhs.Stack_list = nullptr;
    }

    myStack &operator=(myStack &&rhs)
    {
        std::swap(m_size, rhs.m_size);
        std::swap(Stack_list, rhs.Stack_list);
        return *this;
    }

    myStack(const myStack<Object> &rhs)
    {
        m_size = 0;
        m_campacity =10;
        Stack_list =  new Object[m_campacity];
        for (int i = 0; i < rhs.m_size; i++)
        {
            push(rhs.Stack_list[i]);
        }

    }

    myStack &operator=(const myStack &rhs)
    {
        myStack copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    int getSize()
    {
        return m_size;
    }
     void resize()
    {
       if(m_size == m_campacity)
      {
        // cout<<"start stack resize\n";
        m_campacity = m_campacity*2;
        Object *temp  = new Object[m_campacity];
        
        for (int i=0 ;i<m_size;i++)
            {
                temp[i] = Stack_list[i];
            }
       swap(Stack_list, temp);
       delete [] temp;
      }
    }


    void push(Object &newEntry)
    {
        resize();
        Stack_list[m_size] = newEntry;
        m_size++;
       // cout<<"push complete\n";
    }
    Object getItem()
    {
        Object temp = Stack_list[m_size-1];
        return temp;
    }
    Object pop()
    {
       if(empty())
        {
          throw std::runtime_error("empty stack during pop\n");
        }
        else
        {
          Object temp = Stack_list[m_size-1];
            m_size--;
            return temp;

        }
    }
    
     bool empty()
    {
        if(m_size == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }

    Object top()
    {
        return Stack_list[m_size-1];
    }

   
    void clear()
    {
        while(!empty())
        {
            pop();
        }
    }
};

