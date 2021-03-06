// Copyright 2021 GNDavydov

#ifndef HOMEWORK_1_DB_OVERALL_PLAN_H
#define HOMEWORK_1_DB_OVERALL_PLAN_H

#include "db_driver.h"
#include "overall_plan.h"

class DBOverallPlan : public DB{
private:
    std::vector<OverallPlan> students_;

    size_t getSubjectId(const std::string &subject);

    std::pair<size_t, std::string> getSubjectName(const size_t id);

public:
    DBOverallPlan();

    DBOverallPlan(const std::string &path);

    void createDB(const std::string &name, const std::multimap<std::string, size_t> &disciplines);

    void open(const std::string &name);

    void close();

    void insert(const OverallPlan &student);

    void printRecords();

    std::vector<OverallPlan> selectAll();

    std::vector<OverallPlan> selectBySem(const size_t sem);

    std::vector<OverallPlan> selectByDis(const std::string &name);

    void deleteAllStudents();

    void deleteRecord(const std::string &name);

    void editRecords(const std::string &name, const OverallPlan &other);

    template<class Compare = std::less<>>
    void sort(Compare cmp = Compare{}) {
        std::vector<OverallPlan> newStudents;
        newStudents.resize(students_.size());

        merge_sort(students_.begin(), students_.end(), newStudents.begin(), cmp);

        deleteAllStudents();

        for (auto &student : newStudents) {
            insert(student);
        }
    }
};

#endif //HOMEWORK_1_DB_OVERALL_PLAN_H
