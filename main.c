#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseList(int arr[], int size)
{
    int start = size - 8;
    if (size == 8)
    {
        start = 0;
    }

    int end = size - 1;

    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

void hexa(int ipTab[4])
{

    for (int i = 0; i < 4; i++)
    {
        char hexa[100];
        int index = 0;
        int number = 0;
        number = ipTab[i];
         if(number==0){
            printf("0");
        }
        while (number)
        {
            int calc = number % 16;

            
            if (calc < 10)
            {
                hexa[index++] = calc + '0';
            }
            else
            {
                hexa[index++] = calc + 55;
            }

            number = number / 16;
        }

        for (int i = index - 1; i >= 0; i--)
        {
                printf("%c", hexa[i]);
        }
        printf(".");
    }
    printf("\n");
}

void bibine(int n, int tab[33], int size)
{
    int temp = 0;
    int bin = 0;
    int init = size - 8;
    if (size == 8)
    {
        int init = 0;
    }
    for (int i = init; i < size; i++)
    {

        if (n % 2 == 0)
        {
            tab[i] = 0;
            n /= 2;
        }
        else
        {
            tab[i] = 1;
            n /= 2;
        }
    }
    reverseList(tab, size);
}

void networkAdress(int ip[33], int mask[33], int networkAdress[33])
{
    int networkSum = 0;
    for (int i = 0; i < 33; i++)
    {
        if (ip[i] + mask[i] == 2)
        {
            networkAdress[i] = 1;
        }
        else
        {
            networkAdress[i] = 0;
        }
    }
}

int sameNetwork(int tab1[33], int tab2[33])
{
    int verif = 0;
    for (int i = 0; i < 33; i++)
    {
        if (tab1[i] != tab2[i])
        {
            verif = 1;
        }
    }
    return verif;
}

void splitIP(int tab[], char ip[])
{
    char copy[strlen(ip) + 1];
    strcpy(copy, ip);

    char *traitement = NULL;
    int i = 0;

    traitement = strtok(copy, ".");

    while (traitement != NULL && i < 4)
    {
        tab[i++] = atoi(traitement);
        traitement = strtok(NULL, ".");
    }
}

int search()
{
    char ip[13] = "\0";
    char mask[13] = "\0";
    int ipTab[4];
    int maskTab[4];
    int binIp[33];
    int binMask[33];
    int size = 0;
    int networkAdressMyTab[33];
    int networkAdressTab[33];
    printf("Enter address:\n");
    scanf("%s", ip);
    printf("Enter mask;\n");
    scanf("%s", mask);

    splitIP(ipTab, ip);
    splitIP(maskTab, mask);

    for (int j = 0; j < 4; j++)
    {
        size += 8;
        bibine(ipTab[j], binIp, size);
    }
    size=0;
    for (int v = 0; v < 4; v++)
    {
        size += 8;
        bibine(maskTab[v], binMask, size);
    }

    networkAdress(binIp, binMask, networkAdressMyTab);

    FILE *file = fopen("data.csv", "r");

    if (file == NULL)
    {
        printf("Failed to open the file for reading.\n");
        return 1;
    }
    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        int verif = 0;
        char *id = "\0";
        char *ip_address = "\0";
        char *maskchar = "\0";
        size = 0;
        id = strtok(line, ",");
        ip_address = strtok(NULL, ",");
        maskchar = strtok(NULL, ",");
        splitIP(ipTab, ip_address);
        splitIP(maskTab, maskchar);
        for (int j = 0; j < 4; j++)
        {
            size += 8;
            bibine(ipTab[j], binIp, size);
        }
        size=0;
        for (int v = 0; v < 4; v++)
        {
            size += 8;
            bibine(maskTab[v], binMask, size);
        }
        networkAdress(binIp, binMask, networkAdressTab);
        verif = sameNetwork(networkAdressMyTab, networkAdressTab);
        int line_id;
        if (sscanf(line, "%d", &line_id) == 1)
        {
            if (verif == 0)
            {
                printf("[%s]. \n", id);
                printf("      IP Address : %s \n", ip_address);
                printf("      Mask : %s \n", maskchar);
            }
        }
    }
    fclose(file);
    return 0;
}

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
int add_ip()
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
    return 0;
}

//  TO PRINTOUT THE LIST OF IP ADDRESSES
int list_ip()
{
    FILE *file = fopen("data.csv", "r");
    int ipTab[5];
    int maskTab[5];
    int binIp[32];
    int binMask[32];

    if (file == NULL)
    {
        printf("Failed to open the file for reading.\n");
        return 0;
    }

    char line[1024];

    printf("+---------------------------------------------------------------+\n");
    printf("|                      IP Addresses List                        |\n");
    printf("+---------------------------------------------------------------+\n");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        int size = 0;
        int size2 = 0;
        char *id = strtok(line, ",");
        char *ip_address = strtok(NULL, ",");
        char *mask = strtok(NULL, ",");

        splitIP(ipTab, ip_address);
        splitIP(maskTab, mask);

        for (int j = 0; j < 4; j++)
        {
            size += 8;
            bibine(ipTab[j], binIp, size);
        }

        for (int v = 0; v < 4; v++)
        {
            size2 += 8;
            bibine(maskTab[v], binMask, size2);
        }

        int line_id;
        if (sscanf(line, "%d", &line_id) == 1)
        {
            printf("[%s]. \n", id);
            printf("      IP Address : %s\n", ip_address);
            printf("      Binaire ip : ");

            for (int i = 0; i < 32; i++)
            {
                if (i % 8 == 0 && i != 0)
                {
                    printf(".");
                }
                printf("%d", binIp[i]);
            }
            printf("\n");
            printf("      Hexa ip :");
            hexa(ipTab);
            printf("      Mask : %s", mask);
            printf("      Binaire mask : ");
            for (int i = 0; i < 32; i++)
            {
                if (i % 8 == 0 && i != 0)
                {
                    printf(".");
                }
                printf("%d", binMask[i]);
            }
            printf("\n");
            printf("      Hexa mask :");
            hexa(maskTab);
        }
    }

    fclose(file);
    return 0;
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

    char select = ' ';

    while (select != 'q')
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
            search();
            break;
        case 'd':
            //delete();
            break;
        case 'q':

            printf("Exiting....");
            exit(1);
            break;
        default:
            printf("Please choose one from these options. \n");
            break;
        }
    }

    return 0;
}