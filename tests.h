#ifndef TESTS__H
#define TESTS__H

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "C2L.h"
#include "Lnko.h"

namespace test
{
    // Egy C2L listat hasonlit ossze elemenkent a vart eredmennyel
    template<size_t ArraySize>
    bool compareWithResult(C2L* E1, int(&array)[ArraySize])
    {
        C2L* p = E1->next;
        size_t i = 0;
        bool allMatches = true;
        while(p != E1 && i < (sizeof(array) / sizeof(array[0])))
        {
            CHECK(p->key == array[i]);
            if(p->key != array[i])
                allMatches = false;
            ++i;
            p = p->next;
        }
        return allMatches;
    }
}

TEST_CASE("Nemletezo fajl")
{
    CHECK_THROWS(C2L::C2L_read(":/?%.txt"));
}

TEST_CASE("Primtenyezos felbontas tesztelese")
{
    SECTION("2-nel kisebb (nem megengedett szam)")
    {
        CHECK_THROWS(C2L::C2L_read("./tests/Test00.txt"));
    }

    SECTION("Paros szam")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test01.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test02.txt");
        C2L* E3 = C2L::C2L_read("./tests/Test03.txt");

        int A1[] = {2};
        int A2[] = {2,2,2,3,3};
        int A3[] = {2,2,2,2,2,2,2,2};
        CHECK(test::compareWithResult<>(E1,A1));
        CHECK(test::compareWithResult<>(E2,A2));
        CHECK(test::compareWithResult<>(E3,A3));


        delete E1;
        delete E2;
        delete E3;
    }

    SECTION("Paratlan szam")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test04.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test05.txt");
        C2L* E3 = C2L::C2L_read("./tests/Test06.txt");

        int A1[] = {7};
        int A2[] = {3,5,7};
        int A3[] = {3,7,11};
        CHECK(test::compareWithResult<>(E1,A1));
        CHECK(test::compareWithResult<>(E2,A2));
        CHECK(test::compareWithResult<>(E3,A3));
        delete E1;
        delete E2;
        delete E3;
    }
}

TEST_CASE("Legnagyobb kozos oszto tesztelese eredmeny szama szerint")
{
    SECTION("Nincs kozos primtenyezo - lnko=1")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test07.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test08.txt");
        largestCommonDivisor(E1,E2);

        CHECK(E1->next == E1);
        CHECK(E1->prev == E1);

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }

    SECTION("Egy primtenyezo eredmeny")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test09.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test10.txt");
        largestCommonDivisor(E1,E2);

        int A1[] = {2};
        CHECK(test::compareWithResult(E1,A1));

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }

    SECTION("Ketto primtenyezo eredmeny")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test11.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test12.txt");
        largestCommonDivisor(E1,E2);

        int A1[] = {5,11};
        CHECK(test::compareWithResult(E1,A1));

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }

    SECTION("Tobb (osszes - 5) primtenyezo eredmeny")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test13.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test13.txt");
        largestCommonDivisor(E1,E2);

        int A1[] = {2,3,5,11,13};
        CHECK(test::compareWithResult(E1,A1));

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }
}

TEST_CASE("Legnagyobb kozos oszto, kozos primtenyezok elhelyezkedese szerint")
{
    SECTION("Kozosek elol")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test14.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test15.txt");
        largestCommonDivisor(E1,E2);

        int A1[] = {3};
        CHECK(test::compareWithResult(E1,A1));

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }

    SECTION("Kozosek kozepen")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test16.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test17.txt");
        largestCommonDivisor(E1,E2);

        int A1[] = {5,7};
        CHECK(test::compareWithResult(E1,A1));

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }

    SECTION("Kozosek vegen")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test18.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test19.txt");
        largestCommonDivisor(E1,E2);

        int A1[] = {11,13};
        CHECK(test::compareWithResult(E1,A1));

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }

    SECTION("Kozosek szetszorva (+ nagyszam)")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test26.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test27.txt");
        largestCommonDivisor(E1,E2);

        int A1[] = {3,7,13,17};
        CHECK(test::compareWithResult(E1,A1));

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }
}

TEST_CASE("Legnagyobb kozos oszto primtenyezok multiplicitasa szerint")
{
    SECTION("Kettes multiplicitas")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test20.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test21.txt");
        largestCommonDivisor(E1,E2);

        int A1[] = {2,2};
        CHECK(test::compareWithResult(E1,A1));

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }

    SECTION("Harmas multiplicitas")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test22.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test23.txt");
        largestCommonDivisor(E1,E2);

        int A1[] = {3,3,3};
        CHECK(test::compareWithResult(E1,A1));

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }

    SECTION("Negyes multiplicitas")
    {
        C2L* E1 = C2L::C2L_read("./tests/Test24.txt");
        C2L* E2 = C2L::C2L_read("./tests/Test25.txt");
        largestCommonDivisor(E1,E2);

        int A1[] = {5,5,5};
        CHECK(test::compareWithResult(E1,A1));

        CHECK(E2->next == E2);
        CHECK(E2->prev == E2);

        delete E1;
        delete E2;
    }
}

#endif