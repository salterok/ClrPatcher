using System;
using System.Collections.Generic;
using System.Text;

namespace shared
{
    public class BaseInterfaceImpl : BaseInterface
    {
        public string Bypassreference(string reference)
        {
            return reference;
        }

        public int BypassValue(int value)
        {
            return value;
        }

        public string GetReference()
        {
            return "original";
        }

        public int GetValue()
        {
            return 1;
        }

        public object WillThrowException()
        {
            return null;
        }
    }
}
