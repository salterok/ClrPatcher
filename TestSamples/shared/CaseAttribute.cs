using System;
using System.Collections.Generic;

namespace shared
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CaseAttribute : Attribute
    {
        public object MethodName;
        public readonly object OriginalValue;
        public readonly object PatchedValue;
        public readonly object Arg;
        public readonly bool ShouldThrowException;

        public CaseAttribute(object originalValue, object patchedValue, object arg = null)
        {
            OriginalValue = originalValue;
            PatchedValue = patchedValue;
            Arg = arg;
        }

        public CaseAttribute(bool throwException)
        {
            ShouldThrowException = throwException;
        }

        public static IEnumerable<CaseAttribute> GetTestCases()
        {
            var type = typeof(BaseInterface);
            var methods = type.GetMethods();
            foreach (var method in methods)
            {
                var cases = method.GetCustomAttributes(typeof(CaseAttribute), false);
                if (cases == null || cases.Length > 1)
                    continue;
                var @case = cases[0] as CaseAttribute;
                @case.MethodName = method.Name;
                yield return @case;
            }
        }
    }
}
