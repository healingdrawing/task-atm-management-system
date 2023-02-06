#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include "header.h"

const char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;
    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    while (fscanf(fp, "%i %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

// register new user implementation

// check the required name is not already present in the system
int isUserNameUnique(char a[50]){
    FILE *fp;
    struct User userChecker;
    if ((fp = fopen(USERS, "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    
    while (fscanf(fp, "%i %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, a) == 0)
        {
            fclose(fp);
            return 0; // the name is already in database
        }
    }

    fclose(fp);
    return 1; // the name is unique and can be used
}

// (no need to)generate unique index/id for new user
int newUserIndex(){
    return 11; // no need unique index, because the user name is unique(the task requirements).
}

// write the new user data
void saveUserToFile(char a[50], char pass[50])
{
    FILE *ptr = fopen(USERS, "a+"); // open file in mode a+(append data to the end of file)
    fprintf(ptr, "%d %s %s\n",
            newUserIndex(),
            a,
            pass);
    printf("user \"%s\" was added\n\n", a); // print data into file using format %d %s %s => number string string
}


// register new user menu
void registerMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags; // structs to  manipulate terminal output to hide output when password is required

    system("clear"); // clear the terminal and move coret to the upper part of visible area
    printf("\n\n\n\t\t\t\t   Bank Management System\n"); // print into terminal with format x3 newlines x4 tabulators from left
registerAgain: // mark for "goto" command to jump from inside loops or repeat some part of code again from this point(usefull for simple menu implementation, when data is not correct and you need to show input box again)
    printf("\n\t\t\t\t\t Enter new User Login(NO_SPACES): ");
    scanf("%s", a); // after press enter will try to scan first symbols sequence before new line or whitespace into variable. In this case "a" is variable. And "%s" said the result will be converted to string(https://www.freecodecamp.org/news/format-specifiers-in-c/)

    if (isUserNameUnique(a)){ // name is unique , can use it

    }else{ // name is already in database
        system("clear"); // clear the visible area of terminal output
        printf("Login is not unique. Use another\n"); // print inform message
        goto registerAgain; // jump up to label and repeat some code again
    }

    // disabling echo . Black magic disabling terminal input demonstration while user will type password
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    printf("\n\n\t\t\t\tEnter the new password(NO_SPACES):");
    char pass0[50];
    scanf("%s", pass0); // scan input to "pass0" as string, after press enter

    // second password attempt , to compare
    printf("\n\t\t\t\tRepeat the new password:");
    scanf("%s", pass); //  scan input to "pass0" as string, after press enter

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    // here terminal again will show inputs
    if (strcmp(pass0,pass) != 0) { // the passwords is NOT equals
        system("clear"); // clear terminal area
        printf("Passwords was not identical"); // print message
        goto registerAgain; // jump to label, and execute some code (again)
    }

    // new user data is ok, write to database
    saveUserToFile(a, pass);

};
