#ifndef C2L__H
#define C2L__H

#include <string>
#include <iostream>

class C2L
{
    public:

            //-----------FIELDS--------------//
            int key;
            C2L *prev, *next;

            enum class Exceptions { FILE_ERROR, INVALID_VALUE };
            //-----------CONSTRUCTORS--------//
            C2L();
            C2L(int key);
            ~C2L();

            //-----------PUBLIC MEMBER FUNCTIONS----------//
            void setEmpty();
            void print(std::ostream& os = std::cout);
            static void precede(C2L* q, C2L* r);
            static void follow(C2L* p, C2L* q);
            static void out(C2L* q);

            //--------- FILE INPUT FACTORY FUNCTION----------//
            static C2L* C2L_read(const std::string& filename);
};

#endif