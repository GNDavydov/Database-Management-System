// Copyright 2021 GNDavydov

#ifndef HOMEWORK_1_DB_INDIVIDUAL_PLAN_H
#define HOMEWORK_1_DB_INDIVIDUAL_PLAN_H

#include "db_driver.h"
#include "individual_plan.h"
#include "sorting.h"

class DBIndividualPlan : public DB{
private:
    std::vector<IndividualPlan> students_;

    size_t getSubjectId(const std::string &subject);

    std::string getSubjectName(const size_t id);

public:
    DBIndividualPlan();

    DBIndividualPlan(const std::string &path);

    void createDB(const std::string &name, const std::vector<std::string> &disciplines);

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
