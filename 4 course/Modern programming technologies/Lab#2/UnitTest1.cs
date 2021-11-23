using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace UnitTest
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethodFunc1()
        {
            int a = 4, b = 2;
            lab2.Lab2.func1(ref a,ref b);
            Assert.AreEqual(a, 4);
            Assert.AreEqual(b, 2);
            a = 2;
            b = 4;
            lab2.Lab2.func1(ref a, ref b);
            Assert.AreEqual(a, 4);
            Assert.AreEqual(b, 2);
        }

        [TestMethod]
        public void TestMethodFunc2()
        {
            double[,] arr = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 } };
            double ans=lab2.Lab2.func2(arr);
            Assert.AreEqual(ans, 46080);

            arr =new double[,] { { 1, 3 }, { 5, 7 }, { 9, 11 }, { 13 , 15 } };
            ans = lab2.Lab2.func2(arr);
            Assert.AreEqual(ans, -1);
        }

        [TestMethod]
        public void TestMethodFunc3()
        {
            double[,] arr = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 } };
            double ans = lab2.Lab2.func3(arr);
            Assert.AreEqual(ans, 6);

            arr = new double[,] { { 1, 3 }, { 5, 7 }, { 9, 11 }, { 13, 15 } };
            ans = lab2.Lab2.func3(arr);
            Assert.AreEqual(ans, -1);
        }
    }
}
