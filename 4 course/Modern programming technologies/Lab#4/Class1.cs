using System;

namespace ConsoleApplicationMatrix
{
    public class MyException : Exception
    {
        public MyException(string s) : base(s)
        { }
    }
    public class Matrix
    {
        int[,] m;
        //Свойство для работы с числом строк.
        public int I { get; }
        //Свойство для работы с числом столбцов.
        public int J { get; }
        //Конструктор.
        public Matrix(int i, int j)
        {
            if (i <= 0)
                throw new MyException($"недопустимое значение строки = { i }");
        if (j <= 0)
                throw new MyException($"недопустимое значение столбца= { j }");
        I = i;
            J = j;
            m = new int[i, j];
        }
        //Индексатор для доступа к значениям компонентов матрицы.
        public int this[int i, int j]
        {
            get
            {
                if (i < 0 | i > I - 1)
                    throw new MyException($"неверное значение i ={ i }");
            if (j < 0 | j > J - 1)
                throw new MyException($"неверное значение j = { j }");
            return m[i, j];
            }
            set
            {
                if (i < 0 | i > I - 1)
                    throw new MyException($"неверное значение i = { i }");
            if (j < 0 | j > J - 1)
                    throw new MyException($"неверное значение j = { 0 }");
            m[i, j] = value;
            }
        }
        //Сложение матриц.
        public static Matrix operator +(Matrix a, Matrix b)
        {
            Matrix c = new Matrix(a.I, a.J);
            for (int i = 0; i < a.I; i++)
                for (int j = 0; j < a.J; j++)
                {
                    c[i, j] = a.m[i, j] + b.m[i, j];
                }
            return c;
        }
        public static bool operator ==(Matrix a, Matrix b)
        {
            bool q = true;
            for (int i = 0; i < a.I; i++)
                for (int j = 0; j < a.J; j++)
                {
                    if (a[i, j] != b[i, j])
                    {
                        q = false; break;
                    }
                }
            return q;
        }
        public static bool operator !=(Matrix a, Matrix b)
        {

            return !(a == b);
        }

        public static Matrix operator -(Matrix a, Matrix b)
        {
            Matrix c = new Matrix(a.I, a.J);
            for (int i = 0; i < a.I; i++)
                for (int j = 0; j < a.J; j++)
                {
                    c[i, j] = a.m[i, j] - b.m[i, j];
                }
            return c;
        }
        public static Matrix operator *(Matrix a, Matrix b)
        {
            Matrix c = new Matrix(a.I, a.J);
            for (int i = 0; i < a.I; i++)
                for (int j = 0; j < a.J; j++)
                {
                    for (int k = 0; k < a.I; ++k)
                    {
                        c[i, j] += a.m[i, k] * b.m[k, j];
                    }
                }
            return c;
        }
        public Matrix Transp()
        {
            Matrix c = new Matrix(this.I, this.J);
            for (int i = 0; i < this.I; i++)
                for (int j = 0; j < this.J; j++)
                {
                    c[i, j] = this[j, i];
                }
            return c;
        }
        public int Min()
        {
            int ans = int.MaxValue;
            for (int i = 0; i < this.I; i++)
                for (int j = 0; j < this.J; j++)
                {
                    if (this[i, j] < ans)
                    {
                        ans = this[i, j];
                    }
                }
            return ans;
        }
        public string ToString()
        {
            string ans = "{ {";
            for (int i = 0; i < this.I; i++)
                for (int j = 0; j < this.J; j++)
                {
                    ans += this[i, j].ToString();
                    if (j != this.J - 1 || i!=this.I-1)
                    {
                        ans += ", ";
                    }
                }
            ans += "} }";
            return ans;
        }
        //Вывод значений компонентов на консоль.
        public void Show()
        {
            for (int i = 0; i < I; i++)
            {
                for (int j = 0; j < J; j++)
                {
                    Console.Write("\t" + this[i, j]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
        public override bool Equals(object obj)
        {
            return (this as Matrix) == (obj as Matrix);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Matrix a = new Matrix(3, 3);
                Matrix b = new Matrix(3, 3);
                Matrix c;
                for (int i = 0; i < a.I; i++)
                {
                    for (int j = 0; j < a.J; j++)
                    {
                        a[i, j] = a.J * i + j;
                    }
                }
                a.Show();
                for (int i = 0; i < a.I; i++)
                {
                    for (int j = 0; j < a.J; j++)
                    {
                        b[i, j] = a.J * i + j + 1;
                    }
                }
                b.Show();
                c = a + b;
                c.Show();
                c = a - b;
                c.Show();
                c = a * b;
                c.Show();
                int mn = c.Min();
                Console.WriteLine(mn);
                c = a.Transp();
                c.Show();
                string s = c.ToString();
                Console.WriteLine(s);
            }
            catch (MyException e)
            {
                Console.WriteLine(e.Message);
            }
            Console.ReadKey();
        }
    }
}
