#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSENGERS 100000
#define MAX_NAME_LENGTH 50
#define MAX_GENDER_LENGTH 10
#define MAX_OPERATOR_LENGTH 50
#define MAX_LOCATION_LENGTH 50
#define MAX_TIME_LENGTH 20

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char gender[MAX_GENDER_LENGTH];
    int busNumber;
    char operatorName[MAX_OPERATOR_LENGTH];
    char seatNumber[3];
    float fare;
    char boardingPoint[MAX_LOCATION_LENGTH];
    char droppingPoint[MAX_LOCATION_LENGTH];
    char boardingTime[MAX_TIME_LENGTH];
    char droppingTime[MAX_TIME_LENGTH];
} Passenger;

Passenger passengers[MAX_PASSENGERS];
int passengerCount = 0;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void updatePassengerFile() {
    FILE *file = fopen("passengers.txt", "w");
    if (!file) {
        printf("Error saving file!\n");
        return;
    }

    fprintf(file, "==============================================================================================================================================\n");
    fprintf(file, "| ID | BusNo | Operator       | Name            | Age | Gender | Seat | Fare  | Board Point      | Drop Point       | Board Time | Drop Time |\n");
    fprintf(file, "==============================================================================================================================================\n");

    for (int i = 0; i < passengerCount; i++) {
        fprintf(file, "| %-2d | %-5d | %-15s | %-15s | %-3d | %-6s | %-4d | %-6.2f | %-15s | %-15s | %-9s | %-8s |\n",
                passengers[i].id, passengers[i].busNumber, passengers[i].operatorName,
                passengers[i].name, passengers[i].age, passengers[i].gender,
                passengers[i].seatNumber, passengers[i].fare,
                passengers[i].boardingPoint, passengers[i].droppingPoint,
                passengers[i].boardingTime, passengers[i].droppingTime);
    }

    fprintf(file, "======================================================================================================================\n");
    fprintf(file, "Total Passengers: %d\n", passengerCount);
    fclose(file);
    printf("Passenger records updated successfully!\n");
}

void addNewPassenger() {
    int n;
    printf("How many no.of passengers do you want to add?: \n");
    scanf("%d",&n);
    clearInputBuffer();

    for (int i=1;i<=n;i++)
    {
        if(passengerCount >= MAX_PASSENGERS) {
            printf("Cannot add more passengers!\n");
            return;
        }
        Passenger *p = &passengers[passengerCount];
        p->id = passengerCount + 1;
        printf("\n=== ADDING PASSENGERS===\n");
        printf("Enter Name: ");
        fgets(p->name, MAX_NAME_LENGTH, stdin);
        p->name[strcspn(p->name, "\n")] = 0;

        printf("Enter Age: ");
        scanf("%d", &p->age);
        clearInputBuffer();

        printf("Enter Gender: ");
        fgets(p->gender, MAX_GENDER_LENGTH, stdin);
        p->gender[strcspn(p->gender, "\n")] = 0;

        printf("Enter Bus Number: ");
        scanf("%d", &p->busNumber);
        clearInputBuffer();

        printf("Enter Operator Name: ");
        fgets(p->operatorName, MAX_OPERATOR_LENGTH, stdin);
        p->operatorName[strcspn(p->operatorName, "\n")] = 0;

        printf("Enter Seat Number(e.g., S1,U8): ");
        fgets(p->seatNumber, MAX_NAME_LENGTH, stdin);
        p->seatNumber[strcspn(p->seatNumber, "\n")] = 0;

        printf("Enter Fare: ");
        scanf("%f", &p->fare);
        clearInputBuffer();

        printf("Enter Boarding Point: ");
        fgets(p->boardingPoint, MAX_LOCATION_LENGTH, stdin);
        p->boardingPoint[strcspn(p->boardingPoint, "\n")] = 0;

        printf("Enter Dropping Point: ");
        fgets(p->droppingPoint, MAX_LOCATION_LENGTH, stdin);
        p->droppingPoint[strcspn(p->droppingPoint, "\n")] = 0;

        printf("Enter Boarding Time (e.g., 13/04/2023 06:00 AM/PM): ");
        fgets(p->boardingTime, MAX_TIME_LENGTH, stdin);
        p->boardingTime[strcspn(p->boardingTime, "\n")] = 0;

        printf("Enter Dropping Time (e.g., 13/04/2023 06:00 AM/PM): ");
        fgets(p->droppingTime, MAX_TIME_LENGTH, stdin);
        p->droppingTime[strcspn(p->droppingTime, "\n")] = 0;

        passengerCount++;
        printf("\n Passenger added successfully! ID: %d\n",p->id);
    }
    updatePassengerFile();
}

