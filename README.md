# Intellector
## О проекте

### Основная идея

Интеллектор - настольная игра с гексагональным полем наподобие шахмат.

В интеллектор играют 2 игрока, за белых и чёрных соответственно. Каждый по очереди ходит своими фигурами. Цель - срубить вражескую фигуру "Интеллектор". 
В отличие от классических шахмат с квадратными клетками, в интеллекторе доска состоит из шестиугольных ячеек:

<p align="center">
<img src="/markdown/original_game.jpg?raw=true" alt="Поле интеллектора">
</p>

Подробнее узнать об игре, а также ознакомиться с правилами, вы можете на [официальном сайте игры](https://intellector.info)

### Проект

Данный проект - реализация Интеллектора в виде компьютерной игры.

Текущая версия проекта представляет собой консольное приложение, написанное на **ncurses**. 

<p align="center">
<img src="/markdown/screenshot_1.png?raw=true" alt="Скриншот игры" width="70%">
</p>

Программа работает в терминале и поддерживает только ввод с клавиатуры, засчёт чего не требует графической оболочки для использования.

Этот проект является учебным в рамках 1 курса программы ["Прикладная математика и информатика" Санкт-Петербургской Высшей Школы Экономики](https://spb.hse.ru/ba/appmath), 2019-2020 гг.


## Установка
### Зависимости

Операционная система: **OS Linux** или **MacOS**

Терминал, поддерживающий 256 цветов. Чтобы это проверить, введите
```
$ tput colors
```
Значение должно быть равно 256.

#### Библиотеки
##### Ubuntu, Debian, Linux Mint
- **ncurses**

    ```
    $ sudo apt install libncurses5-dev libncursesw5-dev
    ```

    При разработке данного приложения использовалась версия 6.1. Впрочем, более старые версии тоже должны работать.
- doctest

    Используется для тестирования
    ```
    $ sudo apt install doctest-dev
    ```

    Использовалась версия 2.3.7, но и более старые версии должны работать.
    
##### Другие операционные системы
Вы можете установить указанные зависимости из репозиториев для своей операционной системы.

Также вы можете скачать наиболее новые стабильные версии библиотек и собрать их из исходников:
- [**ncurses**](https://ftp.gnu.org/pub/gnu/ncurses) 
- [doctest](https://github.com/onqtam/doctest)

##### Примечание

Также для разработки программы используется [figlet](http://www.figlet.org/), позволяющий создавать ASCII картинки и баннеры. 

### Сборка

Для сборки запустите скрипт:
```
$ ./build.sh
```

---
### Использование

Для запуска после сборки:
```
$ ./start.sh
```

#### Перемещение по программе с помощью клавиатуры

Вы можете перемещаться по меню с помощью клавиш `w`, `s`, а также стрелок вверх `🠕` и вниз `🠗`. Выбор пункта меню происходит при нажатии на `пробел`.

На поле вы можете перемещать курсор с помощью клавиш `q`,`w`,`e`,`a`,`s`,`d` в соответствии с направлением грани шестиугольника:

<p align="center">
<img src="/markdown/arrows.png?raw=true" alt="Направления движения курсора">
</p>

Для выделения фигуры переместите на неё курсор и нажмите `пробел`

У фигуры подсветятся поля, доступные для хода. Вы можете переместить курсор на одно из них и снова нажать `пробел`, тогда фигура сходит на это поле. Вы также можете нажать нажать `пробел` на выделенной вами фигуре, тогда с неё снимется выделение. Другой способ снять выделение - нажать клавишу `c` (***c**lear* selection).

После того, как вы сходили, наступает ход противника. В зависимости от настроек, следующим ходит либо ваш оппонент, играющий с вами за одним компьютером по очереди, либо бот определенного уровня сложности.

В игре также поддерживается история ходов. Чтобы показать её, нажмите `h`, справа появится боковое меню истории с совершенными ходами. Чтобы скрыть его, также нажмите `h`. 

Чтобы отменить ход, нажмите `u`, чтобы обратно повторить его, нажмите `Shift-u`. 

В ситуации, когда вы дошли пешкой до последнего ряда поля, вы можете выбрать фигуру, в которую хотите превратиться. Это можно сделать с помощью клавиш `r` и `f`, пролистывая доступные фигуры, а затем выбрать нужную и сходить на `пробел`.

Чтобы выйти из игры и вернуться в главное меню, вы можете нажать `x` или `Esc` (в некоторых терминалах после нажатия `Esc` нужно нажать его ещё раз или подождать пару секунд).

Обратите внимание, что на данный момент игра работает только на английской раскладке клавиатуры. Следите за тем, нажат ли у вас `Caps Lock` - с ним игра работать также не будет.

#### Настройки

В игре есть ряд вкладка с рядом настроек:

- Настройка уровня сложности бота - от 1 до 6
- Настройка цветовой темы:
    * Classic
    * Dracula
    * Snow blue

## Авторы

* [https://github.com/23jura23](https://github.com/23jura23)

* [https://github.com/vsgol](https://github.com/vsgol)

* [https://github.com/cabpacob](https://github.com/cabpacob)
