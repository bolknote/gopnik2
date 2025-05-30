ОБ ИГРЕ
=======
«Гопник-2» - это продолжение культовой текстовой игры «Гопник», жанр которой
наиболее близок к жанру Hack and Slash RPG. Во второй части полностью сохранена
изначальная концепция, улучшен алгоритм генерирования противников в
соответствии с текущим состоянием главного героя, выровнен баланс прохождения
и прокачки, добавлено три уровня сложности.

АВТОРЫ
======
Автор оригинальной версии игры «Гопник 2»  — d-maxx\
Портированная бета-версия под Linux       — @tiandrey\
Дальнейшее портирование и развитие         — @bolknote

СБОРКА И ЗАПУСК
=========

## Зависимости

- `cmake` >= 3.14
- `gcc`, `clang` или `MSVC`

## Этапы сборки

- `mkdir -p ~/.builds/gopnik2`
- `cmake -B ~/.builds/gopnik2 -DCMAKE_BUILD_TYPE=Release`
- `cd ~/.builds/gopnik2 && cmake --build . -- -j 10`

## Запуск тестов
- `cd ~/.builds/gopnik2 && ctest --extra-verbose`

## Запуск

`~/.builds/gopnik2/gop2`

ЛИЦЕНЗИЯ
========

Лицензия на код в исходном состоянии мне неизвестна, прошу авторов этого кода
связаться со мной (например, написать мне на почту: `imbolk@gmail.com`).

Лицензия на остальные правки (включая вклад @tiandrey) — MIT.
```text
                                      ▄▄
                                  ▄▄▀▀▀▀▀▀▄▄▄
                                ██           ▀▀▀▄▄
                              ██                  ▀▄
                            ▄▀                      ▀▄
                          ▄█         ▄▄▀▀▀▀▀▀▀▄▄▄▄   █
                        ▄█       ▄▄▀▀  ▀▀▀▄▄      █ █
                        ▀█▄    ▄▀           ▀▀▄  ▄▀█
                           ▀▀▄▀                ▀█▀
                             █  ▄▀▀▄▄   ▄▄▀▀▀▄    █
                             █   ▄▄▄      ▄▄▄ ▀   █
                             █  ▀▓▓▓█    █▓▓▓▀    █
                             █   ▀▀▀      ▀▀▀    █
                              █       ▓▓         █
                               █     █▓▓█        █
                               █     █▓▓█        █
                               █    █▒▒▒▒█      █
                               █   ▀▄▄  ▄▄▀     █
                               █                █
                                █               █
                                 █  ▄▀▀▀▄▄     ▄▀
                                  █ ▀▄▄▒▒     █
                                   █    ▒▒  ▄▀
                                    █    ▓▓█
                                     ▀▀▀▀ ▓▓
                                           ▓▓
                                            ▓▓
                                             ▓▓
                                                     ██
                                                    █  █
                      ███ ████ ████ █  █ █  █ █  █      █
                      █   █  █ █  █ █  █ █  █ █ █      █
                      █   █  █ █  █ ████ █ ██ ██  ██  █
                      █   █  █ █  █ █  █ ██ █ █ █    █
                      █   ████ █  █ █  █ █  █ █  █  █
                                                    ████
                           ███ ОКОРЕНИЕ
                           █ █
                           █ █    █ █ УЛЬТУРНОЙ
                                  ██
                                  █ █     ██ ТОЛИЦЫ
                                          █
                                          ██

                             version 1.29 Release
```
