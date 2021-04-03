// Copyright 2021 GNDavydov

#include "db_driver.h"

int main() {
    menu();
    createDB("Directory");
    createDB("MyDirectory");
    printBD();
    renameDB("Directory", "Dir");
    deleteDB("Dir");
}