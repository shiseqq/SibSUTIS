#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12/TProc.h"
#include "../../lab6/lab6/TComplex.h"
#include "../../lab6/lab6/TComplex.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(INIT)
		{
			TComplex leftFrac(1,2);
			TComplex rightFrac(3,4);
			TProc<TComplex> obj(leftFrac, rightFrac);
			TComplex answer(3,4);
			Assert::IsTrue(answer.ToStr() == obj.readRight().ToStr());
		}
		TEST_METHOD(ADD)
		{
			TComplex leftFrac(1, 2);
			TComplex rightFrac(1, 2);
			TProc<TComplex> obj(leftFrac, rightFrac);
			TOperations oper = Add;
			obj.writeOper(oper);
			obj.doOper();
			TComplex answer(2, 4);
			Assert::IsTrue(answer.ToStr() == obj.readLeft().ToStr());
		}
		TEST_METHOD(SUB)
		{
			TComplex leftFrac(1, 2);
			TComplex rightFrac(1, 2);
			TProc<TComplex> obj(leftFrac, rightFrac);
			TOperations oper = Sub;
			obj.writeOper(oper);
			obj.doOper();
			TComplex answer(0, 0);
			Assert::IsTrue(answer.ToStr() == obj.readLeft().ToStr());
		}
		TEST_METHOD(MUL)
		{
			TComplex leftFrac(1, 2);
			TComplex rightFrac(1, 2);
			TProc<TComplex> obj(leftFrac, rightFrac);
			TOperations oper = Mul;
			obj.writeOper(oper);
			obj.doOper();
			TComplex answer(-3, 4);
			Assert::IsTrue(answer.ToStr() == obj.readLeft().ToStr());
		}
		TEST_METHOD(DIV)
		{
			TComplex leftFrac(1, 2);
			TComplex rightFrac(1, 2);
			TProc<TComplex> obj(leftFrac, rightFrac);
			TOperations oper = Div;
			obj.writeOper(oper);
			obj.doOper();
			TComplex answer(1, 0);
			Assert::IsTrue(answer.ToStr() == obj.readLeft().ToStr());
		}
		TEST_METHOD(REV)
		{
			TComplex leftFrac;
			TComplex rightFrac(4, 2);
			TProc<TComplex> obj(leftFrac, rightFrac);
			TFunc funcOper = Rev;
			obj.doFunc(funcOper);
			TComplex answer(0.2, 0.1);
			Assert::IsTrue(answer.ToStr() == obj.readRight().ToStr());
		}
		TEST_METHOD(SQR)
		{
			TComplex leftFrac;
			TComplex rightFrac(4, 2);
			TProc<TComplex> obj(leftFrac, rightFrac);
			TFunc funcOper = Sqr;
			obj.doFunc(funcOper);
			TComplex answer(12, 16);
			Assert::IsTrue(answer.ToStr() == obj.readRight().ToStr());
		}
	};
}
