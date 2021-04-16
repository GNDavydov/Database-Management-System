// Copyright 2021 GNDavydov

#ifndef SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H
#define SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H

#include <filesystem>
#include <fstream>
#include <iostream>

#include "sorting.h"

namespace fs = std::filesystem;

namespace config {
    const char separator = fs::path::preferred_separator;
    const std::string currentPath = fs::current_path();
    const std::string DirectoryDB = "DirectoryDB";
    const std::string pathToDB = currentPath + separator + DirectoryDB;
}

class DB {
protected:
    const std::string Directory_;
    const std::string path_ = config::pathToDB + config::separator + Directory_;
    const std::string fileName1_ = "students";
    const std::string fileName2_ = "disciplines";
    const std::string fileName3_ = "union";
    std::string nameOpenDB_ = "";

public:
    DB(const std::string &Directory);

    DB(const std::string &path, const std::string &Directory);

    void renameDB(const std::string &oldName, const std::string &newName);

    void printBD();

    void deleteDB(const std::string &name);

    virtual void open(const std::string &name) = 0;

    virtual  void close() = 0;
};


#endif //SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H
