using Microsoft.VisualStudio.TestTools.UnitTesting;
using ConsoleApplicationMatrix;
namespace MatrixTests
{
    [TestClass]
    public class MatrixTests
    {
        [TestMethod]
        [ExpectedException(typeof(MyException))]
        public void Matrix_Expected_MyException_i()
        {
            Matrix a = new Matrix(0, 2);
        }
        [TestMethod]
        [ExpectedException(typeof(MyException))]
        public void Matrix_Expected_MyException_j()
        {
            Matrix a = new Matrix(2, -1);
        }
        [TestMethod]
        [ExpectedException(typeof(MyException))]
        public void this_Expected_MyException_set_j()
        {
            Matrix a = new Matrix(2, 2);
            a[1, 3] = 2;
        }
        [TestMethod]
        [ExpectedException(typeof(MyException))]
        public void this_Expected_MyException_get_i()
        {
            Matrix a = new Matrix(2, 2);
            int r = a[3, 1];
        }
        [TestMethod]
        public void Equel()
        {
            Matrix a = new Matrix(2, 2);
            a[0, 0] = 1; a[0, 1] = 1; a[1, 0] = 1; a[1, 1] = 1;
            Matrix b = new Matrix(2, 2);
            b[0, 0] = 1; b[0, 1] = 1; b[1, 0] = 1; b[1, 1] = 1;
            bool r = a == b;
            Assert.IsTrue(r);
            Assert.AreEqual(a, b);
        }
        [TestMethod]
        public void Summa()
        {
            Matrix a = new Matrix(2, 2);
            a[0, 0] = 1; a[0, 1] = 1; a[1, 0] = 1; a[1, 1] = 1;
            Matrix b = new Matrix(2, 2);
            b[0, 0] = 2; b[0, 1] = 2; b[1, 0] = 2; b[1, 1] = 2;
            Matrix expected = new Matrix(2, 2);
            expected[0, 0] = 3; expected[0, 1] = 3;
            expected[1, 0] = 3; expected[1, 1] = 3;
            Matrix actual = new Matrix(2, 2);
            actual = a + b;
            Assert.IsTrue(actual == expected);
        }
        [TestMethod]
        public void Proizvedenie()
        {
            Matrix a = new Matrix(2, 2);
            a[0, 0] = 1; a[0, 1] = 1; a[1, 0] = 1; a[1, 1] = 1;
            Matrix b = new Matrix(2, 2);
            b[0, 0] = 2; b[0, 1] = 2; b[1, 0] = 2; b[1, 1] = 2;
            Matrix expected = new Matrix(2, 2);
            expected[0, 0] = 4; expected[0, 1] = 4;
            expected[1, 0] = 4; expected[1, 1] = 4;
            Matrix actual = new Matrix(2, 2);
            actual = a * b;
            Assert.IsTrue(actual == expected);
        }
        [TestMethod]
        public void Raznostb()
        {
            Matrix a = new Matrix(2, 2);
            a[0, 0] = 1; a[0, 1] = 1; a[1, 0] = 1; a[1, 1] = 1;
            Matrix b = new Matrix(2, 2);
            b[0, 0] = 2; b[0, 1] = 2; b[1, 0] = 2; b[1, 1] = 2;
            Matrix expected = new Matrix(2, 2);
            expected[0, 0] = -1; expected[0, 1] = -1;
            expected[1, 0] = -1; expected[1, 1] = -1;
            Matrix actual = new Matrix(2, 2);
            actual = a - b;
            Assert.IsTrue(actual == expected);
        }
        [TestMethod]
        public void Minimum()
        {
            Matrix a = new Matrix(2, 2);
            a[0, 0] = 1; a[0, 1] = 2; a[1, 0] = 3; a[1, 1] = 4;
            int actual;
            actual = a.Min();
            Assert.IsTrue(actual == 1);
        }
        [TestMethod]
        public void ToStr()
        {
            Matrix a = new Matrix(2, 2);
            a[0, 0] = 1; a[0, 1] = 2; a[1, 0] = 3; a[1, 1] = 4;
            string actual;
            actual = a.ToString();
            Assert.IsTrue(actual == "{ {1, 2, 3, 4} }");
        }
        [TestMethod]
        public void Transponirovanie()
        {
            Matrix a = new Matrix(2, 2);
            a[0, 0] = 1; a[0, 1] = 2; a[1, 0] = 3; a[1, 1] = 4;
            Matrix expected = new Matrix(2, 2);
            expected[0, 0] = 1; expected[0, 1] = 3;
            expected[1, 0] = 2; expected[1, 1] = 4;
            Matrix actual = new Matrix(2, 2);
            actual = a.Transp();
            Assert.IsTrue(actual == expected);
        }
    }
}
