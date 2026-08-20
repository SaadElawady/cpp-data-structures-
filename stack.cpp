#include <iostream>
using namespace std;

struct node
{
    int elem;
    node* next;
};

class stack
{
    private:
      node* first;
      int n;
    public:
    stack() : n(0), first(NULL) {}
    int size() const;
    bool empty() const;
    int top() const;
    void push(int var);
    int pop();
    void display() const;
    ~stack();
};

int stack::size() const
{
    return n;
}

bool stack::empty() const
{
    return n == 0;
}

int stack::top() const
{
    if(empty())
    {cout<<"error: empty stack\n"; return -1;}
    return first->elem;

}

void stack::push(int var)
{
    node* newnode = new node;
    newnode->elem = var;
    newnode->next = first;
    first = newnode;
    n++;
}

int stack::pop()
{
     if(empty())
    {cout<<"error: empty stack\n"; return -1;}
    node* temp = first;
    int tempval = first->elem;
    first = first->next;
      n--;
    delete temp;
    return tempval;
}

stack::~stack()
{
    while ( first != NULL)
    {
        node* temp = first;
        first = first->next;
        delete temp;
    }
    cout << "stack destroyed\n";
}

void stack::display() const
{
    node* temp = first;
    while(temp != NULL)
    {
        cout<< temp->elem << " ";
        temp = temp->next;
    }
}

int main()
{
    stack s;
    cout << s.empty() << '\n';
    cout << s.size() << '\n';
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    stack s2;
    s2.push(5);
    s2.push(15);
    s2 = s;
    s2.display();
    return 0;
}