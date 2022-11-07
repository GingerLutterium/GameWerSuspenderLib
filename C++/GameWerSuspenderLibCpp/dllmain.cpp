// dllmain.cpp : Defines the entry point for the DLL application.
#pragma warning (disable : 6387)
#pragma warning (disable : 6001)
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <usb.h>
#include <TlHelp32.h> //For Finding Proc ID :D
#define export_dll __declspec(dllexport)

DWORD FindProcessId(const std::wstring& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}
void suspend(DWORD processId)
{
    HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    THREADENTRY32 threadEntry;
    threadEntry.dwSize = sizeof(THREADENTRY32);

    Thread32First(hThreadSnapshot, &threadEntry);

    do
    {
        if (threadEntry.th32OwnerProcessID == processId)
        {
            HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE,
                threadEntry.th32ThreadID);

            SuspendThread(hThread);
            CloseHandle(hThread);
        }
    } while (Thread32Next(hThreadSnapshot, &threadEntry));

    CloseHandle(hThreadSnapshot);

}
    

EXTERN_C{
    export_dll bool FindGameWerProcess() 
    {
            DWORD alkad = FindProcessId(L"Alkad.exe"); //Alkad AntiCheat :D
            if (!alkad) //If Alkad Has not Founded by Finding Process ID... Exiting With Code 123 :D 
            {
                MessageBoxA(0, "Alkad Has Not Founded", "GameWerSuspenderLib", 0);
                ExitProcess(123);
                return false;
            }
            else 
            {
                suspend(alkad);
                MessageBoxA(0, "GameWer is Successfull Suspended", "GameWerSuspenderLib", 0);
                return true;
            }
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(0, "Welcome to Party :D", "GameWerSuspenderLibCpp", 0); //MessageBox Attach :D
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

