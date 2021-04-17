// Copyright 2021 GNDavydov

#include "interpreter.h"

void help() {
    setlocale(LC_ALL, "Russian");
    std::cout.fixed;
    std::cout << "------------------------------------------------------------------------------------" << '\n';
    std::cout << "----Доступные функции:--------------------------------------------------------------" << '\n';
    std::cout << "----Печать доступных предметов - PRINT_DIS------------------------------------------" << '\n';
    std::cout << "----Создание БД - CREATE_DB <TYPE DB> <NAME DB>-------------------------------------" << '\n';
    std::cout << "----Вывод на экран списка БД - PRINT_DB <TYPE DB>-----------------------------------" << '\n';
    std::cout << "----Удаление БД - DELETE_DB <TYPE DB> <NAME>----------------------------------------" << '\n';
    std::cout << "----Переименование БД - RENAME <TYPE DB> <NAME> <NEW NAME>--------------------------" << '\n';
    std::cout << "----Открытие БД - OPEN <TYPE DB> <NAME>---------------------------------------------" << '\n';
    std::cout << "----Закрытие БД - CLOSE ------------------------------------------------------------" << '\n';
    std::cout << "----Добавление записи в БД - INSERT <VARIABLE> (for Hybrid)-------------------------" << '\n';
    std::cout << "----Редактирование записи в БД - UPDATE_SET <VARIABLE> WHERE <NAME>-----------------" << '\n';
    std::cout << "----Удаление записи в БД - DELETE_WHERE <NAME>--------------------------------------" << '\n';
    std::cout << "----Вывод на экран записей БД - PRINT_RECORDS --------------------------------------" << '\n';
    std::cout << "----Сортировка записей БД - SORT <PARAM> <COMPARISON>-------------------------------" << '\n';
    std::cout << "----Сохранение выборки как новый БД - SELECT_AND_SAVE <PARAM> in <NEW NAME>---------" << '\n';
    std::cout << "----Завершение работы - QUIT--------------------------------------------------------" << '\n';
    std::cout << "------------------------------------------------------------------------------------" << '\n';
    std::cout << "----Доступные параметры:------------------------------------------------------------" << '\n';
    std::cout << "----Тип БД: Individual, Overall, Hybrid --------------------------------------------" << '\n';
    std::cout << "----Параметры для сортировки: SEMESTER, NAME ---------------------------------------" << '\n';
    std::cout << "----Параметры для выборки: SEMESTER, DISCIPLINE ------------------------------------" << '\n';
}

void getWords(const std::string &command, std::vector<std::string> &wordsVector){
    std::string word;
    std::istringstream iss(command, std::istringstream::in);
    while (iss >> word)
    {
        wordsVector.push_back(word);
    }
}

std::map<std::string, size_t> fillMarksIndividual(){
    std::map<std::string, size_t> subjectsStudied_;
    size_t number;
    std::cout << "Введите количество изученных дисциплин\n";
    std::cin >> number;
    for (size_t i = 0; i < number; ++i){
        std::cin.ignore();
        std::string name;
        size_t mark;
        std::cout << "Введите название дисциплины\n";
        std::getline(std::cin, name, '\n');
        std::cout << "Введите оценку за нее\n";
        std::cin >> mark;
        subjectsStudied_.insert({name, mark});
    }
    return subjectsStudied_;
}

std::vector<semester> fillMarksOverall(size_t sem){
    std::vector<semester> subjectsStudied_;
    subjectsStudied_.resize(sem);
    size_t i = 1;
    for (auto &sem : subjectsStudied_){
        sem.number = i;
        size_t number;
        std::cout << "Введите количество изученных дисциплин на семестре " << i << '\n';
        std::cin >> number;
        for (size_t i = 0; i < number; ++i){
            std::cin.ignore();
            std::string name;
            size_t mark;
            std::cout << "Введите название дисциплины\n";
            std::getline(std::cin, name, '\n');
            std::cout << "Введите оценку за нее\n";
            std::cin >> mark;
            sem.subjects.insert({name, mark});
        }
        ++i;
    }
    return subjectsStudied_;
}

IndividualPlan getIndividual(){
    std::string name;
    std::string chair;
    size_t sem;
    std::map<std::string, size_t> subjectsStudied_;

    std::cout << "Введите имя студента\n";
    std::getline(std::cin, name, '\n');
    std::cout << "Введите кафедру, на которой он обучается\n";
    std::getline(std::cin, chair, '\n');
    std::cout << "Введите семестр его обучения\n";
    std::cin >> sem;
    subjectsStudied_ = fillMarksIndividual();
    std::cin.ignore();

    IndividualPlan student(name, chair, sem, subjectsStudied_);
    return student;
}

