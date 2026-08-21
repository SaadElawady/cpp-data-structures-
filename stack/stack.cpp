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
    stack() : n(0), first(nullptr) {}
    stack(const stack& s);
    stack operator = (const stack& s);
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
    while(temp != nullptr)
    {
        cout<< temp->elem << " ";
        temp = temp->next;
    }
    cout << endl;
}

stack::stack(const stack& s) : first(nullptr), n(0)
{   
    for(int i=0; i<s.size(); i++)
    {
        node* newnode = new node;
        newnode->next = first;
        first = newnode;
        n++;
    }
    node* temp = s.first;
    node* current = first;
    while(current != nullptr)
    {
        current->elem = temp->elem;
        temp = temp->next;
        current = current->next;
    }
}

stack stack::operator= (const stack& s)
{
    if (this == &s)
    return *this;

    while (first != nullptr)
    {
        node* temp = first;
        first = first->next;
        delete temp;
        n--;
    }

    for (int i=0; i<s.size(); i++)
    {
        node* newnode = new node;
        newnode->next = first;
        first = newnode;
        n++;
    }

    node* temp = s.first; 
    node* current = first;
    while (current != nullptr)
    {
        current->elem = temp->elem;
        current = current->next;
        temp = temp->next;
    }
    return *this;
}

int main()
{
    stack s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);
    s1.push(40);
    stack s2;
    s2.push(5);
    s2.push(15);
    s2 = s1;
    s2.pop();
    s2.push(90);
    s2 = s2;
    s1.display();
    s2.display();
    return 0;
}