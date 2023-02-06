#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// header.h should be imported to provide structures User, Record, and some functions declared inside. Not flexible stuff
// The "owner.c" was created from zero point and added to project, as the modification of the make file too.
// import replacement . Some code bottom is duplication of solutions(with tiny refactoring) but with different names, to prevent conflicts of #include result, and compiler fails, and in same time to do not break the original code provided as task template

#define BUFFER_SIZE 1000 // need to allow "scanf" work properly, with not enough buffer size could be crushes (segmentation fault etc) in time of reading inputs 

// menu, choose 1 to go back to main menu and choose 0 to exit
void successOwner(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid; // input was not correct, repeat request again
    }
}

// This is just simulation of boolean return, and in same time incoming parameters(structures in this case) passed by reference "*" will be updated in time of function execution.
//
// The "fscanf" will read the stream according to format string and parse the separated stream line into variables determined by format.
//
// After that formatted and parsed values will be passed to structure "r" of type "Record" as values for feilds.
//
// The structure "r" is passed into function by reference, so it will be just updated/refreshed on place.
int getAccountFromFileOwner(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %d/%d/%d %d/%d/%d %s %d %lf %s",
                  &r->id,
		  &r->userId,
		  name,
                  &r->accountNbr,
                  &r->created.month,
                  &r->created.day,
                  &r->created.year,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  &r->withdraw.month,
                  &r->withdraw.day,
                  &r->withdraw.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}


// account transfer ownership implementation

int findFreeAccountNumber(FILE *ptr, char *userName, struct Record *r){
    int acnum = 1; // first account number for check
    int free = 0; // account number "acnum" is free for user, not used in system
    char *acname; // gap for scanf testing
    
    while (free == 0){ //do while free number not found
        free = 1; // let is guess the number is free by default
        rewind(ptr); // jump to the beginning of the stream. To read opened file "ptr" from beginning again
        while (getAccountFromFileOwner(ptr, acname, r)) { // returns 0 when no string inside "ptr" file pointer can be  read anymore. And inside function the structures just refreshed every time using new scanned data.
            if(r->accountNbr == acnum && strcmp(acname, userName) == 0){
                free =  0; //if account number "acnum" was found inside scanned data, confirm that this number is already used as account number for selected user(check of user name is the second part of "if" statement condition)
                break; // break the loop, because number is not unique and can not be used as account number for required user
            }
        }
        if(free == 1){ // After full check , the number was not detected as number of the account of the required user, so the number can be used for new account of this user.
            break; // stop the check and use the free number
        }else{acnum++;} // increment number and check again on the next step of loop
    }
    if (free == 1){return acnum;}else{return 0;} // if free number found return "acnum", else return 0 as false simulation(but generally zero and negative number of account is not deprecated, just for comfort not positive numbers was not used)
}

// addresses for pointer to files

// to check new owner name is in the system
const char *USERSOWNER = "./data/users.txt";
// to manage accounts
const char *RECORDSOWNER = "./data/records.txt";
// to manage template file
const char *TEMPRECORDSOWNER = "./data/temprecords.tmp";