OverallPlan getOverall(){
    std::string name;
    std::string chair;
    size_t sem;
    std::vector<semester> subjectsStudied;

    std::cout << "Введите имя студента\n";
    std::getline(std::cin, name, '\n');
    std::cout << "Введите кафедру, на которой он обучается\n";
    std::getline(std::cin, chair, '\n');
    std::cout << "Введите семестр его обучения\n";
    std::cin >> sem;
    subjectsStudied = fillMarksOverall(sem);
    std::cin.ignore();

    OverallPlan student(name, chair, sem, subjectsStudied);
    return student;
}

void interpreter() {
    std::string command;
    std::string openDB;
    DBHybrid dbHybrid;
    DBOverallPlan dbOverallPlan;
    DBIndividualPlan dbIndividualPlan;

    while (true){
        std::vector<std::string> wordsVector;
        std::getline(std::cin, command, '\n');
        getWords(command, wordsVector);

        try{
            if (wordsVector.at(0) == "PRINT_DIS"){
                for (auto &semester : studentSpace::disciplinesAll){
                    std::cout << "Семестер: " << semester.second << " название: " << semester.first << '\n';
                }
            }

            else if (wordsVector.at(0) == "CREATE_DB"){
                if (wordsVector.at(1) == "Individual"){
                    dbIndividualPlan.createDB(wordsVector.at(2) , studentSpace::disciplines);
                }
                else if (wordsVector.at(1) == "Overall"){
                    dbOverallPlan.createDB(wordsVector.at(2), studentSpace::disciplinesAll);
                }
                else if (wordsVector.at(1) == "Hybrid"){
                    dbHybrid.createDB(wordsVector.at(2), studentSpace::disciplinesAll);
                }
                else{
                    std::cout << "Неверный ввод команды попробуйте еще раз" << '\n';
                }
            }

            else if (wordsVector.at(0)  == "PRINT_DB"){
                if (wordsVector.at(1) == "Individual"){
                    dbIndividualPlan.printBD();
                }
                else if (wordsVector.at(1) == "Overall"){
                    dbOverallPlan.printBD();
                }
                else if (wordsVector.at(1) == "Hybrid"){
                    dbHybrid.printBD();
                }
                else{
                    std::cout << "Неверный ввод команды попробуйте еще раз" << '\n';
                }
            }

            else if (wordsVector.at(0) == "DELETE_DB"){
                if (wordsVector.at(1) == "Individual"){
                    dbIndividualPlan.deleteDB(wordsVector.at(2));
                }
                else if (wordsVector.at(1)== "Overall"){
                    dbOverallPlan.deleteDB(wordsVector.at(2));
                }
                else if (wordsVector.at(1)== "Hybrid"){
                    dbHybrid.deleteDB(wordsVector.at(2));
                }
                else{
                    std::cout << "Неверный ввод команды попробуйте еще раз" << '\n';
                }
            }

            else if (wordsVector.at(0)  == "RENAME"){
                if (wordsVector.at(1) == "Individual"){
                    dbIndividualPlan.renameDB(wordsVector.at(2), wordsVector.at(3));
                }
                else if (wordsVector.at(1)== "Overall"){
                    dbOverallPlan.renameDB(wordsVector.at(2), wordsVector.at(3));
                }
                else if (wordsVector.at(1)== "Hybrid"){
                    dbHybrid.renameDB(wordsVector.at(2), wordsVector.at(3));
                }
                else{
                    std::cout << "Неверный ввод команды попробуйте еще раз" << '\n';
                }
            }

            else if (wordsVector.at(0)  == "OPEN"){
                if (wordsVector.at(1) == "Individual"){
                    dbIndividualPlan.open(wordsVector.at(2));
                    openDB = "Individual";
                }
                else if (wordsVector.at(1)== "Overall"){
                    dbOverallPlan.open(wordsVector.at(2));
                    openDB = "Overall";
                }
                else if (wordsVector.at(1)== "Hybrid"){
                    dbHybrid.open(wordsVector.at(2));
                    openDB = "Hybrid";
                }
                else{
                    std::cout << "Неверный ввод команды попробуйте еще раз" << '\n';
                }
            }

            else if (wordsVector.at(0)  == "CLOSE"){
                if (openDB == "Individual") {
                    dbIndividualPlan.close();
                }
                else if (openDB == "Overall"){
                    dbOverallPlan.close();
                }
                else if (openDB == "Hybrid"){
                    dbHybrid.close();
                }
                openDB = "";
            }

            else if (wordsVector.at(0)  == "INSERT"){
                if (openDB == "Individual" || openDB == "Hybrid" && wordsVector.at(1) == "Individual") {
                    if (openDB == "Individual"){
                        dbIndividualPlan.insert(getIndividual());
                    }
                    else{
                        dbHybrid.insertIndividual(getIndividual());
                    }

                }
                else if (openDB == "Overall" || openDB == "Hybrid" && wordsVector.at(1) == "Overall"){
                    if (openDB == "Overall"){
                        dbOverallPlan.insert(getOverall());
                    }
                    else {
                        dbHybrid.insertOverall(getOverall());
                    }
                }
                else{
                    std::cout << "Неверный ввод команды попробуйте еще раз" << '\n';
                }
            }

            else if (wordsVector.at(0)  == "UPDATE_SET"){

            }
            else if (wordsVector.at(0)  == "DELETE_WHERE"){
                if (openDB == "Individual") {
                    dbIndividualPlan.deleteRecord(wordsVector.at(1));
                }
                else if (openDB == "Overall"){
                    dbOverallPlan.deleteRecord(wordsVector.at(1));
                }
                else if (openDB == "Hybrid"){
                    dbHybrid.deleteRecord(wordsVector.at(1));
                }
            }

            else if (wordsVector.at(0)  == "PRINT_RECORDS"){
                if (openDB == "Individual") {
                    dbIndividualPlan.printRecords();
                }
                else if (openDB == "Overall"){
                    dbOverallPlan.printRecords();
                }
                else if (openDB == "Hybrid"){
                    dbHybrid.printRecords();
                }
            }

            else if (wordsVector.at(0)  == "SORT") {
                if (openDB == "Individual") {
                    if (wordsVector.at(1) == "SEMESTER") {
                        if (wordsVector.at(2) == ">") {
                            dbIndividualPlan.sort([](IndividualPlan a, IndividualPlan b) {
                                return a.GetSemester() > b.GetSemester();
                            });
                        } else if (wordsVector.at(2) == "<") {
                            dbIndividualPlan.sort([](IndividualPlan a, IndividualPlan b) {
                                return a.GetSemester() < b.GetSemester();
                            });
                        }
                    } else if (wordsVector.at(1) == "NAME") {
                        if (wordsVector.at(2) == ">") {
                            dbIndividualPlan.sort([](IndividualPlan a, IndividualPlan b) {
                                return a.GetName() > b.GetName();
                            });
                        } else if (wordsVector.at(2) == "<") {
                            dbIndividualPlan.sort([](IndividualPlan a, IndividualPlan b) {
                                return a.GetName() < b.GetName();
                            });
                        }
                    }
                }
                else if (openDB == "Overall") {
                    if (wordsVector.at(1) == "SEMESTER") {
                        if (wordsVector.at(2) == ">") {
                            dbOverallPlan.sort([](OverallPlan a, OverallPlan b) {
                                return a.GetSemester() > b.GetSemester();
                            });
                        } else if (wordsVector.at(2) == "<") {
                            dbOverallPlan.sort([](OverallPlan a, OverallPlan b) {
                                return a.GetSemester() < b.GetSemester();
                            });
                        }
                    } else if (wordsVector.at(1) == "NAME") {
                        if (wordsVector.at(2) == ">") {
                            dbOverallPlan.sort([](OverallPlan a, OverallPlan b) {
                                return a.GetName() > b.GetName();
                            });
                        } else if (wordsVector.at(2) == "<") {
                            dbOverallPlan.sort([](OverallPlan a, OverallPlan b) {
                                return a.GetName() < b.GetName();
                            });
                        }
                    }
                }
                else if (openDB == "Hybrid") {
                    if (wordsVector.at(1) == "SEMESTER") {
                        if (wordsVector.at(2) == ">") {
                            dbHybrid.sortOverall([](OverallPlan a, OverallPlan b) {
                                return a.GetSemester() > b.GetSemester();
                            });
                            dbHybrid.sortIndividual([](IndividualPlan a, IndividualPlan b) {
                                return a.GetSemester() > b.GetSemester();
                            });
                        } else if (wordsVector.at(2) == "<") {
                            dbHybrid.sortOverall([](OverallPlan a, OverallPlan b) {
                                return a.GetSemester() < b.GetSemester();
                            });
                            dbHybrid.sortIndividual([](IndividualPlan a, IndividualPlan b) {
                                return a.GetSemester() < b.GetSemester();
                            });
                        }
                    } else if (wordsVector.at(1) == "NAME") {
                        if (wordsVector.at(2) == ">") {
                            dbHybrid.sortOverall([](OverallPlan a, OverallPlan b) {
                                return a.GetName() > b.GetName();
                            });
                            dbHybrid.sortIndividual([](IndividualPlan a, IndividualPlan b) {
                                return a.GetName() > b.GetName();
                            });
                        } else if (wordsVector.at(2) == "<") {
                            dbHybrid.sortOverall([](OverallPlan a, OverallPlan b) {
                                return a.GetName() < b.GetName();
                            });
                            dbHybrid.sortIndividual([](IndividualPlan a, IndividualPlan b) {
                                return a.GetName() < b.GetName();
                            });
                        }
                    }
                }
            }

            else if (wordsVector.at(0)  == "SELECT_AND_SAVE"){
                if (openDB == "Individual") {
                    if (wordsVector.at(1) == "SEMESTER") {
                        size_t num;
                        std::vector<IndividualPlan> students;

                        std::cout << "Введите номер семестра,по которому хотите совершить выборку\n";
                        std::cin >> num;
                        std::cin.ignore();
                        students = dbIndividualPlan.selectBySem(num);

                        dbIndividualPlan.createDB(wordsVector.at(3), studentSpace::disciplines);
                        dbIndividualPlan.open(wordsVector.at(3));

                        for (auto &student : students){
                            dbIndividualPlan.insert(student);
                        }
                    }
                    else if (wordsVector.at(1) == "DISCIPLINE") {
                        std::string name;
                        std::vector<IndividualPlan> students;

                        std::cout << "Введите название дисциплины, по которой осуществляется выборка\n";
                        std::getline(std::cin, name, '\n');
                        students = dbIndividualPlan.selectByDis(name);

                        dbIndividualPlan.createDB(wordsVector.at(3), studentSpace::disciplines);
                        dbIndividualPlan.open(wordsVector.at(3));

                        for (auto &student : students){
                            dbIndividualPlan.insert(student);
                        }
                    }
                }
                else if (openDB == "Overall"){
                    if (wordsVector.at(1) == "SEMESTER") {
                        size_t num;
                        std::vector<OverallPlan> students;

                        std::cout << "Введите номер семестра,по которому хотите совершить выборку\n";
                        std::cin >> num;
                        std::cin.ignore();
                        students = dbOverallPlan.selectBySem(num);

                        dbOverallPlan.createDB(wordsVector.at(3), studentSpace::disciplinesAll);
                        dbOverallPlan.open(wordsVector.at(3));

                        for (auto &student : students){
                            dbOverallPlan.insert(student);
                        }
                    }
                    else if (wordsVector.at(1) == "DISCIPLINE") {
                        std::string name;
                        std::vector<OverallPlan> students;

                        std::cout << "Введите название дисциплины, по которой осуществляется выборка\n";
                        std::getline(std::cin, name, '\n');
                        students = dbOverallPlan.selectByDis(name);

                        dbOverallPlan.createDB(wordsVector.at(3), studentSpace::disciplinesAll);
                        dbOverallPlan.open(wordsVector.at(3));

                        for (auto &student : students){
                            dbOverallPlan.insert(student);
                        }
                    }
                }
                else if (openDB == "Hybrid"){
                    if (wordsVector.at(1) == "SEMESTER") {
                        size_t num;
                        std::pair<std::vector<OverallPlan>, std::vector<IndividualPlan>> students;

                        std::cout << "Введите номер семестра,по которому хотите совершить выборку\n";
                        std::cin >> num;
                        std::cin.ignore();
                        students = dbHybrid.selectBySem(num);

                        dbHybrid.createDB(wordsVector.at(3), studentSpace::disciplinesAll);
                        dbHybrid.open(wordsVector.at(3));

                        for (auto &student : students.first){
                            dbHybrid.insertOverall(student);
                        }
                        for (auto &student : students.second){
                            dbHybrid.insertIndividual(student);
                        }
                    }
                    else if (wordsVector.at(1) == "DISCIPLINE") {
                        std::string name;
                        std::pair<std::vector<OverallPlan>, std::vector<IndividualPlan>> students;

                        std::cout << "Введите название дисциплины, по которой осуществляется выборка\n";
                        std::getline(std::cin, name, '\n');
                        students = dbHybrid.selectByDis(name);

                        dbHybrid.createDB(wordsVector.at(3), studentSpace::disciplinesAll);
                        dbHybrid.open(wordsVector.at(3));

                        for (auto &student : students.first){
                            dbHybrid.insertOverall(student);
                        }
                        for (auto &student : students.second){
                            dbHybrid.insertIndividual(student);
                        }
                    }
                }
            }

            else if (wordsVector.at(0)  == "QUIT"){
                break;
            }

            else{
                std::cout << "Неверный ввод команды попробуйте еще раз" << '\n';
            }
        }
        catch (std::out_of_range){
            std::cout << "Неверный ввод команды попробуйте еще раз" << '\n';
        }
    }
}
