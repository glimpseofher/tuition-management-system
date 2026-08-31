#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

// ====== Global Data ======
const int MAX_RECORDS = 100;

struct Student {
    string id;
    string name;
    int age = 0;
};

struct Service {
    string id;
    string name;
    double price = 0.0;
};

struct Booking {
    string id;
    string studentID;
    string serviceID;
    string date;
};

enum attendanceStatus { ABSENT, PRESENT };

struct Attendance {
    string id;
    string studentID;
    string serviceID;
    string date;
    attendanceStatus status = ABSENT;
};

Student students[MAX_RECORDS];
Service services[MAX_RECORDS];
Booking bookings[MAX_RECORDS];
Attendance attendances[MAX_RECORDS];

int studentCount = 0;
int serviceCount = 0;
int bookingCount = 0;
int attendanceCount = 0;

// ====== Function Declarations ======
int getIntInput(string prompt);
bool IDexists(Student records[], int count, string id);
bool IDexists(Service records[], int count, string id);
bool IDexists(Booking records[], int count, string id);
bool IDexists(Attendance records[], int count, string id);

string getNameByID(Student records[], int count, string id);
string getNameByID(Service records[], int count, string id);

void addStudent();
void searchStudent();
void updateStudent();
void displayStudents();
void deleteStudent();

void addService();
void displayServices();
void updateService();
void deleteService();

void createBooking();
void displayBookings();
void updateBooking();
void deleteBooking();

void markAttendance();
void displayAttendance();
void updateAttendance();
void deleteAttendance();

void summaryReport();
void detailedReport();
void statisticsReport();
void sortRecord();

void studentMenu();
void serviceMenu();
void bookingMenu();
void attendanceMenu();
void reportMenu();
void mainMenu();

// ======================= MAIN FUNCTION =======================
int main() {
    mainMenu();
    return 0;
}

