#include <stdio.h>
#include <string.h>

// Structure to represent a guest
struct Guest {
    char name[50];
    char phoneNumber[15];
    char governmentId[17];
};

// Function to display available rooms
void displayAvailableRooms(int acRooms[], int nonAcRooms[]) {
    printf("Available AC Rooms: ");
    for (int i = 0; i < 5; i++) {
        if (acRooms[i] == 1) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");

    printf("Available Non-AC Rooms: ");
    for (int i = 0; i < 5; i++) {
        if (nonAcRooms[i] == 1) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

// Function to perform check-in
void checkIn(int acRooms[], int nonAcRooms[], struct Guest guests[], int roomType) {
    int roomNumber = -1;
    int numGuests;

    // Find the first available room
    for (int i = 0; i < 5; i++) {
        if ((roomType == 1 && acRooms[i] == 1) || (roomType == 2 && nonAcRooms[i] == 1)) {
            roomNumber = i + 1;
            break;
        }
    }

    if (roomNumber != -1) {
        // Room is available
        guests[roomNumber - 1].governmentId[0] = '\0'; // Clearing governmentId for the case of multiple check-ins
        printf("Enter your name: ");
        scanf("%s", guests[roomNumber - 1].name);

        // Clear input buffer
        while (getchar() != '\n');

        printf("Enter your phone number: ");
        scanf("%s", guests[roomNumber - 1].phoneNumber);

        printf("Enter your 16-digit government ID: ");
        scanf("%s", guests[roomNumber - 1].governmentId);

        // Check the number of guests accompanying
        printf("Enter the total number of guests: ");
        scanf("%d", &numGuests);

        // Check if additional rooms are needed
        if (numGuests > 2) {
            printf("Would you like to book additional rooms for your guests? (Enter 'yes' or 'no'): ");
            char response[10];
            scanf("%s", response);

            if (strcmp(response, "yes") == 0) {
                int additionalRooms = (numGuests - 2) / 2;  // Calculate additional rooms needed
                printf("Allocating %d additional rooms.\n", additionalRooms);

                for (int i = 0; i < additionalRooms; i++) {
                    // Find the next available room
                    int additionalRoom = -1;
                    for (int j = 0; j < 5; j++) {
                        if ((roomType == 1 && acRooms[j] == 1) || (roomType == 2 && nonAcRooms[j] == 1)) {
                            additionalRoom = j + 1;
                            break;
                        }
                    }

                    if (additionalRoom != -1) {
                        // Additional room is available
                        guests[additionalRoom - 1].governmentId[0] = '\0'; // Clearing governmentId for the case of multiple check-ins
                        printf("Enter name for additional guest in Room %d: ", additionalRoom);
                        scanf("%s", guests[additionalRoom - 1].name);

                        // Update room availability
                        if (roomType == 1) {
                            acRooms[additionalRoom - 1] = 0;  // 0 represents booked AC room
                        } else if (roomType == 2) {
                            nonAcRooms[additionalRoom - 1] = 0;  // 0 represents booked non-AC room
                        }

                        printf("Guest added to Room %d.\n", additionalRoom);
                    } else {
                        // No additional room available
                        printf("Sorry, no additional rooms of the selected type are available.\n");
                        break;
                    }
                }
            }
        }

        // Update room availability for the main room
        if (roomType == 1) {
            acRooms[roomNumber - 1] = 0;  // 0 represents booked AC room
        } else if (roomType == 2) {
            nonAcRooms[roomNumber - 1] = 0;  // 0 represents booked non-AC room
        }

        printf("Checked-in successfully to Room %d.\n", roomNumber);
    } else {
        // No available rooms
        printf("Sorry, all rooms of the selected type are booked.\n");
    }
}

// Function to perform check-out
void checkOut(int acRooms[], int nonAcRooms[], struct Guest guests[]) {
    int roomNumber;
    printf("Enter the room number to check-out: ");
    scanf("%d", &roomNumber);

    if (roomNumber >= 1 && roomNumber <= 5) {
        if (acRooms[roomNumber - 1] == 0 || nonAcRooms[roomNumber - 1] == 0) {
            // Room is booked, proceed with check-out
            acRooms[roomNumber - 1] = 1;  // 1 represents available AC room
            nonAcRooms[roomNumber - 1] = 1;  // 1 represents available non-AC room
            guests[roomNumber - 1].name[0] = '\0'; // Clear guest name
            guests[roomNumber - 1].phoneNumber[0] = '\0'; // Clear guest phone number
            guests[roomNumber - 1].governmentId[0] = '\0'; // Clear guest government ID
            printf("Checked-out successfully from Room %d.\n", roomNumber);
        } else {
            // Room is not booked
            printf("Room %d is not currently booked.\n", roomNumber);
        }
    } else {
        // Invalid room number
        printf("Invalid room number.\n");
    }
}

int main() {
    // Arrays to track room availability
    int acRooms[5] = {1, 1, 1, 1, 1};  // 1 represents available AC room
    int nonAcRooms[5] = {1, 1, 1, 1, 1};  // 1 represents available non-AC room

    // Array to store guest information
    struct Guest guests[5];

    int choice;
    do {
        // Display menu
        printf("\nHotel Management System\n");
        printf("1. Display Available Rooms\n");
        printf("2. Check-In\n");
        printf("3. Check-Out\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAvailableRooms(acRooms, nonAcRooms);
                break;
            case 2:
                printf("Select room type (1 for AC, 2 for Non-AC): ");
                int roomType;
                scanf("%d", &roomType);

                if (roomType == 1 || roomType == 2) {
                    checkIn(acRooms, nonAcRooms, guests, roomType);
                } else {
                    printf("Invalid choice.\n");
                }
                break;
            case 3:
                checkOut(acRooms, nonAcRooms, guests);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}
