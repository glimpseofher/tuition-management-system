// ======================= BOOKING MANAGEMENT =======================

string dateconv()
{
    int date, day, month, year;

    while (true)
    {
        cout << "Enter a date (DD/MM/YYYY): " << endl;
        cin >> day >> month >> year;
        if (year < 2026 || year > 2099 || month <= 0 || month > 12 || day <= 0 || day > 31)
        {
            cout << "I  " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else
        {
            break;
        }
        break;
    }
    date = (year * 10000) + (month * 100) + day;
    string sdate = to_string(date);
    return sdate;
}

void createBooking()
{
    if (studentCount == 0 && serviceCount == 0)
    {
        cout << "You Must Have At Least One Student And One Service Before Booking!\n";
        return;
    }

    if (studentCount == 0 || serviceCount == 0)
    {
        cout << "You must have at least one more student Or service before making a booking";
        return;
    }

    if (bookingCount >= MAX_RECORDS)
    {
        cout << "Booking storage is full,Please try to delete or change booking details!" << endl;
        return;
    }
    Booking booking;
    string StudentId, ServiceId;
    cout << "Enter Booking ID: ";
    cin >> booking.id;
    if (IDexists(bookings, bookingCount, booking.id))
    {
        cout << "Duplicate Booking ID Detected!" << endl;
        return;
    }
    else
    {
        cout << "Booking ID accepted!" << endl << endl;
    }

    cout << "Enter Student ID: ";
    cin >> booking.studentID;
    if (IDexists(students, studentCount, booking.studentID))
    {
        cout << "Student ID accepted!" << endl << endl;
    }
    else
    {
        cout << "Student ID Not Found" << endl;
        return;
    }
    cout << "Enter Service ID: ";
    cin >> booking.serviceID;
    if (IDexists(services, serviceCount, booking.serviceID))
    {
        cout << "Service ID accepted!" << endl;
    }
    else
    {
        cout << "Service ID Not found!" << endl;
        return;
    }

    Booking stuff;
    booking.date = dateconv();
    bookings[bookingCount++] = booking;
    cout << "Booking succesfully created!" << endl;

}

void displayBookings()
{

    cout << endl << "===============================================" << endl;
    cout << right << setw(30) << "BOOKING MODULE";
    cout << endl << "===============================================" << endl;
    for (int i = 0; i < bookingCount; ++i)
    {
        cout << left << "Index" << setw(5) << "|Student Name" << setw(30) << right << "|Service Name" << setw(28) << "|Date" << endl;
        cout << left << setw(5) << bookings[i].id << "|" << setw(29) << getNameByID(students, studentCount, bookings[i].studentID) << "|"
            << setw(35) << getNameByID(services, serviceCount, bookings[i].serviceID) << "|" << bookings[i].date << endl;
        cout << "===============================================" << endl;

    }

}

void updateBooking()
{
    string changeID;
    cout << "Enter Booking ID to update: "; getline(cin, changeID);
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].id == changeID)
        {
            cout << "Enter changed Student's ID: ";
            getline(cin, bookings[i].studentID);
            cout << "Enter a changed Service ID: ";
            getline(cin, bookings[i].serviceID);
            bookings[i].date = dateconv();
            cout << "Booking succesfully updated!" << endl;
            return;
        }
        else
        {
            cout << "Booking records not found!" << endl;
            return;
        }
    }
}

void searchBooking()
{
    if (bookingCount == 0)
    {
        cout << "No bookings available to search!\n";
        return;
    }
    Booking booking;
    cout << "Enter Booking ID to search: ";
    cin >> booking.id;

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].id == booking.id)
        {
            cout << endl << "===============================================" << endl;
            cout << setw(35) << right << "Booking found";
            cout << endl << "===============================================" << endl;
            cout << "Booking ID : " << bookings[i].id << endl;
            cout << "Student    : " << getNameByID(students, studentCount, bookings[i].studentID)
                << " (ID: " << bookings[i].studentID << ")" << endl;
            cout << "Service    : " << getNameByID(services, serviceCount, bookings[i].serviceID)
                << " (ID: " << bookings[i].serviceID << ")" << endl;
            cout << "Date       : " << bookings[i].date << endl;
            return;
        }
        else
        {
            break;
        }
    }
}

void deleteBooking()
{
    string id;
    char confirmation;
    cout << "Enter Booking ID to delete: ";
    getline(cin, id);
    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].id == id)
        {
            cout << "Are you sure to delete this booking?(Y/N):";
            cin >> confirmation;
            switch (confirmation)
            {
                case 'y':
                case 'Y':
                {
                    for (int j = i; j < bookingCount - 1; j++)
                    {
                        bookings[j] = bookings[j + 1];  
                    }
                    bookingCount--;
                        cout << "Booking deleted!" << endl;
                        return;
                }
                case 'N':
                case'n':
                {
                    cout << "Action canceled!" << endl;
                    return;
                }
                default:
                {
                    cout << "invalid character detected,Try Again" << endl;
                    return;
                }
            }

        }
    }    cout << "Booking ID not found!" << endl;

}
