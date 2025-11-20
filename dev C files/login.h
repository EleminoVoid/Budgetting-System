

struct User {
    char username[50];
    char password[50];
};
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//prototypes

struct User createUser();

// Check if the given username and password match with any user in the "users.txt" file
// Returns 1 if the user is authenticated, 0 otherwise
int login(char* username, char* password);

// Add the given user to the "users.txt" file
void addUser(struct User newUser);

// Count the number of users in the "users.txt" file
int countUsers();

// Display a login menu and perform the corresponding actions
// Returns 0 if the user chooses to quit
int loginMenu();

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct User createUser() {
    struct User newUser;
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);
    return newUser;
}

int login(char* username, char* password) {
    FILE* fp = fopen("DATA/users.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 0;
    }
    char line[100];
    while (fgets(line, 100, fp)) {
        char fileUsername[50];
        char filePassword[50];
        sscanf(line, "%s %s", fileUsername, filePassword);
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void addUser(struct User newUser) {
    FILE* fp = fopen("DATA/users.txt", "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    fprintf(fp, "%s %s\n", newUser.username, newUser.password);
    fclose(fp);
}

int countUsers() {
    FILE* fp = fopen("DATA/users.txt", "r");
    if (fp == NULL) {
        printf("No file found\n");
        return 0;
    }
    char line[100];
    int count = 0;
    while (fgets(line, 100, fp)) {
        count++;
    }
    fclose(fp);
    return count;
}

int loginMenu() {
    char input[50];
    int choice;
    int goThrough = 0;
    printf("Total users: %d\n", countUsers());
    do {
        printf("1. Login\n");
        printf("2. Sign up\n");
        printf("3. Exit\n");
        scanf("%s", input);
        choice = atoi(input);
        system("cls");
        if (choice == 1) {
            char username[50];
            char password[50];
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");
            scanf("%s", password);
            if (login(username, password)) {
                system("cls");
                printf("Login successful\n");
                goThrough = 1;
            } else {
                system("cls");
                printf("Invalid username or password\n");
                printf("Total users: %d\n", countUsers());
            }
        } else if (choice == 2) {
            if (countUsers() < MAX_USERS) {
                struct User newUser = createUser();
                addUser(newUser);
                system("cls");
                printf("User created\n");
                printf("Total users: %d\n", countUsers());
            } else {
                system("cls");
                printf("Max Users attained\n");
            }

        }else if (choice == 3) {
            	return 1;
            	break;
            } else {
            system("cls");
            printf("Invalid Input\n");
        }
    } while (goThrough != 1);

}

