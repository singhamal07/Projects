#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#define DEBUG 0
using namespace std;

typedef struct acc_type {
     char bank_name[300];
     char bank_branch[300];
     char acc_holder_name[300];
     char acc_number[300];
     double available_balance;
} Acc_type;

typedef struct  otp_data
{
  char acc_number[300];
  int otp;
} Otp_data;

vector<Acc_type> accounts;
vector<Otp_data> otp_data;

char * gets(char *);
void Create_new_account();
void Cash_Deposit();
void Cash_withdrawl();
void Display_options();
void Display_options_OTP();
void Display_options_Transfer();
void Generate_OTP();
void Generate_OTP_operation();
void Display_OTP(char input[300], int otp);
void Transfer();
int valid_otp(int otp, Acc_type a);
int Find_Account(char input[300]);
void Transfer_amount_with_OTP();

/* Utility functions */
int Get_Number_of_Accounts() { return accounts.size(); }
void List_All_Accounts();
void Display_account(Acc_type i);
int Check_unique_account(char input[300]);
void Clear_OTP(int otp);
void ListOTP();
int Check_unique_otp(int otp);

/* main program */
int main() 
{   
    int option;
    printf("\n***** Welcome to Amal Bank Application *****\n");
    while(true) 
    {
       Display_options();
       printf("Please enter any options (1/2/3/4/5/6/0) ");
       printf("to continue : ");
       scanf("%d", &option); 
       switch(option)  
       {
          case 1:  
                   Create_new_account();
                   break;
          case 2: 
                    Cash_Deposit();
                    break;
          case 3: 
                    Cash_withdrawl();
                    break;
          case 4: 
                    List_All_Accounts();
                    break;

          case 5:   
                    Transfer();
                    break;
          case 6: 
                    Generate_OTP();
                    if(DEBUG)
                    ListOTP();
                    break;
          case 0: 
                    return 0;
          default :
                    printf("%d is !!! INVALID OPTION !!!\n", option);
                    break;
        }
    }
    return 0;
}

void ListOTP() {
  for(int i = 0; i < otp_data.size(); ++i) {
    printf("%s, %d\n",otp_data[i].acc_number,otp_data[i].otp);
  }
}

int Check_unique_otp(int otp) {
   if(otp == 0) return 1;
   for(int i = 0; i < otp_data.size(); ++i) {
     if(otp_data[i].otp == otp)
      return 0;
   }
   return 1;
}

/* Function to create new account */
void Create_new_account() 
{
 
   Acc_type new_account;
   char input[300];

   printf ("Enter bank name (Default: (ASB) Amal State Bank) :\n");
   gets(input);
   gets(input);
   
   if(!strcmp(input,"")) 
     strcpy(input,"(ASB) Amal State Bank");
   
   strcpy(new_account.bank_name,input);
   
   printf ("Enter bank name (Default: Silk board) : \n");
   
   gets(input);
   
   if(!strcmp(input,"")) 
     strcpy(input,"Silk board");

   strcpy(new_account.bank_branch, input);

   printf("Enter account holder name: \n");
   gets(input);
   strcpy(new_account.acc_holder_name,input);

   printf("Enter account Number: \n");
   scanf("%s",input);
   strcpy(new_account.acc_number,input);

   if(!Check_unique_account(new_account.acc_number)) {
     printf("Account creation Failed, account number already in use, Try again.\n\n");
     return;
   }

   printf("Enter intial balance deposit : \n");
   scanf("%lf",&new_account.available_balance);

   //pushing account structure in vector
   accounts.push_back(new_account);

   printf("\nAccount has been created successfully \n\n");
   printf("Bank name              : %s \n" , new_account.bank_name);
   printf("Bank branch            : %s \n" , new_account.bank_branch);
   printf("Account holder name    : %s \n" , new_account.acc_holder_name);
   printf("Account number         : %s \n" , new_account.acc_number);
   printf("Available balance      : %.2lf \n" , new_account.available_balance);
}

// To list all accounts
void List_All_Accounts()
{
   for( int i = 0; i < accounts.size(); ++i ) {
       printf("\nAccount Info Record : %d\n\n", i + 1);
       Display_account(accounts[i]);
   }

}

void Display_account(Acc_type a) {

    printf("Bank name              : %s \n" , a.bank_name);
    printf("Bank branch            : %s \n" , a.bank_branch);
    printf("Account holder name    : %s \n" , a.acc_holder_name);
    printf("Account number         : %s \n" , a.acc_number);
    printf("Available balance      : %.2lf \n" , a.available_balance);  
}

void Generate_OTP() {
  int option;
   while(true) 
   {
       Display_options_OTP();
       printf("Enter option to continue .... ");
       scanf("%d",&option);
       switch(option) 
       {
          case 1:
                  Generate_OTP_operation();
                  break;
          case 0:
                  return; 
          default:
                printf("Selected Option \"%d\" is Invalid, please select option 1 or 0 \n",option);
       }
   }
}

void Generate_OTP_operation() 
{
     char input[300];
     printf("Enter account number: ");
     scanf("%s",input);
     int account_index = Find_Account(input);
     if (account_index == -1) {
       printf("Account not found [%s] \n", input);
       return;
     }
     Otp_data o;
     int otp = 0;
     while (otp < 1000 && Check_unique_otp(otp)) {
          otp = rand() % 10000;
     }
     strcpy(o.acc_number,accounts[account_index].acc_number);
     o.otp = otp;
     otp_data.push_back(o);
     Display_OTP(o.acc_number,o.otp);
     if(DEBUG)
     ListOTP(); // remove this
}

