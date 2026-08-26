#include <iostream>
using namespace std;

typedef int Elem;
struct Node{
    Elem elem;
    Node* next;
    Node* prev;
};

class Nodelist
{
    private:
      // insert node declaration here
    public:
      class Iterator{
    private:
      Node* v;
      Iterator(Node* u);
    public:
      Elem& operator *();
      bool operator == (const Iterator& p);
      bool operator != (const Iterator& p);
      Iterator& operator++();
      Iterator operator++(int);
      Iterator& operator--();
      friend class Nodelist;
};

    public:
      Nodelist();
      int size() const;
      bool empty() const;
      Iterator begin() const;
      Iterator end() const;
      void insertFront(const Elem& e);
      void insertBack(const Elem& e );
      void insert(const Iterator& p, const Elem& e);
      void eraseFront();
      void eraseBack();
      void erase(const Iterator& p);
      void printList() const;
      
    private:
      int n;
      Node* header;
      Node* trailer;

};

Nodelist::Iterator::Iterator(Node* u)
{v = u;}

Elem& Nodelist::Iterator::operator*()
{return v->elem;}

bool Nodelist::Iterator::operator == (const Iterator& p)
{return v == p.v;}

bool Nodelist::Iterator::operator != (const Iterator& p)
{return v != p.v;}

Nodelist::Iterator Nodelist::Iterator::operator++(int)
{
    Iterator old = *this;
    v = v->next;
     return old;
}

Nodelist::Iterator& Nodelist::Iterator::operator++()
{
    v = v->next;
    return *this;
}

Nodelist::Iterator& Nodelist::Iterator::operator--()
{
    v = v-> prev;
     return *this;
}

Nodelist::Nodelist()
{
    n = 0;
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;
}

int Nodelist::size() const
{
    return n;
}

bool Nodelist::empty() const
{
    return n == 0;
}

Nodelist::Iterator Nodelist::begin() const
{
    return Iterator(header->next);
}

Nodelist::Iterator Nodelist::end() const
{
    return Iterator(trailer);
}

void Nodelist::insert(const Nodelist::Iterator& p, const Elem& e)
{
    Node* w = p.v;
    Node* u = w->prev;
    Node* v = new Node;
    v->elem = e;
    v->next = w; w->prev = v;
    v->prev = u; u->next = v;
    n++;
}

void Nodelist::insertFront(const Elem& e)
{
    insert(begin(), e);
}

void Nodelist::insertBack(const Elem& e)
{
    insert(end(), e);
}

void Nodelist::erase(const Iterator& p)
{
    Node* temp = p.v;
    Node* w = temp->next;
    Node* u = temp->prev;
    w->prev = u;
    u->next = w;
    delete temp;
    n--;
}

void Nodelist::eraseFront()
{
    erase(begin());
}

void Nodelist::eraseBack()
{
    erase(--end());
}

void Nodelist::printList() const
{
    int i = -1;
    for(Iterator it = begin(); it != end(); it++)
    {
        i++;
        if(i%10 == 0)
        {
            cout << endl;
        }
        cout << *it << " ";
    }
    cout << endl;
}

int main()
{
    Nodelist list;
    for(int i = 0; i < 100; i++)
    {
        list.insertBack(i);
    }
    for (Nodelist::Iterator it = list.begin(); it != list.end(); it++)
    {
        if( (*it) %2 != 0 )
        list.erase(it);
    }
    list.printList();
    return 0;

}