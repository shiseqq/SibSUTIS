#include "pch.h"
#include "CppUnitTest.h"
#include "../lab11/TMemory.h"
#include "../../lab6/lab6/TComplex.h"
#include "../../lab6/lab6/TComplex.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(ADD) {
            TComplex t(1, 5);
            TMemory<TComplex> tmem(t);
            tmem.add(t);
            Assert::IsTrue("2+i*10" == tmem.get().ToStr());
        }

        TEST_METHOD(WRITE) {
            TComplex t1(1, 5), t2(5, 7);
            TMemory<TComplex> tmem(t1);
            tmem.write(t2);
            Assert::IsTrue("5+i*7" == tmem.get().ToStr());
        }

        TEST_METHOD(GET) {
            TComplex t(1, 5);
            TMemory<TComplex> tmem(t);
            Assert::IsTrue("1+i*5" == tmem.get().ToStr());
        }

        TEST_METHOD(CLEAR) {
            TComplex t(1, 5);
            TMemory<TComplex> tmem(t);
            tmem.clear();
            Assert::IsTrue(string("0+i*0") == tmem.get().ToStr());
        }

        TEST_METHOD(READ_FSTATE_OFF) {
            TComplex t(1, 5);
            TMemory<TComplex> tmem(t);
            tmem.clear();
            Assert::IsTrue("0" == tmem.readFState());
        }

        TEST_METHOD(READ_FSTATE_ON) {
            TComplex t(1, 5);
            TMemory<TComplex> tmem(t);
            tmem.add(t);
            Assert::IsTrue("1" == tmem.readFState());
        }

        TEST_METHOD(READ_NUMBER) {
            TComplex t(1, 5);
            TMemory<TComplex> tmem(t);
            Assert::IsTrue(t.ToStr() == tmem.readNumber().ToStr());
        }
	};
}
