using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CLRPatcher.Test.SampleTests
{
    [TestClass]
    public class Console_40 : Console_35
    {
        public Console_40(string targetName) : base(targetName) { }

        public Console_40() : base("console_40.exe") { }
    }
}
