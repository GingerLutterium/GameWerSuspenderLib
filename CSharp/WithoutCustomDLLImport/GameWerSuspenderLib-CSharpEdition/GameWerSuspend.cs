using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace GameWerSuspenderLib_CSharpEdition
{
    public class GameWerSuspend
    {
        [DllImport("ntdll.dll", PreserveSig = false)]
        public static extern void NtSuspendProcess(IntPtr processHandle);
        private IntPtr GetHandleGameWerProcess()
        {
            IntPtr int_ptr = IntPtr.Zero;
            Process[] gamewer = Process.GetProcessesByName("Alkad.exe");
            foreach(Process proc in gamewer)
            {
                int_ptr = proc.Handle; //Handle Window :D
            }
            return int_ptr; //Returning Result of Handle Window :D
        }
        public bool SuspendGameWer()
        {
            Process[] process = Process.GetProcessesByName("Alkad.exe");
            if(process.Length == 1)
            {
                NtSuspendProcess(GetHandleGameWerProcess()); //Fully Suspending Alkad AntiCheat :D
                return true; //Fully Suspending of This AntiCheat :D
            }
            else
            {
                return false; //Returning If Alkad has not Suspended :D
            }
        }
    }
}
