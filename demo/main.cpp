// Copyright 2021 GNDavydov

#include "db_driver.h"
#include "individual_plan.h"
#include "overall_plan.h"

int main() {
    OverallPlan student1("Niko", "IU8-21", 2, {{1, {{"math", 5}}},
                                               {1, {{"fisra", 3}}}});
    OverallPlan student2("Grigori", "IU8-21", 2, {{1, {{"math", 5}}},
                                               {1, {{"fisra", 4}}}});
    OverallPlan student3("Roma", "PS-11", 2, {{1, {{"math", 3}}},
                                                  {1, {{"fisra", 5}}}});
    DBOverallPlan db;
    db.createDB("FFF", {{1, "math"}, {1, "fisra"}});
    db.open("FFF");
    db.insert(student1);
    db.insert(student2);
    db.insert(student3);

    db.printBD();
    db.printRecords();
}