#include <iostream>
#include <stdexcept>
using namespace std;

struct node
{
    int elem;
    node* next;
};

class queue
{
    private:
      node* first;
      node* last;
      int n;
    public:
      queue();
      int size() const;
      bool empty() const;
      int front() const;
      queue(const queue& q);
      queue& operator= (const queue& q);
      void enqueue( int var);
      int dequeue();
      void display() const;
      ~queue();

};

queue::queue() : first(nullptr), last(nullptr), n(0) {}

int queue::size() const
{
    return n;
}

bool queue::empty() const
{
    return n == 0;
}

int queue::front() const
{
    if(empty())
    throw runtime_error("empty queue\n");
    return first->elem;
}

queue::queue(const queue& q) : first(nullptr), last(nullptr), n(0)
{
    node* temp = q.first; 
    {
       while(temp != nullptr)
       {
       node* newnode = new node;
       newnode->elem = temp->elem;
       newnode->next = nullptr;
       if(empty())
       {
        first = last = newnode;
       }
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

void queue::enqueue(int var)
{
    node* newnode = new node;
    newnode->elem = var;
    newnode->next = nullptr;
    if(empty())
    {
        first = last = newnode;
    }
    else
    {
        last->next = newnode;
        last = newnode;
    }
    n++;
}

int queue::dequeue()
{
    if(empty())
    throw runtime_error("empty queue\n");
    node* temp = first;
    int val = temp->elem;
    if(size() == 1)
    {
        first = last = nullptr;
    }
    else
    {
        first = first->next;
    }
    delete temp;
    n--;
    return val;
}

queue& queue::operator= (const queue& q)
{
    if (this == &q)
    return *this;
    while(!empty())
    dequeue();
    node* temp = q.first;
    while(temp != nullptr)
    {
       node* newnode = new node;
       newnode->elem = temp->elem;
       newnode->next = nullptr;
       if(empty())
       {
        first = last = newnode;
       }
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

queue::~queue()
{
    while(!empty())
    dequeue();
}

void queue::display() const
{
    node* temp = first;
    while(temp != nullptr)
    {
        cout << temp->elem << " ";
        temp = temp->next;
    }
    cout << endl;
}

int joeseph(const queue& q, int k)
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
    queue q1;
    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);
    q1.enqueue(4);
    q1.enqueue(5);
    q1.enqueue(6);
    q1.enqueue(7);
    int x = joeseph(q1,3);
    cout << x;
    return 0;
}