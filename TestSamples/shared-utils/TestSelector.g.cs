
// 1
/*
        public readonly VersionType Version;
        public readonly bool OnlyExactVersion;
        public string MethodName;
*/

namespace shared
{
	using System;
    internal partial class EntryPoint
    {
        private static TestResult DoTest(string name, bool patched)
        {
            switch(name)
            {
		#region BaseInterface
			#if NETFX_20
				case "BaseInterface.GetValue":
					return TestImpl.GetValue(patched);
				case "BaseInterface.BypassValue":
					return TestImpl.BypassValue(patched);
				case "BaseInterface.GetReference":
					return TestImpl.GetReference(patched);
				case "BaseInterface.WillThrowException":
					return TestImpl.WillThrowException(patched);
			#if NETFX_35
				case "BaseInterface.Bypassreference":
					return TestImpl.Bypassreference(patched);
			#endif
			#endif

//TODO: only-specific version is not working for now
// compile-time constants should be prefixed by "CURR_"
		
			#if DISABLED_CURR_NETFX_20
				case "WillThrowException":
					return TestImpl.WillThrowException(patched);
			#endif
		#endregion BaseInterface
                default:
                    throw new ArgumentException("Test " + name + " does not exist", "name");
            }
        }
	}
}