// Copyright 2021 GNDavydov

#ifndef SEM_2_ALG_LANG_HOMEWORK_1_STUDENT_H
#define SEM_2_ALG_LANG_HOMEWORK_1_STUDENT_H

#include <map>
#include <vector>
#include <string>

namespace studentSpace {
    const std::multimap<size_t, std::string> disciplinesAll = {
            {1, "mathematics"},
            {1, "history"},
            {1, "informatics"},
            {1, "programming_1"},
            {1, "physical culture"},
            {1, "linear algebra"},
            {2, "analytic geometry"},
            {2, "mathematical foundations of computer science"},
            {2, "integrals"},
            {2, "programming_2"}
    };
}

class Student {
public:
    virtual double Count_average() = 0;

    virtual ~Student() {}
};

#endif //SEM_2_ALG_LANG_HOMEWORK_1_STUDENT_H
