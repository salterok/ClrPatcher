using System;
using System.Collections.Generic;
using System.Text;

namespace shared
{
    [AttributeUsage(AttributeTargets.Interface | AttributeTargets.Method, AllowMultiple = true)]
    public class TestTarget : Attribute
    {
        public readonly VersionType Version;
        public readonly bool OnlyExactVersion;
        public readonly string ImplTarget;
        public string MethodName;

        public TestTarget(VersionType version, bool onlyExact = false)
        {
            Version = version;
            OnlyExactVersion = onlyExact;
        }

        public TestTarget(string implTarget)
        {
            ImplTarget = implTarget;
        }
    }

    public enum VersionType
    {
        NETFX_20,
        NETFX_30,
        NETFX_35,
        NETFX_40,
        NETFX_45,
        NETFX_46,
    }
}