// the user is registered in the system at the moment
int isUser(char *name)
{
    FILE *fp; // create file pointer object
    struct User userChecker;
    if ((fp = fopen(USERSOWNER, "r")) == NULL) // open file with check it was no errors
    {
        printf("Error! opening file");
        exit(1); // exit from the programm with status
    }
    while (fscanf(fp, "%i %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    { // scan file pointer "fp" as stream with formatting according "%i %s %s" and parsing to the "User"(userChecker.*) structure fields
        if (strcmp(userChecker.name, name) == 0)
        { // compare the user name which was found in data (userChecker.name) with tested "name"
            fclose(fp); // close file pointer stream
            return 1; // user  found, 1 is simulation of "true"
        }
    }
    fclose(fp); // close the stream
    return 0; // user not found, 0 is simulation of "false"
}


// update account implementation

// update account

// update line in data file using new incoming data
void updateLineOwner(FILE *src, FILE *temp, const int line, struct Record *r, struct User u){
    char buffer[BUFFER_SIZE];
    int count = 1;
    while ((fgets(buffer, BUFFER_SIZE, src)) != NULL){ // fgets is like fscanf but read not the first sequence before whitespace or new line but read the full string from file(opened as stream)
        if (line != count){ // if the line is not the line, which we planned to update, then just put it into file without modifications
            fputs(buffer, temp); // put the line which was read from stream using "fgets" into template file(opened as stream) "temp"
        }else{
            char* sline; // declaire new variable for store string
            // "asprintf" is more safe way of "sprintf", but it is fresh realisation, and can cause some warnings(include compiler warnings) if environment is not very good meet the requirements for use "asprintf"
            asprintf(&sline, "%d %d %s %d %d/%d/%d %d/%d/%d %d/%d/%d %s %d %.2lf %s\n",
            r->id,
	    r->userId, // reading from structure. Arrow "->" because structure passed by reference "*r"
	    u.name, // reading from structure. Dot "." because structure passed by value "u", but NOT by reference "*u"
            r->accountNbr,
            r->created.month,
            r->created.day,
            r->created.year,
            r->deposit.month,
            r->deposit.day,
            r->deposit.year,
            r->withdraw.month,
            r->withdraw.day,
            r->withdraw.year,
            r->country,
            r->phone,
            r->amount,
            r->accountType);
            fputs(sline, temp); // put data into file(opened as stream)
        }
        count++; // increment +1
    }
}

// "const int line" is line number in file where account data placed
void updateAccountOwner(const int line, struct Record r, struct User u){
   FILE *src; // file pointer
   FILE *temp; // same
   
   src = fopen(RECORDSOWNER, "r"); // open for read
   temp = fopen(TEMPRECORDSOWNER, "w"); // open for write
   if (src == NULL || temp == NULL){ // some fail happens with opening of files
      printf("Unable to open file.\n");
      exit(EXIT_FAILURE); // exit the programm
   }
   
   // Move src file pointer to beginning
   rewind(src);
   // Update given line inside file.
   updateLineOwner(src, temp, line, &r, u);
   /* Close all open files */
   fclose(src); // close file pointer(stream)
   fclose(temp); // same
   /* Delete src file and rename temp file as src */
   remove(RECORDSOWNER); // remove file
   rename(TEMPRECORDSOWNER, RECORDSOWNER); // rename file with "old" name(it was template file) to "new" name(the name of the file removed above)
}

// transfer ownership upper level function
void transferOwnership(struct User u){
    int acnum = 0; // account number property(structure field)
    int strnum = 0; // number of line of the account data in the file
    int acfound = 0; // boolean simulation
    char userName[100]; // string to manage user name
    struct Record r; // to manage account data properly

    FILE *pf = fopen(RECORDSOWNER, "r"); // open for read

    system("clear"); // clear visible terminal area
    printf("\t\t====== %s, enter your account number to transfer ownership =====\n\n", u.name);
    scanf("%d",&acnum); // scan desired account number

    // checking/searching of requested account among of logged in user accounts
    while (getAccountFromFileOwner(pf, userName, &r))
    { // iteration of all accounts in the data file
        strnum++;
        if (strcmp(userName, u.name) == 0 && r.accountNbr == acnum)
        { // requested user account found. The user name and account number are as required
            printf("_____________________\n");
            printf("\nAccount number: %d\nCreation Date: %d/%d/%d\ncountry:%s\nPhone number: %d\nAmount deposited: $%.2f\nType Of Account: %s\n\n",
                   r.accountNbr,
                   r.created.day,
                   r.created.month,
                   r.created.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType); // print account info in terminal
            acfound = 1; // account found , break the while loop
            break;
        }
    }
    fclose(pf); // close file(stream)
    // check the new user name for account and calculate new account number free for new owner
    if (acfound){
        char newowner[100]; // for desirable name for the new account owner
        nameagain: // label for "goto" operator
        printf("\nEnter the new owner name for your account %d: ", acnum);
        
        fscanf(stdin, "%s", newowner); // scan and parse stdin (standart input) with format of result "string" to variable "newowner"
        // if no user with given name found then request new name
        if(!isUser(newowner)){ // execute code inside if newowner is not registered in system
            printf("User %s not found", newowner);
            goto nameagain; // jump and make request for another user name as new desired owner for account
        }

        
        char oldowner[100]; // previous owner of account
        strcpy(oldowner, userName); // recommended way to copy value of "userName" into "oldowner" variable.

        // find free account number, among the owned accounts of new owner
        struct Record rn; // dummy structure for safe managing of the data
        FILE *pf = fopen(RECORDSOWNER, "r"); // open file pointer for read
        int newnum = findFreeAccountNumber(pf, newowner, &rn); //find free number for the new account of new owner
        fclose(pf); // close the file(stream)
        if (newnum){ // new owner is registered user and have free number for new account
            strcpy(u.name, newowner); // u.name used just to prevent extra refactoring of code, r.name is possible to use too
            r.accountNbr = newnum; // set Record.accountNbr value to "newnum", to prepare data for replace data inside data file
            updateAccountOwner(strnum*2-1, r, u); // to update other account data
            strcpy(u.name, oldowner); // copy "oldowner" value to "u.name"
            system("clear"); // clear the terminal
            printf("\naccount %d old owner: %s", acnum, oldowner);
            printf("\naccount %d new owner: %s", acnum, newowner);

            printf("\nAccount number %d was updated!\n", acnum);
        }else{
            printf("User %s do not have free numbers for new account number", newowner);
        }
    }else{
        printf("\nAccount number %d was not found!\n", acnum);
    }
    successOwner(u); // call the choose menu ... 1 -> main menu , 0 -> exit
}
