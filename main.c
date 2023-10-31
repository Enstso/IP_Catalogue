#include <stdio.h>
#include <stdlib.h>

int main(){
    char saisie = ' ';
    while(saisie!='q'){
        printf("a - Add a new IP adress \n l - List IP addresses\n s - Search similar by mask\n d- Delete an IP \n q - quit\n ");

        scanf("%c",&saisie);
        switch (saisie)
        {
        case 'a' :
            
            break;
        case 'l':
            break;
        case 's':
            break;
        case 'd':
            break;
        case 'q':
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}