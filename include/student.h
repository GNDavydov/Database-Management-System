// Copyright 2021 GNDavydov

#ifndef SEM_2_ALG_LANG_HOMEWORK_1_STUDENT_H
#define SEM_2_ALG_LANG_HOMEWORK_1_STUDENT_H

#include <map>
#include <vector>
#include <string>

namespace studentSpace {
    const std::multimap<std::string, size_t> disciplinesAll = {
            {"mathematics", 1},
            {"history", 1},
            {"informatics", 1},
            {"programming 1", 1},
            {"physical culture 1", 1},
            {"analytic geometry", 1},
            {"linear algebra", 2},
            {"mathematical foundations of computer science", 2},
            {"integrals", 2},
            {"physical culture 2", 2},
            {"programming 2", 2},
            {"physics 2", 2},
            {"physics 3", 3},
            {"programming 3", 3},
            {"physical culture 3", 3},
            {"sociology", 3},

    };

    const std::vector<std::string> disciplines {
            "mathematics",
            "history",
            "informatics",
            "programming 1",
            "physical culture 1",
            "analytic geometry",
            "linear algebra",
            "mathematical foundations of computer science",
            "integrals",
            "physical culture 2",
            "programming 2",
            "physics 2",
            "physics 3",
            "programming 3",
            "physical culture 3",
            "sociology"
    };
}

class Student {
public:
    virtual double Count_average() = 0;

    virtual ~Student() {}
};

#endif //SEM_2_ALG_LANG_HOMEWORK_1_STUDENT_H
