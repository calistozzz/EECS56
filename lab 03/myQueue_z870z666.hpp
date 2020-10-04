#include <iostream>
#include <vector>
#include <algorithm>
template <typename Object>
class myQueue
{
private:
    int m_campacity;
    int m_size;
    Object *myQueue_List;
    int first;
    int last;

public:


 myQueue()
    {
        m_size = 0;
        m_campacity = 10;
        myQueue_List = new Object[m_campacity];
        first = -1;
        last = -1;
    }
    ~myQueue()
    {
        delete[]  myQueue_List;
        myQueue_List = nullptr;
    }
    myQueue(myQueue &&rhs): m_size{rhs.m_size}, m_campacity{rhs.m_campacity},  myQueue_List{rhs.myQueue_List}, first{rhs.first}, last{rhs.last}
    {
        rhs.m_size = 0;
        first = 0;
        last = 0;
        rhs.myQueue_List = nullptr;
    }
    myQueue &operator=(myQueue &&rhs)
    {
        std::swap(m_size, rhs.m_size);
        std::swap(myQueue_List, rhs.myQueue_List);
        std::swap(first, rhs.first);
        std::swap(last, rhs.last);
        return *this;
    }
    myQueue(const myQueue<Object> &rhs)
    {
        m_size = 0;
        m_campacity = 10;
        myQueue_List = new Object[m_campacity];
        first = -1;
        last = -1;
        int f = rhs.first;
        for (int i = 0; i < rhs.m_size; i++)
        {
            enqueue(rhs.myQueue_List[f]);
            f++;
            if(f == rhs.m_campacity)
            {
                f = 0;
            }
        }
    }
    myQueue &operator=(const myQueue &rhs)
    {
        myQueue copy(rhs);
        std::swap(*this, copy);
        return *this;
    }

    void resize()
    {
        if (m_size == m_campacity)
        {
            m_campacity = m_campacity * 2;
            Object *temp = new Object[m_campacity];
            int f = first;
            int i = 0;
            while (i != m_size)
            {
                temp[i] = myQueue_List[f];
                i++;
                f++;
                if(f == m_size)
                {
                    f = 0;
                }
            }
            swap(myQueue_List, temp);
            delete[] temp;
            first = 0;
            last = m_size - 1;
        }
    }


   
    void enqueue(Object &newEntry)
    {
        
        if (last == m_campacity)
        {
            last = -1;
        }
        myQueue_List[++last] = newEntry;
        if (empty())
        {
            first = 0;
            last = 0;
        }
        m_size++;
        resize();
        
    }
    Object dequeue()
    {
        if (empty())
        {
            throw std::runtime_error("Empty Queue\n");
        }
        Object temp =  myQueue_List[first];
        if (m_size == 1)
        {
            first = -1;
            last = -1;
        }
        else
        {
            first++;
            if(last == m_campacity)
            {
                last = 0;
            }
        }
        m_size--;
        return temp;
    }
    Object& front()
    {
        if (empty())
        {
            throw std::runtime_error("Empty Queue\n");
        }
        return myQueue_List[first];
    }
    bool empty()
    {
       if(m_size ==0)
     {
         return true;
     }
     else
     {
         return false;
     }
     
    }
    void clear()
    {
       while(!empty())
       {
           dequeue();
       }
      
    }
};
