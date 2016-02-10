using System;
using System.Collections.Generic;
using System.Text;

namespace shared
{
    public class BaseInterfaceDonorImpl : BaseInterface
    {
        public string Bypassreference(string reference)
        {
            return null;
        }

        public int BypassValue(int value)
        {
            return -value;
        }

        public string GetReference()
        {
            return "patched";
        }

        public int GetValue()
        {
            return 0;
        }

        public object WillThrowException()
        {
            throw new NotImplementedException();
        }
    }
}
