#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "find_min_max.h"
#include "utils.h"

// Структура для передачи данных в поток
struct ThreadData {
    int *array;
    int start;
    int end;
    int min;
    int max;
};

// Функция для потока - ищет min/max в своей части массива
DWORD WINAPI FindMinMaxThread(LPVOID lpParam) {
    struct ThreadData *data = (struct ThreadData *)lpParam;
    data->min = 1000000;
    data->max = -1000000;
    
    for (int i = data->start; i < data->end; i++) {
        if (data->array[i] < data->min) data->min = data->array[i];
        if (data->array[i] > data->max) data->max = data->array[i];
    }
    
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Usage: %s <array_size> <threads_count> <by_files>\n", argv[0]);
        printf("  by_files: 0 - use memory, 1 - use files\n");
        return 1;
    }

    int array_size = atoi(argv[1]);
    int threads_count = atoi(argv[2]);
    int by_files = atoi(argv[3]);

    if (array_size <= 0 || threads_count <= 0) {
        printf("Error: array_size and threads_count must be positive\n");
        return 1;
    }

    // Генерируем массив
    int *array = GenerateArray(array_size);
    if (array == NULL) {
        printf("Error: memory allocation failed\n");
        return 1;
    }

    printf("Generated array (%d elements):\n", array_size);
    PrintArray(array, array_size);

    // Вычисляем размер части массива для каждого потока
    int chunk_size = array_size / threads_count;
    
    if (by_files) {
        // Использование файлов для синхронизации
        printf("Using files for synchronization\n");
        
        HANDLE threads[10];
        struct ThreadData thread_data[10];
        
        // Создаем потоки
        for (int i = 0; i < threads_count; i++) {
            thread_data[i].array = array;
            thread_data[i].start = i * chunk_size;
            thread_data[i].end = (i == threads_count - 1) ? array_size : thread_data[i].start + chunk_size;
            
            threads[i] = CreateThread(NULL, 0, FindMinMaxThread, &thread_data[i], 0, NULL);
            if (threads[i] == NULL) {
                printf("Error creating thread %d\n", i);
                return 1;
            }
        }
        
        // Ждем завершения всех потоков
        WaitForMultipleObjects(threads_count, threads, TRUE, INFINITE);
        
        // Закрываем handles потоков
        for (int i = 0; i < threads_count; i++) {
            CloseHandle(threads[i]);
        }
        
        // Записываем результаты в файлы
        for (int i = 0; i < threads_count; i++) {
            char filename[20];
            sprintf(filename, "result_%d.txt", i);
            FILE *file = fopen(filename, "w");
            if (file) {
                fprintf(file, "%d %d", thread_data[i].min, thread_data[i].max);
                fclose(file);
            }
        }
        
        // Собираем результаты из файлов
        int global_min = 1000000;
        int global_max = -1000000;
        
        for (int i = 0; i < threads_count; i++) {
            char filename[20];
            sprintf(filename, "result_%d.txt", i);
            FILE *file = fopen(filename, "r");
            if (file) {
                int local_min, local_max;
                fscanf(file, "%d %d", &local_min, &local_max);
                fclose(file);
                
                if (local_min < global_min) global_min = local_min;
                if (local_max > global_max) global_max = local_max;
                
                // Удаляем временный файл
                remove(filename);
            }
        }
        
        printf("Global Min: %d\n", global_min);
        printf("Global Max: %d\n", global_max);
        
    } else {
        // Использование общей памяти для синхронизации
        printf("Using memory for synchronization\n");
        
        HANDLE threads[10];
        struct ThreadData thread_data[10];
        
        // Создаем потоки
        for (int i = 0; i < threads_count; i++) {
            thread_data[i].array = array;
            thread_data[i].start = i * chunk_size;
            thread_data[i].end = (i == threads_count - 1) ? array_size : thread_data[i].start + chunk_size;
            
            threads[i] = CreateThread(NULL, 0, FindMinMaxThread, &thread_data[i], 0, NULL);
            if (threads[i] == NULL) {
                printf("Error creating thread %d\n", i);
                return 1;
            }
        }
        
        // Ждем завершения всех потоков
        WaitForMultipleObjects(threads_count, threads, TRUE, INFINITE);
        
        // Собираем результаты из памяти
        int global_min = 1000000;
        int global_max = -1000000;
        
        for (int i = 0; i < threads_count; i++) {
            if (thread_data[i].min < global_min) global_min = thread_data[i].min;
            if (thread_data[i].max > global_max) global_max = thread_data[i].max;
            
            CloseHandle(threads[i]);
        }
        
        printf("Global Min: %d\n", global_min);
        printf("Global Max: %d\n", global_max);
    }

    free(array);
    return 0;
}