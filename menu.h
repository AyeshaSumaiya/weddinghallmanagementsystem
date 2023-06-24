#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct CustomerDetails // STRUCTURE DECLARATION
{
    char hallnumber[10];
    char name[20];
    char address[25];
    char phonenumber[15];
    char eventvenue[15];
    char email[20];
    char guest[10];
    char eventdate[10];
} s;

void add();
void list();
void edit();
int delete();
void search();

void menu()
{
    int i = 0;
    time_t t;
    time(&t);
    char choice;

    while (1)
    {
        system("cls");
        printf("\t\t=============================================\n");
        printf("\t\t|                                           |\n");
        printf("\t\t|       ----------------------------        |\n");
        printf("\t\t|      WEDDING HALL BOOKING SYSTEM          |\n");
        printf("\t\t|       ----------------------------        |\n");
        printf("\t\t|                                           |\n");
        printf("\t\t|                                           |\n");
        printf("\t\t|                                           |\n");
        printf("\t\t============================================\n\n\n");
        for (int i = 0; i < 80; i++)
            printf("-");
        printf("\n");
        printf("\t\t\t| MAIN MENU |  \n");
        for (i = 0; i < 80; i++)
            printf("-");
        printf("\n");
        for (i = 0; i < 80; i++)
            printf("-");
        printf("\nDate and Time: %s", ctime(&t));
        for (i = 0; i < 80; i++)
            printf("-");
        printf(" \n 1. Book a wedding hall");
        printf(" \n 2. View Customer Details");
        printf(" \n 3. Delete Customer Details");
        printf(" \n 4. Search Record");
        printf(" \n 5. Update Record");
        printf(" \n 6. Exit\n");
        printf("\t\t Select an option:\n\n");
        choice = getche();
        choice = toupper(choice);

        switch (choice)
        {
        case '1':
            add();
            break;
        case '2':
            list();
            break;
        case '3':
            delete();
            break;
        case '4':
            search();
            break;
        case '5':
            edit();
            break;
        case '6':
            system("cls");
            printf("\n\n\t ****THANK YOU****");
            printf("\n\t FOR TRUSTING OUR SERVICE");
            getch();
            exit(0);
            break;
        default:
            system("cls");
            printf("Incorrect Input");
            printf("\n Press any key to continue");
            getch();
        }
    }
}

void add()
{
    FILE *f;
    char test;
    f = fopen("cus.txt", "a+");
    if (f == 0)
    {
        f = fopen("cus.txt", "w+");
        system("cls");
        printf("\n Process completed. Press any key to continue!");
        getch();
    }
    while (1)
    {
        system("cls");
        printf("\n Enter Customer Details:");
        printf("\n**************************");
        printf("\n Enter Hall number: ");
        scanf("%s", s.hallnumber);
        printf("\nEnter Name: ");
        scanf(" %[^\n]", s.name);
        printf("\nEnter Address: ");
        scanf(" %[^\n]", s.address);
        printf("\nEnter Phone Number: ");
        scanf("%s", s.phonenumber);
        printf("\nEnter the Venue of the event: ");
        scanf(" %[^\n]", s.eventvenue);
        printf("\nEnter Email: ");
        scanf("%s", s.email);
        printf("\nEnter guests amount: ");
        scanf("%s", s.guest);
        printf("\nEnter Event date (dd/mm/yyyy): ");
        scanf("%s", s.eventdate);
        fwrite(&s, sizeof(s), 1, f);
        fflush(stdin);
        printf("\n\n1 Wedding Hall is successfully booked!!");
        printf("\n Press esc key to exit, any other key to add another customer detail:");
        test = getche();
        if (test == 27)
            break;
    }
    fclose(f);
}

