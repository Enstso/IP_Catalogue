#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isQuit = 0;

//  TO GET HOLD OF THE LAST INSERTED DATA'S ID
int get_Id()
{
    FILE *file = fopen("data.csv", "r");

    if (file == NULL)
    {
        printf("Failed to open the file for reading.\n");
        return 1;
    }

    char line[1024];
    int last_id = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        int line_id;
        if (sscanf(line, "%d", &line_id) == 1)
        {
            last_id = line_id;
        }
    }

    fclose(file);

    return last_id;
}

// ADD NEW IP/MASK INTO DATA.CSV
void add_ip()
{
    int id;
    char ip_address[33], mask[33];

    int last_id = get_Id();
    id = last_id + 1;

    FILE *file = fopen("data.csv", "a");

    if (file == NULL)
    {
        printf("Failed to open the file for writing.\n");
        return 1;
    }

    printf("Enter IP Address : ");
    scanf("%s", ip_address);
    printf("Enter Mask Address : ");
    scanf("%s", mask);

    fprintf(file, "\n%d, %s, %s", id, ip_address, mask);

    printf("\n\n");
    printf("The IP Address : %s and The Mask : %s are added successfully!", ip_address, mask);
    printf("\n\n");

    fclose(file);
}

//  TO PRINTOUT THE LIST OF IP ADDRESSES
int list_ip()
{
    FILE *file = fopen("data.csv", "r");

    if (file == NULL)
    {
        printf("Failed to open the file for reading.\n");
        return 1;
    }

    char line[1024];

    printf("+---------------------------------------------------------------+\n");
    printf("|                      IP Addresses List                        |\n");
    printf("+---------------------------------------------------------------+\n");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Split the line into tokens using strtok
        char *id = strtok(line, ",");
        char *ip_address = strtok(NULL, ",");
        char *mask = strtok(NULL, ",");

        int line_id;
        if (sscanf(line, "%d", &line_id) == 1)
        {
            printf("[%s]. \n", id);
            printf("      IP Address : %s\n", ip_address);
            printf("      Mask : %s\n", mask);
        }
    }

    fclose(file);
}

// PRINTOUT THE INTOR/HEADER PART (LOGO,GROUP-INFO,.....)
void logo()
{
    char Logo[] = "██╗██████╗░  ░█████╗░░░░░░░░█████╗░████████╗░█████╗░██╗░░░░░░█████╗░░██████╗░██╗░░░██╗███████╗ \n██║██╔══██╗  ██╔══██╗░░░░░░██╔══██╗╚══██╔══╝██╔══██╗██║░░░░░██╔══██╗██╔════╝░██║░░░██║██╔════╝ \n██║██████╔╝  ██║░░╚═╝█████╗███████║░░░██║░░░███████║██║░░░░░██║░░██║██║░░██╗░██║░░░██║█████╗░░ \n██║██╔═══╝░  ██║░░██╗╚════╝██╔══██║░░░██║░░░██╔══██║██║░░░░░██║░░██║██║░░╚██╗██║░░░██║██╔══╝░░ \n██║██║░░░░░  ╚█████╔╝░░░░░░██║░░██║░░░██║░░░██║░░██║███████╗╚█████╔╝╚██████╔╝╚██████╔╝███████╗ \n╚═╝╚═╝░░░░░  ░╚════╝░░░░░░░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝░╚════╝░░╚═════╝░░╚═════╝░╚══════╝";

    printf("\n\n");
    printf("%s \n", Logo);
    printf("\n\n");
    printf("Created by : \n\n");
    printf("    1.  JANVIER Enstso \n");
    printf("    2.  OUCHERIF Lounis \n");
    printf("    3.  FERNANDO PRICARD Diron Polson \n");
    printf("\n\n");

    printf("Press : \n");
    printf("a - Add a new IP address.\n");
    printf("l - List IP addresses.\n");
    printf("s - Search similar by mask.\n");
    printf("d - Delete an IP.\n");
    printf("q - quit.");
    printf("\n\n");
}

int main()
{

    logo();

    char select;

    while (isQuit == 0)
    {
        printf("Please choose one : ");
        scanf("%c", &select);

        switch (select)
        {
        case 'a':
            add_ip();
            break;
        case 'l':
            list_ip();
            break;
        case 's':
            //  SEARCH FUNCTION
            break;
        case 'd':
            //  DELETE FUNCTION
            break;
        case 'q':
            printf("Exiting....");
            isQuit = 1;
            break;
        default:
            printf("Please choose one from these options. \n");
            break;
        }
    }

    return 0;
}