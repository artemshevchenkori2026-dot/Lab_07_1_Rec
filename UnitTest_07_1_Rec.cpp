#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_07_1_Rec/Lab_07_1_Rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab071Rec
{
    TEST_CLASS(UnitTestLab071Rec)
    {
    public:
        TEST_METHOD(TestMethodCalcRows)
        {
            const int rowCount = 2;
            const int colCount = 2;
            int** q = new int* [rowCount];
            for (int i = 0; i < rowCount; i++)
                q[i] = new int[colCount];

            // Заповнення даними:
            // q[0][0] = 10 (i=0, j=0 — парні індекси, пропускається)
            // q[0][1] = 5  (підходить)
            // q[1][0] = 7  (підходить)
            // q[1][1] = -3 (не підходить)
            q[0][0] = 10; q[0][1] = 5;
            q[1][0] = 7;  q[1][1] = -3;

            int S = 0, k = 0;
            CalcRows(q, rowCount, colCount, 0, S, k);

            Assert::AreEqual(12, S);       // 5 + 7 = 12
            Assert::AreEqual(2, k);        // 2 елементи
            Assert::AreEqual(0, q[0][1]);   // Обнулено
            Assert::AreEqual(0, q[1][0]);   // Обнулено

            for (int i = 0; i < rowCount; i++)
                delete[] q[i];
            delete[] q;
        }
    };
}