void displayAllPassengers() {
    if(passengerCount == 0) {
        printf("No passenger records found!\n");
        return;
    }
    for(int i=0;i<176;i++) printf("=");
    printf("\n");
    printf("| %-4s | %-6s | %-15s | %-15s | %-4s | %-8s | %-6s | %-8s | %-15s | %-15s | %-20s | %-20s |\n",
           "ID", "BusNo", "Operator", "Name", "Age", "Gender", "Seat", "Fare", "Board Point", "Drop Point", "Boarding", "Dropping");

    for(int i=0;i<176;i++) printf("=");
    printf("\n");
    for(int i = 0; i < passengerCount; i++) {
        printf("| %-4d | %-6d | %-15s | %-15s | %-4d | %-8s | %-6s | %-8.2f | %-15s | %-15s | %-20s | %-20s |\n",
               passengers[i].id, passengers[i].busNumber, passengers[i].operatorName,
               passengers[i].name, passengers[i].age, passengers[i].gender,
               passengers[i].seatNumber, passengers[i].fare,
               passengers[i].boardingPoint, passengers[i].droppingPoint,
               passengers[i].boardingTime, passengers[i].droppingTime);
    }

    for(int i=0;i<176;i++) printf("=");
    printf("\n");
    printf("Total Passengers: %d\n", passengerCount);
}

