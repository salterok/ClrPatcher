using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CLRPatcher.Test
{
    public class BaseSamplesTest
    {
        
        public string TargetName;
        protected ProcessOutputGetter pog;

        public BaseSamplesTest(string targetName)
        {
            if (targetName == null)
            {
                throw new ArgumentNullException("Pass valid target name", nameof(TargetName));
            }
            TargetName = targetName;
        }

        protected void HandleResult(SampleTestResult result)
        {
            if (!result.IsSuccess)
            {
                Trace.TraceError(result.Message);
            }
            Assert.AreEqual(SampleTestResultStatus.Ok, result.Status);   
        }

        [TestInitialize]
        public void Initialize()
        {
            pog = new ProcessOutputGetter(TargetName);
        }
    }
}
