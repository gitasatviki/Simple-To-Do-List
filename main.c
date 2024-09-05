#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define username 50
#define password 50
#define max_user 100

struct task
{
    char name[100];
    char description[100];
    char deadline[100];
    int completed;
    struct task* next;
};

struct user
{
    char usn[username];
    char pass[password];
    struct task* tasks;
};

struct user data;
struct user penyimpanan[max_user];

void tampilanAwal()
{
    printf("\t\t                                                              \n");
    printf("\t\t==============================================================\n");
    printf("\t\t|                S E L A M A T  D A T A N G !                |\n");
    printf("\t\t|                                                            |\n");
    printf("\t\t|              P R O G R A M  T O  D O  L I S T              |\n");
    printf("\t\t|                                                            |\n");
    printf("\t\t|                  F I N A L  P R O J E C T                  |\n");
    printf("\t\t|                                                            |\n");
    printf("\t\t|                  S T R U K T U R  D A T A                  |\n");
    printf("\t\t==============================================================\n");
    printf("\t\t                                                              \n");
    printf("\t\t                                           Oleh : Gita & Intan\n\n");
    system ("pause");
    system ("cls");
}


void daftar()
{
    system("cls");
    printf("============================================================\n");
    printf("|                       S I G N - U P                      |\n");
    printf("============================================================\n");
    printf("                                                            \n");
    printf("U S E R N A M E : ");
    scanf("%s", data.usn);
    printf("                                                          \n");
    printf("P A S S W O R D : ");
    scanf("%s", data.pass);

    FILE* file = fopen("data.txt", "a");
    if (file == NULL)
    {
        printf("File Tidak Ditemukan!\n");
        return;
    }

    fprintf(file, "%s %s\n", data.usn, data.pass);
    printf("\n\n                S I G N - U P  B E R H A S I L!              \n");

    fclose(file);
}

void masuk()
{
    system("cls");
    printf("============================================================\n");
    printf("|                       S I G N - I N                      |\n");
    printf("============================================================\n");
    printf("                                                            \n");
    printf("U S E R N A M E : ");
    scanf("%s", data.usn);
    printf("                                                          \n");
    printf("P A S S W O R D : ");
    scanf("%s", data.pass);

    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("File Tidak Ditemukan!\n");
        return;
    }

    int a = 0;
    int i = 0;
    while (fscanf(file, "%s %s", penyimpanan[i].usn, penyimpanan[i].pass) == 2)
    {
        if (strcmp(data.usn, penyimpanan[i].usn) == 0 && strcmp(data.pass, penyimpanan[i].pass) == 0)
        {
            a = 1;
            break;
        }
        i++;
    }

    fclose(file);

    if (a)
    {
        printf("                                 \n");
        printf("S I G N -  I N  B E R H A S I L !\n");
        printf("                                 \n");
        toDoListMenu();
    }
    else
    {
        printf("                                                      \n");
        printf("U S E R N A M E  A T A U  P A S S W O R D  S A L A H !\n");
        printf("                                                      \n");
    }
}

void tambahTask(struct task** head, const char* name, const char* desc, const char* deadline)
{
    system("cls");
    struct task* newTask = (struct task*)malloc(sizeof(struct task));
    strcpy(newTask->name, name);
    strcpy(newTask->description, desc);
    strcpy(newTask->deadline, deadline);
    newTask->completed = 0;
    newTask->next = NULL;

    if (*head == NULL)
    {
        *head = newTask;
    }
    else
    {
        struct task* current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newTask;
    }
}

