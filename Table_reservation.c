#include <stdio.h>
#include <stdlib.h>
#define MAX_TABLES 10
typedef struct {
    int tables[MAX_TABLES];
    int front;
    int rear;
    int count;
} Restaurant;

void initializeRestaurant(Restaurant *r);
int isFull(Restaurant *r);
int isEmpty(Restaurant *r);
void bookTable(Restaurant *r, int tableNumber);
void cancelTable(Restaurant *r);
void displayFreeTables(Restaurant *r);
void displayTotalTables();

int main() {
    Restaurant reservationQueue;
    initializeRestaurant(&reservationQueue);
    int choice, tableNumber;
    do {
        printf("\nRestaurant Table Reservation System:\n");
        printf("1. Book a table\n");
        printf("2. Cancel a table\n");
        printf("3. Display number of free tables\n");
        printf("4. Display total number of tables\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (!isFull(&reservationQueue)) {
                    printf("Enter table number to book (1 to %d): ", MAX_TABLES);
                    scanf("%d", &tableNumber);
                    if (tableNumber > 0 && tableNumber <= MAX_TABLES) {
                        bookTable(&reservationQueue, tableNumber);
                    } else {
                        printf("Invalid table number.\n");
                    }
                } else {
                    printf("All tables are reserved. No free tables available.\n");
                }
                break;
            case 2:
                cancelTable(&reservationQueue);
                break;
            case 3:
                displayFreeTables(&reservationQueue);
                break;
            case 4:
                displayTotalTables();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}

void initializeRestaurant(Restaurant *r) {
    r->front = 0;
    r->rear = -1;
    r->count = 0;
}

int isFull(Restaurant *r) {
    return r->count == MAX_TABLES;
}

int isEmpty(Restaurant *r) {
    return r->count == 0;
}

void bookTable(Restaurant *r, int tableNumber) {
    if (isFull(r)) {
        printf("All tables are reserved.\n");
        return;
    }
    r->rear = (r->rear + 1) % MAX_TABLES;
    r->tables[r->rear] = tableNumber;
    r->count++;
    printf("Table %d has been booked.\n", tableNumber);
}

void cancelTable(Restaurant *r) {
    if (isEmpty(r)) {
        printf("No reservations to cancel.\n");
        return;
    }
    int cancelledTable = r->tables[r->front];
    r->front = (r->front + 1) % MAX_TABLES;
    r->count--;
    printf("Table %d reservation has been cancelled.\n", cancelledTable);
}

void displayFreeTables(Restaurant *r) {
    printf("Number of free tables: %d\n", MAX_TABLES - r->count);
}

void displayTotalTables() {
    printf("Total number of tables: %d\n", MAX_TABLES);
}
