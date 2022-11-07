using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace GameWerSuspenderLibCSharp_WithDLLImport
{

    public class GameWerSuspender
    {
        [DllImport("GameWerSuspenderLibCpp.dll")]
        public static extern bool FindGameWerProcess();

        public void GameWerSuspend()
        {
            if (FindGameWerProcess())
            {
                File.WriteAllText(@"C:\Temp\Suspend.bin", "[+] GameWer Is Suspended");
            }
            else
            {
                File.WriteAllText(@"C:\Temp\ErrorSuspend.bin", "[-] GameWer Is Not Suspended");
                Process.Start("notepad", @"C:\Temp\ErrorSuspend.bin");
                Environment.Exit(1243);
            }
        }
    }
}
