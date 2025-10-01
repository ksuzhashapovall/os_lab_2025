# Компилятор и флаги
CC = cl
CFLAGS = /nologo /W3
LDFLAGS = /nologo

# Папки
SRC_DIR = .
FIND_MIN_MAX_DIR = find_min_max
PARALLEL_MIN_MAX_DIR = parallel_min_max

# Цели (targets)
all: sequential parallel exec

# Сборка последовательной версии
sequential:
	cd $(FIND_MIN_MAX_DIR) && \
	$(CC) $(CFLAGS) /c find_min_max.c && \
	$(CC) $(CFLAGS) /c utils.c && \
	$(CC) $(CFLAGS) /c sequential_min_max.c && \
	$(CC) $(LDFLAGS) sequential_min_max.obj find_min_max.obj utils.obj /Fesequential_min_max.exe

# Сборка параллельной версии
parallel:
	cd $(PARALLEL_MIN_MAX_DIR) && \
	$(CC) $(CFLAGS) /c find_min_max.c && \
	$(CC) $(CFLAGS) /c utils.c && \
	$(CC) $(CFLAGS) /c parallel_min_max.c && \
	$(CC) $(LDFLAGS) parallel_min_max.obj find_min_max.obj utils.obj /Feparallel_min_max.exe

# Сборка программы с CreateProcess (для задания 4)
exec:
	$(CC) $(CFLAGS) /c exec_min_max.c
	$(CC) $(LDFLAGS) exec_min_max.obj /Feexec_min_max.exe

# Очистка бинарных файлов
clean:
	cd $(FIND_MIN_MAX_DIR) && del *.obj *.exe 2>nul
	cd $(PARALLEL_MIN_MAX_DIR) && del *.obj *.exe 2>nul
	del *.obj *.exe 2>nul

# Тестирование последовательной версии
test_sequential: sequential
	cd $(FIND_MIN_MAX_DIR) && sequential_min_max.exe 10 1

# Тестирование параллельной версии
test_parallel: parallel
	cd $(PARALLEL_MIN_MAX_DIR) && parallel_min_max.exe 10 2 0
	cd $(PARALLEL_MIN_MAX_DIR) && parallel_min_max.exe 10 2 1

# Тестирование exec программы
test_exec: exec
	exec_min_max.exe 10 1

# Тестирование всех программ
test_all: test_sequential test_parallel test_exec

# Показать помощь
help:
	@echo "Доступные цели:"
	@echo "  all           - собрать все программы"
	@echo "  sequential    - собрать последовательную версию"
	@echo "  parallel      - собрать параллельную версию"
	@echo "  exec          - собрать программу с CreateProcess"
	@echo "  clean         - удалить все бинарные файлы"
	@echo "  test_sequential - протестировать последовательную версию"
	@echo "  test_parallel - протестировать параллельную версию"
	@echo "  test_exec     - протестировать программу с CreateProcess"
	@echo "  test_all      - протестировать все программы"
	@echo "  help          - показать эту справку"

.PHONY: all sequential parallel exec clean test_sequential test_parallel test_exec test_all help