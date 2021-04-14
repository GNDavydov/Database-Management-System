// Copyright 2021 GNDavydov

#include "db_overall_plan.h"

size_t DBOverallPlan::getSubjectId(const std::string &subject) {
    const std::string pathToFile2 = path_ + config::separator + nameOpenDB_ + config::separator + fileName2_;
    std::fstream file(pathToFile2, std::ios::binary | std::ios::in);
    size_t len;
    size_t id = 0;

    file.read((char *) &len, sizeof(size_t));

    for (size_t i = 0; i < len; ++i) {
        std::string name;
        size_t sem;

        file.read((char *) &id, sizeof(size_t));
        file.read((char *) &sem, sizeof(size_t));
        std::getline(file, name, '\0');

        if (name == subject) {
            break;
        }
    }

    file.close();

    return id;
}

std::pair<size_t, std::string> DBOverallPlan::getSubjectName(const size_t id) {
    const std::string pathToFile2 = path_ + config::separator + nameOpenDB_ + config::separator + fileName2_;
    std::fstream file(pathToFile2, std::ios::binary | std::ios::in);
    size_t len;
    size_t sem;
    std::string name;

    file.read((char *) &len, sizeof(size_t));

    for (size_t i = 0; i < len; ++i) {
        size_t id_;

        file.read((char *) &id_, sizeof(size_t));
        file.read((char *) &sem, sizeof(size_t));
        std::getline(file, name, '\0');

        if (id_ == id) {
            break;
        }
    }

    file.close();

    return std::pair(sem, name);
}

DBOverallPlan::DBOverallPlan() {
    try {
        fs::create_directory(path_);
    }
    catch (fs::filesystem_error) {
        fs::create_directory(config::currentPath + config::separator + config::DirectoryDB);
        fs::create_directory(path_);
    }
}

void DBOverallPlan::createDB(const std::string &name, const std::multimap<std::string, size_t> &disciplines) {
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
        fileDis.write((char *) &subject.second, sizeof(size_t));
        fileDis << subject.first << std::ends;
        ++id;
    }
    fileDis.close();

    std::ofstream(DBName + config::separator + fileName3_, std::ios::binary);
}

void DBOverallPlan::renameDB(const std::string &oldName, const std::string &newName) {
    const fs::path oldPath = path_ + config::separator + oldName;
    const fs::path newPath = path_ + config::separator + newName;

    try {
        fs::rename(oldPath, newPath);
    }
    catch (fs::filesystem_error &e) {
        std::cout << e.what() << std::endl;
    }
}

void DBOverallPlan::printBD() {
    for (auto &temp: fs::recursive_directory_iterator(path_)) {
        if (temp.is_directory()) {
            std::cout << temp.path() << std::endl;
        }
    }
}

void DBOverallPlan::deleteDB(const std::string &name) {
    const std::string DBName = path_ + config::separator + name;
    fs::remove_all(DBName);
}

void DBOverallPlan::open(const std::string &name) {
    if (fs::is_directory(path_ + config::separator + name)) {
        nameOpenDB_ = name;
    }
    students_ = selectAll();
}

void DBOverallPlan::close() {
    nameOpenDB_ = "";
    students_.resize(0);
    students_.shrink_to_fit();
}

void DBOverallPlan::insert(const OverallPlan &student) {
    const std::string name = student.GetName();
    const std::string chair = student.GetChair();
    const size_t sem = student.GetSemester();
    const std::vector<semester> subjectsStudied = student.GetSubjects();

    for (size_t i = 0; i < students_.size(); ++i) {
        if (student.GetName() == students_[i].GetName()) {
            return;
        }
    }

    // write in vector
    students_.push_back(student);

    // write in Table Students
    const std::string pathToFile1 = path_ + config::separator + nameOpenDB_ + config::separator + fileName1_;
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

    // write in Union Table
    const std::string pathToFile3 = path_ + config::separator + nameOpenDB_ + config::separator + fileName3_;
    file.open(pathToFile3, std::ios::binary | std::ios::app);

    for (auto &semester : subjectsStudied) {
        for (auto &subject : semester.subjects) {
            size_t idSubject = getSubjectId(subject.first);
            size_t mark = subject.second;
            file.write((char *) &id, sizeof(size_t));
            file.write((char *) &idSubject, sizeof(size_t));
            file.write((char *) &mark, sizeof(size_t));
        }
    }

    file.close();
}

