// Copyright 2021 GNDavydov

#include "db_hybrid.h"

DBHybrid::DBHybrid() : DBOverallPlan("db_hybrid"), DBIndividualPlan("db_hybrid") {};

void DBHybrid::createDB(const std::string &name, const std::multimap<std::string, size_t> &disciplines) {
    DBOverallPlan::createDB(name, disciplines);

    std::vector<std::string> subjects;
    for (auto discipline : disciplines){
        subjects.push_back(discipline.first);
    }
    DBIndividualPlan::createDB(name, subjects);
}

void DBHybrid::printBD(){
    DBOverallPlan::printBD();
}

void DBHybrid::deleteDB(const std::string &name) {
    DBOverallPlan::deleteDB(name);
    DBIndividualPlan::deleteDB(name);
}

void DBHybrid::renameDB(const std::string &oldName, const std::string &newName) {
    DBOverallPlan::renameDB(oldName, newName);
    DBIndividualPlan::renameDB(oldName, newName);
}

void DBHybrid::open(const std::string &name) {
    DBOverallPlan::open(name);
    DBIndividualPlan::open(name);
}

void DBHybrid::close() {
    DBOverallPlan::close();
    DBIndividualPlan::close();
}

void DBHybrid::insertIndividual(const IndividualPlan &student) {
    DBIndividualPlan::insert(student);
}

void DBHybrid::insertOverall(const OverallPlan &student) {
    DBOverallPlan::insert(student);
}

void DBHybrid::printRecords() {
    std::cout << "Records of individual-plan students\n";
    DBIndividualPlan::printRecords();
    std::cout << "Records of overall-plan students\n";
    DBOverallPlan::printRecords();
}

std::pair<std::vector<OverallPlan>, std::vector<IndividualPlan>> DBHybrid::selectBySem(const size_t sem) {
    std::pair<std::vector<OverallPlan>, std::vector<IndividualPlan>> students;
    for (auto student : DBOverallPlan::selectBySem(sem)){
        students.first.push_back(student);
    }

    for (auto student : DBIndividualPlan::selectBySem(sem)){
        students.second.push_back(student);
    }

    return students;
}

std::pair<std::vector<OverallPlan>, std::vector<IndividualPlan>> DBHybrid::selectByDis(const std::string &name) {
    std::pair<std::vector<OverallPlan>, std::vector<IndividualPlan>> students;
    for (auto student : DBOverallPlan::selectByDis(name)){
        students.first.push_back(student);
    }

    for (auto student : DBIndividualPlan::selectByDis(name)){
        students.second.push_back(student);
    }

    return students;
}

void DBHybrid::deleteRecord(const std::string &name) {
    DBOverallPlan::deleteRecord(name);
    DBIndividualPlan::deleteRecord(name);
}

void DBHybrid::editIndividual(const std::string &name, const IndividualPlan &other) {
    DBIndividualPlan::editRecords(name, other);
}

void DBHybrid::editOverall(const std::string &name, const OverallPlan &other) {
    DBOverallPlan::editRecords(name, other);
}

