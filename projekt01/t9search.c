#include <stdio.h>
#define MAX_ARRAY_SIZE 102

void printContact(char name[], char phone[]);
void removeNewLine(char name[]);
void convertToT9(char text[]);
void toLower(char text[]);
bool checkForContact(char name[], char phone[], char filter[]);
void cloneArray(char array1[], char array2[]);
bool contains(char text[], char search[]);
bool isStringRightSize(char text[]);
bool isFilterValid(char filter[]);
int main(int argc, char *argv[])
{
    char name[MAX_ARRAY_SIZE];
    char phone[MAX_ARRAY_SIZE];
    
    if(argc == 1)
    {
        while (fgets(name, sizeof(name), stdin) != NULL && fgets(phone, sizeof(phone), stdin) != NULL)
        {
            removeNewLine(name);
            removeNewLine(phone);
            printContact(name, phone);
        }
        

    }
    else if (argc == 2)
    {
        bool isFound = false;
        if(!isFilterValid(argv[1]))
        {
            return 1;
        }
        while (fgets(name, sizeof(name), stdin) != NULL)
        {
            if(fgets(phone, sizeof(phone), stdin) == NULL)
            {
                fprintf(stderr, "Chyba pico");
                return 1;
            }
            if(name[0] == '\0'|| phone[0] == '\0' )
            {
                fprintf(stderr, "Chyba pico");
                return 1;
            }
            if(!isStringRightSize(name) || !isStringRightSize(phone))
            {
                fprintf(stderr, "Chyba pico");
                return 1;
            }
            
            
            char nameClone[MAX_ARRAY_SIZE];
            char phoneClone[MAX_ARRAY_SIZE];
            cloneArray(name, nameClone);
            cloneArray(phone, phoneClone);
            if(checkForContact(nameClone, phoneClone, argv[1]))
            {
                removeNewLine(name);
                removeNewLine(phone);
                printContact(name, phone);
                isFound = true;
            }
        }
        if(!isFound)
        {
            printf("Not found\n");
        }
        

        
        
    }
    else
    {   
        fprintf(stderr, "picovina more");
        return 1;
    }
    return 0;
}

void printContact(char name[], char phone[])
{
    printf("%s, %s\n", name, phone);
}
void removeNewLine(char text[])
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '\n' || text[i] == '\r')
        {
            text[i] = '\0';
            return;
        }
    }
}
void convertToT9(char text[])
{
    toLower(text);
    for (int i = 0; text[i] != '\0'; i++)
    {
        switch (text[i])
        {
        case 'a':
        case 'b':
        case 'c':
            text[i] = '2';
            break;

        case 'd':
        case 'e':
        case 'f':
            text[i] = '3';
            break;

        case 'g':
        case 'h':
        case 'i':
            text[i] = '4';
            break;

        case 'j':
        case 'k':
        case 'l':
            text[i] = '5';
            break;

        case 'm':
        case 'n':
        case 'o':
            text[i] = '6';
            break;

        case 'p':
        case 'q':
        case 'r':
        case 's':
            text[i] = '7';
            break;

        case 't':
        case 'u':
        case 'v':
            text[i] = '8';
            break;

        case 'w':
        case 'x':
        case 'y':
        case 'z':
            text[i] = '9';
            break;

        case '+':
            text[i] = '0';
            break;

        default:
            // mezery, čísla a ostatní znaky zůstanou beze změny
            break;
        }
    }
}
void toLower(char text[])
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            text[i] = text[i] + 32;
        }
    }
}
bool checkForContact(char name[], char phone[], char filter[])
{
    convertToT9(name);
    convertToT9(phone);
    return contains(name, filter) || contains(phone, filter);
}
/// @brief Nakopíruje hodnoty z jednoho pole do druhého
/// @param array1 Pole které je nakopírováno
/// @param array2 Pole do kterého se kopíruje
void cloneArray(char array1[], char array2[])
{
    int i = 0;

    while (array1[i] != '\0')
    {
        array2[i] = array1[i];
        i++;
    }

    array2[i] = '\0';
}

bool contains(char text[], char search[])
{
    int i = 0;

    while (text[i] != '\0')
    {
        int j = 0;

        while (text[i + j] != '\0' &&
               search[j] != '\0' &&
               text[i + j] == search[j])
        {
            j++;
        }

        if (search[j] == '\0')
        {
            return true;
        }

        i++;
    }

    return false;
}
bool isStringRightSize(char text[])
{
    for (int i = 0;text[i] != '\0'; i++)
    {
        if(text[i] == '\n')
        {
            return true;
        }
    }
    return false;
}
bool isFilterValid(char filter[])
{
    if(filter[0] == '\0')
    {
        fprintf(stderr, "picovina more, na vstupu je %c", filter[0]);
        return false;
    }
    int i;
    for (i = 0; filter[i] != '\0'; i++)
    {
        if(filter[i] < '0' || filter[i] > '9')
        {
            fprintf(stderr, "picovina more, na vstupu je %c", filter[i]);
            return false;
        }
    }
    return i <= 100;
}