void DBOverallPlan::printRecords() {
    size_t id = 1;
    for (auto &student : students_) {
        std::cout << "Student " << id << std::endl;
        std::cout << "Name: " << student.GetName() << std::endl;
        std::cout << "Chair: " << student.GetChair() << std::endl;
        std::cout << "Semester: " << student.GetSemester() << std::endl;
        for (auto semester : student.GetSubjects()) {
            std::cout << "Semester of subject: " << semester.number << std::endl;
            for (auto subject : semester.subjects) {
                std::cout << "Subject: " << subject.first << ", mark: " << subject.second << std::endl;
            }
        }
        ++id;
        std::cout << std::endl;
    }
}

std::vector<OverallPlan> DBOverallPlan::selectAll() {
    const std::string pathToFile1 = path_ + config::separator + nameOpenDB_ + config::separator + fileName1_;
    const std::string pathToFile3 = path_ + config::separator + nameOpenDB_ + config::separator + fileName3_;
    std::fstream file;
    std::vector<OverallPlan> students; // Answer for this function
    std::map<size_t, OverallPlan> studentsWithId; // An array of students with their id in the table
    size_t len; // Len of files

    file.open(pathToFile1, std::ios::binary | std::ios::in);
    file.read((char *) &len, sizeof(size_t));

    // Fill in the array of students without specifying subjects and grades for them
    for (size_t i = 0; i < len; ++i) {
        size_t id;
        std::string name;
        std::string chair;
        size_t sem;

        file.read((char *) &id, sizeof(size_t));
        std::getline(file, name, '\0');
        std::getline(file, chair, '\0');
        file.read((char *) &sem, sizeof(size_t));

        OverallPlan s;
        s.SetName(name);
        s.SetChair(chair);
        s.SetSemester(sem);

        studentsWithId.insert({id, s});
    }
    file.close();

    // Supplement the map with an array of estimates and add it to the final vector
    for (auto &student : studentsWithId) {
        file.open(pathToFile3, std::ios::binary | std::ios::in);
        std::map<size_t, size_t> disciplines;
        std::vector<semester> subjectsStudied;

        while (true) {
            size_t id1;
            size_t id2;
            size_t mark;

            file.read((char *) &id1, sizeof(size_t));
            file.read((char *) &id2, sizeof(size_t));
            file.read((char *) &mark, sizeof(size_t));

            if (id1 == student.first) {
                disciplines.insert({id2, mark});
            }

            if (file.eof()) {
                break;
            }
        }

        subjectsStudied.resize(student.second.GetSemester());
        for (size_t i = 0; i < student.second.GetSemester(); ++i) {
            subjectsStudied[i].number = i + 1;
        }

        for (auto &discipline : disciplines) {
            std::pair<size_t, std::string> subject = getSubjectName(discipline.first);
            subjectsStudied[subject.first - 1].subjects.insert({subject.second, discipline.second});
        }

        student.second.SetSubjects(subjectsStudied);
        students.push_back(student.second);
        file.close();
    }

    return students;
}

std::vector<OverallPlan> DBOverallPlan::selectBySem(const size_t sem) {
    std::vector<OverallPlan> students;
    for (auto &student : students_) {
        if (student.GetSemester() == sem) {
            students.push_back(student);
        }
    }
    return students;
}

std::vector<OverallPlan> DBOverallPlan::selectByDis(const std::string &name) {
    std::vector<OverallPlan> students;
    for (auto &student : students_) {
        std::vector<semester> semesters = student.GetSubjects();
        for (auto &semester : semesters) {
            if (semester.subjects.find(name) != semester.subjects.end()) {
                students.push_back(student);
            }
        }
    }
    return students;
}

void DBOverallPlan::deleteAllStudents() {
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

void DBOverallPlan::deleteRecord(const std::string &name) {
    std::vector<OverallPlan> students = students_;
    deleteAllStudents();
    for (auto &student : students) {
        if (student.GetName() == name) {
            continue;
        }
        insert(student);
    }
}

void DBOverallPlan::editRecords(const std::string &name, const OverallPlan &other) {
    std::vector<OverallPlan> students = students_;
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
