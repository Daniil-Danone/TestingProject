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
.\build\Debug\variant10_analyzer.exe
```

Запуск варианта 11
```shell
.\build\Debug\variant11_derivative.exe
```

Запуск генерации тестовых данных
```shell
.\build\Debug\test_generator.exe
```