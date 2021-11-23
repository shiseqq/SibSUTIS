#include "pch.h"
#include "CppUnitTest.h"
#include "../lab10/TComplexEditor.h"
#include "../lab10/TComplexEditor.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(TComplexEditorTests)
	{
	public:
		TEST_METHOD(Constructor)
		{
			string expected = "0";
			TComplexEditor a;
			Assert::IsTrue(expected == a.getComplexString());
		}

        TEST_METHOD(isZero) {
            TComplexEditor a;
            Assert::IsTrue(a.isZero());
        }

        TEST_METHOD(isZero2) {
            TComplexEditor a;
            a.addNumber(1);
            Assert::IsFalse(a.isZero());
        }

        TEST_METHOD(addNumber) {
            string expected = "1";
            TComplexEditor a;
            a.addNumber(1);
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(addNumber2) {
            string expected = "-16";
            TComplexEditor a;
            a.addNumber(-16);
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(addSign) {
            string expected = "-16";
            TComplexEditor a;
            a.addNumber(16);
            a.addSign();
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(addSign2) {
            string expected = "44+i*11";
            TComplexEditor a;
            a.setComplexString("-44+i*11");
            a.addSign();
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(addSign3) {
            string expected = "-58-i*1";
            TComplexEditor a;
            a.addNumber(-58);
            a.addIm();
            a.addNumber(1);
            a.addSign();
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(addIm) {
            string expected = "15+i*4";
            TComplexEditor a;
            a.addNumber(15);
            a.addIm();
            a.addNumber(4);
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(addIm2) {
            std::string expected = "-5+i*10";
            TComplexEditor a;
            a.addNumber(-5);
            a.addIm();
            a.addNumber(10);
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(addIm3) {
            auto func = [] { 
                TComplexEditor a;
                a.addIm();
                a.addIm(); 
            };
            Assert::ExpectException<logic_error>(func);
        }

        TEST_METHOD(editComplex) {
            string expected = "-8";
            TComplexEditor a;
            a.addNumber(8);
            a.editComplex(ComplexOperations::ADD_SIGN);
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(editComplex2) {
            string expected = "8";
            TComplexEditor a;
            a.addNumber(-8);
            a.editComplex(ComplexOperations::ADD_SIGN);
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(editComplex3) {
            string expected = "8+i*4";
            TComplexEditor a;
            a.addNumber(8);
            a.editComplex(ComplexOperations::ADD_IM);
            a.addNumber(4);
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(editComplex4) {
            string expected = "8+i*40";
            TComplexEditor a;
            a.addNumber(8);
            a.editComplex(ComplexOperations::ADD_IM);
            a.addNumber(4);
            a.editComplex(ComplexOperations::ADD_ZERO);
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(editComplex5) {
            string expected = "8-i*4";
            TComplexEditor a;
            a.addNumber(8);
            a.editComplex(ComplexOperations::ADD_IM);
            a.addNumber(4);
            a.editComplex(ComplexOperations::ADD_SIGN);
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(setComplexString) {
            string expected = "8+i*4";
            TComplexEditor a;
            a.setComplexString("8+i*4");
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(setComplexString2) {
            string expected = "-8-i*4";
            TComplexEditor a;
            a.setComplexString("-8-i*4");
            Assert::IsTrue(expected == a.getComplexString());
        }

        TEST_METHOD(setComplexString3) {
            auto func = [] {
                TComplexEditor a;
                a.setComplexString("i*4");
            };
            Assert::ExpectException<invalid_argument>(func);
        }
	};
}
