#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <time.h>
#include <ctype.h>

#define NUMBER_OF_LETTERS 1000

enum{INTERNET, FIREFOX, PROGRAMMATION, MINECRAFT_MULTI, MINECRAFT_SOLO, JEUX, CHAT, PROG_WEB, PROG_LOCAL, OTHER};

int planifiedExit = 0;

void writeTime(FILE* file)
{
    time_t timestamp;
    struct tm *t;

    timestamp = time(NULL);
    t = localtime(&timestamp);
    fprintf(file, "[%02u/%02u/%04u][%02u:%02u:%02u] ", t->tm_wday, t->tm_mon, 1900 + t->tm_year, t->tm_hour, t->tm_min, t->tm_sec);
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}

int scans(wchar_t chaine[])
{
    wchar_t* positionEntree = NULL;

    if (fgetws(chaine, NUMBER_OF_LETTERS, stdin) != NULL)
    {
        positionEntree = wcschr(chaine, '\n');
        if (positionEntree != NULL)
            *positionEntree = '\0';
        else
            viderBuffer();

        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

void login(void)
{
    FILE* file = NULL;

    file = fopen("historique.log", "a");
    fputs("\n-------------------------------------------\n\n", file);
    writeTime(file);
    fputs("Ouverture de session\n", file);
    fclose(file);
    printf("Ouverture de session\n");
}

void closeSession(wchar_t chaine[])
{
    FILE* file = NULL;

    file = fopen("historique.log", "a");
    writeTime(file);
    fputs("Fermeture de session. En attente de login.\n", file);
    fclose(file);
    printf("Fermeture de session. En attente de login.\n");
    while (wcscmp(chaine, L"start") && wcscmp(chaine, L"open") && wcscmp(chaine, L"login") && wcscmp(chaine, L"hello"))
        scans(chaine);
    login();
}

void closeAll(void)
{
    FILE* file = NULL;

    if(planifiedExit)
    {
        file = fopen("historique.log", "a");
        writeTime(file);
        fputs("Fermeture du programme demandee par l'utilisateur.\n", file);
        printf("Fermeture du programme demandee par l'utilisateur.\n");
        system("pause");
        fclose(file);
    }
    else
    {
        file = fopen("historique.log", "a");
        writeTime(file);
        fputs("[GRAVE]Fermeture du programme innatendue.\n", file);
        fclose(file);
    }
}

void CheckCommand(wchar_t* chaine, int* activity)
{
    FILE* file = NULL;
    int i = 0;

    if (chaine[0] == '!' || chaine[0] == '/' || chaine[0] == '\\' || chaine[0] == '%' || chaine[0] == '<' || chaine[0] == '>' || chaine[0] == '.' || chaine[0] == '?' || chaine[0] == '&' || chaine[0] == '$')
    {
        for (i = 0 ; chaine[i] != '\0' ; i++)
            chaine[i] = chaine[i + 1];
        for (i = 0 ; chaine[i] != '\0' ; i++)
            chaine[i] = tolower(chaine[i]);
        if (!wcscmp(chaine, L"stop") || !wcscmp(chaine, L"close") || !wcscmp(chaine, L"logout") || !wcscmp(chaine, L"bye"))
            closeSession(chaine);
        else if (!wcscmp(chaine, L"cls") || !wcscmp(chaine, L"clear"))
            system("cls");
        else if (!wcscmp(chaine, L"view") || !wcscmp(chaine, L"see") || !wcscmp(chaine, L"historique") || !wcscmp(chaine, L"history"))
            system("call historique.log");
        else if (!wcscmp(chaine, L"exit"))
            planifiedExit = 1;
        else if (!wcscmp(chaine, L"internet") || !wcscmp(chaine, L"chrome") || !wcscmp(chaine, L"google") || !wcscmp(chaine, L"google chrome"))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fputs("Mode internet active ! (Google Chrome)\n", file);
            fclose(file);
            wprintf(L"Mode internet activ\x82 ! (Google Chrome)\n");
            *activity = INTERNET;
        }
        else if (!wcscmp(chaine, L"firefox") || !wcscmp(chaine, L"ff"))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fputs("Mode internet active ! (Firefox)\n", file);
            fclose(file);
            wprintf(L"Mode internet activ\x82 ! (Firefox)\n");
            *activity = FIREFOX;
        }
        else if (!wcscmp(chaine, L"prog") || !wcscmp(chaine, L"progra") || !wcscmp(chaine, L"programmation"))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fputs("Mode programmation active ! (local/web non specifie)\n", file);
            fclose(file);
            wprintf(L"Mode programmation activ\x82 ! (local/web non sp%ccifi\x82)\n", 130);
            *activity = PROGRAMMATION;
        }
        else if (!wcscmp(chaine, L"minecraft") || !wcscmp(chaine, L"mine") || !wcscmp(chaine, L"craft") || !wcscmp(chaine, L"minecraft multi"))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fputs("Mode minecraft active ! (multi uniquement)\n", file);
            fclose(file);
            wprintf(L"Mode minecraft activ\x82 ! (multi uniquement)\n");
            *activity = MINECRAFT_MULTI;
        }
        else if (!wcscmp(chaine, L"minecraft solo"))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fputs("Mode minecraft active ! (solo et multi)\n", file);
            fclose(file);
            wprintf(L"Mode minecraft activ\x82 ! (solo et multi)\n");
            *activity = MINECRAFT_SOLO;
        }
        else if (!wcscmp(chaine, L"jeux") || !wcscmp(chaine, L"jeu") || !wcscmp(chaine, L"games") || !wcscmp(chaine, L"game"))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fputs("Mode jeux active !\n", file);
            fclose(file);
            wprintf(L"Mode jeux activ\x82 !\n");
            *activity = JEUX;
        }
        else if (!wcscmp(chaine, L"skype") || !wcscmp(chaine, L"ts") || !wcscmp(chaine, L"mumble") || !wcscmp(chaine, L"chat"))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fputs("Mode communication active ! (Skype/team speak/mumble/fb)\n", file);
            fclose(file);
            wprintf(L"Mode communication activ\x82 ! (Skype/team speak/mumble/fb)\n");
            *activity = CHAT;
        }
        else if (!wcscmp(chaine, L"prog web") || !wcscmp(chaine, L"progra web") || !wcscmp(chaine, L"programmation web") || !wcscmp(chaine, L"web") || !wcscmp(chaine, L"html") || !wcscmp(chaine, L"css") || !wcscmp(chaine, L"php") || !wcscmp(chaine, L"sql") || !wcscmp(chaine, L"javascript") || !wcscmp(chaine, L"securitze") || !wcscmp(chaine, L"menagerie") || !wcscmp(chaine, L"speedbeaute") || !wcscmp(chaine, L"laina"))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fputs("Mode programmation active ! (web)\n", file);
            fclose(file);
            wprintf(L"Mode programmation activ\x82 ! (web)\n");
            *activity = PROG_WEB;
        }
        else if (!wcscmp(chaine, L"prog local") || !wcscmp(chaine, L"progra local") || !wcscmp(chaine, L"programmation local") || !wcscmp(chaine, L"shaak"))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fputs("Mode programmation active ! (local)\n", file);
            fclose(file);
            wprintf(L"Mode programmation activ\x82 ! (local)\n");
            *activity = PROG_LOCAL;
        }
        else if (!wcscmp(chaine, L"other") || !wcscmp(chaine, L"autre") || !wcscmp(chaine, L"rien"))
        {
            wprintf(L"pr%ccisez : ", 130);
            scans(chaine);
            file = fopen("historique.log", "a");
            writeTime(file);
            fwprintf(file, L"Mode autre active ! (%ls)\n", chaine);
            fclose(file);
            wprintf(L"Mode autre activ\x82 ! (%ls)\n", chaine);
            *activity = OTHER;
        }
        else
            printf("Commande inconnue\n");
    }
}

int main()
{
    FILE* file = NULL;
    wchar_t chaine[NUMBER_OF_LETTERS + 1] = {0};
    int activity = OTHER;

    system("color 0F");
    atexit(closeAll);
    login();
    while (!planifiedExit)
    {
        if (!scans(chaine))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fputs("[ATTENTION] Function scans failed.\n", file);
            fclose(file);
            printf("[ATTENTION] Function scans failed.\n");
        }
        if (wcscmp(chaine, L"!cls") && wcscmp(chaine, L"!clear") && wcscmp(chaine, L"!view") && wcscmp(chaine, L"!see") && wcscmp(chaine, L"!historique") && wcscmp(chaine, L"!history"))
        {
            file = fopen("historique.log", "a");
            writeTime(file);
            fwprintf(file, L"%ls\n", chaine);
            fclose(file);
        }
        CheckCommand(chaine, &activity);
    }

    return EXIT_SUCCESS;
}
