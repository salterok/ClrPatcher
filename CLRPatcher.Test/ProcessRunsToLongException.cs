using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CLRPatcher.Test
{
    public class ProcessRunsToLongException : Exception
    {
        public ProcessRunsToLongException(string message) 
            : base(message)
        {

        }
    }
}
