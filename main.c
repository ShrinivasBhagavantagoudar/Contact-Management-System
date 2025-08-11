#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked List Node for Phone Numbers
typedef struct PhoneNumberNode {
    char phoneNumber[15];
    struct PhoneNumberNode* next;
} PhoneNumberNode;

// BST Node for Contacts
typedef struct ContactNode {
    char name[50];
    PhoneNumberNode* phoneNumbers;
    struct ContactNode* left;
    struct ContactNode* right;
} ContactNode;

// Function to create a new phone number node
PhoneNumberNode* createPhoneNumberNode(char* phoneNumber) {
    PhoneNumberNode* newNode = (PhoneNumberNode*)malloc(sizeof(PhoneNumberNode));
    strcpy(newNode->phoneNumber, phoneNumber);
    newNode->next = NULL;
    return newNode;
}

// Function to create a new contact node
ContactNode* createContactNode(char* name) {
    ContactNode* newNode = (ContactNode*)malloc(sizeof(ContactNode));
    strcpy(newNode->name, name);
    newNode->phoneNumbers = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a contact into the BST
ContactNode* insertContact(ContactNode* root, char* name) {
    if (root == NULL) {
        return createContactNode(name);
    }

    if (strcmp(name, root->name) < 0) {
        root->left = insertContact(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insertContact(root->right, name);
    }

    return root;
}

// Function to search for a contact
ContactNode* searchContact(ContactNode* root, char* name) {
    if (root == NULL || strcmp(name, root->name) == 0) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        return searchContact(root->left, name);
    } else {
        return searchContact(root->right, name);
    }
}

// Function to add a phone number to a contact
void addPhoneNumber(ContactNode* contact, char* phoneNumber) {
    if (contact == NULL) {
        printf("Contact not found.\n");
        return;
    }

    PhoneNumberNode* newNumber = createPhoneNumberNode(phoneNumber);
    newNumber->next = contact->phoneNumbers;
    contact->phoneNumbers = newNumber;
    printf("Phone number added successfully!\n");
}

// Function to display phone numbers of a contact
void displayPhoneNumbers(PhoneNumberNode* phoneNumbers) {
    if (phoneNumbers == NULL) {
        printf("No phone numbers available.\n");
        return;
    }

    printf("Phone Numbers:\n");
    while (phoneNumbers) {
        printf("- %s\n", phoneNumbers->phoneNumber);
        phoneNumbers = phoneNumbers->next;
    }
}

// Function to display all contacts in alphabetical order (in-order traversal)
void displayContacts(ContactNode* root) {
    if (root == NULL) return;

    displayContacts(root->left);
    printf("Name: %s\n", root->name);
    displayPhoneNumbers(root->phoneNumbers);
    printf("\n");
    displayContacts(root->right);
}
// Function to find the minimum value node in a BST
ContactNode* findMin(ContactNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
// Function to delete a contact by name
ContactNode* deleteContact(ContactNode* root, char* name) {
    if (root == NULL) {
        printf("Contact not found.\n");
        return NULL;
    }

    if (strcmp(name, root->name) < 0) {
        root->left = deleteContact(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = deleteContact(root->right, name);
    } else {
        // Contact found
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            ContactNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            ContactNode* temp = root->left;
            free(root);
            return temp;
        } else {
            ContactNode* temp = findMin(root->right);
            strcpy(root->name, temp->name);
            root->phoneNumbers = temp->phoneNumbers;  // Assuming phone numbers are transferred.
            root->right = deleteContact(root->right, temp->name);
        }
    }
    return root;
}


// Main Function
int main() {
    ContactNode* root = NULL;
    int choice;
    char name[50], phoneNumber[15];

    do {
        printf("\nContact Management System\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display All Contacts\n");
        printf("4. Add Phone Number to Contact\n");
        printf("5. Delete contact\n");
        printf("6.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add Contact
                printf("Enter contact name: ");
                getchar(); // To clear the newline from input buffer
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove trailing newline
                root = insertContact(root, name);
                printf("Contact added successfully!\n");
                break;

            case 2:
                // Search Contact
                printf("Enter contact name to search: ");
                getchar();
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';

                ContactNode* contact = searchContact(root, name);
                if (contact) {
                    printf("Contact found: %s\n", contact->name);
                    displayPhoneNumbers(contact->phoneNumbers);
                } else {
                    printf("Contact not found.\n");
                }
                break;

            case 3:
                // Display All Contacts
                printf("All Contacts:\n");
                displayContacts(root);
                break;

            case 4:
                // Add Phone Number
                printf("Enter contact name: ");
                getchar();
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';

                contact = searchContact(root, name);
                if (contact) {
                    printf("Enter phone number to add: ");
                    fgets(phoneNumber, 15, stdin);
                    phoneNumber[strcspn(phoneNumber, "\n")] = '\0';

                    addPhoneNumber(contact, phoneNumber);
                } else {
                    printf("Contact not found.\n");
                }
                break;
                
            case 5:
                // Delete Contact
                printf("Enter contact name to delete: ");
                getchar();
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';
                root = deleteContact(root, name);
                printf("Contact deleted successfully (if it existed)!\n");
                break;

            case 6:
                // Exit
                printf("Exiting...\n");
                exit(0);
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
