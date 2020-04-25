#include "Lnko.h"

void largestCommonDivisor(C2L* E1, C2L* E2)
{
    C2L* p = E1->next;
    C2L* q = E2->next;
    while(p != E1 && q != E2)
    {
        if(p->key < q->key)
        {
            C2L* r = p->next;
            C2L::out(p);
            delete p;

            p = r;
        }
        else if(p->key == q->key)
        {
            C2L* r = q->next;
            C2L::out(q);
            delete q;

            q = r;
            p = p->next;
        }
        else if(p->key > q->key)
        {
            C2L* r = q->next;
            C2L::out(q);
            delete q;

            q = r;
        }
    }
    while(p != E1)
    {
        C2L* r = p->next;
        C2L::out(p);
        delete p;

        p = r;
    }
    while(q != E2)
    {
        C2L* r = q->next;
        C2L::out(q);
        delete q;

        q = r;
    }
}