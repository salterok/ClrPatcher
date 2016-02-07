using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace Runner
{
    class Program
    {
        private const string COR_PROFILER = "{38A7EA35-B221-425a-AD07-D058C581611D}";
        private const int COR_ENABLE_PROFILING = 1;
        private const string EXECUTABLE_TO_RUN = "Victim.exe";
        


        static void Main(string[] args)
        {

            var startInfo = new ProcessStartInfo(EXECUTABLE_TO_RUN)
            {
                UseShellExecute = false
            };
            startInfo.EnvironmentVariables.Add(nameof(COR_ENABLE_PROFILING), COR_ENABLE_PROFILING.ToString());
            startInfo.EnvironmentVariables.Add(nameof(COR_PROFILER), COR_PROFILER);

            var process = new Process()
            {
                StartInfo = startInfo
            };
            process.Start();

            process.WaitForExit();
            Console.WriteLine("Done");
        }
    }
}
