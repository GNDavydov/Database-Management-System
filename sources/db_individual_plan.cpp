// Copyright 2021 GNDavydov

#include "db_individual_plan.h"

size_t DBIndividualPlan::getSubjectId(const std::string &subject) {
    const std::string pathToFile2 = path_ + config::separator + nameOpenDB_ + config::separator + fileName2_;
    std::fstream file(pathToFile2, std::ios::binary | std::ios::in);
    size_t len;
    size_t id = 0;

    file.read((char *) &len, sizeof(size_t));

    for (size_t i = 0; i < len; ++i) {
        std::string name;

        file.read((char *) &id, sizeof(size_t));
        std::getline(file, name, '\0');

        if (name == subject) {
            break;
        }
    }

    file.close();

    return id;
}

std::string DBIndividualPlan::getSubjectName(const size_t id) {
    const std::string pathToFile2 = path_ + config::separator + nameOpenDB_ + config::separator + fileName2_;
    std::fstream file(pathToFile2, std::ios::binary | std::ios::in);
    size_t len;
    std::string name;

    file.read((char *) &len, sizeof(size_t));

    for (size_t i = 0; i < len; ++i) {
        size_t id_;

        file.read((char *) &id_, sizeof(size_t));
        std::getline(file, name, '\0');

        if (id_ == id) {
            break;
        }
    }

    file.close();

    return name;
}

DBIndividualPlan::DBIndividualPlan() {
    try {
        fs::create_directory(path_);
    }
    catch (fs::filesystem_error) {
        fs::create_directory(config::currentPath + config::separator + config::DirectoryDB);
        fs::create_directory(path_);
    }
}

void DBIndividualPlan::createDB(const std::string &name, const std::vector<std::string> &disciplines) {
    const std::string DBName = path_ + config::separator + name;
    fs::create_directory(DBName);

    std::ofstream fileStudent(DBName + config::separator + fileName1_, std::ios::binary);
    size_t recordsS = 0;
    fileStudent.write((char *) &recordsS, sizeof(size_t));
    fileStudent.close();

    std::ofstream fileDis(DBName + config::separator + fileName2_, std::ios::binary);
    size_t recordsD = disciplines.size();
    size_t id = 1;

    fileDis.write((char *) &recordsD, sizeof(size_t));
    for (auto &subject : disciplines) {
        fileDis.write((char *) &id, sizeof(size_t));
        fileDis << subject << std::ends;
        ++id;
    }
    fileDis.close();

    std::ofstream(DBName + config::separator + fileName3_, std::ios::binary);
}

void DBIndividualPlan::renameDB(const std::string &oldName, const std::string &newName) {
    const fs::path oldPath = path_ + config::separator + oldName;
    const fs::path newPath = path_ + config::separator + newName;

    try {
        fs::rename(oldPath, newPath);
    }
    catch (fs::filesystem_error &e) {
        std::cout << e.what() << std::endl;
    }
}

void DBIndividualPlan::printBD() {
    for (auto &temp: fs::recursive_directory_iterator(path_)) {
        if (temp.is_directory()) {
            std::cout << temp.path() << std::endl;
        }
    }
}

void DBIndividualPlan::deleteDB(const std::string &name) {
    const std::string DBName = path_ + config::separator + name;
    fs::remove_all(DBName);
}

void DBIndividualPlan::open(const std::string &name) {
    if (fs::is_directory(path_ + config::separator + name)) {
        nameOpenDB_ = name;
    }
    students_ = selectAll();
}

void DBIndividualPlan::close() {
    nameOpenDB_ = "";
    students_.resize(0);
    students_.shrink_to_fit();
}

void DBIndividualPlan::insert(const IndividualPlan &student) {
    const std::string name = student.GetName();
    const std::string chair = student.GetChair();
    const size_t sem = student.GetSemester();
    const std::map<std::string, size_t> subjectsStudied = student.GetSubjects();
    const std::string pathToFile1 = path_ + config::separator + nameOpenDB_ + config::separator + fileName1_;
    const std::string pathToFile3 = path_ + config::separator + nameOpenDB_ + config::separator + fileName3_;

    for (size_t i = 0; i < students_.size(); ++i) {
        if (student.GetName() == students_[i].GetName()) {
            return;
        }
    }

    students_.push_back(student);

    std::fstream file;

    file.open(pathToFile1, std::ios::binary | std::ios::in | std::ios::out);
    size_t id;
    file.read((char *) &id, sizeof(size_t));
    ++id;
    file.seekp(0);
    file.write((char *) &id, sizeof(size_t));
    file.close();

    file.open(pathToFile1, std::ios::binary | std::ios::app);
    file.write((char *) &id, sizeof(size_t));
    file << name << std::ends;
    file << chair << std::ends;
    file.write((char *) &sem, sizeof(size_t));
    file.close();

    file.open(pathToFile3, std::ios::binary | std::ios::app);
    for (auto &subject : subjectsStudied) {
        size_t idSubject = getSubjectId(subject.first);
        size_t mark = subject.second;
        file.write((char *) &id, sizeof(size_t));
        file.write((char *) &idSubject, sizeof(size_t));
        file.write((char *) &mark, sizeof(size_t));
    }
    file.close();
}

