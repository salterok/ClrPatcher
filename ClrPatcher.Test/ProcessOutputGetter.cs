using CLRPatcher.Test.Properties;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CLRPatcher.Test
{
    public class ProcessOutputGetter
    {
        public const int WaitForExit = 200;
        public readonly string TargetName;

        public ProcessOutputGetter(string targetName)
        {
            TargetName = targetName;
        }

        public SampleTestResult RunTest(string testName, int customTimeLimit = WaitForExit)
        {
            return Run(testName, null, customTimeLimit);
        }

        public SampleTestResult RunPatchedTest(string testName, string command, int customTimeLimit = WaitForExit)
        {
            return Run(testName, command, customTimeLimit);
        }

        private SampleTestResult Run(string testName, string command, int customTimeLimit = WaitForExit)
        {
            try
            {
                var result = RunForResult(testName, command, customTimeLimit);
                var testResult = SampleTestResult.TryCreateFromString(result);
                if (testResult.HasValue)
                {
                    return testResult.Value;
                }
                else
                {
                    return new SampleTestResult()
                    {
                        Status = SampleTestResultStatus.Exception,
                        Message = "Test return unexpected result: " + result
                    };
                }
            }
            catch (ProcessRunsToLongException ex)
            {
                return new SampleTestResult()
                {
                    Status = SampleTestResultStatus.Exception,
                    Message = ex.Message
                };
            }
        }

        private string RunForResult(string testName, string command, int customTimeLimit)
        {
            var args = command == null ? testName : $"{testName} --patched";
            var processStartInfo = new ProcessStartInfo(TargetName, args);
            processStartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            processStartInfo.CreateNoWindow = true;
            processStartInfo.UseShellExecute = false;
            processStartInfo.RedirectStandardOutput = true;
            if (command != null)
            {
                processStartInfo.EnvironmentVariables.Add("COR_ENABLE_PROFILING", "1");
                processStartInfo.EnvironmentVariables.Add("COR_PROFILER", Settings.Default.PatcherGUID);
                processStartInfo.EnvironmentVariables.Add("PATCHER_COMMAND", command);

            }
            using (var process = new Process())
            {
                process.StartInfo = processStartInfo;
                process.Start();

                var result = process.StandardOutput.ReadToEnd();
                // FIX: make limiting time work, by now it is not.
                process.WaitForExit(customTimeLimit);
                if (!process.HasExited)
                {
                    process.Kill();
                    throw new ProcessRunsToLongException($"Process exceed {customTimeLimit}ms to run");
                }

                return result;
            }
        }
    }
}
