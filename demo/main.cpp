// Copyright 2021 GNDavydov

#include "db_driver.h"
#include "individual_plan.h"
#include "overall_plan.h"

int main() {
    OverallPlan student1("Niko", "IU8-21", 2, {{1, {{"math", 5}}},
                                               {1, {{"fisra", 3}}}});
    OverallPlan student2("Grigori", "IU8-21", 3, {{1, {{"math", 5}}},
                                               {1, {{"fisra", 4}}}});
    OverallPlan student3("Roma", "PS-11", 4, {{1, {{"math", 3}}},
                                                  {1, {{"fisra", 5}}}});
    DBOverallPlan db;
    db.createDB("FFF", {{"math", 1}, {"fisra", 1}});

    db.open("FFF");
    db.insert(student1);
    db.insert(student2);
    db.insert(student3);

    db.printBD();
    db.printRecords();
    db.sort([](MainInfo a, MainInfo b){
        return a.name < b.name;
    });
    db.printRecords();

    OverallPlan student4("Nikita", "RC-21", 2, {{1, {{"math", 2}}},
                                              {1, {{"fisra", 3}}}});
    db.insert(student4);
    db.printRecords();
    db.sort([](MainInfo a, MainInfo b){
        return a.sem < b.sem;
    });
    db.printRecords();

    std::vector<OverallPlan> students = db.selectBySem(2);
    size_t c = 0;
    db.createDB("F2", {{"math", 1}, {"fisra", 1}});
    db.open("F2");
    db.insert(students[0]);
    db.insert(students[1]);
    db.printRecords();
    db.open("FFF");
    db.deleteRecord("Grigori");
    db.printRecords();
}