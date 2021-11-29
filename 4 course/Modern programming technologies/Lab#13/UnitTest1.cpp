#include "pch.h"
#include "CppUnitTest.h"
#include "../lab13/TSet.h"
#include <set>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(INIT)
		{
			TSet<int> a;
			set<int> b;
			Assert::IsTrue(a.container == b);
		}
		TEST_METHOD(CLEAR)
		{
			TSet<int> a;
			a.insert_(1);
			a.insert_(2);
			a.clear();
			set<int> b;
			Assert::IsTrue(a.container == b);
		}
		TEST_METHOD(INSERT)
		{
			TSet<int> a;
			a.insert_(1);
			a.insert_(2);
			set<int> b{1,2};
			Assert::IsTrue(a.container == b);
		}
		TEST_METHOD(IS_EMPTY)
		{
			TSet<int> a;
			Assert::IsTrue(a.isEmpty());
		}

		TEST_METHOD(CONTAINS_1)
		{
			TSet<int> a;
			a.insert_(1);
			a.insert_(2);
			a.insert_(3);
			Assert::IsTrue(a.contains(1));
		}
		TEST_METHOD(CONTAINS_2)
		{
			TSet<int> a;
			a.insert_(1);
			a.insert_(2);
			a.insert_(3);
			Assert::IsTrue(a.contains(2));
		}
		TEST_METHOD(CONTAINS_3)
		{
			TSet<int> a;
			a.insert_(1);
			a.insert_(2);
			a.insert_(3);
			Assert::IsTrue(a.contains(3));
		}
		TEST_METHOD(UNION)
		{
			TSet<int> a;
			TSet<int> b;
			set<int> c{ 1, 2, 3 };
			a.insert_(1);
			a.insert_(2);
			a.insert_(3);
			b.insert_(1);
			b.insert_(2);
			b.insert_(3);
			TSet<int> result = a.add(b);
			Assert::IsTrue(result.container==c);
		}
		TEST_METHOD(SUB)
		{
			TSet<int> a;
			TSet<int> b;
			set<int> c{ 1, 2, 3 };
			a.insert_(1);
			a.insert_(2);
			a.insert_(3);
			b.insert_(4);
			TSet<int> result = a.subtract(b);
			Assert::IsTrue(result.container == c);
		}
		TEST_METHOD(MUL)
		{
			TSet<int> a;
			TSet<int> b;
			set<int> c{ 1 };
			a.insert_(1);
			a.insert_(2);
			a.insert_(3);
			b.insert_(1);
			b.insert_(4);
			b.insert_(5);
			TSet<int> result = a.multiply(b);
			Assert::IsTrue(result.container == c);
		}
		TEST_METHOD(COUNTER)
		{
			TSet<int> a;
			a.insert_(1);
			a.insert_(2);
			a.insert_(3);
			Assert::IsTrue(a.count() == 3);
		}
		TEST_METHOD(ELEMENT)
		{
			TSet<int> a;
			a.insert_(5);
			Assert::IsTrue(a.element(0) == 5);
		}
	};
}