void hapusTask(struct task** head, const char* desc)
{
    system("cls");
    if (*head == NULL)
    {
        printf("                                                   \n");
        printf("T I D A K  A D A  T A S K  Y A N G  T E R S E D I A\n");
        printf("                                                   \n");
        return;
    }

    struct task* current = *head;
    struct task* prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->description, desc) == 0)
        {
            if (prev == NULL)
            {
                *head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("Task '%s' dihapus.\n", desc);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Task '%s' tidak ditemukan.\n", desc);
}

void tandaiSelesai(struct task* head, const char* desc)
{
    system("cls");
    if (head == NULL)
    {
        printf("                                                   \n");
        printf("T I D A K  A D A  T A S K  Y A N G  T E R S E D I A\n");
        printf("                                                   \n");
        return;
    }

    struct task* current = head;
    while (current != NULL)
    {
        if (strcmp(current->description, desc) == 0)
        {
            current->completed = 1;
            printf("Task '%s' ditandai selesai.\n", desc);
            return;
        }
        current = current->next;
    }

    printf("Task '%s' tidak ditemukan.\n", desc);
}

void tampilkanTask(struct task* head)
{
    system("cls");
    if (head == NULL)
    {
        printf("Tidak ada task yang tersedia.\n");
        return;
    }

    struct task* current = head;
    printf("\t\t====================================================|\n");
    printf("\t\t|               D A F T A R  T A S K                |\n");
    printf("\t\t====================================================|\n");
    printf("                                                         \n");
    while (current != NULL)
    {
        printf("N A M A            : %s\n", current->name);
        printf("D E S K R I P S I  : %s\n", current->description);
        printf("D E A D L I N E    : %s\n", current->deadline);
        printf("S E L E S A I      : %s\n", current->completed ? "Ya" : "Belum");
        printf("--------------------------------\n");
        current = current->next;
    }
}

void cariTask(struct task* head, const char* keyword)
{
    system("cls");
    if (head == NULL)
    {
        printf("                                                   \n");
        printf("T I D A K  A D A  T A S K  Y A N G  T E R S E D I A\n");
        printf("                                                   \n");
        return;
    }

    struct task* current = head;
    printf("\t\t====================================================|\n");
    printf("\t\t|           H A S I L  P E N C A R I A N            |\n");
    printf("\t\t====================================================|\n");
    printf("                                                         \n");
    while (current != NULL)
    {
        if (strstr(current->name, keyword) != NULL || strstr(current->description, keyword) != NULL)
        {
            printf("N A M A            : %s\n", current->name);
            printf("D E S K R I P S I  : %s\n", current->description);
            printf("D E A D L I N E    : %s\n", current->deadline);
            printf("S E L E S A I      : %s\n", current->completed ? "Ya" : "Belum");
            printf("------------------------------\n");
        }
        current = current->next;
    }
}

void urutkanTask(struct task** head)
{
    system("cls");
    if (*head == NULL || (*head)->next == NULL)
    {
        printf("Tidak ada task yang tersedia.\n");
        return;
    }

    struct task* current = *head;
    struct task* sortedList = NULL;

    while (current != NULL)
    {
        struct task* nextTask = current->next;

        if (sortedList == NULL || strcmp(current->deadline, sortedList->deadline) < 0)
        {
            current->next = sortedList;
            sortedList = current;
        }
        else
        {
            struct task* temp = sortedList;

            while (temp->next != NULL && strcmp(current->deadline, temp->next->deadline) > 0)
            {
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }

        current = nextTask;
    }

    *head = sortedList;

    printf("Tugas telah diurutkan berdasarkan deadline.\n");
}

void simpanTaskKeFile(struct task* head)
{
    FILE* file = fopen("tasks.txt", "w");
    if (file == NULL)
    {
        printf("G A G A L   M E M B U K A   F I L E   T A S K S.txt.\n");
        return;
    }

    struct task* current = head;
    while (current != NULL)
    {
        fprintf(file, "%s;%s;%s;%d\n", current->name, current->description, current->deadline, current->completed);
        current = current->next;
    }

    fclose(file);
    printf("                                                                              \n");
    printf("T A S K S   B E R H A S I L   D I S I M P A N   K E   F I L E   T A S K S.txt.\n");
    printf("                                                                              \n");
}

void bacaTaskDariFile(struct task** head)
{
    FILE* file = fopen("tasks.txt", "r");
    if (file == NULL)
    {
        printf("                                                    \n");
        printf("G A G A L   M E M B U K A   F I L E   T A S K S.txt.\n");
        printf("                                                    \n");
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        char* name = strtok(line, ";");
        char* desc = strtok(NULL, ";");
        char* deadline = strtok(NULL, ";");
        int completed = atoi(strtok(NULL, ";\n"));

        tambahTask(head, name, desc, deadline);
        struct task* current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->completed = completed;
    }

    fclose(file);

    printf("                                                                              \n");
    printf("T A S K S   B E R H A S I L   D I B A C A   D A R I   F I L E   T A S K S.txt.\n");
    printf("                                                                              \n");
}


void toDoListMenu()
{
    struct task* head = NULL;
    int pilihan;
    char p;

    bacaTaskDariFile(&head);
    system("pause");
    system("cls");

    do
    {
        printf("|========================================================================|\n");
        printf("|                          T O  -  D O  L I S T  M E N U                 |\n");
        printf("|------------------------------------------------------------------------|\n");
        printf("|                                                                        |\n");
        printf("|                1. T A M B A H  T A S K                                 |\n");
        printf("|                2. H A P U S  T A S K                                   |\n");
        printf("|                3. T A N D A I  T A K S  S E L E S A I                  |\n");
        printf("|                4. T A M P I L K A N  T  A S K                          |\n");
        printf("|                5. C A R I  T A S K                                     |\n");
        printf("|                6. U R U T A N  T A S K                                 |\n");
        printf("|                7. S I M P A N  T A S K  K E  F I L E                   |\n");
        printf("|                8. K E L U A R                                          |\n");
        printf("|                                                                        |\n");
        printf("|------------------------------------------------------------------------|\n");
        printf("|                                                                        |\n");
        printf("|========================================================================|\n");
        printf("                                                                          \n");
        printf("P I L I H   M E N U : ");
        scanf("%d", &pilihan);
        printf("\n");

        switch (pilihan)
        {
            case 1:
                {
                    char name[100];
                    char desc[100];
                    char deadline[100];

                    printf("Note : Penulisan Deadline Harus YYYY-MM-DD\n\n");
                    printf("N A M A : ");fflush(stdin);
                    gets(name);
                    printf("D E S K R I P S I : ");fflush(stdin);
                    gets(desc);
                    printf("D E A D L I N E : ");fflush(stdin);
                    gets(deadline);

                    tambahTask(&head, name, desc, deadline);
                    system("pause");
                    system("cls");
                    break;
                }
            case 2:
                {
                    char desc[100];
                    printf("D E S K R I P S I  T A S K  Y A N G  A K A N  D I H A P U S : ");fflush(stdin);
                    gets(desc);
                    hapusTask(&head, desc);
                    system("pause");
                    system("cls");
                    break;
                }
            case 3:
                {
                    char desc[100];
                    printf("D E S K R I P S I   T A S K   Y A N G   S E L E S A I : ");fflush(stdin);
                    gets(desc);
                    tandaiSelesai(head, desc);
                    system("pause");
                    system("cls");
                    break;
                }
            case 4:
                tampilkanTask(head);
                system("pause");
                system("cls");
                break;
            case 5:
                {
                    char keyword[100];
                    printf("M A S U K K A N   K A T A   K U N C I : ");
                    scanf("%s", keyword);
                    cariTask(head, keyword);
                    system("pause");
                    system("cls");
                    break;
                }
            case 6:
                urutkanTask(&head);
                printf("T A S K   B E R H A S I L   D I U R U T K A N   B E R D A S A R K A N   D E A D L I N E.\n");
                system("pause");
                system("cls");
                break;
            case 7:
                simpanTaskKeFile(head);
                system("pause");
                system("cls");
                break;
            case 8:
                printf("K E L U A R   D A R I   T O  -  D O  L I S T   M E N U\n");
                system("pause");
                system("cls");
                break;
            default:
                printf("P I L I H A N   T I D A K   V A L I D\n");
                system("pause");
                system("cls");
                break;
        }
    } while (pilihan != 8);

    // Hapus semua task sebelum keluar
    struct task* current = head;
    while (current != NULL)
    {
        struct task* temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    int choice;
    tampilanAwal();

    do
    {
        printf("========== L O G I N ==========\n");
        printf("|                             |\n");
        printf("|      1. S I G N - U P       |\n");
        printf("|                             |\n");
        printf("|      2. S I G N - I N       |\n");
        printf("|                             |\n");
        printf("|      3. E X I T             |\n");
        printf("|                             |\n");
        printf("===============================\n");
        printf("                               \n");
        printf("P I L I H  M E N U : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                daftar();
                system("pause");
                system("cls");
                break;
            case 2:
                masuk();
                system("pause");
                system("cls");
                break;
            case 3:
                printf("K E L U A R   D A R I   P R O G R A M\n");
                break;
            default:
                printf("P I L I H A N   T I D A K   V A L I D\n");
        }
    } while (choice != 3);

    return 0;
}
