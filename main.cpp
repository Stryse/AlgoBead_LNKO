#include <iostream>
#include "C2L.h"
#include "Lnko.h"

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    try
    {
        C2L* E1 = C2L::C2L_read("input_E1.txt");
        C2L* E2 = C2L::C2L_read("input_E2.txt");
        largestCommonDivisor(E1,E2);

        std::cout << "=================LEGNAGYOBB KOZOS OSZTO=================" << std::endl;
        if(E1->next == E1 && E1->prev == E1)
        {
            std::cout << "Legnagyobb kozos oszto: 1" << std::endl;
        }
        else
        {
            std::cout << "Legnagyobb kozos oszto primtenyezos felbontasa: ";
            E1->print();
            std::cout << std::endl;
        }
        std::cout << "========================================================" << std::endl;

        delete E1;
        delete E2;
    }
    catch (C2L::Exceptions &excpt)
    {
        switch (excpt)
        {
        case C2L::Exceptions::FILE_ERROR:
            std::cerr << "Hiba tortent a fajlok beolvasasa soran! Kilepes..." << std::endl;
            break;

        case C2L::Exceptions::INVALID_VALUE:
            std::cerr << "Hibas erteket tartalmazo bemeneti fajl (Az ertek legyen legalabb (+2) (legyen primtenyezos felbontasa)) Kilepes..." << std::endl;
            break;
        default:
            std::cerr << "Nem kezelt kivetel lepett fel! Kilepes..." << std::endl;
            break;
        }
    }
    return 0;
}

#else
#include "tests.h"
#endif