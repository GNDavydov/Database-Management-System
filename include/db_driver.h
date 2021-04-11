// Copyright 2021 GNDavydov

#ifndef SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H
#define SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H

#include <filesystem>
#include <fstream>
#include <iostream>

#include "overall_plan.h"
#include "individual_plan.h"

namespace fs = std::filesystem;

namespace config {
    const char separator = fs::path::preferred_separator;
    const std::string currentPath = fs::current_path();
    const std::string DirectoryDB = "DirectoryDB";
    const std::string pathToDB = currentPath + separator + DirectoryDB;
}

class DBOverallPlan {
private:
    const std::string Directory_ = "overall_plan";
    const std::string path_ = config::pathToDB + config::separator + Directory_;
    const std::string fileName1_ = "students";
    const std::string fileName2_ = "disciplines";
    const std::string fileName3_ = "union";
    std::string nameOpenDB_ = "";


    size_t getSubjectId(const std::string &subject) {
        const std::string pathToFile2 = path_ + config::separator + nameOpenDB_ + config::separator + fileName2_;
        std::fstream file(pathToFile2, std::ios::binary | std::ios::in);
        size_t len;
        size_t id = 0;

        file.read((char *) &len, sizeof(size_t));

        for (size_t i = 0; i < len; ++i) {
            std::string name;
            size_t sem;

            file.read((char *) &id, sizeof(size_t));
            file.read((char*)&sem, sizeof(size_t));
            std::getline(file, name, '\0');

            if (name == subject) {
                break;
            }
        }

        return id;
    }


public:
    DBOverallPlan() {
        try {
            fs::create_directory(path_);
        }
        catch (fs::filesystem_error) {
            fs::create_directory(config::currentPath + config::separator + config::DirectoryDB);
            fs::create_directory(path_);
        }
    }

    void createDB(const std::string &name, const std::multimap<size_t, std::string> &disciplines) {
        const std::string DBName = path_ + config::separator + name;
        fs::create_directory(DBName);

        std::ofstream fileStudent(DBName + config::separator + fileName1_, std::ios::binary);
        size_t recordsS = 0;

        fileStudent.write((char *) &recordsS, sizeof(size_t));
        fileStudent.close();

        std::ofstream fileDis(DBName + config::separator + fileName2_, std::ios::binary);
        size_t recordsD = disciplines.size();
        size_t id = 0;

        fileDis.write((char *) &recordsD, sizeof(size_t));
        for (auto subject : disciplines) {
            fileDis.write((char *) &id, sizeof(size_t));
            fileDis.write((char *) &subject.first, sizeof(size_t));
            fileDis << subject.second << std::ends;
            ++id;
        }
        fileDis.close();

        std::ofstream(DBName + config::separator + fileName3_, std::ios::binary);
    }

    void renameDB(const std::string &oldName, const std::string &newName) {
        const fs::path oldPath = path_ + config::separator + oldName;
        const fs::path newPath = path_ + config::separator + newName;

        try {
            fs::rename(oldPath, newPath);
        }
        catch (fs::filesystem_error &e) {
            std::cout << e.what() << std::endl;
        }
    }

    void printBD() {
        for (auto &temp: fs::recursive_directory_iterator(path_)) {
            if (temp.is_directory()) {
                std::cout << temp.path() << std::endl;
            }
        }
    }

    void deleteDB(const std::string &name) {
        const std::string DBName = path_ + config::separator + name;
        fs::remove_all(DBName);
    }

    void open(const std::string &name) {
        if (fs::is_directory(path_ + config::separator + name)) {
            nameOpenDB_ = name;
        }
    }

    void insert(const OverallPlan &student) {
        const std::string name = student.GetName();
        const std::string chair = student.GetChair();
        const size_t sem = student.GetSemester();
        const std::vector<semester> subjectsStudied = student.GetSubjects();

        // write in Table Students
        const std::string pathToFile1 = path_ + config::separator + nameOpenDB_ + config::separator + fileName1_;
        std::fstream file;

        file.open(pathToFile1, std::ios::binary | std::ios::in | std::ios::out);
        size_t id;
        file.read((char *) &id, sizeof(size_t));
        ++id;
        file.seekp(0);
        file.write((char *) &id, sizeof(size_t));
        file.close();

        file.open(pathToFile1, std::ios::binary | std::ios::app);
        file.write((char *) &id, sizeof(size_t));
        file << name << std::ends;
        file << chair << std::ends;
        file.write((char *) &sem, sizeof(size_t));

        file.close();

        // write in Union Table
        const std::string pathToFile3 = path_ + config::separator + nameOpenDB_ + config::separator + fileName3_;
        file.open(pathToFile3, std::ios::binary | std::ios::app);

        for (auto semester : subjectsStudied) {
            for (auto subject : semester.subjects) {
                size_t idSubject = getSubjectId(subject.first);
                size_t mark = subject.second;
                file.write((char *) &id, sizeof(size_t));
                file.write((char *) &idSubject, sizeof(size_t));
                file.write((char *) &mark, sizeof(size_t));
            }
        }
    }

    void printRecords(){
        std::fstream file;
        const std::string pathToFile1 = path_ + config::separator + nameOpenDB_ + config::separator + fileName1_;
        const std::string pathToFile2 = path_ + config::separator + nameOpenDB_ + config::separator + fileName2_;
        const std::string pathToFile3 = path_ + config::separator + nameOpenDB_ + config::separator + fileName3_;

        std::cout << "-------------------------------------------------------\n";

        std::cout << "Table Students:\n";
        std::cout << "id\t name\t chair\t sem\n";
        file.open(pathToFile1, std::ios::binary | std::ios::in);
        size_t len;
        file.read((char*)&len, sizeof(size_t));

        for (size_t i = 0; i < len; ++i){
            size_t id;
            std::string name;
            std::string chair;
            size_t sem;

            file.read((char*)&id, sizeof(size_t));
            std::getline(file, name, '\0');
            std::getline(file, chair, '\0');
            file.read((char*)&sem, sizeof(size_t));

            std::cout << id << '\t' << name << '\t' << chair << '\t' << sem << '\n';
        }
        std::cout << '\n';
        file.close();

        file.open(pathToFile2, std::ios::binary | std::ios::in);
        std::cout << "Table Disciplines:\n";
        std::cout << "id\t subject\t sem\n";
        file.read((char*)&len, sizeof(size_t));

        for (size_t i = 0; i < len; ++i){
            size_t id;
            std::string name;
            size_t sem;

            file.read((char*)&id, sizeof(size_t));
            file.read((char*)&sem, sizeof(size_t));
            std::getline(file, name, '\0');

            std::cout << id << '\t' << name << '\t' << sem << '\n';
        }
        std::cout << '\n';
        file.close();

        file.open(pathToFile3, std::ios::binary | std::ios::in);
        std::cout << "Table Union:\n";
        std::cout << "id(student)\t id(subject)\t mark\n";

        while (true){
            size_t id1;
            size_t id2;
            size_t mark;


            file.read((char*)&id1, sizeof(size_t));
            file.read((char*)&id2, sizeof(size_t));
            file.read((char*)&mark, sizeof(size_t));

            if (file.eof()){
                break;
            }

            std::cout << id1 << '\t' << id2 << '\t' << mark << '\n';
        }
        std::cout << "-------------------------------------------------------\n";
        file.close();
    }



};

#endif //SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H
