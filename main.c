#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1024

void delete_ip(unsigned int id)
{
    FILE *data = fopen("data.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    char row[MAXLINE];
    unsigned int l = 0;

    while (fgets(row, MAXLINE, data))
    {
         char *id_split = strtok(row, ",");
         char *ip_address = strtok(NULL, ",");
         char *mask = strtok(NULL, ",");
         int current_id = atoi(id_split);

        if (current_id != id)
        {
            if (l == 0)
            {
                fprintf(temp, "%s,%s,%s", "ID", ip_address, mask);
            }
            else
            {
                fprintf(temp, "%d,%s,%s", l, ip_address, mask);
            }
            l++;
        }
    }
    fclose(data);
    fclose(temp);

    remove("data.csv");
    rename("temp.csv", "data.csv");

 }
void reverseList(unsigned int tab[],unsigned int size)
{
    unsigned int start = size - 8;
    if (size == 8)
    {
        start = 0;
    }

    unsigned int end = size - 1;

    while (start < end)
    {
        unsigned int temp = tab[start];
        tab[start] = tab[end];
        tab[end] = temp;

        start++;
        end--;
    }
}

int VerifierIP(unsigned int ip[4])
{
    unsigned int compteur = 0;
    for (int i = 0; i < 4; i++)
    {
        if (ip[i] >= 0 && ip[i] <= 255)
        {
            compteur++;
        }
    }
    return compteur;
}

int verifPoint(char ip[16])
{
    int i = 0;
    int compteur = 0;
    while (ip[i] != '\0')
    {
        if (ip[i] == '.')
        {
            compteur++;
        }
        i++;
    }
    return compteur;
}
void hexa(unsigned int ipTab[4])
{

    for (int i = 0; i < 4; i++)
    {
        unsigned char hexa[100];
        unsigned int index = 0;
        unsigned int number = 0;
        number = ipTab[i];
        if (number == 0)
        {
            printf("0");
        }
        while (number)
        {
            unsigned int calc = number % 16;

            if (calc < 10)
            {
                hexa[index] = calc + '0';
            }
            else
            {
                hexa[index] = calc + 55;
            }
            index++;
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

void bibine(unsigned int n,unsigned int tab[33], unsigned int size)
{
    unsigned int temp = 0;
    unsigned int bin = 0;
    unsigned int init = size - 8;
    if (size == 8)
    {
        unsigned int init = 0;
    }
    for (unsigned int i = init; i < size; i++)
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

void networkAdress(unsigned int ip[33], unsigned int mask[33], unsigned int networkAdress[33])
{
    unsigned int networkSum = 0;
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

unsigned int sameNetwork(unsigned int tab1[33], unsigned int tab2[33])
{
    unsigned int verif = 0;
    for (int i = 0; i < 33; i++)
    {
        if (tab1[i] != tab2[i])
        {
            verif = 1;
        }
    }
    return verif;
}

void splitIP(unsigned int tab[4], char ip[16])
{
    size_t len = strlen(ip)+1;
    char copy[len];
    strcpy(copy, ip);

    char *traitement = NULL;
    int i = 0;

    traitement = strtok(copy, ".");
    while (traitement != NULL && i < 4)
    {
        char *ptr;
        tab[i] = strtol(traitement, &ptr, 10);
        if(ptr == traitement || *ptr !='\0')
        {
            break;
        }
        traitement = strtok(NULL, ".");
        i++;
    }
}

int search()
{
    char ip[13] = "\0";
    char mask[13] = "\0";
    unsigned int ipTab[4];
    unsigned int maskTab[4];
    unsigned int binIp[33];
    unsigned int binMask[33];
    unsigned int size = 0;
    unsigned int networkAdressMyTab[33];
    unsigned int networkAdressTab[33];
    printf("Enter address:\n");
    scanf(" %s", ip);
    printf("Enter mask:\n");
    scanf(" %s", mask);
    printf("%s", ip);
    splitIP(ipTab, ip);
    splitIP(maskTab, mask);

    for (int j = 0; j < 4; j++)
    {
        size += 8;
        bibine(ipTab[j], binIp, size);
    }
    size = 0;
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
    char row[MAXLINE];
    printf("\n addresses found: \n");

    while (fgets(row, MAXLINE, file) != NULL)
    {
        int verif = 0;
        char *id = "\0";
        char *ip_address = "\0";
        char *maskchar = "\0";
        size = 0;
        id = strtok(row, ",");
        ip_address = strtok(NULL, ",");
        maskchar = strtok(NULL, ",");
        splitIP(ipTab, ip_address);
        splitIP(maskTab, maskchar);
        for (int j = 0; j < 4; j++)
        {
            size += 8;
            bibine(ipTab[j], binIp, size);
        }
        size = 0;
        for (int v = 0; v < 4; v++)
        {
            size += 8;
            bibine(maskTab[v], binMask, size);
        }
        networkAdress(binIp, binMask, networkAdressTab);
        verif = sameNetwork(networkAdressMyTab, networkAdressTab);
        int line_id;
        if (sscanf(row, " %d", &line_id) == 1)
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


unsigned int get_Id()
{
    FILE *file = fopen("data.csv", "r");

    if (file == NULL)
    {
        printf("Failed to open the file for reading.\n");
        return 1;
    }

    char row[MAXLINE];
    unsigned int last_id = 0;

    while (fgets(row, MAXLINE, file) != NULL)
    {
        char *id = strtok(row, ",");
        int line_id = atoi(id);

        last_id = line_id;
    }

    fclose(file);

    return last_id;
}


unsigned int add_ip()
{
    unsigned int id=0;
    char ip_address[16] = "\0";
    char mask[16] = "\0";
    unsigned int ipTab[4];
    unsigned int maskTab[4];
    unsigned int last_id = get_Id();
    id = last_id + 1;

    FILE *file = fopen("data.csv", "a");

    if (file == NULL)
    {
        printf("Failed to open the file for writing.\n");
        return 1;
    }

    printf("Enter IP Address : ");
    scanf(" %s", ip_address);
    printf("Enter Mask Address : ");
    scanf(" %s", mask);
    splitIP(ipTab, ip_address);
    splitIP(maskTab, mask);

    unsigned int verif_ip = VerifierIP(ipTab);
    unsigned int verif_mask = VerifierIP(maskTab);
    verif_ip += verifPoint(ip_address);
    verif_mask += verifPoint(mask);
    if (verif_ip == 7 && verif_mask == 7)
    {
        fprintf(file, "%d, %s, %s\n", id, ip_address, mask);
        printf("\n\n");
        printf("The IP Address : %s and The Mask : %s are added successfully!", ip_address, mask);
        printf("\n\n");
    }
    else
    {
        printf("\n\n");
        printf("The IP Address : %s and The Mask : %s are not valid!", ip_address, mask);
        printf("\n\n");
    }

    fclose(file);
    return 0;
}

unsigned int list_ip()
{
    FILE *file = fopen("data.csv", "r");
    unsigned int ipTab[4];
    unsigned int maskTab[4];
    unsigned int binIp[32];
    unsigned int binMask[32];

    if (file == NULL)
    {
        printf("Failed to open the file for reading.\n");
        return 0;
    }

    char row[MAXLINE];

    printf("+---------------------------------------------------------------+\n");
    printf("|                      IP Addresses List                        |\n");
    printf("+---------------------------------------------------------------+\n");

    while (fgets(row, MAXLINE, file) != NULL)
    {
        unsigned int size = 0;
        char *id = strtok(row, ",");
        char *ip_address = strtok(NULL, ",");
        char *mask = strtok(NULL, ",");
       
        splitIP(ipTab, ip_address);
        splitIP(maskTab, mask);

        for (int j = 0; j < 4; j++)
        {
            size += 8;
            bibine(ipTab[j], binIp, size);
        }
        size = 0;
        for (int v = 0; v < 4; v++)
        {
            size += 8;
            bibine(maskTab[v], binMask, size);
        }

        unsigned int line_id;
        if (sscanf(row, " %d", &line_id) == 1)
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
    unsigned int delete_id=0;
    char select = ' ';

    while (select != 'q')
    {
        printf("Please choose one : ");
        scanf(" %c", &select);

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
            printf("Enter the ID : ");
            scanf(" %d", &delete_id);
            delete_ip(delete_id);
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