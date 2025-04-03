#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <ctime>
#include <map>
#include <cctype>
#include <cstring>
using namespace std;

// Define ROOM_RANGES as a static const outside the class
static const map<string, pair<int, int>> ROOM_RANGES = {
    {"Standard", {100, 120}},
    {"Double", {210, 250}},
    {"Family", {320, 335}},
    {"Grand Suite", {430, 440}},
    {"Superior Gold", {540, 550}}
};

class HOTEL {
private:
    int room_no;
    char name[30];       // Main guest name
    char phone[15];
    char email[50];
    int num_guests;
    long days;
    long cost;
    char rtype[20];
    time_t check_in_date;
    time_t check_out_date; // Actual check-out date, 0 if not checked out
    bool checked_out;
    char other_guests[100]; // Comma-separated list of additional guest names

    // In-memory database: map of room_no to HOTEL record
    static map<int, HOTEL> hotel_db;

public:
    HOTEL() : check_out_date(0), checked_out(false), num_guests(0) {
        other_guests[0] = '\0'; // Initialize as empty string
    }
    void main_menu();
    void check_in();
    void check_out();
    void display_guest();
    void available_rooms();
    bool is_room_available(int room);
    vector<int> get_available_rooms(const string& type);
    void wait_for_key();
};

// Define the static member outside the class
map<int, HOTEL> HOTEL::hotel_db;

void HOTEL::wait_for_key() {
    cout << "\n\tPress any key to continue...";
    cin.ignore(10000, '\n');
    cin.get();
}

