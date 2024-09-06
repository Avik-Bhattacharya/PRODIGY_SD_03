#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define FILENAME "contacts.txt"

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

void loadContacts(Contact contacts[], int *count);
void saveContacts(Contact contacts[], int count);
void addContact(Contact contacts[], int *count);
void viewContacts(Contact contacts[], int count);
void editContact(Contact contacts[], int count);
void deleteContact(Contact contacts[], int *count);
void displayMenu();

int main() {
    Contact contacts[MAX_CONTACTS];
    int count = 0;
    int choice;
    loadContacts(contacts, &count);

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addContact(contacts, &count);
                break;
            case 2:
                viewContacts(contacts, count);
                break;
            case 3:
                editContact(contacts, count);
                break;
            case 4:
                deleteContact(contacts, &count);
                break;
            case 5:
                saveContacts(contacts, count);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void displayMenu() {
    printf("\nContact Management System\n");
    printf("1. Add Contact\n");
    printf("2. View Contacts\n");
    printf("3. Edit Contact\n");
    printf("4. Delete Contact\n");
    printf("5. Save Contacts\n");
    printf("6. Exit\n");
}

void loadContacts(Contact contacts[], int *count) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No contacts file found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%49[^\n]\n%19[^\n]\n%49[^\n]\n", contacts[*count].name, contacts[*count].phone, contacts[*count].email) == 3) {
        (*count)++;
    }

    fclose(file);
}

void saveContacts(Contact contacts[], int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error saving contacts.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n%s\n%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }

    fclose(file);
}

void addContact(Contact contacts[], int *count) {
    if (*count >= MAX_CONTACTS) {
        printf("Contact list is full.\n");
        return;
    }

    printf("Enter contact name: ");
    fgets(contacts[*count].name, sizeof(contacts[*count].name), stdin);
    contacts[*count].name[strcspn(contacts[*count].name, "\n")] = 0;

    printf("Enter phone number: ");
    fgets(contacts[*count].phone, sizeof(contacts[*count].phone), stdin);
    contacts[*count].phone[strcspn(contacts[*count].phone, "\n")] = 0;

    printf("Enter email address: ");
    fgets(contacts[*count].email, sizeof(contacts[*count].email), stdin);
    contacts[*count].email[strcspn(contacts[*count].email, "\n")] = 0;

    (*count)++;
}

void viewContacts(Contact contacts[], int count) {
    if (count == 0) {
        printf("No contacts to display.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nContact %d:\n", i + 1);
        printf("Name: %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].phone);
        printf("Email: %s\n", contacts[i].email);
    }
}

void editContact(Contact contacts[], int count) {
    int index;

    printf("Enter contact number to edit (1-%d): ", count);
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > count) {
        printf("Invalid contact number.\n");
        return;
    }

    index--;

    printf("Editing contact %d:\n", index + 1);
    printf("Enter new name (or press Enter to keep current): ");
    fgets(contacts[index].name, sizeof(contacts[index].name), stdin);
    if (contacts[index].name[0] == '\n') {
        contacts[index].name[0] = '\0';
    } else {
        contacts[index].name[strcspn(contacts[index].name, "\n")] = 0; 
    }

    printf("Enter new phone number (or press Enter to keep current): ");
    fgets(contacts[index].phone, sizeof(contacts[index].phone), stdin);
    if (contacts[index].phone[0] == '\n') {
        contacts[index].phone[0] = '\0'; 
    } else {
        contacts[index].phone[strcspn(contacts[index].phone, "\n")] = 0;
    }

    printf("Enter new email address (or press Enter to keep current): ");
    fgets(contacts[index].email, sizeof(contacts[index].email), stdin);
    if (contacts[index].email[0] == '\n') {
        contacts[index].email[0] = '\0';
    } else {
        contacts[index].email[strcspn(contacts[index].email, "\n")] = 0;
    }
}

void deleteContact(Contact contacts[], int *count) {
    int index;

    printf("Enter contact number to delete (1-%d): ", *count);
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > *count) {
        printf("Invalid contact number.\n");
        return;
    }

    index--;

    for (int i = index; i < *count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    (*count)--;
    printf("Contact deleted.\n");
}
