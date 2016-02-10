using shared;
using System;
using System.Collections.Generic;
using System.Text;

namespace shared
{
#if !STUB_PROJ
    static class TestImpl
    {
        public static TestResult GetValue(bool patched)
        {
            var impl = new BaseInterfaceImpl();
            return TestVerifier.Verify(patched ? 0 : 1, impl.GetValue());
        }

        public static TestResult BypassValue(bool patched)
        {
            throw new NotImplementedException();
        }

        public static TestResult GetReference(bool patched)
        {
            throw new NotImplementedException();
        }

        public static TestResult Bypassreference(bool patched)
        {
            throw new NotImplementedException();
        }

        public static TestResult WillThrowException(bool patched)
        {
            throw new NotImplementedException();
        }

    }
#endif
}
