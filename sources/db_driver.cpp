// Copyright 2021 GNDavydov

#include "db_driver.h"

DB::DB(const std::string &Directory) : Directory_(Directory) {
    try {
        fs::create_directory(path_);
    }
    catch (fs::filesystem_error) {
        fs::create_directory(config::currentPath + config::separator + config::DirectoryDB);
        fs::create_directory(path_);
    }
}

DB::DB(const std::string &path, const std::string &Directory) : Directory_(path + config::separator + Directory) {
    try {
        fs::create_directory(path_);
    }
    catch (fs::filesystem_error) {
        try {
            fs::create_directory(config::DirectoryDB + config::separator + path);
            fs::create_directory(path_);
        } catch (fs::filesystem_error) {
            fs::create_directory(config::currentPath + config::separator + config::DirectoryDB);
            fs::create_directory(config::DirectoryDB + config::separator + path);
            fs::create_directory(path_);
        }
    }
}

void DB::renameDB(const std::string &oldName, const std::string &newName) {
    const fs::path oldPath = path_ + config::separator + oldName;
    const fs::path newPath = path_ + config::separator + newName;

    try {
        fs::rename(oldPath, newPath);
    }
    catch (fs::filesystem_error &e) {
        std::cout << e.what() << std::endl;
    }
}

void DB::printBD() {
    for (auto &temp: fs::recursive_directory_iterator(path_)) {
        if (temp.is_directory()) {
            const size_t i = std::string(temp.path()).find_last_of('/');
            const std::string name = std::string(temp.path()).substr(i);
            std::cout << name << std::endl;
        }
    }
}

void DB::deleteDB(const std::string &name) {
    if (nameOpenDB_ != name) {
        close();
    }

    const std::string DBName = path_ + config::separator + name;
    fs::remove_all(DBName);
}
