using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CLRPatcher.Test.SampleTests
{
    [TestClass]
    public class Console_45 : Console_40
    {
        public Console_45(string targetName) : base(targetName) { }

        public Console_45() : base("console_45.exe") { }
    }
}
