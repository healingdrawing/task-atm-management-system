# task-atm-management-system  
grit:lab Åland Islands 2022

To execute/test app:
- clone the repo
- open terminal in repo folder
- execute `make` command
- execute `./omg` command

Some code explanation are placed inside `src/auth.c` and `src/owner.c`

Some sources was used:
- https://www.w3schools.com/c/index.php
---
- https://www.programiz.com/c-programming/c-structures
---
- https://www.programiz.com/c-programming/c-unions
---
- https://www.programiz.com/c-programming/c-file-input-output
---
- https://stackoverflow.com/questions/11543341/reading-strings-integers-etc-from-files-using-fscanf
---
- https://www.tutorialspoint.com/c-program-to-remove-a-line-from-the-file#
---
- https://www.geeksforgeeks.org/how-to-print-using-printf/
---
- https://stackoverflow.com/questions/28744407/taking-date-as-dd-mm-yy-in-c-language
---
- https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program
---
- https://www.tutorialspoint.com/c_standard_library/time_h.htm
---
-  http://tpcg.io/_9Q9K0S online compiler
---
- https://stackoverflow.com/questions/153890/printing-leading-0s-in-c leading zeros print format
---
https://www.geeksforgeeks.org/getdate-and-setdate-function-in-c-with-examples/

# the testing task is terrible.

F.e. if you decided to use database then you can't pass the tests, because testing steps requires open text files, which you will do not have, because you use database ... facepalm

---
Type in the 5-caracters code we communicated you
Try running these instructions in your terminal to clone the correct version of the repo  
```
git clone https://01.gritlab.ax/git/lenivaya10003/atm-management-system
cd atm-management-system  
git reset --hard 5c7536d04d9f678267ddd0b688dfce2f1aeb5b6c  
```
Does the repo clone properly and not show an error (fatal: reference is not a tree: `5c7536d04d9f678267ddd0b688dfce2f1aeb5b6c`) ?
yes
no  

Functional
Open the application and register a new user with the name "Alice" and the password "q1w2e3r4t5y6".
Is this user saved in the file
"./data/users.txt"
, and if so, are all credentials correct (name and password)?
yes
no  

Open the application and re-register the user "Alice".
Did it display an error message stating that this user already exist?
yes
no  

Open the file "./data/users.txt".
Are all the user’s names unique? (ex: no repetition on the name Alice)
yes
no  

Try and login as "Alice".
Was Alice able to enter the main menu?
yes
no  

Try to create two accounts using the user Alice, then select the option "Update information of account" and select an account number that does not exist for Alice.
Did the application displayed some kind of error message stating that this account does not exist?
yes
no  

Resorting to the user Alice, try and select the option "Update information of account" and select one of the accounts you created for Alice.
Did the the application prompt a choice of updating the phone number or the country?
yes
no  

Resorting to the user Alice, try and select the option "Update information of account" and select one of the accounts you created for Alice. Then update the phone number of that account.
Was the phone number of that account updated in the application and the file
"records.txt"
?
yes
no  

Resorting to the user Alice, try and select the option "Update information of account" and select one of the accounts you created for Alice. Then update the country of that account.
Was the country of that account updated in the application and the file
"records.txt"
?
yes
no  

Resorting to the user Alice, try to create a new account with: date "10/10/2012" account number "834213", country "UK", phone number "291231392", deposit amount $"1001.20", type of account "saving". Then select "Check accounts" choose the account you just created.
Did the application displayed the account information and the gain of $5.84 of interest on day 10 of every month?
yes
no  

Resorting to the user Alice create again an account but with account number “320421” and type of account “fixed01” with the rest of the information as in the last account . Then select "Check accounts" and choose the account you just created.
Did the application displayed the account information and the gain of $40.05 of interest on 10/10/2013?
yes
no  

Resorting to the user Alice create again an account but with account number "3214" and type of account "fixed02" with the rest of the information as in the last account. Then select "Check accounts" and choose the account you just created.
Did the application displayed the account information and the gain of $100.12 of interest on 10/10/2014?
yes
no  

Resorting to the user Alice create again an account but with account number "3212" and type of account "fixed03" with the rest of the information as in the last account. Then select "Check accounts" and choose the account you just created.
Did the application displayed the account information and the gain of $240.29 of interest on 10/10/2015?
yes
no  

Resorting to the user Alice select the option "Make transaction". Then choose the account with the id "3212"
Are you able to choose between withdrawing or depositing?
yes
no  

Resorting to the user Alice select the option "Make transaction", choose the account with the id "3212". Then try to withdraw money.
Are you able to withdraw money?
yes
no  

And if so, was the withdraw updated in the file
"records.txt"
?
yes
no  

Is it not possible to withdraw an amount superior to your available balance?
yes
no  

Try to deposit money into the account "3212".
Were you able to deposit money into this account?
yes
no  

And if so did it update the file
"records.txt"
?
yes
no  

Resorting to the user Alice try to select the option "Remove existing account" and remove the accounts "834213", "320421" and "3214".
Can you confirm that those account were deleted, both in the application and file
"records.txt"
?
yes
no  

Resorting to the user Alice select the option "Remove existing account" and try to remove and nonexisting account.
Did the application prompt some type of error saying that the account does not exists?
yes
no  

Create another user named "Michel". Then by using Alice select the option "transfer owner" and try to transfer ownership of the account "3212" to Michel.
Were you able to transfer the ownership of this account to Michel? And if so did it update both application and file
"records.txt"
?
yes
no  

Bonus  

Open two terminals and login with two different users. Then transfer ownership of an account to the other user.
Was the user whom received the account notified instantly?Bonus
yes
no  

Did the student update the terminal interface?Bonus
yes
no  

Is the password saved in the file
"users.txt"
encrypted?Bonus
yes
no  

Did the student create a relational database? Bonus
yes
no  

Did the student make their own Makefile?Bonus
yes
no  

Did the student add more features to the project?Bonus
yes
no  

Did the student optimise the code already given?Bonus
yes
no  

