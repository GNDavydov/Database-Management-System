// Copyright 2021 GNDavydov

#ifndef SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H
#define SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace config {
    char separator = fs::path::preferred_separator;
    const std::string currentPath = fs::current_path();
    const std::string DirectoryDB = "DirectoryDB";
    const std::string pathToDB = currentPath + separator + DirectoryDB;
}

void menu() {
    setlocale(LC_ALL, "Russian");
}

void createDB(const std::string &name) {
    try {
        fs::create_directory(config::pathToDB + config::separator + name);
    }
    catch (fs::filesystem_error) {
        fs::create_directory(config::currentPath + config::separator + config::DirectoryDB);
        fs::create_directory(config::pathToDB + config::separator + name);
    }

}

void renameDB(const std::string &oldName, const std::string &newName) {
    const fs::path oldPath = config::pathToDB + config::separator + oldName;
    const fs::path newPath = config::pathToDB + config::separator + newName;
    try{
        fs::rename(oldPath, newPath);
    }
    catch (fs::filesystem_error & e){
        std::cout << e.what() << std::endl;
    }
}

void printBD() {
    for (auto &temp: fs::recursive_directory_iterator(config::pathToDB)) {
        std::cout << temp.path() << std::endl;
    }
}

void deleteDB(const std::string &name){
    std::string path = config::pathToDB + config::separator + name;
    fs::remove_all(path);
}

void createTable();

/*

connect()

insert();

update();

deleteRecord();

printRecords();

sort();

select();

saveSelection();

saveBD();
*/

#endif //SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H
