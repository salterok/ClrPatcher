using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Linq;
using System.Collections.Generic;

namespace CLRPatcher.Test.SampleTests
{
    [TestClass]
    public class Console_20 : BaseSamplesTest
    {
        public Console_20() : base("console_20.exe") { }

        [TestMethod]
        public void BasicInterface_GetValue()
        {
            var result = pog.RunTest("BaseInterface.GetValue");
            HandleResult(result);
        }

        [TestMethod]
        public void BasicInterface_GetValue_Patched()
        {
            var result = pog.RunPatchedTest("BaseInterface.GetValue");
            HandleResult(result);
        }

        [TestMethod]
        void BasicInterface_BypassValue()
        {

        }

        [TestMethod]
        void BasicInterface_BypassValue_Patched()
        {

        }

        [TestMethod]
        void BasicInterface_GetReference()
        {

        }

        [TestMethod]
        void BasicInterface_GetReference_Patched()
        {

        }

        [TestMethod]
        void BasicInterface_Bypassreference()
        {

        }

        [TestMethod]
        void BasicInterface_Bypassreference_Patched()
        {

        }

        [TestMethod]
        void BasicInterface_WillThrowException()
        {

        }

        [TestMethod]
        void BasicInterface_WillThrowException_Patched()
        {

        }


    }
}
