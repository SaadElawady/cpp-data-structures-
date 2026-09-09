#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
struct node
{
    T elem;
    node<T>* next;
};

template <typename T>
class Iterator
{
    private:
      node<T>* current;
    public:
    Iterator();
    Iterator(node<T>* somenode);
    T& operator*();
    void operator++();
    Iterator<T> operator++(int);
    bool operator==(const Iterator<T>& it);
    bool operator!=(const Iterator<T>& it);

};

template <typename T>
class list
{
    private:
      node<T>* first;
      node<T>* last;
      int n;
    public:
    list();
    int size() const;
    bool empty() const;
    T front() const;
    T back() const;
    void push_front(T item);
    void push_back(T item);
    T pop_front();
    T pop_back();
    void clear();
    void insert(int index, T item);
    void erase(int index);
    int find(T item) const;
    list(const list<T>& li);
    list<T>& operator= (const list<T>& li);
    Iterator<T> begin() const;
    Iterator<T> end() const;
    void display() const;
    ~list();
};

template <typename T>
list<T>::list() : first(nullptr), last(nullptr), n(0) {}

template<typename T>
int list<T>::size() const
{
    return n;
}

template <typename T>
bool list<T>::empty() const
{
    return n == 0;
}

template <typename T>
T list<T>::front() const
{
    return first->elem;
}

template <typename T>
T list<T>::back() const 
{
    return last->elem;
}

template <typename T>
void list<T>::push_front(T item)
{
    node<T>* newnode = new node<T>;
    newnode->elem = item;
    newnode->next =first;
    if(empty())
    first = last = newnode;
    else
    first = newnode;
    n++;
}

template <typename T>
void list<T>::push_back(T item)
{
    node<T>* newnode = new node <T>;
    newnode->elem = item;
    newnode->next = nullptr;
    if(empty())
    first = last = newnode;
    else
    {
        last->next = newnode;
        last = newnode;
    }
    n++;
}

template <typename T>
T list<T>::pop_front()
{
    if(empty())
    throw runtime_error("empty list");
    node<T>* temp = first;
    T val = first->elem;
    if(size() == 1)
    first = last = nullptr;
    else
    first = first->next;
    delete temp;
    n--;
    return val;
}

template<typename T>
T list<T>::pop_back()
{
    if(empty())
    throw runtime_error("empty stack");
    node<T>* temp = first;
    T val;
    if(size() == 1)
    first = last = nullptr;
    else
    {
        int index = 0;
        while(index < size()-2)
        {
            temp = temp->next;
            index++;
        }
        last = temp;
        temp = temp->next;
        last->next = nullptr;
    }
    val = temp->elem;
    delete temp;
    n--;
    return val;
}

template <typename T>
void list<T>::clear()
{
    while(!empty())
    pop_front();
}

template <typename T>
list<T>::list(const list<T>& li) : first(nullptr), last(nullptr), n(0)
{
    node<T>* temp = li.first;
    for(int i=0; i<li.size(); i++)
    {
        push_back(temp->elem);
        temp = temp->next;
    }
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& li)
{
    if(this == &li)
    return *this;
    while(!empty())
    pop_front();
    node<T>* temp = li.first;
    for(int i=0; i<li.size(); i++)
    {
        push_back(temp->elem);
        temp = temp->next;
    }
    return *this;
}

template <typename T>
list<T>::~list()
{
    while(!empty())
    pop_front();
    cout << "list destroyed\n";
}

template <typename T>
void list<T>::insert(int index,T item)
{
    if(index <= 0 || index > size()+1)
    throw runtime_error("wrong index");
    else if(empty() || index == 1)
    push_front(item);
    else if (index == size()+1)
    push_back(item);
    else
    {
        node<T>* temp = first;
        for(int i=0; i<index-2; i++)
        temp = temp->next;
        node<T>* newnode = new node<T>;
        newnode->elem = item;
        newnode->next = temp->next;
        temp->next = newnode;
    }
}

template <typename T>
void list<T>::erase(int index)
{
    if(empty())
    throw runtime_error("empty list");
    else if(index <= 0 || index > size())
    throw runtime_error("wrong index");
    else if(index == 1)
    pop_front();
    else if(index == size())
    pop_back();
    else
    {
        node<T>* temp1 = first;
        node<T>* temp2;
        node<T>* temp3;
        for(int i=0; i<index-2; i++)
        temp1 = temp1->next;
        temp2 = temp1->next;
        temp3 = temp2->next;
        temp1->next = temp3;
        delete temp2;
        n--;
    }

}

template <typename T>
int list<T>::find(T item) const
{
    if(empty())
    throw runtime_error("empty list");
    node<T>* temp = first;
    int n = 1;
    while(temp != nullptr)
    {
        if(temp->elem == item)
        return n;
        temp = temp->next;
        n++;
    }
    cout<< " this value is not in the list\n";
    return -1;
}

template <typename T>
Iterator<T> list<T>::begin() const
{
    return Iterator<T>(first);
}

template <typename T>
Iterator<T> list<T>::end() const
{
    return Iterator<T>(nullptr);
}

template <typename T>
void list<T>::display() const
{
    node<T>* temp = first;
    while (temp != nullptr)
    {
        cout << temp->elem << " ";
        temp = temp->next;
    }
    cout << endl;
}

template <typename T>
Iterator<T>::Iterator() : current(nullptr) {}

template <typename T>
Iterator<T>::Iterator(node<T>* somenode) : current(somenode) {}

template <typename T>
T& Iterator<T>::operator*()
{
    return current->elem;
}

template <typename T>
void Iterator<T>::operator++()
{
    current = current->next;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator<T> temp(current);
    current = current->next;
    return temp;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& it)
{
    return current == it.current;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& it)
{
    return current != it.current;
}




int main()
{
    list<int> l1;
    l1.push_back(5);
    l1.push_back(10);
    l1.push_back(15);
    l1.push_back(20);
    l1.push_front(4);
    l1.push_front(3);
    l1.push_front(2);
    l1.push_front(1);
    //l1.erase(8);
    //l1.insert(8,25);
    //cout << "25 is found at index: " << l1.find(25) << endl;
    Iterator<int> it = l1.begin();
    cout << *it++ <<endl;
    cout << *it << endl;
    return 0;
}