void searchPassenger() {
    int choice;
    printf("\n=== SEARCH PASSENGERS ===\n");
    printf("1. Search by Name\n");
    printf("2. Search by Bus Number\n");
    printf("3. Search by Bus Operator\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    clearInputBuffer();

    switch(choice) {
        case 1: {
            char searchTerm[MAX_NAME_LENGTH];
            printf("Enter Name to search: ");
            fgets(searchTerm, MAX_NAME_LENGTH, stdin);
            searchTerm[strcspn(searchTerm, "\n")] = 0;

            int found = 0;
            for(int i = 0; i < passengerCount; i++) {
                if(strstr(passengers[i].name, searchTerm) != NULL) {
                    printf("| ID:%d | Name:%s | BusNo:%d | Seat:%d | Age:%d | Gender:%s | Fare:%.2f | Board:%s | Drop:%s | B.Time:%s | D.Time:%s |\n",
                           passengers[i].id, passengers[i].name, passengers[i].busNumber,
                           passengers[i].seatNumber, passengers[i].age, passengers[i].gender,
                           passengers[i].fare, passengers[i].boardingPoint,
                           passengers[i].droppingPoint, passengers[i].boardingTime,
                           passengers[i].droppingTime);
                    found = 1;
                }
            }
            if(!found) printf("No passengers found with name '%s'.\n", searchTerm);
            break;
        }
        case 2: {
            int busNo;
            printf("Enter Bus Number to search: ");
            scanf("%d", &busNo);
            clearInputBuffer();

            int found = 0;
            for(int i = 0; i < passengerCount; i++) {
                if(passengers[i].busNumber == busNo) {
                    printf("| ID:%d | Name:%s | Seat:%d | Age:%d | Gender:%s | Fare:%.2f | Board:%s | Drop:%s | B.Time:%s | D.Time:%s |\n",
                           passengers[i].id, passengers[i].name, passengers[i].seatNumber,
                           passengers[i].age, passengers[i].gender, passengers[i].fare,
                           passengers[i].boardingPoint, passengers[i].droppingPoint,
                           passengers[i].boardingTime, passengers[i].droppingTime);
                    found = 1;
                }
            }
            if(!found) printf("No passengers found for Bus Number %d.\n", busNo);
            break;
        }
        case 3: {
            char operatorName[MAX_OPERATOR_LENGTH];
            printf("Enter Bus Operator Name to search: ");
            fgets(operatorName, MAX_OPERATOR_LENGTH, stdin);
            operatorName[strcspn(operatorName, "\n")] = 0;

            int found = 0;
            printf("\nPassengers for Operator '%s':\n", operatorName);
            for(int i = 0; i < passengerCount; i++) {
                if(strcmp(passengers[i].operatorName, operatorName) == 0) {
                    printf("| ID:%d | Name:%s | BusNo:%d | Seat:%d | Age:%d | Gender:%s | Fare:%.2f | Board:%s | Drop:%s | B.Time:%s | D.Time:%s |\n",
                           passengers[i].id, passengers[i].name, passengers[i].busNumber,
                           passengers[i].seatNumber, passengers[i].age, passengers[i].gender,
                           passengers[i].fare, passengers[i].boardingPoint,
                           passengers[i].droppingPoint, passengers[i].boardingTime,
                           passengers[i].droppingTime);
                    found = 1;
                }
            }
            if(!found) printf("No passengers found for this operator.\n");
            break;
        }
        default:
            printf("Invalid choice!\n");
    }
}

void updatePassenger() {
    if(passengerCount == 0) {
        printf("No passengers to update!\n");
        return;
    }

    int id;
    printf("Enter Passenger ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = -1;
    for(int i = 0; i < passengerCount; i++) {
        if(passengers[i].id == id) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("Passenger ID not found!\n");
        return;
    }

    char more;
    do {
        int choice;
        printf("\nWhich field do you want to update for %s?\n", passengers[index].name);
        printf("1. Age\n2. Gender\n3. Seat Number\n4. Fare\n5. Bus Number\n6. Operator Name\n7. Boarding Point\n8. Dropping Point\n9. Boarding Time\n10. Dropping Time\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
            case 1: 
                printf("Current Age: %d\nEnter new Age: ", passengers[index].age); 
                scanf("%d", &passengers[index].age); 
                clearInputBuffer(); 
                break;
            case 2: 
                printf("Current Gender: %s\nEnter new Gender: ", passengers[index].gender); 
                fgets(passengers[index].gender, MAX_GENDER_LENGTH, stdin); 
                passengers[index].gender[strcspn(passengers[index].gender, "\n")] = 0; 
                break;
            case 3: 
                printf("Current Seat Number: %d\nEnter new Seat Number: ", passengers[index].seatNumber); 
                fgets(passengers[index].seatNumber, MAX_NAME_LENGTH, stdin); 
                passengers[index].seatNumber[strcspn(passengers[index].seatNumber, "\n")] = 0; 
                break;
            case 4: 
                printf("Current Fare: %.2f\nEnter new Fare: ", passengers[index].fare); 
                scanf("%f", &passengers[index].fare); 
                clearInputBuffer(); 
                break;
            case 5: 
                printf("Current Bus Number: %d\nEnter new Bus Number: ", passengers[index].busNumber); 
                scanf("%d", &passengers[index].busNumber); 
                clearInputBuffer(); 
                break;
            case 6: 
                printf("Current Operator Name: %s\nEnter new Operator Name: ", passengers[index].operatorName); 
                fgets(passengers[index].operatorName, MAX_OPERATOR_LENGTH, stdin); passengers[index].operatorName[strcspn(passengers[index].operatorName, "\n")] = 0; 
                break;
            case 7: 
                printf("Current Boarding Point: %s\nEnter new Boarding Point: ", passengers[index].boardingPoint); 
                fgets(passengers[index].boardingPoint, MAX_LOCATION_LENGTH, stdin); passengers[index].boardingPoint[strcspn(passengers[index].boardingPoint, "\n")] = 0; 
                break;
            case 8: 
                printf("Current Dropping Point: %s\nEnter new Dropping Point: ", passengers[index].droppingPoint); 
                fgets(passengers[index].droppingPoint, MAX_LOCATION_LENGTH, stdin); passengers[index].droppingPoint[strcspn(passengers[index].droppingPoint, "\n")] = 0; 
                break;
            case 9: 
                printf("Current Boarding Time: %s\nEnter new Boarding Time: ", passengers[index].boardingTime); 
                fgets(passengers[index].boardingTime, MAX_TIME_LENGTH, stdin); passengers[index].boardingTime[strcspn(passengers[index].boardingTime, "\n")] = 0; 
                break;
            case 10: 
                printf("Current Dropping Time: %s\nEnter new Dropping Time: ", passengers[index].droppingTime); 
                fgets(passengers[index].droppingTime, MAX_TIME_LENGTH, stdin); passengers[index].droppingTime[strcspn(passengers[index].droppingTime, "\n")] = 0; 
                break;
            default: printf("Invalid choice!\n"); 
            continue;
        }

        updatePassengerFile();

        printf("Do you want to update another field for %s? (y/n): ", passengers[index].name);
        scanf(" %c", &more);
        clearInputBuffer();
    } while(more == 'y' || more == 'Y');
}

void deletePassenger() {
    if(passengerCount == 0) {
        printf("No passengers to delete!\n");
        return;
    }

    int id;
    printf("Enter Passenger ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = -1;
    for(int i = 0; i < passengerCount; i++) {
        if(passengers[i].id == id) {
            index = i;
            break;
        }
    }

    if(index == -1) {
        printf("Passenger ID not found!\n");
        return;
    }

    for(int i = index; i < passengerCount - 1; i++) {
        passengers[i] = passengers[i + 1];
    }
    passengerCount--;
    printf("Passenger deleted successfully!\n");
    updatePassengerFile();
}

void saveasfile() {
    char filename[100];
    printf("Enter file name to save passengers (e.g., mypassengers.txt): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0; // remove newline

    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for saving!\n");
        return;
    }

    fprintf(file, "======================================================================================================================\n");
    fprintf(file, "| ID | BusNo | Operator       | Name            | Age | Gender | Seat | Fare  | Board Point      | Drop Point       | Board Time | Drop Time |\n");
    fprintf(file, "======================================================================================================================\n");

    for (int i = 0; i < passengerCount; i++) {
        fprintf(file, "| %-2d | %-5d | %-15s | %-15s | %-3d | %-6s | %-4d | %-6.2f | %-15s | %-15s | %-9s | %-8s |\n",
                passengers[i].id, passengers[i].busNumber, passengers[i].operatorName,
                passengers[i].name, passengers[i].age, passengers[i].gender,
                passengers[i].seatNumber, passengers[i].fare,
                passengers[i].boardingPoint, passengers[i].droppingPoint,
                passengers[i].boardingTime, passengers[i].droppingTime);
    }

    fprintf(file, "======================================================================================================================\n");
    fprintf(file, "Total Passengers: %d\n", passengerCount);
    fclose(file);

    printf("Passenger records saved successfully to '%s'!\n", filename);
}

int main() {
    int choice;
    do {
        printf("\n=== PASSENGER MANAGEMENT SYSTEM ===\n");
        printf("1. Add Passenger\n");
        printf("2. Display All Passengers\n");
        printf("3. Search Passenger\n");
        printf("4. Update Passenger\n");
        printf("5. Delete Passenger\n");
        printf("6. Save to File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
            case 1: addNewPassenger(); break;
            case 2: displayAllPassengers(); break;
            case 3: searchPassenger(); break;
            case 4: updatePassenger(); break;
            case 5: deletePassenger(); break;
            case 6: saveasfile(); break;
            case 7: printf("Exiting program.\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 7);

    return 0;
}