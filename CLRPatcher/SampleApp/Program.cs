// ==++==
// 
//   Copyright (c) Microsoft Corporation.  All rights reserved.
// 
// ==--==

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace SampleApp
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("DOING THINGS");
			Console.WriteLine("------------");


            ConsoleKeyInfo key;
            do
            {
                Do();
                Console.Write(Environment.NewLine + "ARE YOU THERE? PRESS SOMETHING:");
                key = Console.ReadKey(true);
                Console.WriteLine();
            }	
            while (key.Key != ConsoleKey.Escape);
		}

		static void Do()
		{
			Thread.Sleep(2000);

            var objToReplace = new Test1();
            objToReplace.foo();
        }
	}

    interface G
    {
        void foo();
    }

    class Test1 : G
    {
        private int value = 1;
        protected int value2 = 10;
        public virtual void foo()
        {
            Console.WriteLine("Test1 method = " + value);
        }
    }

    class Test2 : G
    {
        private int value = 2;
        public void foo()
        {
            Console.WriteLine("Test2 method = " + value);
        }
    }

    class Test3 : Test1
    {
        private int value = 3;
        public override void foo()
        {
            Console.WriteLine("Test3 method = " + value2);
        }
    }

    class Test4 : Test1
    {
        public new void foo()
        {
            Console.WriteLine("Test4 method");
        }
    }

    class One
	{
		private int i1, i2;
		private char c1, c2;

		public One(int i, char c)
		{
			i1 = i2 = i;
			c1 = c2 = (char) ('a' - char.ToLower(c));

			one(i1);
		}

		private int one(int a)
		{
			int t = 0;
			for (int i = 0; i < a && i < i1 && i2 > 0; i++)
				t += two(i2--);

			return t;
		}

		private int two(int t)
		{
			Console.Write((char) ('a' + c2++));

			if (t <= 0 || i2 <= 0)
				return (int) c2;

			if (t % 2 == 0)
				return two(i2-- - 1);

			return jaz(i2 - 1);
		}

		private int jaz(int t)
		{
			Console.Write((char) ('z' - c2--));

			return t % 7;
		}

		public int lul(int t)
		{
			Console.Write((char) t);
			return t;
		}
	}

	class Two
	{
		static char c = 'a';

		public Two()
		{
			one(); two(); jaz(); lul();

			Random r = new Random();
			new One(r.Next(9), (char) ('a' + r.Next(26))).lul(r.Next(100));
		}

		private void one()
		{
			two();
			Thread.Sleep(2);
			jaz();
			Thread.Sleep(10);
			lul();
		}

		private void two()
		{
			jaz();
			Thread.Sleep(7);
			lul();
		}

		private void jaz()
		{
			lul();
		}

		private void lul()
		{
			Thread.Sleep(3);

			Console.Write(c++);

			if ((int) c >= 100)
				c = (char) 10;

			Random r = new Random();
			new One(r.Next(9), (char) ('a' + r.Next(26))).lul(r.Next(100));
		}
	}
}