void DBIndividualPlan::printRecords() {
    size_t id = 1;
    for (auto &student : students_) {
        std::cout << "Student " << id << std::endl;
        std::cout << "Name: " << student.GetName() << std::endl;
        std::cout << "Chair: " << student.GetChair() << std::endl;
        std::cout << "Semester: " << student.GetSemester() << std::endl;
        for (auto &subject : student.GetSubjects()) {
            std::cout << "Subject name: " << subject.first << " Mark: " << subject.second << std::endl;
        }
        ++id;
        std::cout << std::endl;
    }
}

std::vector<IndividualPlan> DBIndividualPlan::selectAll() {
    const std::string pathToFile1 = path_ + config::separator + nameOpenDB_ + config::separator + fileName1_;
    const std::string pathToFile3 = path_ + config::separator + nameOpenDB_ + config::separator + fileName3_;
    std::fstream file;
    std::vector<IndividualPlan> students; // Answer for this function
    std::map<size_t, IndividualPlan> studentsWithId; // An array of students with their id in the table
    size_t len; // Len of files

    file.open(pathToFile1, std::ios::binary | std::ios::in);
    file.read((char *) &len, sizeof(size_t));

    for (size_t i = 0; i < len; ++i) {
        size_t id;
        std::string name;
        std::string chair;
        size_t sem;

        file.read((char *) &id, sizeof(size_t));
        std::getline(file, name, '\0');
        std::getline(file, chair, '\0');
        file.read((char *) &sem, sizeof(size_t));

        IndividualPlan s;
        s.SetName(name);
        s.SetChair(chair);
        s.SetSemester(sem);

        studentsWithId.insert({id, s});
    }
    file.close();

    for (auto &student : studentsWithId) {
        file.open(pathToFile3, std::ios::binary | std::ios::in);
        std::map<std::string, size_t> disciplines;

        while (true) {
            size_t id1;
            size_t id2;
            size_t mark;

            file.read((char *) &id1, sizeof(size_t));
            file.read((char *) &id2, sizeof(size_t));
            file.read((char *) &mark, sizeof(size_t));

            if (id1 == student.first) {
                std::string name = getSubjectName(id2);
                disciplines.insert({name, mark});
            }

            if (file.eof()) {
                break;
            }
        }

        student.second.SetSubjects(disciplines);
        students.push_back(student.second);
        file.close();
    }

    return students;
}

std::vector<IndividualPlan> DBIndividualPlan::selectBySem(const size_t sem) {
    std::vector<IndividualPlan> students;
    for (auto &student : students_) {
        if (student.GetSemester() == sem) {
            students.push_back(student);
        }
    }
    return students;
}

std::vector<IndividualPlan> DBIndividualPlan::selectByDis(const std::string &name) {
    std::vector<IndividualPlan> students;
    for (auto &student : students_) {
        for (auto &subject : student.GetSubjects()) {
            if (subject.first == name) {
                students.push_back(student);
            }
        }
    }
    return students;
}

void DBIndividualPlan::deleteAllStudents() {
    const std::string pathToFile1 = path_ + config::separator + nameOpenDB_ + config::separator + fileName1_;
    const std::string pathToFile3 = path_ + config::separator + nameOpenDB_ + config::separator + fileName3_;
    std::fstream file;
    size_t len = 0;

    file.open(pathToFile1, std::ios::binary | std::ios::trunc | std::ios::out);
    file.write((char *) &len, sizeof(size_t));
    file.close();
    file.open(pathToFile3, std::ios::binary | std::ios::trunc | std::ios::out);
    file.close();

    students_.resize(0);
    students_.shrink_to_fit();
}

void DBIndividualPlan::deleteRecord(const std::string &name) {
    std::vector<IndividualPlan> students = students_;
    deleteAllStudents();
    for (auto &student : students) {
        if (student.GetName() == name) {
            continue;
        }
        insert(student);
    }
}

void DBIndividualPlan::editRecords(const std::string &name, const IndividualPlan &other) {
    std::vector<IndividualPlan> students = students_;
    deleteAllStudents();
    for (auto &student : students) {
        if (student.GetName() == name) {
            student.SetName(other.GetName());
            student.SetChair(other.GetChair());
            student.SetSemester(other.GetSemester());
            student.SetSubjects(other.GetSubjects());
        }
        insert(student);
    }
}