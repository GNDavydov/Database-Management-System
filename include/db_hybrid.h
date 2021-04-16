// Copyright 2021 GNDavydov

#ifndef HOMEWORK_1_DB_HYBRID_H
#define HOMEWORK_1_DB_HYBRID_H

#include "db_individual_plan.h"
#include "db_overall_plan.h"

class DBHybrid : public DBIndividualPlan, public DBOverallPlan{
public:
    DBHybrid();

    void createDB(const std::string &name, const std::multimap<std::string, size_t> &disciplines);

    void printBD();

    void deleteDB(const std::string &name);

    void renameDB(const std::string &oldName, const std::string &newName);

    void open(const std::string &name);

    void close();

    void insertIndividual(const IndividualPlan &student);

    void insertOverall(const OverallPlan &student);

    void printRecords();

    std::pair<std::vector<OverallPlan>, std::vector<IndividualPlan>> selectBySem(const size_t sem);

    std::pair<std::vector<OverallPlan>, std::vector<IndividualPlan>> selectByDis(const std::string &name);

    void deleteRecord(const std::string &name);

    void editIndividual(const std::string &name, const IndividualPlan &other);

    void editOverall(const std::string &name, const OverallPlan &other);

    template<class Compare = std::less<>>
    void sortOverall(Compare cmp = Compare{}) {
        DBOverallPlan::sort(cmp);
    }

    template<class Compare = std::less<>>
    void sortIndividual(Compare cmp = Compare{}) {
        DBIndividualPlan::sort(cmp);
    }
};

#endif //HOMEWORK_1_DB_HYBRID_H
