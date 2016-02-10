using System;
using System.Collections.Generic;
using System.Text;

namespace shared
{
    public interface EmptyInterface { }

    public interface EmptyInterface<T> { }

    public interface EmptyGenericInterface : EmptyInterface<int> { }

    public class EmptyGenericClass<T> : EmptyInterface<T> { }

    [TestTarget("TestImpl")]
    public interface BaseInterface
    {
        [TestTarget(VersionType.NETFX_20)]
        int GetValue();
        [TestTarget(VersionType.NETFX_20)]
        int BypassValue(int value);

        [TestTarget(VersionType.NETFX_20)]
        string GetReference();
        [TestTarget(VersionType.NETFX_35)]
        string Bypassreference(string reference);

        [TestTarget(VersionType.NETFX_20, true)]
        [TestTarget(VersionType.NETFX_20)]
        object WillThrowException();

    }
}
