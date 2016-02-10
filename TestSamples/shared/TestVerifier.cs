using System;
using System.Collections.Generic;
using System.Text;

namespace shared
{
#if !STUB_PROJ
    public static class TestVerifier
    {
        public static TestResult Verify<T>(T expected, T actual)
        {
            bool passed;
            if (expected == null && actual == null)
            {
                passed = true;
            }
            else if (expected == null || actual == null)
            {
                passed = false;
            }
            else
            {
                passed = expected.Equals(actual);
            }
            return new TestResult(passed, expected, actual);
        }
    }
#endif
}
