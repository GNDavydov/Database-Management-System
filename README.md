# sem-2-alg-lang-homework-1
##Домашнее задание №1 по алгоритмическим языкам
###_СУБД_
**Задание**:
1. Реализовать абстрактный класс, содержащий чистые виртуальные функции,
   функционал которых различается для наследников, в соответствии с вариантом и
   заданной им организацией данных (группировкой).
2. Реализовать разбор текстовых команд, введённых с клавиатуры.
3. Разработать формат сохранения БД в файл.
4. Реализовать функции в соответствии с вариантом.
5. Реализовать управление базами данных через интерфейс СУБД:
    + Создание однотипных БД и гибридных БД.
    + Вывод на экран* списка существующих БД.
    + Удаление* БД.
    + Переименование* БД.
    + Открытие** БД.
    + Сохранение** БД.
    + Добавление записей в БД.
    + Редактирование записей в БД.
    + Удаление записей в БД.
    + Вывод на экран записей БД.
    + Сортировка записей БД.
    + Выборка записей БД по правилу (значению поля).
    + Сохранение** выборки как новой БД.

**Справка**. Использовать известные приёмы и технологии: типы и алгоритмы STL,
многофайловые программы, полиморфизм, исключения.

*Реализовать, используя Filesystem library.
  
**Работа с текстовыми файлами.

###Вариант №5
БД – совокупность студентов (вуз). Класс 1 – студенты, обучающиеся по общему учебному плану, класс 2 –
студенты, обучающиеся по индивидуальному учебному плану. Каждый студент имеет ФИО, кафедру, семестр
обучения. У студентов, обучающихся по общему учебному плану, дисциплины сгруппированы по семестрам,
по каждой дисциплине есть оценка. У студентов, обучающихся по индивидуальному учебному плану,
дисциплины не сгруппированы по семестрам, по каждой дисциплине есть оценка.

**Функции (п. 4):**
* Подсчёт среднего балла для студента: по дисциплинам последнего семестра для обучающихся по
  общему учебному плану, по всем дисциплинам для обучающихся по индивидуальному учебному
  плану.
* Поиск студента внутри БД по ФИО.

**Правила сортировки записей БД (п. 5.11):**
* По ФИО студента (по алфавиту).
* По номеру семестра.

**Правила выборки записей из БД (п. 5.12):**
* Студенты n семестра (n задаётся с клавиатуры).
* Студенты, изучавшие дисциплину name (name задаётся с клавиатуры).

// Copyright 2021 GNDavydov