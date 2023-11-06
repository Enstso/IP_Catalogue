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

// Fonction pour vérifier si un segment de chaîne est un octet IP valide
int estSegmentValide(char* segment) {
    int num = atoi(segment);
    // Vérifie si le segment est entre 1 et 255
    if (num >= 1 && num <= 255) {
        // Vérifie l'absence de zéros non significatifs
        if (segment[0] != '0' || (segment[0] == '0' && segment[1] == '\0')) {
            return 1;
        }
    }else if (num == 0)
    {
        return 1;
    }
    
    return 0;
}

// Fonction pour vérifier si l'entrée est une adresse IP valide
int estAdresseIPValide(char* ip) {
    int nbSegments = 0;
    int dernierCaractere = -1; // Suivre le dernier caractère traité
    char segmentCourant[4]; // Segment d'adresse IP à vérifier

    for (int i = 0; i <= strlen(ip); i++) {
        // Si le caractère actuel est un point ou la fin de la chaîne
        if (ip[i] == '.' || ip[i] == '\0') {
            // Vérifier l'existence de points consécutifs ou de segment vide
            if (dernierCaractere + 1 == i || i - dernierCaractere > 4) {
                return 0;
            }
            // Terminer la chaîne de segment
            strncpy(segmentCourant, ip + dernierCaractere + 1, i - dernierCaractere - 1);
            segmentCourant[i - dernierCaractere - 1] = '\0';

            // Vérifier si le segment est valide
            if (!estSegmentValide(segmentCourant)) {
                return 0;
            }
            dernierCaractere = i;
            nbSegments++; // Augmenter le compte de segments
        } else if (ip[i] < '0' || ip[i] > '9') {
            // Les caractères autres que les chiffres et le point ne sont pas autorisés
            return 0;
        }
    }
    // L'adresse IP doit contenir exactement 4 segments
    return nbSegments == 4;
}


// ADD NEW IP/MASK INTO DATA.CSV
void add_ip()
{
    int id;
    char verif_ip[16];
    char ip_address[33], mask[33];

    int last_id = get_Id();
    id = last_id + 1;

    FILE *file = fopen("data.csv", "a");

    if (file == NULL)
    {
        printf("Failed to open the file for writing.\n");
        return 1;
    }


    // Demande à l'utilisateur de saisir une adresse IP
    printf("Enter IP Address : ");
    sscanf("%15s", verif_ip);

    
    // Valide l'adresse IP
    if (estAdresseIPValide(verif_ip)) {
        printf("L'adresse IP est valide.\n");
        for (int i = 0; i < 15; i++)
        {
            ip_address[i] = verif_ip[i];
        }
        
    } else {
        while (!estAdresseIPValide(verif_ip))
        {
            printf("L'adresse IP est invalide.\n");
            printf("Veuillez entrer une autre adresse IP: ");
            scanf("%15s", verif_ip);
        }
        printf("L'adresse IP est valide.\n");
        for (int i = 0; i < 15; i++)
        {
            ip_address[i] = verif_ip[i];
        }
        
    }

    printf("Enter Mask Address : ");
    scanf("%s", verif_ip);

        // Valide l'adresse IP
    if (estAdresseIPValide(verif_ip)) {
        printf("Le Mask est valide.\n");
        for (int i = 0; i < 15; i++)
        {
            mask[i] = verif_ip[i];
        }
        
    } else {
        while (!estAdresseIPValide(verif_ip))
        {
            printf("Le Mask est invalide.\n");
            printf("Veuillez entrer un autre Mask: ");
            scanf("%15s", verif_ip);
        }
        printf("Le Mask est valide.\n");
        for (int i = 0; i < 15; i++)
        {
            mask[i] = verif_ip[i];
        }
        
    }

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