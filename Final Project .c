#include <stdio.h>

// Structure to store guest details
struct Guest {
    char name[50];
    char phoneNumber[15];
    char governmentId[20];
};

// Function to initialize rooms
void initializeRooms(int acRooms[], int nonAcRooms[], int totalRooms) {
    for (int i = 0; i < totalRooms; i++) {
        acRooms[i] = 1;  // 1 represents available AC room
        nonAcRooms[i] = 1;  // 1 represents available non-AC room
    }
}

// Function to display menu
void displayMenu() {
    printf("\n===== Hotel Management System =====\n");
    printf("1. Check-In\n");
    printf("2. Check-Out\n");
    printf("3. Display Available Rooms\n");
    printf("4. Exit\n");
}

// Function to perform check-in
void checkIn(int acRooms[], int nonAcRooms[], struct Guest guests[], int roomType) {
    int roomNumber = -1;

    // Find the first available room
    for (int i = 0; i < 5; i++) {
        if ((roomType == 1 && acRooms[i] == 1) || (roomType == 2 && nonAcRooms[i] == 1)) {
            roomNumber = i + 1;
            break;
        }
    }

    if (roomNumber != -1) {
        // Room is available
        int numberOfGuests;
        printf("Enter the number of guests: ");
        scanf("%d", &numberOfGuests);

        // Clear input buffer
        while (getchar() != '\n');

        guests[roomNumber - 1].governmentId[0] = '\0'; // Clearing governmentId for the case of multiple check-ins

        printf("Enter your name: ");
        scanf("%s", guests[roomNumber - 1].name);

        printf("Enter your phone number: ");
        scanf("%s", guests[roomNumber - 1].phoneNumber);

        printf("Enter your 12-digit Adhar Card No: ");
        scanf("%s", guests[roomNumber - 1].governmentId);

        if (roomType == 1) {
            acRooms[roomNumber - 1] = 0;  // 0 represents booked AC room
        } else if (roomType == 2) {
            nonAcRooms[roomNumber - 1] = 0;  // 0 represents booked non-AC room
        }

        printf("Checked-in successfully to Room %d with %d guest(s).\n", roomNumber, numberOfGuests);
    } else {
        // No available rooms
        printf("Sorry, all rooms of the selected type are booked.\n");
    }
}

// Function to perform check-out
void checkOut(int acRooms[], int nonAcRooms[], struct Guest guests[], int roomType) {
    int roomNumber;

    printf("Enter the room number to check-out: ");
    scanf("%d", &roomNumber);

    if ((roomType == 1 && acRooms[roomNumber - 1] == 0) || (roomType == 2 && nonAcRooms[roomNumber - 1] == 0)) {
        // Room is booked
        if (roomType == 1) {
            acRooms[roomNumber - 1] = 1;  // 1 represents available AC room
        } else if (roomType == 2) {
            nonAcRooms[roomNumber - 1] = 1;  // 1 represents available non-AC room
        }

        printf("Checked-out successfully from Room %d.\n", roomNumber);
    } else {
        // Room is not booked
        printf("Room %d is not booked.\n", roomNumber);
    }
}

// Function to display available rooms in tabular form
void displayAvailableRooms(int acRooms[], int nonAcRooms[], struct Guest guests[]) {
    printf("\n===== Available Rooms =====\n");
    printf("| %-15s | %-15s | %-15s |\n", "Room Type", "Room Number", "Status");
    printf("|---------------|---------------|---------------|\n");

    for (int i = 0; i < 5; i++) {
        printf("| %-13s | %-13d | ", "AC Room", i + 1);
        if (acRooms[i] == 1) {
            printf("%-15s |\n", "Available");
        } else {
            printf("Booked by %-10s |\n", guests[i].name);
        }

        printf("| %-13s | %-13d | ", "Non-AC Room", i + 1);
        if (nonAcRooms[i] == 1) {
            printf("%-15s |\n", "Available");
        } else {
            printf("Booked by %-10s |\n", guests[i].name);
        }
    }
}

int main() {
    int acRooms[5], nonAcRooms[5];
    struct Guest guests[10]; // Changed total rooms to 10

    initializeRooms(acRooms, nonAcRooms, 10); // Changed total rooms to 10

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Check-In
                printf("1. AC Room\n2. Non-AC Room\n");
                int roomType;
                printf("Enter the room type: ");
                scanf("%d", &roomType);
                checkIn(acRooms, nonAcRooms, guests, roomType);
                break;
            case 2:
                // Check-Out
                printf("1. AC Room\n2. Non-AC Room\n");
                printf("Enter the room type: ");
                scanf("%d", &roomType);
                checkOut(acRooms, nonAcRooms, guests, roomType);
                break;
            case 3:
                // Display Available Rooms
                displayAvailableRooms(acRooms, nonAcRooms, guests);
                break;
            case 4:
                // Exit
                printf("Thank you for using the Hotel Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