void HOTEL::main_menu() {
    int choice = 0;
    while (choice != 5) {
        system("clear || cls");
        cout << "\n\t\t\t*************";
        cout << "\n\t\t\t* HOTEL DE RANCH *";
        cout << "\n\t\t\t* MAIN MENU *";
        cout << "\n\t\t\t*************";
        cout << "\n\n\t\t1. Check-In";
        cout << "\n\t\t2. Check-Out";
        cout << "\n\t\t3. View Guest Info";
        cout << "\n\t\t4. Available Rooms";
        cout << "\n\t\t5. Exit";
        cout << "\n\n\t\tEnter Your Choice: ";

        // Replace try-catch with a loop for valid input
        bool valid_input = false;
        while (!valid_input) {
            if (cin >> choice) {
                if (choice >= 1 && choice <= 5) {
                    valid_input = true;
                } else {
                    cout << "\t\tInvalid choice! Please enter a number between 1 and 5.\n";
                    cout << "\t\tEnter Your Choice: ";
                }
            } else {
                cout << "\t\tInvalid input! Please enter a number.\n";
                cout << "\t\tEnter Your Choice: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        switch (choice) {
            case 1: check_in(); break;
            case 2: check_out(); break;
            case 3: display_guest(); break;
            case 4: available_rooms(); break;
            case 5: return;
        }
    }
}

bool HOTEL::is_room_available(int room) {
    auto it = hotel_db.find(room);
    return (it == hotel_db.end() || it->second.checked_out);
}

vector<int> HOTEL::get_available_rooms(const string& type) {
    vector<int> available;
    auto range = ROOM_RANGES.at(type);

    for (int room = range.first; room <= range.second; room++) {
        if (is_room_available(room)) {
            available.push_back(room);
        }
    }
    return available;
}

void HOTEL::check_in() {
    system("clear || cls");
    int choice, selected_room;
    double price_per_night, total_cost, vat;
    int max_guests = 0;

    cout << "\n\tSelect Room Type:\n";
    cout << "\t1. Standard (100-120, Max 2 guests)\n";
    cout << "\t2. Double (210-250, Max 2 guests)\n";
    cout << "\t3. Family (320-335, Max 4 guests)\n";
    cout << "\t4. Grand Suite (430-440, Max 6 guests)\n";
    cout << "\t5. Superior Gold (540-550, Max 8 guests)\n";

    // Room type selection
    bool valid_choice = false;
    while (!valid_choice) {
        cout << "\n\tEnter Choice (1-5): ";
        if (cin >> choice && choice >= 1 && choice <= 5) {
            valid_choice = true;
        } else {
            cout << "\tInvalid choice! Please enter a number between 1-5.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    cin.ignore(10000, '\n');

    switch (choice) {
        case 1: strcpy(rtype, "Standard"); price_per_night = 50.0; max_guests = 2; break;
        case 2: strcpy(rtype, "Double"); price_per_night = 70.0; max_guests = 2; break;
        case 3: strcpy(rtype, "Family"); price_per_night = 100.0; max_guests = 4; break;
        case 4: strcpy(rtype, "Grand Suite"); price_per_night = 150.0; max_guests = 6; break;
        case 5: strcpy(rtype, "Superior Gold"); price_per_night = 200.0; max_guests = 8; break;
    }

    vector<int> available_rooms = get_available_rooms(rtype);
    if (available_rooms.empty()) {
        cout << "\n\tSorry, no " << rtype << " rooms available.";
        wait_for_key();
        return;
    }

    cout << "\n\tAvailable " << rtype << " Rooms:\n";
    for (int room : available_rooms) {
        cout << "\t- Room " << room << "\n";
    }

    // Room number selection
    bool valid_room = false;
    while (!valid_room) {
        cout << "\n\tEnter your preferred room number: ";
        if (cin >> selected_room) {
            for (int room : available_rooms) {
                if (room == selected_room) {
                    valid_room = true;
                    break;
                }
            }
            if (!valid_room) {
                cout << "\tSelected room is not available or invalid! Please choose from the list.\n";
            }
        } else {
            cout << "\tInvalid room number! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    cout << "\n\tRoom Type: " << rtype << "\n";
    cout << "\tPrice per Night: $" << fixed << setprecision(2) << price_per_night << "\n";

    // Number of guests
    bool valid_guests = false;
    while (!valid_guests) {
        cout << "\tHow many guests will be staying (max " << max_guests << ")? ";
        if (cin >> num_guests && num_guests > 0 && num_guests <= max_guests) {
            valid_guests = true;
        } else {
            cout << "\tNumber of guests must be between 1 and " << max_guests << "!\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    // Number of nights
    bool valid_days = false;
    while (!valid_days) {
        cout << "\tHow many nights will you stay? ";
        if (cin >> days && days > 0) {
            valid_days = true;
        } else {
            cout << "\tNumber of nights must be positive!\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    check_in_date = time(nullptr);
    check_out_date = 0;

    total_cost = price_per_night * days;
    vat = total_cost * 0.03;
    cost = static_cast<long>(total_cost + vat);

    cout << "\tSubtotal: $" << fixed << setprecision(2) << total_cost << "\n";
    cout << "\tVAT (3%): $" << vat << "\n";
    cout << "\tTotal Amount: $" << cost << "\n";

    cout << "\n\tEnter Guest Details:\n";
    cout << "\tPrimary Guest Name: ";
    cin.ignore();
    cin.getline(name, 30);

    // Reset other_guests
    other_guests[0] = '\0';

    // Prompt for additional guests if num_guests > 1
    if (num_guests > 1) {
        char temp_name[30];
        char response;
        int registered = 0;
        for (int i = 1; i < num_guests; i++) {
            bool valid_response = false;
            while (!valid_response) {
                cout << "\tRegister guest " << (i + 1) << "? (y/n): ";
                if (cin >> response && (tolower(response) == 'y' || tolower(response) == 'n')) {
                    valid_response = true;
                } else {
                    cout << "\tPlease enter 'y' or 'n'!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            cin.ignore(10000, '\n');
            if (tolower(response) == 'y') {
                cout << "\tGuest " << (i + 1) << " Name: ";
                cin.getline(temp_name, 30);
                if (registered > 0) {
                    strncat(other_guests, ", ", 100 - strlen(other_guests) - 1);
                }
                strncat(other_guests, temp_name, 100 - strlen(other_guests) - 1);
                registered++;
            }
        }
    }

    cout << "\tPhone Number: ";
    cin.getline(phone, 15);
    cout << "\tEmail Address: ";
    cin.getline(email, 50);

    room_no = selected_room;
    checked_out = false;

    hotel_db[room_no] = *this;

    cout << "\n\tRoom " << room_no << " (" << rtype << ") booked for " << name;
    if (other_guests[0] != '\0') {
        cout << " with " << other_guests;
    }
    cout << "!\n";
    wait_for_key();
}

void HOTEL::check_out() {
    system("clear || cls");
    int room;

    // Room number input
    bool valid_room = false;
    while (!valid_room) {
        cout << "\n\tEnter Room Number: ";
        if (cin >> room) {
            auto it = hotel_db.find(room);
            if (it != hotel_db.end() && !it->second.checked_out) {
                valid_room = true;
            } else {
                cout << "\tRoom is vacant or already checked out. Please enter a valid occupied room number.\n";
            }
        } else {
            cout << "\tInvalid room number! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    auto it = hotel_db.find(room);
    HOTEL& guest = it->second;
    cout << "\n\tMain Guest: " << guest.name;
    if (guest.other_guests[0] != '\0') {
        cout << "\n\tOther Guests: " << guest.other_guests;
    }
    cout << "\n\tRoom Type: " << guest.rtype;
    cout << "\n\tStayed for: " << guest.days << " days";
    cout << "\n\tTotal Bill: $" << guest.cost;

    // Confirmation input
    char confirm;
    bool valid_confirm = false;
    while (!valid_confirm) {
        cout << "\n\n\tCheck out this guest? (y/n): ";
        if (cin >> confirm && (tolower(confirm) == 'y' || tolower(confirm) == 'n')) {
            valid_confirm = true;
        } else {
            cout << "\tPlease enter 'y' or 'n'!\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    if (tolower(confirm) == 'y') {
        guest.check_out_date = time(nullptr);
        guest.checked_out = true;
        cout << "\n\tGuest checked out successfully.";
    } else {
        cout << "\n\tCheck out canceled.";
    }
    wait_for_key();
}

void HOTEL::display_guest() {
    system("clear || cls");
    int choice;

    // Choice input
    bool valid_choice = false;
    while (!valid_choice) {
        cout << "\n\tDisplay Guests:\n";
        cout << "\t1. Current Guests\n";
        cout << "\t2. Past Guests\n";
        cout << "\t3. All Guests\n";
        cout << "\tEnter Choice (1-3): ";
        if (cin >> choice && choice >= 1 && choice <= 3) {
            valid_choice = true;
        } else {
            cout << "\tInvalid choice! Please enter a number between 1-3.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    if (hotel_db.empty()) {
        cout << "\n\tNo guest records found!";
        wait_for_key();
        return;
    }

    cout << "\n\t\tGuests at HOTEL DE RANCH\n";
    cout << "\t\t------------------------\n";
    cout << "\t" << left << setw(12) << "Room No" 
         << setw(20) << "Main Guest" 
         << setw(30) << "Other Guests" 
         << setw(15) << "Room Type" 
         << setw(10) << "Days" 
         << setw(15) << "Total Cost" 
         << setw(15) << "Check-In" 
         << setw(15) << "Check-Out" 
         << setw(10) << "Status" << "\n"; // Adjusted width to 10 for longer status text
    cout << "\t" << string(125, '-') << "\n"; // Adjusted to match new width

    bool found = false;
    time_t now = time(nullptr); // Current time for comparison
    for (const auto& entry : hotel_db) {
        const HOTEL& guest = entry.second;
        if ((choice == 1 && !guest.checked_out) || (choice == 2 && guest.checked_out) || (choice == 3)) {
            found = true;
            struct tm* check_in_tm = localtime(&guest.check_in_date);
            string check_in_str = to_string(check_in_tm->tm_mon + 1) + "/" +
                                  to_string(check_in_tm->tm_mday) + "/" +
                                  to_string(check_in_tm->tm_year + 1900);

            string check_out_str;
            string status;
            if (guest.checked_out) {
                struct tm* check_out_tm = localtime(&guest.check_out_date);
                check_out_str = to_string(check_out_tm->tm_mon + 1) + "/" +
                                to_string(check_out_tm->tm_mday) + "/" +
                                to_string(check_out_tm->tm_year + 1900);
                status = "*CHKD-OUT*"; // Checked Out 
            } else {
                time_t expected_check_out = guest.check_in_date + (guest.days * 24 * 60 * 60);
                struct tm* expected_tm = localtime(&expected_check_out);
                check_out_str = to_string(expected_tm->tm_mon + 1) + "/" +
                                to_string(expected_tm->tm_mday) + "/" +
                                to_string(expected_tm->tm_year + 1900) + " (Exp)";
                if (now <= expected_check_out) {
                    status = "ACTIVE"; // Pending
                } else {
                    status = "OVERDUE"; // Overdue
                }
            }

            cout << "\t" << left << setw(12) << guest.room_no 
                 << setw(20) << guest.name 
                 << setw(30) << (guest.other_guests[0] != '\0' ? guest.other_guests : "-") 
                 << setw(15) << guest.rtype 
                 << setw(10) << guest.days 
                 << "$" << fixed << setprecision(2) << setw(13) << guest.cost 
                 << setw(15) << check_in_str 
                 << setw(15) << check_out_str 
                 << setw(10) << status << "\n";
        }
    }

    if (!found) {
        cout << "\tNo guests found matching your criteria.\n";
    }
    wait_for_key();
}

void HOTEL::available_rooms() {
    system("clear || cls");
    cout << "\n\tAvailable Rooms at HOTEL DE RANCH\n";
    cout << "\t---------------------------------\n";

    for (const auto& room_type : ROOM_RANGES) {
        vector<int> available = get_available_rooms(room_type.first);
        cout << "\n\t" << room_type.first << " Rooms (" 
             << room_type.second.first << "-" << room_type.second.second << "): ";
        
        if (available.empty()) {
            cout << "\n\t\tNone available";
        } else {
            for (size_t i = 0; i < available.size(); i++) {
                if (i % 5 == 0) cout << "\n\t\t";
                cout << available[i] << " ";
            }
        }
        cout << "\n";
    }
    wait_for_key();
}

int main() {
    system("clear || cls");
    HOTEL hotel;
    hotel.main_menu();
    return 0;
}