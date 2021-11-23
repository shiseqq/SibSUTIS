using System;

namespace lab2
{
    public class Lab2
    {
        public static void func1(ref int a,ref int b)
        {
            if (a < b)
            {
                int tmp = a;
                a = b;
                b = tmp;}
        }

        public static double func2(double[,] a)
        {
            double ans = 1;
            bool f = false;
            int rows = a.GetUpperBound(0) + 1;
            int columns = a.Length / rows;
            for (int i = 0; 
                i < rows; 
                ++i)
            {for (int j = 0; 
                    j < columns;
                    ++j)
                {if (a[i,j] % 2 == 0)
                        {f = true;
                         ans *= a[i,j];}
                }
            }
            if (f)
                return ans;
            else return -1;
        }
        public static double func3(double[,] a)
        {
            double ans = 0;
            bool f = false;
            int rows = a.GetUpperBound(0) + 1;
            int columns = a.Length / rows;
            for (int i = 0;
                i < rows;
                ++i)
            {for (int j=0;
                    j<columns;
                    ++j)
                {if (a[i,j]%2==0 && i+j<columns)
                    {f = true;
                        ans += a[i, j];
                    }
                }
            }
            if (f)
                return ans;
            else return -1;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            int a = 2;
            int b = 5;
            //Lab2.func1(ref a, ref b);
            double[,] arr = { { 1, 2, 3}, { 4, 5, 6 }, { 7, 8, 9 },{ 10, 11, 12 } };

            //Console.WriteLine(a);
            //Console.WriteLine(b);

            //Console.WriteLine(Lab2.func2(arr));

            Console.WriteLine(Lab2.func3(arr));

            Console.ReadKey();
        }
    }
}
