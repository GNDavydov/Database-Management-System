// Copyright 2021 GNDavydov

#ifndef SEM_2_ALG_LANG_HOMEWORK_1_OVERALL_PLAN_H
#define SEM_2_ALG_LANG_HOMEWORK_1_OVERALL_PLAN_H

#include "student.h"

struct semester {
    size_t number;
    std::map<std::string, size_t> subjects;
};

class OverallPlan : public Student {
private:
    std::string name_;
    std::string chair_;
    size_t sem_;
    std::vector<semester> subjectsStudied_;

public:
    OverallPlan();

    OverallPlan(const std::string &name, const std::string &chair, const size_t sem,
                const std::vector<semester> &subjectsStudied);

    std::string GetName() const;

    std::string GetChair() const;

    size_t GetSemester() const;

    std::vector<semester> GetSubjects() const;

    void SetName(const std::string &name);

    void SetChair(const std::string &chair);

    void SetSemester(const size_t sem);

    void SetSubjects(const std::vector<semester> &subjectsStudied);

    double Count_average();

    ~OverallPlan();
};

#endif //SEM_2_ALG_LANG_HOMEWORK_1_OVERALL_PLAN_H
