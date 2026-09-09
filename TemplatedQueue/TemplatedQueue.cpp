#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
struct node
{
    int elem;
    node<T>* next;
};

template <typename T>
class queue
{
    private:
      node<T>* first;
      node<T>* last;
      int n;
    public:
      queue();
      int size() const;
      bool empty() const;
      T front() const;
      queue(const queue<T>& q);
      queue<T>& operator= (const queue<T>& q);
      void enqueue(T var);
      int dequeue();
      void display() const;
      ~queue();

};

template <typename T>
queue<T>::queue() : first(nullptr), last(nullptr), n(0) {}

template <typename T>
int queue<T>::size() const
{
    return n;
}

template <typename T>
bool queue<T>::empty() const
{
    return n == 0;
}

template <typename T>
T queue<T>::front() const
{
    if(empty())
    throw runtime_error("empty queue\n");
    return first->elem;
}

template <typename T>
queue<T>::queue(const queue<T>& q) : first(nullptr), last(nullptr), n(0)
{
    node<T>* temp = q.first; 
    {
       while(temp != nullptr)
       {
       node<T>* newnode = new node<T>;
       newnode->elem = temp->elem;
       newnode->next = nullptr;
       if(empty())
        first = last = newnode;
       else
       {
        last->next = newnode;
        last = newnode;
       }
       n++;
       temp = temp->next;
    }

    }
}

template <typename T>
void queue<T>::enqueue(T var)
{
    node<T>* newnode = new node<T>;
    newnode->elem = var;
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
int queue<T>::dequeue()
{
    if(empty())
    throw runtime_error("empty queue\n");
    node<T>* temp = first;
    T val = temp->elem;
    if(size() == 1)
    first = last = nullptr;

    else
    first = first->next;

    delete temp;
    n--;
    return val;
}

template <typename T>
queue<T>& queue<T>::operator= (const queue<T>& q)
{
    if (this == &q)
    return *this;
    while(!empty())
    dequeue();
    node<T>* temp = q.first;
    while(temp != nullptr)
    {
       node<T>* newnode = new node<T>;
       newnode->elem = temp->elem;
       newnode->next = nullptr;
       if(empty())
        first = last = newnode;
       else
       {
        last->next = newnode;
        last = newnode;
       }
       n++;
       temp = temp->next;

    }
    return *this;
}

template <typename T>
queue<T>::~queue()
{
    while(!empty())
    dequeue();
}

template <typename T>
void queue<T>::display() const
{
    node<T>* temp = first;
    while(temp != nullptr)
    {
        cout << temp->elem << " ";
        temp = temp->next;
    }
    cout << endl;
}

int joeseph(const queue<int>& q, int k)
{
    queue temp = q;
    while(temp.size() > 1)
    {
        for(int i=0; i<k-1; i++)
        {
            int x = temp.dequeue();
            temp.enqueue(x);
        }
        temp.dequeue();
    }
    return temp.front();
} 

int main()
{
    queue<int> q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.enqueue(4);
    q1.enqueue(5);
    q1.enqueue(6);
    q1.enqueue(7);
    //int x = joeseph(q1,3);
    //cout << x;
    queue<int> q2(q1);
    queue<int> q3;
    q3 = q2;
    q3 = q3;
    q3.display();
    return 0;
}