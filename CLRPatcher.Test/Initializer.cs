using CLRPatcher.Test.Properties;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CLRPatcher.Test
{
    [TestClass]
    public class Initializer
    {

        [AssemblyInitialize]
        public static void Initialize(TestContext context)
        {
#if DEBUG
            var workingDir = Path.Combine(Environment.CurrentDirectory, Settings.Default.SampleRelativePath, "Debug");

#elif RELEASE
            var workingDir = Path.Combine(Environment.CurrentDirectory, Settings.Default.SampleRelativePath, "Release");
#endif
            Environment.CurrentDirectory = workingDir;
        }
    }
}
