// Copyright 2021 GNDavydov

#include "overall_plan.h"

OverallPlan::OverallPlan() = default;

OverallPlan::OverallPlan(const std::string &name, const std::string &chair, const size_t sem,
                         const std::vector<size_t> &marks) : name_(name), chair_(chair), sem_(sem) {
    std::vector<std::string> disciplines = studentSpace::GetDisciplines(sem_);
    for (size_t i = 0; i < disciplines.size(); ++i) {
        subjectsStudied_.insert({disciplines[i], marks[i]});
    }
}

std::string OverallPlan::GetName() const {
    return name_;
}

std::string OverallPlan::GetChair() const {
    return chair_;
}

size_t OverallPlan::GetSemester() const {
    return sem_;
}

std::map<std::string, size_t> OverallPlan::GetSubjects() const {
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

void OverallPlan::SetSubjects(const std::vector<size_t> &marks) {
    std::vector<std::string> disciplines = studentSpace::GetDisciplines(sem_);
    for (size_t i = 0; i < disciplines.size(); ++i) {
        subjectsStudied_.insert({disciplines[i], marks[i]});
    }
}

OverallPlan::~OverallPlan() = default;