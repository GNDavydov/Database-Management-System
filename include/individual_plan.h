// Copyright 2021 GNDavydov

#ifndef SEM_2_ALG_LANG_HOMEWORK_1_INDIVIDUAL_PLAN_H
#define SEM_2_ALG_LANG_HOMEWORK_1_INDIVIDUAL_PLAN_H

#include "student.h"

class IndividualPlan {
private:
    std::string name_;
    std::string chair_;
    size_t sem_;
    std::map<std::string, size_t> subjectsStudied_;

public:
    IndividualPlan();

    IndividualPlan(const std::string &name, const std::string &chair, const size_t sem,
                   const std::map<std::string, size_t> &subjectsStudied);

    std::string GetName() const;

    std::string GetChair() const;

    size_t GetSemester() const;

    std::map<std::string, size_t> GetSubjects() const;

    void SetName(const std::string &name);

    void SetChair(const std::string &chair);

    void SetSemester(const size_t sem);

    void SetSubjects(const std::map<std::string, size_t> &subjectsStudied);

    double Count_average();

    ~IndividualPlan();
};

#endif //SEM_2_ALG_LANG_HOMEWORK_1_INDIVIDUAL_PLAN_H
