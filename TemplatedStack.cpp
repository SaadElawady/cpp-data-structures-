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
class stack
{
    private:
      node<T>* first;
      int n;
    public:
    stack();
    stack(const stack& s);
    stack<T>& operator = (const stack<T>& s);
    int size() const;
    bool empty() const;
    T top() const;
    void push(const T& var);
    T pop();
    void display() const;
    ~stack();
};

template <typename T>
stack<T>::stack() : n(0), first(nullptr) {}

template <typename T>
int stack<T>::size() const
{
    return n;
}

template <typename T>
bool stack<T>::empty() const
{
    return n == 0;
}

template <typename T>
T stack<T>::top() const
{
    if(empty())
    throw runtime_error("empty stack");
    return first->elem;

}

template <typename T>
void stack<T>::push(const T& var)
{
    node<T>* newnode = new node<T>;
    newnode->elem = var;
    newnode->next = first;
    first = newnode;
    n++;
}

template <typename T>
T stack<T>::pop()
{
     if(empty())
     throw runtime_error("empty stack");
    node<T>* temp = first;
    T tempval = first->elem;
    first = first->next;
      n--;
    delete temp;
    return tempval;
}

template <typename T>
stack<T>::~stack()
{
    while ( first != nullptr)
    {
        node<T>* temp = first;
        first = first->next;
        delete temp;
    }
    cout << "stack destroyed\n";
}

template <typename T>
void stack<T>::display() const
{
    node<T>* temp = first;
    while(temp != nullptr)
    {
        cout<< temp->elem << " ";
        temp = temp->next;
    }
    cout << endl;
}

template <typename T>
stack<T>::stack(const stack<T>& s) : first(nullptr), n(0)
{   
    for(int i=0; i<s.size(); i++)
    {
        node<T>* newnode = new node<T>;
        newnode->next = first;
        first = newnode;
        n++;
    }
    node<T>* temp = s.first;
    node<T>* current = first;
    while(current != nullptr)
    {
        current->elem = temp->elem;
        temp = temp->next;
        current = current->next;
    }
}

template <typename T>
stack<T>& stack<T>::operator= (const stack<T>& s)
{
    if (this == &s)
    return *this;

    while (first != nullptr)
    {
        node<T>* temp = first;
        first = first->next;
        delete temp;
        n--;
    }

    for (int i=0; i<s.size(); i++)
    {
        node<T>* newnode = new node<T>;
        newnode->next = first;
        first = newnode;
        n++;
    }

    node<T>* temp = s.first; 
    node<T>* current = first;
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
stack<char> c;

c.push('(');
c.push('[');
c.push('{');

//cout << c.pop() << '\n';
//cout << c.pop() << '\n';
//cout << c.pop() << '\n';
stack<char> c2 = c;
c2 = c2;
c2.display();
}