void list()
{
    FILE *f;
    int i;
    if ((f = fopen("cus.txt", "r")) == NULL)
        exit(0);
    system("cls");
    printf("HALL \t");
    printf("NAME \t ");
    printf("\tADDRESS ");
    printf("\tPHONENUMBER ");
    printf("\tEVENTVENUE ");
    printf("\tEMAIL ");
    printf("\t\t  GUEST ");
    printf("\t EVENTDATE \n");

    for (i = 0; i < 118; i++)
        printf("-");
    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        printf("\n%s \t%s \t\t%s \t\t%s \t%s  \t%s  \t     %s  \t  %s", s.hallnumber, s.name, s.address, s.phonenumber, s.eventvenue, s.email, s.guest, s.eventdate);
    }
    printf("\n");
    for (i = 0; i < 118; i++)
        printf("-");

    fclose(f);
    getch();
}

int delete()
{
    FILE *f, *t;
    int i = 1;
    char hallnumber[20];
    if ((t = fopen("temp.txt", "w")) == NULL)
        exit(0);
    if ((f = fopen("cus.txt", "r")) == NULL)
        exit(0);
    system("cls");
    printf("Enter the Hall Number to delete from the database: \n");
    fflush(stdin);
    scanf("%s", hallnumber);
    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        if (strcmp(s.hallnumber, hallnumber) == 0)
        {
            i = 0;
            continue;
        }
        else
            fwrite(&s, sizeof(s), 1, t);
    }
    if (i == 1)
    {
        printf("\n\n Records of the customer in this Hall number are not found!!");

        getch();
        fclose(f);
        fclose(t);
        return 1;
    }
    fclose(f);
    fclose(t);
    remove("cus.txt");
    rename("temp.txt", "cus.txt");
    printf("\n\nThe customer record is successfully removed....");
    fclose(f);
    fclose(t);
    getch();
}

void search()
{
    system("cls");
    FILE *f;
    char hallnumber[20];
    int flag = 1;
    f = fopen("cus.txt", "r+");
    if (f == 0)
        exit(0);
    fflush(stdin);
    printf("Enter the Hall number of the customer to search for their details: \n");
    scanf("%s", hallnumber);
    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        if (strcmp(s.hallnumber, hallnumber) == 0)
        {
            flag = 0;
            printf("\n\tRecord Found\n ");
            printf("\nHall Number:\t%s", s.hallnumber);
            printf("\nName:\t%s", s.name);
            printf("\nAddress:\t%s", s.address);
            printf("\nPhone number:\t%s", s.phonenumber);
            printf("\nEvent Venue:\t%s", s.eventvenue);
            printf("\nEmail:\t%s", s.email);
            printf("\nGuest:\t%s", s.guest);
            printf("\nEvent date:\t%s", s.eventdate);
            flag = 0;
            break;
        }
    }
    if (flag == 1)
    {
        printf("\n\tRequested Customer could not be found!");
    }
    getch();
    fclose(f);
}

void edit()
{
    FILE *f;
    int k = 1;
    char hallnumber[20];
    long int size = sizeof(s);
    if ((f = fopen("cus.txt", "r+")) == NULL)
        exit(0);
    system("cls");
    printf("Enter the Hall number of the customer to edit:\n\n");
    scanf("%s", hallnumber);
    fflush(stdin);
    while (fread(&s, sizeof(s), 1, f) == 1)
    {
        if (strcmp(s.hallnumber, hallnumber) == 0)
        {
            k = 0;
            printf("\nEnter Hall Number: ");
            scanf("%s", &s.hallnumber);
            fflush(stdin);
            printf("Enter Name: ");
            scanf("%s", &s.name);
            printf("Enter Address: ");
            scanf("%s", &s.address);
            printf("Enter Phone Number: ");
            scanf("%s", &s.phonenumber);
            printf("Enter Event Venue: ");
            scanf("%s", &s.eventvenue);
            printf("Enter Email: ");
            scanf("%s", &s.email);
            printf("Enter Guests amount: ");
            scanf("%s", &s.guest);
            printf("Enter Event date (dd/mm/yyyy): ");
            scanf("%s", &s.eventdate);
            fseek(f, -size, SEEK_CUR);
            fwrite(&s, sizeof(s), 1, f);
            break;
        }
        fflush(stdin);
    }
    if (k == 1)
    {
        printf("\n\n THE HALL NUMBER DOES NOT EXIST!!!!");
        fclose(f);
        getch();
    }
    else
    {
        printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!");
        fclose(f);
        getch();
    }
}
