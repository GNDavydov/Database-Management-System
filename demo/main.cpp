// Copyright 2021 GNDavydov

#include "db_driver.h"
#include "db_overall_plan.h"
#include "db_individual_plan.h"

int main() {
    IndividualPlan s1("Grisha", "IU8-21", 2, {{"math", 5}, {"fisra", 4}, {"prog", 5}});
    IndividualPlan s2("Niko", "IU8-21", 3, {{"math", 5}, {"fisra", 4}, {"prog", 4}});
    IndividualPlan s3("Roma", "PS-21", 2, {{"math", 4}, {"fisra", 4}, {"prog", 2}});
    IndividualPlan s4("Nikita", "SM-42", 4, {{"math", 1}, {"fisra", 1}});
    DBIndividualPlan db;
    db.createDB("DB1", {"math", "fisra", "prog"});
    db.open("DB1");
    db.insert(s1);
    db.insert(s1);
    db.insert(s2);
    db.insert(s3);
    db.printRecords();
    db.close();
    db.open("DB1");
    db.printRecords();
    db.insert(s4);
    db.sort([](IndividualPlan a, IndividualPlan b){
        return a.GetSemester() < b.GetSemester();
    });

    db.printRecords();
    std::vector<IndividualPlan> students = db.selectByDis("prog");
    db.close();
    db.createDB("DB2", {"math", "fisra", "prog"});
    db.open("DB2");
    for (auto s : students){
        db.insert(s);
    }
    db.printRecords();
    db.close();
    db.open("DB2");
    db.printRecords();
    db.deleteRecord("Grisha");
    db.printRecords();
    db.close();
    db.open("DB2");
    db.printRecords();
    IndividualPlan s2_1("Niko", "IU8-31", 3, {{"math", 5}, {"fisra", 4}, {"prog", 5}});
    db.editRecords("Niko", s2_1);
    db.printRecords();
    db.close();
    db.open("DB2");
    db.printRecords();
    db.printBD();
    db.renameDB("DB1", "DB1_2");
    db.deleteDB("DB1_2");
    db.printBD();


     /*
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
    db.sort([](OverallPlan a, OverallPlan b){
        return a.GetName() < b.GetName();
    });
    db.printRecords();

    OverallPlan student4("Nikita", "RC-21", 2, {{1, {{"math", 2}}},
                                                {1, {{"fisra", 3}}}});
    db.insert(student4);
    db.printRecords();
    db.sort([](OverallPlan a, OverallPlan b){
        return a.GetSemester() < b.GetSemester();
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
    db.printRecords();*/
}