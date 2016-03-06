using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace CLRPatcher.Test
{
    public struct SampleTestResult
    {
        private const string Pattern = @"^(?<status>(?:OK)|(?:ERROR)|(?:EXCEPTION)): (?<message>.+)";
        private static Regex m_resultMatcher = new Regex(Pattern,
    RegexOptions.Compiled | RegexOptions.Multiline | RegexOptions.IgnoreCase);


        public SampleTestResultStatus Status;
        public string Message;

        public bool IsSuccess { get { return Status == SampleTestResultStatus.Ok; } }

        public static SampleTestResult? TryCreateFromString(string input)
        {
            var match = m_resultMatcher.Match(input);
            if (!match.Success)
            {
                return null;
            }
            var result = new SampleTestResult();
            var status = match.Groups["status"].Value;
            switch (status)
            {
                case "OK":
                    result.Status = SampleTestResultStatus.Ok;
                    break;
                case "ERROR":
                    result.Status = SampleTestResultStatus.Error;
                    break;
                case "EXCEPTION":
                    result.Status = SampleTestResultStatus.Exception;
                    break;
                default:
                    throw new ArgumentException($"Regular matcher return unexpected status group {status}");
            }
            result.Message = match.Groups["message"].Value;
            return result;
        }
    }

    public enum SampleTestResultStatus
    {
        Ok,
        Error,
        Exception
    }
}
