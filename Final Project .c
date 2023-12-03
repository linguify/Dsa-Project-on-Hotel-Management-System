#include <stdio.h>

// Structure to store Guest details
struct Guest {
    char Name[50];
    char PhoneNumber[15];
    char governmentId[20];
};

// Function to initialize Rooms
void initializeRooms(int acRooms[], int nonAcRooms[], int totalRooms) {
    for (int i = 0; i < totalRooms; i++) {
        acRooms[i] = 1;  // 1 represents available AC Room
        nonAcRooms[i] = 1;  // 1 represents available non-AC Room
    }
}

// Function to display menu
void displayMenu() {
    printf("\n===== Welcome To Engineers Paradise=====\n");
    printf("1. Check-In\n");
    printf("2. Check-Out\n");
    printf("3. Display Available Rooms\n");
    printf("4. Exit\n");
}

// Function to perform check-in
void checkIn(int acRooms[], int nonAcRooms[], struct Guest Guests[], int RoomType) {
    int RoomNumber = -1;

    // Find the first available Room
    for (int i = 0; i < 5; i++) {
        if ((RoomType == 1 && acRooms[i] == 1) || (RoomType == 2 && nonAcRooms[i] == 1)) {
            RoomNumber = i + 1;
            break;
        }
    }

    if (RoomNumber != -1) {
        // Room is available
        int NumberOfGuests;
        printf("Enter the Number of Guests: ");
        scanf("%d", &NumberOfGuests);

        // Clear input buffer
        while (getchar() != '\n');

        Guests[RoomNumber - 1].governmentId[0] = '\0'; // Clearing governmentId for the case of multiple check-ins

        printf("Enter Your Name: ");
        scanf("%s", Guests[RoomNumber - 1].Name);

        printf("Enter Your PhoneNumber: ");
        scanf("%s", Guests[RoomNumber - 1].PhoneNumber);

        printf("Enter Your 12-digit Aadhar Card No: ");
        scanf("%s", Guests[RoomNumber - 1].governmentId);

        if (RoomType == 1) {
            acRooms[RoomNumber - 1] = 0;  // 0 represents booked AC Room
        } else if (RoomType == 2) {
            nonAcRooms[RoomNumber - 1] = 0;  // 0 represents booked non-AC Room
        }

        printf("Checked-in successfully to Room %d with %d Guest(s).\n", RoomNumber, NumberOfGuests);
    } else {
        // No available Rooms
        printf("Sorry, all Rooms of the selected type are booked.\n");
    }
}

// Function to perform check-out
void checkOut(int acRooms[], int nonAcRooms[], struct Guest Guests[], int RoomType) {
    int RoomNumber;

    printf("Enter the Room Number to check-out: ");
    scanf("%d", &RoomNumber);

    if ((RoomType == 1 && acRooms[RoomNumber - 1] == 0) || (RoomType == 2 && nonAcRooms[RoomNumber - 1] == 0)) {
        // Room is booked
        if (RoomType == 1) {
            acRooms[RoomNumber - 1] = 1;  // 1 represents available AC Room
        } else if (RoomType == 2) {
            nonAcRooms[RoomNumber - 1] = 1;  // 1 represents available non-AC Room
        }

        printf("Checked-out successfully from Room %d.\n", RoomNumber);
    } else {
        // Room is not booked
        printf("Room %d is not booked.\n", RoomNumber);
    }
}

// Function to display available Rooms in tabular form
void displayAvailableRooms(int acRooms[], int nonAcRooms[], struct Guest Guests[]) {
    printf("\n===== Available Rooms =====\n");
    printf("| %-15s | %-15s | %-15s |\n", "Room Type", "Room Number", "Status");
    printf("|---------------|---------------|---------------|\n");

    for (int i = 0; i < 5; i++) {
        printf("| %-13s | %-13d | ", "AC Room", i + 1);
        if (acRooms[i] == 1) {
            printf("%-15s |\n", "Available");
        } else {
            printf("Booked by %-10s |\n", Guests[i].Name);
        }

        printf("| %-13s | %-13d | ", "Non-AC Room", i + 1);
        if (nonAcRooms[i] == 1) {
            printf("%-15s |\n", "Available");
        } else {
            printf("Booked by %-10s |\n", Guests[i].Name);
        }
    }
}

int main() {
    int acRooms[5], nonAcRooms[5];
    struct Guest Guests[10]; // Changed total Rooms to 10

    initializeRooms(acRooms, nonAcRooms, 10); // Changed total Rooms to 10

    int choice;
    do {
        displayMenu();
        printf("Enter Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Check-In
                printf("1. AC Room\n2. Non-AC Room\n");
                int RoomType;
                printf("Enter the Room type: ");
                scanf("%d", &RoomType);
                checkIn(acRooms, nonAcRooms, Guests, RoomType);
                break;
            case 2:
                // Check-Out
                printf("1. AC Room\n2. Non-AC Room\n");
                printf("Enter the Room type: ");
                scanf("%d", &RoomType);
                checkOut(acRooms, nonAcRooms, Guests, RoomType);
                break;
            case 3:
                // Display Available Rooms
                displayAvailableRooms(acRooms, nonAcRooms, Guests);
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
