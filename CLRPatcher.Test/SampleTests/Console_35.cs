using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CLRPatcher.Test.SampleTests
{
    [TestClass]
    public class Console_35 : Console_20
    {
        public Console_35(string targetName) : base(targetName) { }

        public Console_35() : base("console_35.exe") { }
    }
}
