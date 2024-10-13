# Rasterizer

## Сборка и запуск

`make && make run`

## Генерация compile_commands.json

Этот файл нужен для корректной работы LSP,
чтобы Language Server видел хедер `windows.h`.
Для этого нужно выполнить команду `bear -- make`.
