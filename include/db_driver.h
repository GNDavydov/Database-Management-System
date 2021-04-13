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


#endif //SEM_2_ALG_LANG_HOMEWORK_1_DB_DRIVER_H
