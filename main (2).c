#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include "splashscreen.h" //header file that contains the function for splash screen
#include "menu.h"         //header file that contains the function for booking hall
#include "login.h"        //header file that contains the function for login

int main(void)
{
    system("COLOR E0");
    splashScreen();
    loginmenu();
    system("cls");
    menu();
    return 0;
}