// ====== Function Definitions ======
// ======================= VALIDATION =======================
int getIntInput(string prompt) {
    int choice;
    while (true) {
        cout << prompt;
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        else {
            cout << "Invalid input! Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

bool IDexists(Student records[], int count, string id) {
    for (int i = 0; i < count; i++) {
        if (records[i].id == id) return true;
    }
    return false;
}

bool IDexists(Service records[], int count, string id) {
    for (int i = 0; i < count; i++) {
        if (records[i].id == id) return true;
    }
    return false;
}

bool IDexists(Booking records[], int count, string id) {
    for (int i = 0; i < count; i++) {
        if (records[i].id == id) return true;
    }
    return false;
}

bool IDexists(Attendance records[], int count, string id) {
    for (int i = 0; i < count; i++) {
        if (records[i].id == id) return true;
    }
    return false;
}

// ======================= HELPER FUNCTION =======================

string getNameByID(Student records[], int count, string id) {
    for (int i = 0; i < count; i++) {
        if (records[i].id == id) return records[i].name;
    }
    return "Name NOT FOUND!";
}

string getNameByID(Service records[], int count, string id) {
    for (int i = 0; i < count; i++) {
        if (records[i].id == id) return records[i].name;
    }
    return "Name NOT FOUND!";
}

// ======================= USER MANAGEMENT =======================
void addStudent() {
    if (studentCount >= MAX_RECORDS) {
        cout << "Storage full!\n";
        return;
    }
    string id, name;
    int age;
    cout << "Enter Student ID: "; getline(cin, id);
    if (IDexists(students, studentCount, id)) {
        cout << "Duplicate ID!\n";
        return;
    }
    cout << "Enter Name: "; getline(cin, name);
    age = getIntInput("Enter Age: ");
    students[studentCount++] = { id, name, age };
    cout << "Student added!\n";
}

void displayStudents() {
    cout << "\n--- Student Records ---\n";
    for (int i = 0; i < studentCount; i++) {
        cout << students[i].id << " | " << students[i].name << " | " << students[i].age << endl;
    }
}

void updateStudent() {
    string id;
    cout << "Enter Student ID to update: "; getline(cin, id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "Enter new name: "; getline(cin, students[i].name);
            students[i].age = getIntInput("Enter new age: ");
            cout << "Student updated!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

void deleteStudent() {
    string id;
    cout << "Enter Student ID to delete: "; getline(cin, id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Student deleted!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

// ======================= SERVICE MANAGEMENT =======================
void addService() {
    if (studentCount == 0) {
        cout << "You must add at least one student before adding services!\n";
        return;
    }
    string id, name;
    double price;
    cout << "Enter Service ID: "; getline(cin, id);
    if (IDexists(services, serviceCount, id)) {
        cout << "Duplicate Service ID!\n";
        return;
    }
    cout << "Enter Service Name: "; getline(cin, name);
    cout << "Enter Price: "; cin >> price;
    services[serviceCount++] = { id, name, price };
    cout << "Service added!\n";
}

void displayServices() {
    cout << "\n--- Services ---\n";
    for (int i = 0; i < serviceCount; i++) {
        cout << services[i].id << " | " << services[i].name << " | RM" << fixed << setprecision(2) << services[i].price << endl;
    }
}

void updateService() {
    string id;
    cout << "Enter Service ID to update: "; getline(cin, id);
    for (int i = 0; i < serviceCount; i++) {
        if (services[i].id == id) {
            cout << "Enter new name: "; getline(cin, services[i].name);
            cout << "Enter new price: "; cin >> services[i].price;
            cout << "Service updated!\n";
            return;
        }
    }
    cout << "Service not found!\n";
}

void deleteService() {
    string id;
    cout << "Enter Service ID to delete: "; getline(cin, id);
    for (int i = 0; i < serviceCount; i++) {
        if (services[i].id == id) {
            for (int j = i; j < serviceCount - 1; j++) {
                services[j] = services[j + 1];
            }
            serviceCount--;
            cout << "Service deleted!\n";
            return;
        }
    }
    cout << "Service not found!\n";
}

// ======================= BOOKING MANAGEMENT =======================
void createBooking() {
    if (studentCount == 0 || serviceCount == 0) {
        cout << "You must have at least one student AND one service before booking!\n";
        return;
    }
    string bID, sID, svID, date;
    cout << "Enter Booking ID: "; getline(cin, bID);
    if (IDexists(bookings, bookingCount, bID)) {
        cout << "Duplicate Booking ID!\n";
        return;
    }
    cout << "Enter Student ID: "; getline(cin, sID);
    if (!IDexists(students, studentCount, sID)) {
        cout << "Student NOT FOUND!\n";
        return;
    }
    cout << "Enter Service ID: "; getline(cin, svID);
    if (!IDexists(services, serviceCount, svID)) {
        cout << "Service NOT FOUND!\n";
        return;
    }
    cout << "Enter Date (DD/MM/YYYY): "; getline(cin, date);
    bookings[bookingCount++] = { bID, sID, svID, date };
    cout << "Booking created!\n";
}

void displayBookings() {
    cout << "\n--- Bookings ---\n";
    for (int i = 0; i < bookingCount; i++) {
        cout << bookings[i].id << " | "
            << getNameByID(students, studentCount, bookings[i].studentID) << " | "
            << getNameByID(services, serviceCount, bookings[i].serviceID) << " | "
            << bookings[i].date << endl;
    }
}

void updateBooking() {
    string id;
    cout << "Enter Booking ID to update: "; getline(cin, id);
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].id == id) {
            cout << "Enter new Student ID: "; getline(cin, bookings[i].studentID);
            cout << "Enter new Service ID: "; getline(cin, bookings[i].serviceID);
            cout << "Enter new Date: "; getline(cin, bookings[i].date);
            cout << "Booking updated!\n";
            return;
        }
    }
    cout << "Booking not found!\n";
}

void deleteBooking() {
    string id;
    cout << "Enter Booking ID to delete: "; getline(cin, id);
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].id == id) {
            for (int j = i; j < bookingCount - 1; j++) {
                bookings[j] = bookings[j + 1];
            }
            bookingCount--;
            cout << "Booking deleted!\n";
            return;
        }
    }
    cout << "Booking not found!\n";
}

// ======================= ATTENDANCE MANAGEMENT =======================
void markAttendance() {
    string ID, sID, svID, date;
    cout << "Enter Attendance ID: "; getline(cin, ID);
    while (IDexists(attendances, attendanceCount, ID)) {
        cout << "Duplicate attendance ID found! Please enter again: "; getline(cin, ID);
    }
    cout << "Enter Student ID: "; getline(cin, sID);
    while (!IDexists(students, studentCount, sID)) {
        cout << "Student NOT FOUND! Please enter again: "; getline(cin, sID);
    }
    cout << "Enter Service ID: "; getline(cin, svID);
    while (!IDexists(services, serviceCount, svID)) {
        cout << "Service NOT FOUND! Please enter again: "; getline(cin, svID);
    }
    cout << "Enter Attendance Date: "; getline(cin, date);
    int status = getIntInput("Enter Attendance Status: \n0: Absent \n1: Present \n> ");
    while (status != 0 && status != 1) {
        status = getIntInput("Invalid Attendance Status! Please enter again: ");
    }
    attendances[attendanceCount++] = { ID, sID, svID, date, static_cast<attendanceStatus>(status) };
    cout << "Attendance Created!\n";
}

void displayAttendance() {
    cout << "======== Attendance ========\n";
    for (int i = 0; i < attendanceCount; i++) {
        cout << left
            << setw(6) << attendances[i].id << "|"
            << setw(40) << getNameByID(students, studentCount, attendances[i].studentID) << "|"
            << setw(40) << getNameByID(services, serviceCount, attendances[i].serviceID) << "|"
            << setw(14) << attendances[i].date << "|"
            << setw(10) << ((attendances[i].status == PRESENT) ? "Present" : "Absent") << "\n";
    }
}

void updateAttendance() {
    string id;
    cout << "Enter Attendance ID to update: "; getline(cin, id);
    for (int i = 0; i < attendanceCount; i++) {
        if (attendances[i].id == id) {
            cout << "Enter new Student ID: "; getline(cin, attendances[i].studentID);
            while (!IDexists(students, studentCount, attendances[i].studentID)) {
                cout << "Student NOT FOUND! Please enter again: "; getline(cin, attendances[i].studentID);
            }
            cout << "Enter new Service ID: "; getline(cin, attendances[i].serviceID);
            while (!IDexists(services, serviceCount, attendances[i].serviceID)) {
                cout << "Service NOT FOUND! Please enter again: "; getline(cin, attendances[i].serviceID);
            }
            cout << "Enter new Date: "; getline(cin, attendances[i].date);
            int status = getIntInput("Enter new Attendance Status: \n0: Absent \n1: Present \n> ");
            while (status != 0 && status != 1) {
                status = getIntInput("Invalid Attendance Status! Please enter again: ");
            }
            attendances[i].status = static_cast<attendanceStatus>(status);
            cout << "Attendance has updated!\n";
            return;
        }
    }
    cout << "Attendance not found!\n";
}

void deleteAttendance() {
    string id;
    cout << "Enter Attendance ID to delete: "; getline(cin, id);
    for (int i = 0; i < attendanceCount; i++) {
        if (attendances[i].id == id) {
            for (int j = i; j < attendanceCount - 1; j++) {
                attendances[j] = attendances[j + 1];
            }
            attendanceCount--;
            cout << "Attendance deleted!\n";
            return;
        }
    }
    cout << "Attendance NOT FOUND!\n";
}
// ======================= REPORT MODULE =======================
string getServiceNameByID(const string& serviceID) {
    for (int i = 0; i < serviceCount; i++) {
        if (services[i].id == serviceID) {
            return services[i].name;
        }
    }
    return "Service not found.";
}

double getServicePriceByID(const string& serviceID) {
    for (int i = 0; i < serviceCount; i++) {
        if (services[i].id == serviceID) {
            return services[i].price;
        }
    }
    return 0.0;
}

void summaryReport() {
    if (studentCount == 0) {
        cout << "\nNo student records available to display in summary.\n" << endl;
        return;
    }
    cout << "\n=======================================================================\n";
    cout << "                            SUMMARY REPORT                             \n";
    cout << "=======================================================================\n";
    cout << left << setw(12) << "Student ID"
        << setw(20) << "Student Name"
        << setw(14) << "Booking ID"
        << setw(14) << "Service ID"
        << setw(10) << "Price (RM)" << "\n";
    cout << "-----------------------------------------------------------------------\n";
    double totalValue = 0.0;
    int totalBookingsCount = 0;
    for (int i = 0; i < studentCount; i++) {
        bool hasBooking = false;

        // Search for all bookings belonging to this student
        for (int j = 0; j < bookingCount; j++) {
            if (bookings[j].studentID == students[i].id) {
                hasBooking = true;
                totalBookingsCount++;
                double price = getServicePriceByID(bookings[j].serviceID);
                totalValue += price;

                cout << left << setw(12) << students[i].id
                     << setw(20) << students[i].name
                     << setw(14) << bookings[j].id
                     << setw(14) << bookings[j].serviceID
                     << fixed << setprecision(2) << price << endl;
            }
        }
        // Display students who do not have any bookings recorded
        if (!hasBooking) {
            cout << left << setw(12) << students[i].id
                << setw(20) << students[i].name
                << setw(14) << "N/A"
                << setw(14) << "No Bookings"
                << fixed << setprecision(2) << 0.00 << endl;
        }
    }
    cout << "-----------------------------------------------------------------------\n";
    cout << "Total Students Listed: " << studentCount << endl;
    cout << "Total Active Bookings: " << totalBookingsCount << endl;
    cout << "Total Revenue Expected: RM " << fixed << setprecision(2) << totalValue << endl;
    cout << "=======================================================================\n\n";
}

void detailedReport() {
    if (studentCount == 0) {
        cout << "\nNo student records available.\n" << endl;
        return;
    }
    cout << "\n=======================================================================\n";
    cout << "                          DETAILED STUDENT REPORT                      \n";
    cout << "=======================================================================\n";
    for (int i = 0; i < studentCount; i++) {
        cout << "STUDENT PROFILE #" << (i + 1) << "\n";
        cout << "  ID   : " << students[i].id << "\n";
        cout << "  Name : " << students[i].name << "\n";
        cout << "  Age  : " << students[i].age << "\n";
        cout << "  -- Bookings & Attendance History --\n";
        bool hasBookings = false;
        double studentTotalSpent = 0.0;
        for (int j = 0; j < bookingCount; j++) {
            if (bookings[j].studentID == students[i].id) {
                hasBookings = true;
                string sName = getServiceNameByID(bookings[j].serviceID);
                double price = getServicePriceByID(bookings[j].serviceID);
                studentTotalSpent += price;
                // Find matching attendance record status
                string statusStr = "Not Marked";
                for (int k = 0; k < attendanceCount; k++) {
                    if (attendances[k].studentID == students[i].id &&
                        attendances[k].serviceID == bookings[j].serviceID &&
                        attendances[k].date == bookings[j].date) {
                        statusStr = (attendances[k].status == 1 || attendances[k].status == PRESENT) ? "Present" : "Absent";
                        break;
                    }
                }
                cout << "     * Booking ID: " << bookings[j].id
                    << " | Service: " << sName
                    << " (RM " << fixed << setprecision(2) << price << ")"
                    << " | Date: " << bookings[j].date
                    << " | Status: " << statusStr << "\n";
            }
        }
        if (!hasBookings) {
            cout << "     (No active bookings found for this student)\n";
        }
        else {
            cout << "  Total Spent: RM " << fixed << setprecision(2) << studentTotalSpent << "\n";
        }
        cout << "-----------------------------------------------------------------------\n";
    }
    cout << "=======================================================================\n\n";
}

void statisticsReport() {
    cout << "\n=======================================================================\n";
    cout << "                             STATISTICS REPORT                         \n";
    cout << "=======================================================================\n";
    cout << left << setw(35) << "Total Enrolled Students" << ": " << studentCount << endl;
    cout << left << setw(35) << "Total Available Services" << ": " << serviceCount << endl;
    cout << left << setw(35) << "Total Bookings Recorded" << ": " << bookingCount << endl;

    // Revenue calculation
    double totalExpectedRevenue = 0.0;
    for (int i = 0; i < bookingCount; i++) {
        totalExpectedRevenue += getServicePriceByID(bookings[i].serviceID);
    }

    double avgBookingValue = (bookingCount > 0) ? (totalExpectedRevenue / bookingCount) : 0.0;//returns 0 if booking is less than/is zero
    cout << left << setw(35) << "Total Expected Revenue" << ": RM " << fixed << setprecision(2) << totalExpectedRevenue << endl;
    cout << left << setw(35) << "Average Value Per Booking" << ": RM " << fixed << setprecision(2) << avgBookingValue << endl;

    // Attendance stats calculation
    int presentCount = 0;
    int absentCount = 0;
    for (int i = 0; i < attendanceCount; i++) {
        if (attendances[i].status == 1 || attendances[i].status == PRESENT) {
            presentCount++;
        }
        else {
            absentCount++;
        }
    }

    double attendanceRate = (attendanceCount > 0) ? ((double)presentCount / attendanceCount) * 100.0 : 0.0; 

    cout << "-----------------------------------------------------------------------\n";
    cout << "ATTENDANCE METRICS:\n";
    cout << "  - Total Records Processed : " << attendanceCount << endl;
    cout << "  - Present Sessions        : " << presentCount << endl;
    cout << "  - Absent Sessions         : " << absentCount << endl;
    cout << "  - Overall Attendance Rate : " << fixed << setprecision(1) << attendanceRate << "%\n";
    cout << "=======================================================================\n\n";
}

void sortRecord() {
    if (studentCount <= 1) {
        cout << "\nNot enough records to sort.\n" << endl;
        return;
    }
    int choice = getIntInput("1.Sort by name \n2.Sort by ID\n Enter choice: ");
    switch (choice) {


        case 1: {
            // Bubble sort algorithm sorting students by name
            for (int i = 0; i < studentCount - 1; i++) {
                for (int j = 0; j < studentCount - i - 1; j++) {
                    if (students[j].name > students[j + 1].name) {
                        // Swap student objects
                        Student temp = students[j];
                        students[j] = students[j + 1];
                        students[j + 1] = temp;
                    }
                }
            }
            cout << "\nStudent records sorted successfully by Name (A-Z)!\n" << endl;
            break;
        }

        case 2: {
            // Selection Sort algorithm for student id
            for (int i = 0; i < studentCount - 1; i++) {
                int small = i; 

                //find
                for (int j = i + 1; j < studentCount; j++) {
                    if (students[j].id < students[small].id) {
                        small = j;
                    }
                }

                //swap
                if (small != i) {
                    Student temp = students[small];
                    students[small] = students[i];
                    students[i] = temp;
                }
            }

            cout << "\nStudent records sorted successfully by Name!\n" << endl;
            break;
        }
        default:
            cout << "\nInvalid input, please try again.\n" << endl; return;
        }
    }

// ======================= SAVE & LOAD DATA =======================
void saveData() {
    ofstream myFile("data.txt");
    myFile << studentCount << endl;
    for (int i = 0; i < studentCount; i++) {
        myFile << students[i].id << '|' << students[i].name << '|' << students[i].age << '|' << endl;
    }
    myFile << serviceCount << endl;
    for (int i = 0; i < serviceCount; i++) {
        myFile << services[i].id << '|' << services[i].name << '|' << services[i].price << '|' << endl;
    }
    myFile << bookingCount << endl;
    for (int i = 0; i < bookingCount; i++) {
        myFile << bookings[i].id << '|' << bookings[i].studentID << '|' << bookings[i].serviceID << '|' << bookings[i].date << '|' << endl;
    }
    myFile << attendanceCount << endl;
    for (int i = 0; i < attendanceCount; i++) {
        myFile << attendances[i].id << '|' << attendances[i].studentID << '|' << attendances[i].serviceID << '|' << attendances[i].date << '|' << attendances[i].status << '|' << endl;
    }
    myFile.close();
    cout << "Data has saved succesfully!\n" << endl;
}

void loadData() {
    string line;
    ifstream myFile("data.txt");
    if (!myFile) {
        cout << "File NOT exist! Please save some data first!\n" << endl;
        return;
    }
    getline(myFile, line);
    studentCount = stoi(line);
    for (int i = 0; i < studentCount; i++) {
        string id, name, ageStr;
        getline(myFile, line);
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, ageStr, '|');
        students[i] = { id, name, stoi(ageStr) };
    }
    getline(myFile, line);
    serviceCount = stoi(line);
    for (int i = 0; i < serviceCount; i++) {
        string id, name, priceStr;
        getline(myFile, line);
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, priceStr, '|');
        services[i] = { id, name, stod(priceStr) };
    }
    getline(myFile, line);
    bookingCount = stoi(line);
    for (int i = 0; i < bookingCount; i++) {
        string id, studentID, serviceID, date;
        getline(myFile, line);
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, studentID, '|');
        getline(ss, serviceID, '|');
        getline(ss, date, '|');
        bookings[i] = { id, studentID, serviceID, date };
    }
    getline(myFile, line);
    attendanceCount = stoi(line);
    for (int i = 0; i < attendanceCount; i++) {
        string id, studentID, serviceID, date, statusStr;
        getline(myFile, line);
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, studentID, '|');
        getline(ss, serviceID, '|');
        getline(ss, date, '|');
        getline(ss, statusStr, '|');
        attendances[i] = { id, studentID, serviceID, date, static_cast<attendanceStatus>(stoi(statusStr)) };
    }
    myFile.close();
    cout << "Data has loaded succesfully!\n" << endl;
}



