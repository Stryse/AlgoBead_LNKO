#include "C2L.h"

#include <fstream>

// Constructors
C2L::C2L() : prev(this), next(this){}

C2L::C2L(int key) : key(key), prev(this), next(this) {}

// Destructor
C2L::~C2L()
{
    setEmpty();
}

// File input factory function
C2L* C2L::C2L_read(const std::string& filename)
{
    std::ifstream ifs(filename);
    if(ifs.fail())
        throw Exceptions::FILE_ERROR;

    int inputnumber;
    ifs >> inputnumber;

    if(inputnumber < 2)
        throw Exceptions::INVALID_VALUE; 

    ifs.close();


    C2L* H = new C2L();
    C2L* p = H;
    int k = 2;
    while(inputnumber > 1)
    {
        if(inputnumber % k == 0)
        {
            inputnumber /= k;
            follow(p,new C2L(k));
            p = p->next;
        }
        else ++k;
    }
    return H;
}


void C2L::setEmpty()
{
    C2L* p = this->prev;
    while(p != this)
    {
        out(p);
        delete p;
        p = this->prev;
    }
}

void C2L::print(std::ostream& os)
{
    C2L* p = this->next;
    while(p != this)
    {
        os << p->key << " ";
        p = p->next;
    }
}

void C2L::precede(C2L* q, C2L* r)
{
    C2L* p = r->prev;
    q->prev = p;
    q->next = r;
    p->next = r->prev = q;
}

void C2L::follow(C2L* p, C2L* q)
{
    C2L* r = p->next;
    q->prev = p;
    q->next = r;
    p->next = r->prev = q;
}

void C2L::out(C2L* q)
{
    C2L* p = q->prev;
    C2L* r = q->next;
    p->next = r;
    r->prev = p;
    q->prev = q->next = q;
}
