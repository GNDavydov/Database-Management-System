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
            {"programming_1", 1},
            {"physical_culture_1", 1},
            {"analytic_geometry", 1},
            {"linear_algebra", 2},
            {"mathematical_foundations_of_computer_science", 2},
            {"integrals", 2},
            {"physical_culture_2", 2},
            {"programming_2", 2},
            {"physics_2", 2},
            {"grafics", 2},
            {"physics_3", 3},
            {"programming_3", 3},
            {"physical_culture_3", 3},
            {"sociology", 3},
            {"discrete", 3},
            {"english", 4},
            {"physics_4", 4},
            {"law", 4},
            {"philosophy", 4},
            {"economy", 4},
            {"ecology", 5},
            {"physics_5", 5},
            {"political_science", 5},
            {"machine_learning", 5},
            {"cryptography", 5},
            {"statistics", 6},
            {"electrical_engineering", 6},
            {"security", 6},
            {"sopromat", 6}
    };

    const std::vector<std::string> disciplines {
            "mathematics",
            "history",
            "informatics",
            "programming_1",
            "physical_culture_1",
            "analytic_geometry",
            "linear_algebra",
            "mathematical_foundations_of_computer_science",
            "integrals",
            "physical_culture_2",
            "programming_2",
            "physics_2",
            "grafics",
            "physics_3",
            "programming_3",
            "physical_culture_3",
            "sociology",
            "discrete",
            "english",
            "physics_4",
            "law",
            "philosophy",
            "economy",
            "ecology",
            "physics_5",
            "political_science",
            "machine_learning",
            "cryptography",
            "statistics",
            "electrical_engineering",
            "security",
            "sopromat"
    };
}

class Student {
public:
    virtual double Count_average() = 0;

    virtual ~Student() {}
};

#endif //SEM_2_ALG_LANG_HOMEWORK_1_STUDENT_H
