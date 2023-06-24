#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

void saveLoginInfo(const char* username, const char* password)
{
    FILE* file = fopen("login_info.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing!");
        return;
    }

    fprintf(file, "%s\n%s", username, password);
    fclose(file);
}

int loadLoginInfo(char* username, char* password)
{
    FILE* file = fopen("login_info.txt", "r");
    if (file == NULL)
    {
        printf("No login info found. Please sign up.\n");
        return 0;
    }

    if (fscanf(file, "%s\n%s", username, password) != 2)
    {
        printf("Error reading login info from file.\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

void signup()
{
    char uname[10], pword[10];

    printf("\n============== SIGN UP ==============");
    printf("\n       ENTER USERNAME: ");
    scanf("%s", uname);
    printf("       ENTER PASSWORD: ");
    scanf("%s", pword);

    saveLoginInfo(uname, pword);

    printf("\n Sign up successful!\nNow log in to your account.");
    getch();
    login();
}

void login()
{
    int a = 0, i = 0;
    char uname[10], c = ' ';
    char pword[10], code[10];

    do
    {
        system("cls");
        printf("\n============== LOGIN FORM ==============");
        printf("\n       ENTER USERNAME: ");
        scanf("%s", uname);
        printf("       ENTER PASSWORD: ");

        while (i < 10)
        {
            pword[i] = getch();
            c = pword[i];
            if (c == 13)
                break;
            else
                printf("*");
            i++;
        }
        pword[i] = '\0';
        i = 0;

        char storedUsername[10], storedPassword[10];
        if (loadLoginInfo(storedUsername, storedPassword) && strcmp(uname, storedUsername) == 0 && strcmp(pword, storedPassword) == 0)
        {
            printf("\n\n\n       WELCOME! LOGIN IS SUCCESSFUL.\nPRESS ANY KEY TO CONTINUE.");
            getch();
            menu();
        }
        else
        {
            printf("\n       SORRY! LOGIN IS UNSUCCESSFUL");
            a++;
            getch();
        }
    }
    while (a <= 2);

    if (a > 2)
    {
        printf("\nSorry, you have entered the wrong username and password for four times!!!");
        getch();
        exit(0);
    }

    system("cls");
}

void loginmenu()
{
    int choice;

    do
    {
        system("cls");
        printf("\n============== MENU ==============");
        printf("\n 1. Sign up");
        printf("\n 2. Login");

        printf("\n\n Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            signup();
            break;
        case 2:
            login();
            break;

        default:
            printf("\n Invalid choice! Please enter a valid option.");
            getch();
        }
    }
    while (1);
}
