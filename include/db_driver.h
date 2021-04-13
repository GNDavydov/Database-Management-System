// Copyright 2021 GNDavydov

#ifndef SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H
#define SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H

#include <filesystem>
#include <fstream>
#include <iostream>

#include "individual_plan.h"
#include "sorting.h"
#include "overall_plan.h"

namespace fs = std::filesystem;

namespace config {
    const char separator = fs::path::preferred_separator;
    const std::string currentPath = fs::current_path();
    const std::string DirectoryDB = "DirectoryDB";
    const std::string pathToDB = currentPath + separator + DirectoryDB;
}

struct MainInfo {
    size_t id;
    std::string name;
    std::string chair;
    size_t sem;
};

class DBOverallPlan {
private:
    const std::string Directory_ = "overall_plan";
    const std::string path_ = config::pathToDB + config::separator + Directory_;
    const std::string fileName1_ = "students";
    const std::string fileName2_ = "disciplines";
    const std::string fileName3_ = "union";
    std::string nameOpenDB_ = "";

    size_t getSubjectId(const std::string &subject);

    std::pair<size_t, std::string> getSubjectName(const size_t id);

public:
    DBOverallPlan();

    void createDB(const std::string &name, const std::multimap<size_t, std::string> &disciplines);

    void renameDB(const std::string &oldName, const std::string &newName);

    void printBD();

    void deleteDB(const std::string &name);

    void open(const std::string &name);

    void insert(const OverallPlan &student);

    void printRecords();

    std::vector<OverallPlan> selectAll();

    std::vector<OverallPlan> selectBySem(const size_t sem);

    std::vector<OverallPlan> selectByDis(const std::string &name);

    void deleteAllStudents();

    void deleteRecord(const std::string &name);

    void editRecords(const std::string &name);

    template<class Compare = std::less<>>
    void sort(Compare cmp = Compare{}) {
        const std::string pathToFile1 = path_ + config::separator + nameOpenDB_ + config::separator + fileName1_;
        std::fstream file;
        std::vector<MainInfo> oldStudents;
        std::vector<MainInfo> newStudents;
        size_t len;

        file.open(pathToFile1, std::ios::binary | std::ios::in);
        file.read((char *) &len, sizeof(size_t));
        oldStudents.resize(len);
        newStudents.resize(len);

        for (size_t i = 0; i < len; ++i) {
            file.read((char *) &oldStudents[i].id, sizeof(size_t));
            std::getline(file, oldStudents[i].name, '\0');
            std::getline(file, oldStudents[i].chair, '\0');
            file.read((char *) &oldStudents[i].sem, sizeof(size_t));
        }

        file.close();

        merge_sort(oldStudents.begin(), oldStudents.end(), newStudents.begin(), cmp);

        file.open(pathToFile1, std::ios::binary | std::ios::trunc | std::ios::out);

        file.write((char *) &len, sizeof(size_t));
        for (size_t i = 0; i < len; ++i) {
            file.write((char *) &newStudents[i].id, sizeof(size_t));
            file << newStudents[i].name << std::ends;
            file << newStudents[i].chair << std::ends;
            file.write((char *) &newStudents[i].sem, sizeof(size_t));
        }
        file.close();
    }
};

#endif //SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H
