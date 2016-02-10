using System;
using System.Collections.Generic;
using System.Text;

namespace shared
{
#if !STUB_PROJ
    public struct TestResult
    {
        public readonly bool Passed;
        public readonly object Expected;
        public readonly object Actual;

        public TestResult(bool passed, object expected, object actual)
        {
            Passed = passed;
            Expected = expected;
            Actual = actual;
        }

        public override string ToString()
        {
            return string.Format(Passed ?
                "Expected value is {0}, actual is {1}" :
                "Expected value is {0} but actual is {1}", Expected, Actual);
        }
    }
#endif
}