void Display_OTP(char acc_number[300], int otp) {
    printf("OTP: %d\n", otp);
    printf("This OTP is valid for account number: %s\n\n",acc_number);
}

int Find_Account(char input[300]) 
{
    for( int i = 0; i < accounts.size(); ++i ) {
       if(!strcmp(input,accounts[i].acc_number))
        return i;
    } 
    return -1;
}

// Function to deposit amount in an account
void Cash_Deposit()
{
    char input[300];
    double amount;
    printf("Enter the account number: ");
    scanf("%s",input);
    int account_index = Find_Account(input);
    if(account_index == -1) {
       printf("Account not found [%s] \n", input);
       return;
    }
    printf("Enter the amount to deposit : ");
    scanf("%lf",&amount);
    if(amount <= 0)
    {
       printf("Invalid amount\n");
       return;
    }
    accounts[account_index].available_balance += amount;
    printf("\n ******* Account information *******\n");
    Display_account(accounts[account_index]);
}

void Transfer_amount() {
    char input[300];
    double amount;
    int otp;
    printf("Enter your account number: ");
    scanf("%s",input);
    int account_index_source = Find_Account(input);
    if(account_index_source == -1) {
       printf("Account not found [%s] \n", input);
       return;
    }
    printf("Enter destination account number: ");
    scanf("%s",input);
    int account_index_dest = Find_Account(input);
    if(account_index_source == -1) {
       printf("Account not found [%s] \n", input);
       return;
    }
    printf("Enter the amount to Transfer : ");
    scanf("%lf",&amount);
    if(amount <= 0)
    {
       printf("Invalid amount\n");
       return;
    }
    if(amount > accounts[account_index_source].available_balance) {
       printf("Insufficient balance in Account.\n");
       return;
    }
    printf("Enter the OTP generated for account %s : ",accounts[account_index_source].acc_number);
    scanf("%d",&otp);
    if(valid_otp(otp,accounts[account_index_source]))
    {
      accounts[account_index_source].available_balance -= amount;
      accounts[account_index_dest].available_balance += amount;
      printf("Amount transferred successfully\n\n");
      printf("\n ******* Account information *******\n");
      Display_account(accounts[account_index_source]);
      Clear_OTP(otp);
      ListOTP(); // remove this
      return;
    }
    printf("Invalid OTP, transaction failed.\n\n");
    return;
}

int valid_otp(int otp, Acc_type a)
{
   for(int i = 0; i < otp_data.size(); ++i) {
      if( !strcmp(otp_data[i].acc_number,a.acc_number) && otp_data[i].otp == otp)
        return 1;
   }  
   return 0;
}

void Cash_withdrawl()
{
    char input[300];
    double amount;
    printf("Enter the account number: ");
    scanf("%s",input);
    int account_index = Find_Account(input);
    if(account_index == -1) {
       printf("Account not found [%s] \n", input);
       return;
    }
    printf("Enter the amount to withdraw : ");
    scanf("%lf",&amount);
    if(amount <= 0)
    {
       printf("Invalid amount\n");
       return;
    }
    if(amount > accounts[account_index].available_balance) {
       printf("Insufficient balance in Account.\n");
       return;
    }
    accounts[account_index].available_balance -= amount;
    printf("\n ******* Account information *******\n");
    Display_account(accounts[account_index]);
}

void Transfer()
{
   int option = 0;
   while(true) {
       Display_options_Transfer();
       scanf("%d",&option);
       switch(option) {
           case 1:
               Generate_OTP();
               break;
           case 2:
               Transfer_amount();
               break;
           case 0:
             return;
          default:
             printf("Invalid option: %d\n", option);
             break;

       }
    }
}

/*Function to display available options in this application*/
void Display_options()
{
    printf("\nMenu Options\n");
    printf("\n1. Create new account \n");
    printf("\n2. Cash Deposit \n");
    printf("\n3. Cash withdrawl \n");
    printf("\n4. Account information \n");
    printf("\n5. Transfer \n");
    printf("\n6. Generate OTP\n");
    printf("\n0. Exit Application \n");
    printf("\n\n");
}

void Display_options_OTP() {
    printf("\nOTP Generation sub-Menu\n");
    printf("\n1. Enter account number for which OTP generation is required. \n");
    printf("\n0. Back to main menu \n");
    printf("\n\n"); 
}

void Display_options_Transfer() {
    printf("\nTransfer Amount sub-Menu\n");
    printf("\n1. Generate OTP \n");
    printf("\n2. Already have OTP \n");
    printf("\n0. Back to main menu \n");
    printf("\n\n"); 
}

int Check_unique_account(char input[300])
{
   for(int i = 0; i < accounts.size(); ++i) {
      if(!strcmp(input,accounts[i].acc_number))
        return 0;
   }
   return 1;
}

void Clear_OTP(int otp) {
  int i = 0; 
  for(;i < otp_data.size(); ++i)
  {
      if(otp_data[i].otp == otp)
        break;
  }
  otp_data.erase(otp_data.begin() + i);
}

char * gets (char *s)
{
    char * ch = s;
    int k;
    while ((k = getchar ()) != '\n') {

        if (k == EOF) {
            if (ch == s || !feof(stdin)) 
                return NULL;
            break;
        }
        *ch++ = k;
    }
    *ch = '\0';
    return s; 
}
