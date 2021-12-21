#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
BOOL GetProcesses()
{
    HANDLE hProcess;
    DWORD dwPriorityClass; //unsigned int
    HANDLE hProcSnap;
    PROCESSENTRY32 processEntry;
    hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcSnap == INVALID_HANDLE_VALUE) {
        return FALSE;
    }
    processEntry.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcSnap, &processEntry))
    {
        CloseHandle(hProcSnap);
        return(FALSE);
    }

    do {
        wprintf(TEXT("\nPROCESS NAME:  %s"), processEntry.szExeFile);

        dwPriorityClass = 0;
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry.th32ProcessID);
        dwPriorityClass = GetPriorityClass(hProcess);
        CloseHandle(hProcess);


        wprintf(TEXT("\n  PID        = 0x%08X"), processEntry.th32ProcessID);
        wprintf(TEXT("\n  Parent PID = 0x%08X"), processEntry.th32ParentProcessID);
        wprintf(TEXT("\n  Priority     = %d"), processEntry.pcPriClassBase);
        wprintf(TEXT("\n  Thread count      = %d"), processEntry.cntThreads);
        PrintProcessThreads(processEntry.th32ProcessID);

        PrintProcessModules(processEntry.th32ProcessID);

    } while (Process32Next(hProcSnap, &processEntry));

    CloseHandle(hProcSnap);
    return TRUE;
}

BOOL PrintProcessModules(DWORD CONST dwProcessId)
{
    MODULEENTRY32 moduleEntry;
    HANDLE CONST hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
    if (INVALID_HANDLE_VALUE == hModuleSnap) {
        return FALSE;
    }

    moduleEntry.dwSize = sizeof(MODULEENTRY32);
    if (!Module32First(hModuleSnap, &moduleEntry))
    {
        CloseHandle(hModuleSnap);
        return(FALSE);
    }
    do {
        wprintf(TEXT("\n\n     MODULE NAME:     %s"), moduleEntry.szModule);
        wprintf(TEXT("\n     Path     = %s"), moduleEntry.szExePath);
        wprintf(TEXT("\n     Process ID     = 0x%08X"), moduleEntry.th32ProcessID);
        wprintf(TEXT("\n     Base size      = %d"), moduleEntry.modBaseSize);
    } while (Module32Next(hModuleSnap, &moduleEntry));

    CloseHandle(hModuleSnap);
    return TRUE;
}

BOOL PrintProcessThreads(DWORD CONST dwProcessId)
{
    THREADENTRY32 threadEntry;
    HANDLE CONST hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwProcessId);
    if (INVALID_HANDLE_VALUE == hThreadSnap) {
        return FALSE;
    }

    threadEntry.dwSize = sizeof(THREADENTRY32);
    if (!Thread32First(hThreadSnap, &threadEntry))
    {
        CloseHandle(hThreadSnap);
        return(FALSE);
    }
    do {
        if (threadEntry.th32OwnerProcessID == dwProcessId)
        {
            wprintf(TEXT("\n\n     THREAD ID      = 0x%08X"), threadEntry.th32ThreadID);
            wprintf(TEXT("\n     Base priority  = %d"), threadEntry.tpBasePri);
            wprintf(TEXT("\n     Delta priority = %d"), threadEntry.tpDeltaPri);
            wprintf(TEXT("\n"));
        }
    } while (Thread32Next(hThreadSnap, &threadEntry));

    CloseHandle(hThreadSnap);
    return TRUE;
}

INT main() {

    GetProcesses();
    return 0;
}