## Домашнее задание №4

Создать библиотеку с именем shmem.
В библиотеке должен быть реализован класс словаря Map, состояние которого разделяется между форками.
Словарь должен поддерживать POD типы и std::string в качестве ключа и значения.
Словарь должен быть реализован на std::map с собственным аллокатором памяти.
Должны быть реализованы методы вставки, удаления, изменения и получения элемента.
Библиотека должна гарантировать базовую безопасность исключений.

![Task](deps/diag.jpeg)