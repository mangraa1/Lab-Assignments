#include <iostream>

using namespace std;

struct User {
    string username;
    string password;
};

void createUserBase(User *admin, User *user, int usersCount);
void authorization(User *admin, User *user, int usersCount);
void userInterface(User *user, int index);
void adminInterface(User *admin, User *user, int usersCount);

int main() {
    const int usersCount = 5;
    User admin;
    User user[usersCount];

    createUserBase(&admin, user, usersCount);
    authorization(&admin, user, usersCount);
}

void createUserBase(User *admin, User *user, int usersCount) {
    for (int i = 0; i < usersCount; i++) {
        user[i].username = "User " + to_string(i + 1);
        user[i].password = "user" + to_string(i + 1);
    }
    admin->username = "Administrator";
    admin->password = "admin123";
}

void authorization(User *admin, User *user, int usersCount) {
    string username = "";
    string password = "";
    bool isMoreThanThree = false;
    bool usernameExists = false;
    int loginAttempts = 0;

    while (!isMoreThanThree) {
        cout << "Enter username: ";
        getline(cin, username);
        usernameExists = false;

        for (int i = 0; i < usersCount; i++) {
            if (username == user[i].username || username == admin->username) {
                usernameExists = true;

                cout << "Enter password: ";
                getline(cin, password);

                for (int j = 0; j < 3; j++) {
                    if (password == user[i].password) {
                        cout << endl << "You are logged in" << endl;
                        userInterface(user, i);
                        goto endOfSession;
                    }
                    if (username == admin->username && password == admin->password) {
                        cout << endl << "You are logged in" << endl;
                        adminInterface(admin, user, usersCount);
                        goto endOfSession;
                    }
                    cout << "Password is not correct" << endl;
                }
                cout << endl << "End of session" << endl << endl;
            }
        }

        if (usernameExists) {
            loginAttempts += 1;
            if (loginAttempts >= 3) {
                isMoreThanThree = true;
                cout << "Unauthorized access attempt. Session terminated" << endl;
            }
        } else {
            cout << "Username is not correct" << endl << endl;
        }
    }

endOfSession:
    cout << "";
}

void userInterface(User *user, int index) {
    char choice = '\0';
    string newPassword = "";

    cout << endl << "Do you want to change your password (y/n)?" << endl;

    while (choice != 'y' && choice != 'n') {
        cout << "Enter choice: ";
        cin >> choice;
    }

    if (choice == 'y') {
        cout << "Enter new password: ";

        cin.ignore();
        getline(cin, newPassword);

        user[index].password = newPassword;
        cout << endl << "Username: " << user[index].username << endl
             << "Password: " << user[index].password << endl;
    } else {
        cout << endl << "Ok, bye!" << endl;
    }
}

void adminInterface(User *admin, User *user, int usersCount) {

    char choice = '\0';
    string usernameToChangePass = "";
    string newPassword = "";
    bool isCorrectlyUsername = false;

    cout << endl << "All users: " << endl;

    for (int i = 0; i < usersCount; i++) {
        cout << endl << "Username: " << user[i].username << endl
                     << "Password: " << user[i].password << endl;
    }

    cout << endl << "do you want to change the password of any user (y/n)?" << endl;

    while (choice != 'y' && choice != 'n') {
        cout << "Enter choice: ";
        cin >> choice;
    }

    if (choice == 'y') {
        cout << "Enter usename: ";
        cin.ignore();
        getline(cin, usernameToChangePass);

        while (!isCorrectlyUsername) {
            for (int i = 0; i < usersCount; i++) {
                if (user[i].username == usernameToChangePass) {
                    isCorrectlyUsername = true;

                    cout << "Enter new password: ";
                    cin.ignore();
                    getline(cin, newPassword);

                    user[i].password = newPassword;

                    cout << endl << "Username: " << user[i].username << endl
                                 << "Password: " << user[i].password << endl;
                    
                    break;
                }
            }
        }
    } else {
            cout << endl << "Ok, bye!" << endl;
    }
}