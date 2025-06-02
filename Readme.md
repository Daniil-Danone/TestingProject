# Testing Project


## Требования

- CMake 3.30 или выше

Создание билда
```bash
cmake -S . -B build 
cmake --build build
```

Запуск варианта 10
```shell
./build/Debug/variant10 имя_файла_для_результатов.txt
```

Запуск варианта 11
```shell
./build/Debug/variant11 имя_файла_для_результатов.txt
```

Запуск генерации тестовых данных
```shell
.\build\Debug\generate_test_files.exe
```