// Copyright 2021 GNDavydov

#include "overall_plan.h"

OverallPlan::OverallPlan() = default;

OverallPlan::OverallPlan(const std::string &name, const std::string &chair, const size_t sem,
                         const std::vector<semester> &subjectsStudied) : name_(name), chair_(chair), sem_(sem),
                                                                         subjectsStudied_(subjectsStudied) {}

std::string OverallPlan::GetName() const {
    return name_;
}

std::string OverallPlan::GetChair() const {
    return chair_;
}

size_t OverallPlan::GetSemester() const {
    return sem_;
}

std::vector<semester> OverallPlan::GetSubjects() const {
    return subjectsStudied_;
}

void OverallPlan::SetName(const std::string &name) {
    name_ = name;
}

void OverallPlan::SetChair(const std::string &chair) {
    chair_ = chair;
}

void OverallPlan::SetSemester(const size_t sem) {
    sem_ = sem;
}

void OverallPlan::SetSubjects(const std::vector<semester> &subjectsStudied) {
    subjectsStudied_ = subjectsStudied;
}

double OverallPlan::Count_average() {
    double sum = 0;
    size_t count = 0;

    for (auto &subject : subjectsStudied_.back().subjects){
        sum += subject.second;
        ++count;
    }

    return sum / count;
}

OverallPlan::~OverallPlan() = default;