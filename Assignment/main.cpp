//
//  main.cpp
//  Assignment
//
//  Created by Teodor on 09/01/2017.
//  Copyright © 2017 TeodorGarzdin. All rights reserved.
//

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Date {
public:
    unsigned int day;
    unsigned int month;
    unsigned int year;

    Date(const Date& d) {
        day = d.day;
        month = d.month;
        year = d.year;
    }
    
    Date(const unsigned int d = 0, const unsigned int m = 0, const unsigned int y = 0) {
        this->day = d;
        this->month = m;
        this->year = y;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, Date& date);
    
    int operator==(const Date& d) {
        return day == d.day && month == d.month && year == d.year;
    }
    
    Date& operator=(const Date& d) {
        if(this != &d) {
            day = d.day;
            month = d.month;
            year = d.year;
        }
        
        return *this;
    }
    
    unsigned int getDay() {
        return day;
    }
    
    void setDay(const unsigned int d) {
        if (d > 0) {
            day = d;
        } else {
            throw new std::invalid_argument("Day can't be negative");
        }
    }
    
    unsigned int getMonth() {
        return month;
    }
    
    void setMonth(const unsigned int m) {
        if (m > 0) {
            month= m;
        } else {
            throw new std::invalid_argument("Month can't be negative");
        }
    }
    
    unsigned int getYear() {
        return year;
    }
    
    void setYear(const unsigned int y) {
        if (y > 0) {
            year = y;
        }
        else {
            throw new std::invalid_argument("Year can't be negative");
        }
    }
    
    ~Date () {
        std::cout<<"Destructing <Date>"<<std::endl;
    }
};

class Student {
public:
    std::string name;
    std::string facNumber;
    Date birthDate;
    float avScore;
    
    Student() {}
    
    Student(std::string n, std::string fn, Date d, float s) {
        this->name = n;
        this->facNumber = fn;
        this->birthDate = d;
        this->avScore = s;
    }
    
    ~Student() {
        std::cout<<"Destructing <Student>"<<std::endl;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, Student& student);
    
    void setName(std::string n) { name = n; }
    
    std::string getName() { return name; }
    
    void setFacNumber(std::string id) { facNumber = id; }
    
    std::string getFacNumber() { return facNumber; }
    
    void setAvScore(float s) { avScore = s; }
    
    float getAvScore() { return avScore; }
    
    int showYears(Date date) {
        if (date.getMonth() > this->birthDate.getMonth()) {
            return (date.getYear() - this->birthDate.getYear());
        } else {
            if (date.getMonth() < this->birthDate.getMonth()) {
                return (date.getYear() - this->birthDate.getYear() - 1);
            } else {
                if (date.getDay() > this->birthDate.getDay()) {
                    return (date.getYear() - this->birthDate.getYear());
                } else {
                    return (date.getYear() - this->birthDate.getYear() - 1);
                }
            }
        }
    }
};

class StudentStream {
public:
    unsigned int number;
    std::vector<Student> students;
    
    StudentStream() {
        std::cout<<"Destructing <StudentStream>"<<std::endl;
    }
    
    StudentStream(int number, std::vector<Student> students) {
        this->number = number;
        this->students = students;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, StudentStream& ss);
    
    ~StudentStream() {
        std::cout<<"Destructing <StudentStream>"<<std::endl;
    }
    
    Student getStudentWithHighestGrade() {
        Student currentStudent;
        for(int i = 0; i <= this->students.size(); i++) {
            if(this->students[i].avScore > currentStudent.avScore) currentStudent = this->students[i];
        }
        return currentStudent;
    }
    
    int writeStudentsIntoFile() {
        if(sizeof(this->students) == 0) {
            std::cout<<"Students array is empty."<<std::endl;
            return 1;
        }
        
        std::ofstream textFile;
        textFile.open("students.txt");
        
        if(!textFile) {
            std::cout<<"Cannot open output file."<<std::endl;
            return 1;
        }
        
        for(unsigned int i=0; i<=sizeof(this->students); i++) {
            textFile<<this->students[i]<<std::endl;
        }
        
        textFile.close();
        
        return 0;
    }
};

std::ostream& operator<<(std::ostream& stream, Date& date) {
    return stream<<date.day<<"/"<<date.month<<"/"<<date.year<<std::endl;
}

std::ostream& operator<<(std::ostream& stream, Student& student) {
    return stream<<"Name: "<<student.name<<"Birth date: "<<student.birthDate<<"GPA: "<<student.avScore<<std::endl;
}

std::ostream& operator<<(std::ostream& stream, StudentStream& ss) {
    for(int i = 0; i <= ss.students.size(); i++) {
        if(ss.students[i].showYears(ss.students[i].birthDate) >= 18 && ss.students[i].showYears(ss.students[i].birthDate) <= 26) {
            stream<<ss.students[i].name;
        }
    }
    return stream<<std::endl;
}

int main (int argc, const char * argv[]) {
    std::vector<Student> students;
    students[0] = Student("Teodor", "5109238", Date(14, 8, 1995), 5.95);
    students[1] = Student("Julia", "5109237", Date(17, 11, 1995), 5.12);
    students[2] = Student("Georgi", "5109236", Date(5, 9, 1995), 4.49);
    StudentStream ss = StudentStream(1, students);
    ss.writeStudentsIntoFile();
    
    return 0;
}
