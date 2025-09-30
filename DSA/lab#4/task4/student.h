#include<string>
using namespace std;

 class Student {
 private:
    int id;
    string name;
    double gpa;

 public:

     Student() {
         id = 0;
         name = "";
         gpa = 0.0;
     }

     Student(int id, string name, double gpa) {
         this->id = id;
         this->name = name;
         this->gpa = gpa;
     }
    bool operator<(const Student& other) const {
        if (gpa != other.gpa) return gpa < other.gpa;
        return id < other.id;
    }
    bool operator==( const Student& other)  const {
        return id == other.id && name == other.name && gpa == other.gpa;
    }

    friend ostream& operator<<(ostream& os, const Student& obj) 
    {
        os << "\n id= " << obj.id << "\t name=  " << obj.name << "\t gpa= "<<obj.gpa;
        return os;
    }

    

        
};

