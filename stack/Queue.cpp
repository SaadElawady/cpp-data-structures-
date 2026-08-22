#include <iostream>
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
      void dequeue();
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
    {
        cout<< " queue empty\n "; return 0;
    }
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

void queue::dequeue()
{
    if(empty())
    {
        cout << "error : queue empty\n "; return;
    }
    node* temp = first;
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

int main()
{
    queue q1;
    //cout << q1.empty() << endl;
    //cout << q1.size() << endl;
    //q1.dequeue();
    q1.enqueue(20);
    q1.enqueue(40);
    q1.enqueue(60);
    q1.enqueue(80);
    q1.display();
    queue q2(q1);
    q2.dequeue();
    q2.enqueue(100);
    q2.display();
    queue q3;
    q3 = q2;
    q3.dequeue();
    q3.enqueue(200);
    q3.display();
    q1 = q3;
    q1.display();
    q1 = q1;
    q1.display();
    return 0;
}