using System;
using System.Collections.Generic;
using System.Text;

namespace shared
{
#if !STUB_PROJ
    internal partial class EntryPoint
    {
        static void Main(params string[] args)
        {
            var name = args[0];
            var patched = args.Length > 1 && args[1] == "--patched";
            try
            {
                var result = DoTest(name, patched);
                if (result.Passed)
                {
                    ReturnOk(result.ToString());
                }
                else
                {
                    ReturnError(result.ToString());
                }
            }
            catch (Exception e)
            {
                ReturnException(e.Message);
            }
        }

        private static void ReturnException(string message)
        {
            Console.WriteLine("EXCEPTION: " + message);
        }

        private static void ReturnOk(string message)
        {
            Console.WriteLine("OK: " + message);
        }

        private static void ReturnError(string message)
        {
            Console.WriteLine("ERROR: " + message);
        }
    }
#endif
}