// ======================= MENUS =======================
void studentMenu() {
    int choice;
    do {
        cout << "\n--- Student Management ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Back to Main Menu\n";
        choice = getIntInput("Enter choice: ");
        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayStudents(); break;
        case 3: updateStudent(); break;
        case 4: deleteStudent(); break;
        case 5: break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

void serviceMenu() {
    int choice;
    do {
        cout << "\n--- Service Management ---\n";
        cout << "1. Add Service\n";
        cout << "2. Display Services\n";
        cout << "3. Update Service\n";
        cout << "4. Delete Service\n";
        cout << "5. Back to Main Menu\n";
        choice = getIntInput("Enter choice: ");
        switch (choice) {
        case 1: addService(); break;
        case 2: displayServices(); break;
        case 3: updateService(); break;
        case 4: deleteService(); break;
        case 5: break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

void bookingMenu() {
    int choice;
    do {
        cout << "\n--- Booking Management ---\n";
        cout << "1. Create Booking\n";
        cout << "2. Display Bookings\n";
        cout << "3. Update Booking\n";
        cout << "4. Delete Booking\n";
        cout << "5. Back to Main Menu\n";
        choice = getIntInput("Enter choice: ");
        switch (choice) {
        case 1: createBooking(); break;
        case 2: displayBookings(); break;
        case 3: updateBooking(); break;
        case 4: deleteBooking(); break;
        case 5: break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

void reportMenu() {
    int choice;
    do {
        cout << "\n--- Report Generation ---\n";
        cout << "1. Generate Summary Report\n";
        cout << "2. Generate Detailed Report\n";
        cout << "3. Generate Statistics\n";
        cout << "4. Sort Records\n";
        cout << "5. Back to Main Menu\n";
        choice = getIntInput("Enter choice: ");
        switch (choice) {
        case 1: summaryReport(); break;
        case 2: detailedReport(); break;
        case 3: statisticsReport(); break;
        case 4: sortRecord(); break;
        case 5: break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}


void attendanceMenu() {
    int choice;
    do {
        cout << "\n--- Attendance Management ---\n";
        cout << "1. Mark Attendance\n";
        cout << "2. Display Attendance\n";
        cout << "3. Update Attendance\n";
        cout << "4. Delete Attendance\n";
        cout << "5. Back to Main Menu\n";
        choice = getIntInput("Enter choice: ");
        switch (choice) {
        case 1: markAttendance(); break;
        case 2: displayAttendance(); break;
        case 3: updateAttendance(); break;
        case 4: deleteAttendance(); break;
        case 5: break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

// ======================= MAIN MENU =======================
void mainMenu() {
    int choice;
    do {
        cout << "\n===== Tuition Centre Management System =====\n";
        cout << "1. Student Management\n";
        cout << "2. Service Management\n";
        cout << "3. Booking Management\n";
        cout << "4. Attendance Management\n";
        cout << "5. Report Generation\n";
        cout << "6. Save Data\n";
        cout << "7. Load Data\n";   
        cout << "0. Exit\n";
        choice = getIntInput("Enter choice: ");
        switch (choice) {
        case 1: studentMenu(); break;
        case 2: serviceMenu(); break;
        case 3: bookingMenu(); break;
        case 4: attendanceMenu(); break;
        case 5: reportMenu(); break;
        case 6: saveData(); break;
        case 7: loadData(); break;
        case 0: cout << "Exiting program...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}
