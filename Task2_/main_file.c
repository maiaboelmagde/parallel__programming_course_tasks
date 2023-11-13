#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

union Flag {
    int int_flag;
    bool bool_flag;
};

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    union Flag flag;
};

void registerUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter a username (max %d characters): ", MAX_USERNAME_LENGTH);
    scanf("%s", username);

    printf("Enter a password (max %d characters): ", MAX_PASSWORD_LENGTH);
    scanf("%s", password);

    union Flag flag;
    printf("Enter a flag (0/1, true/false): ");
    scanf("%d", &flag.int_flag); // User can enter 0/1
    if (flag.int_flag == 0) {
        flag.bool_flag = false;
    } else {
        flag.bool_flag = true;
    }

    // Save the username, password, and flag to a file (for demonstration purposes)
    FILE *file = fopen("users.txt", "a");
    if (file != NULL) {
        struct User user;
        strcpy(user.username, username);
        strcpy(user.password, password);
        user.flag = flag;
        fprintf(file, "%s %s %d\n", user.username, user.password, user.flag.int_flag);
        fclose(file);
        printf("User registered successfully.\n");
        printf("Username: %s\n", user.username);
        printf("Password: %s\n", user.password);
    } else {
        printf("Error: Unable to open file for writing.\n");
    }
}

void loginUser() {
    bool flag_active = false;

    // Check if the flag is active before allowing the user to log in
    FILE *file = fopen("users.txt", "r");
    if (file != NULL) {
        struct User user;

        while (fscanf(file, "%s %s %d", user.username, user.password, &user.flag.int_flag) != EOF) {
            if (user.flag.int_flag == 1 || user.flag.bool_flag == true) {
                flag_active = true;
                break;
            }
        }

        fclose(file);

        if (!flag_active) {
            printf("All user accounts are currently inactive. Please contact an administrator.\n");
            return;
        }
    } else {
        printf("Error: Unable to open file for reading.\n");
        return;
    }

    // Prompt the user to enter their username and password
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    // Check if the provided username and password match any stored credentials
    file = fopen("users.txt", "r");
    if (file != NULL) {
        struct User user;

        while (fscanf(file, "%s %s %d", user.username, user.password, &user.flag.int_flag) != EOF) {
            if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
                if (user.flag.int_flag == 1 || user.flag.bool_flag == true) {
                    printf("Login successful. Welcome, %s!\n", username);
                } else {
                    printf("Your account is not active. Please contact an administrator.\n");
                }
                fclose(file);
                return;
            }
        }

        fclose(file);

        printf("Invalid username or password. Please try again.\n");
    } else {
        printf("Error: Unable to open file for reading.\n");
    }
}

int main() {
    int choice, again=1;
    
    while (again) {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                printf("Visit Us Again.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
 
       }
       int check;
       printf("type 0 to quit "); 
       scanf("%d",&check);
       if(check==0) again=0; 
}

    return 0;
}

