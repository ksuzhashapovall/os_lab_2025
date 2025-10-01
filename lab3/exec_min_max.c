#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <array_size> <processes_count>\n", argv[0]);
        return 1;
    }

    int array_size = atoi(argv[1]);
    int processes_count = atoi(argv[2]);

    if (array_size <= 0 || processes_count <= 0) {
        printf("Error: array_size and processes_count must be positive\n");
        return 1;
    }

    printf("Parent process: Starting sequential_min_max with array_size=%d, processes_count=%d\n", 
           array_size, processes_count);

    // Подготавливаем командную строку для дочернего процесса
    char command_line[100];
    sprintf(command_line, "find_min_max\\sequential_min_max.exe %d %d", array_size, processes_count);

    // Создаем структуру для процесса
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Создаем дочерний процесс
    if (!CreateProcess(
        NULL,           // Имя исполняемого файла (используется command_line)
        command_line,   // Командная строка
        NULL,           // Атрибуты безопасности процесса
        NULL,           // Атрибуты безопасности потока
        FALSE,          // Наследование handles
        0,              // Флаги создания
        NULL,           // Окружение
        NULL,           // Текущая директория
        &si,            // STARTUPINFO
        &pi             // PROCESS_INFORMATION
    )) {
        printf("Error: CreateProcess failed (%d)\n", GetLastError());
        return 1;
    }

    printf("Parent process: Child process created with PID %d\n", pi.dwProcessId);

    // Ждем завершения дочернего процесса
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Закрываем handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printf("Parent process: Child process completed\n");

    return 0;
}