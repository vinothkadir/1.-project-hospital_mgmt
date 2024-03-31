#include <iostream>
#include <vector>
#include <string>
#include <chrono>

class Person {
protected:
    std::string name;
    int age;
    char gender;
    std::string contact_info;
public:
    Person(std::string name, int age, char gender, std::string contact_info)
        : name(name), age(age), gender(gender), contact_info(contact_info) {}

    virtual void get_info() = 0;
};

class Patient : public Person {
private:
    int patient_id;
    std::vector<std::string> medical_history;
public:
    Patient(int patient_id, std::string name, int age, char gender, std::string contact_info)
        : Person(name, age, gender, contact_info), patient_id(patient_id) {}

    void add_medical_history(std::string history) {
        medical_history.push_back(history);
    }

    void get_info() override {
        std::cout << "patient id: " << patient_id << ", name: " << name << ", age: " << age << ", gender: " << gender << std::endl;
    }
};

class Doctor : public Person {
private:
    int doctor_id;
    std::string specialization;
    std::vector<std::pair<Patient*, std::chrono::system_clock::time_point>> appointments;
public:
    Doctor(int doctor_id, std::string name, int age, char gender, std::string contact_info, std::string specialization)
        : Person(name, age, gender, contact_info), doctor_id(doctor_id), specialization(specialization) {}

    void schedule_appointment(Patient* patient) {
        appointments.emplace_back(patient, std::chrono::system_clock::now());
    }

    void get_info() override {
        std::cout << "doctor id: " << doctor_id << ", name: " << name << ", age: " << age << ", Gender: " << gender << ", Specialization: " << specialization << std::endl;
    }
};

class Hospital {
private:
    std::string hospital_name;
    std::vector<Patient*> patients;
    std::vector<Doctor*> doctors;
public:
    Hospital(std::string hospital_name) : hospital_name(hospital_name) {}

    void admit_patient(Patient* patient) {
        patients.push_back(patient);
    }

    void assign_doctor(Doctor* doctor, Patient* patient) {
        doctor->schedule_appointment(patient);
    }

    void list_patients() {
        std::cout << "\npatients in the hospital:" << std::endl;
        for (auto patient : patients) {
            patient->get_info();
        }
    }

    void list_doctors() {
        std::cout << "\ndoctors in the hospital:" << std::endl;
        for (auto doctor : doctors) {
            doctor->get_info();
        }
    }
};

int main() {
    Hospital hospital("city Hospital");

    Patient patient1(1, "a", 30, 'F', "a.com");
    Patient patient2(2, "b", 45, 'M', "b.com");
    Doctor doctor1(3, "x_doctor", 40, 'M', "x.com", "Heart Department");
    Doctor doctor2(102, "z_doctor", 35, 'F', "z.com", "Brain Department");

    hospital.admit_patient(&patient1);
    hospital.admit_patient(&patient2);

    hospital.list_patients();
    hospital.list_doctors();

    return 0;
}
