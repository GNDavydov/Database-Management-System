// Copyright 2021 GNDavydov

#ifndef HOMEWORK_1_DB_INDIVIDUAL_PLAN_H
#define HOMEWORK_1_DB_INDIVIDUAL_PLAN_H

#include "db_driver.h"
#include "individual_plan.h"
#include "sorting.h"

class DBIndividualPlan {
private:
    const std::string Directory_ = "individual_plan";
    const std::string path_ = config::pathToDB + config::separator + Directory_;
    const std::string fileName1_ = "students";
    const std::string fileName2_ = "disciplines";
    const std::string fileName3_ = "union";
    std::string nameOpenDB_ = "";
    std::vector<IndividualPlan> students_;

    size_t getSubjectId(const std::string &subject);

    std::string getSubjectName(const size_t id);

public:
    DBIndividualPlan();

    void createDB(const std::string &name, const std::vector<std::string> &disciplines);

    void renameDB(const std::string &oldName, const std::string &newName);

    void printBD();

    void deleteDB(const std::string &name);

    void open(const std::string &name);

    void close();

    void insert(const IndividualPlan &student);

    void printRecords();

    std::vector<IndividualPlan> selectAll();

    std::vector<IndividualPlan> selectBySem(const size_t sem);

    std::vector<IndividualPlan> selectByDis(const std::string &name);

    void deleteAllStudents();

    void deleteRecord(const std::string &name);

    void editRecords(const std::string &name, const IndividualPlan &other);

    template<class Compare = std::less<>>
    void sort(Compare cmp = Compare{}) {
        std::vector<IndividualPlan> newStudents;
        newStudents.resize(students_.size());

        merge_sort(students_.begin(), students_.end(), newStudents.begin(), cmp);

        deleteAllStudents();

        for (auto &student : newStudents){
            insert(student);
        }
    }
};

#endif //HOMEWORK_1_DB_INDIVIDUAL_PLAN_H
