#include <iostream>
#include <stdexcept>
#include <string>
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

   string func(string expression)
    {
        string output;
        stack<char> c;
        for (int i=0; i<expression.length(); i++)
        if (expression[i] >= '0' && expression[i] <= '9')
        {
            output += expression[i];
            if (i <expression.length() -1 && expression[i+1] < '0' || expression[i+1] > '9')
            output += ' ';
        }
        else if (expression[i] == '+' || expression[i] == '-')
        {
            if (c.empty() || c.top() == '(')
            c.push(expression[i]);
            else
            {
                while (!c.empty() && c.top() != '(')
                {
                    output += c.pop();
                    output += ' ';
                }
                c.push(expression[i]);
            }
        }
        else if(expression[i] == '*' || expression[i] == '/')
        {
            if(c.empty() || c.top() =='(')
            c.push(expression[i]);
            
            else if (c.top() == '*' || c.top() == '/')
            {
               // while(!c.empty() && c.top() != '(')
               // {
                    output += c.pop();
                    output += ' ';
              //  }
                c.push(expression[i]);
            }
            else if (c.top() == '+' || c.top() == '-')
            c.push(expression[i]);
        }
        
        else if (expression[i] == '(')
        {
            c.push(expression[i]);
        }
        else if (expression[i] == ')')
        {
            while(!c.empty() && c.top() != '(' )
            {output += c.pop(); output += ' ';}
            c.pop();
        }
        while(!c.empty())
        {output += c.pop(); output += " ";}
        return output;
    }

    int evaluate(string expression)
    {
        stack<int> s;
        for(int i=0; i<expression.length(); i++)
        {
            if(expression[i] >= '0' && expression[i] <= '9')
            {
                int total = 0;
                while(expression[i] >= '0' && expression[i] <= '9')
                {
                    total = total * 10 + (expression[i] - '0');
                    i++;
                }
                s.push(total);
            }
            else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
            {
                int total;
                int left;
                int right;
                switch(expression[i])
                {
                    case '+' : right = s.pop(); left = s.pop(); total = left + right; break;
                    case '-' : right = s.pop(); left = s.pop(); total = left - right; break;
                    case '*' : right = s.pop(); left = s.pop(); total = left * right; break;
                    case '/' : right = s.pop(); left = s.pop();
                    if(right == 0)
                    throw runtime_error (" division by zero ");
                    total = left / right; break;
                }
                s.push(total);
            }
            else if (expression[i] == ' ')
            continue;

            else
            throw runtime_error("bad string value");

        }
        return s.pop();
    }

int main()
{
    string s = "37 - 4 * (12 + 3) / 3 + 2 * (8 - 5)";
    s = func(s);
    cout << s;
    int fin = evaluate(s);
    cout << fin;
    return 0;
}