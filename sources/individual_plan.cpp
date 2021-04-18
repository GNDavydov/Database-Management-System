// Copyright 2021 GNDavydov

#include "individual_plan.h"

IndividualPlan::IndividualPlan() = default;

IndividualPlan::IndividualPlan(const std::string &name, const std::string &chair, const size_t sem,
                               const std::map<std::string, size_t> &subjectsStudied) : name_(name), chair_(chair),
                                                                                       sem_(sem),
                                                                                       subjectsStudied_(
                                                                                               subjectsStudied) {}

std::string IndividualPlan::GetName() const {
    return name_;
}

std::string IndividualPlan::GetChair() const {
    return chair_;
}

size_t IndividualPlan::GetSemester() const {
    return sem_;
}

std::map<std::string, size_t> IndividualPlan::GetSubjects() const {
    return subjectsStudied_;
}

void IndividualPlan::SetName(const std::string &name) {
    name_ = name;
}

void IndividualPlan::SetChair(const std::string &chair) {
    chair_ = chair;
}

void IndividualPlan::SetSemester(const size_t sem) {
    sem_ = sem;
}

void IndividualPlan::SetSubjects(const std::map<std::string, size_t> &subjectsStudied) {
    subjectsStudied_ = subjectsStudied;
}

double IndividualPlan::Count_average() {
    double sum = 0;
    size_t count = subjectsStudied_.size();

    for (auto &iter : subjectsStudied_) {
        sum += iter.second;
    }

    return sum / count;
}

IndividualPlan::~IndividualPlan() = default;
