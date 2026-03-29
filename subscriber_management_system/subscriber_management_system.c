#include "data_set.h" // veri_seti.h changed to data_set.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

// Core Functions
void register_new_subscriber();
void remove_subscriber();
void update_phone_info();
void find_subscriber();

// Analysis Functions
void list_operator_changes();
void loyalty_analysis();
void campaign_popularity();

// Surprise Menu Functions
void surprise_menu();
void draw_lucky_subscriber();

// Validation & Helpers
int is_valid_tc(char tc[]);
int is_valid_date(int day, int month, int year);
int get_subscriber_count();
int is_numeric_only(char str[]);

int main()
{
    setlocale(LC_ALL, "turkish");
    int choice;

    while (1)
    {
        printf("\n===== MAIN MENU =====\n");
        printf("1. New Subscriber Registration\n");
        printf("2. Delete Subscriber\n");
        printf("3. Update Subscriber Info\n");
        printf("4. Search Subscriber\n");
        printf("5. List Operator Changes (Yearly)\n");
        printf("6. Loyalty Analysis\n");
        printf("7. Campaign Popularity\n");
        printf("8. Surprise Menu\n");
        printf("9. Exit\n");

        printf("\nSelection: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: register_new_subscriber(); break;
        case 2: remove_subscriber(); break;
        case 3: update_phone_info(); break;
        case 4: find_subscriber(); break;
        case 5: list_operator_changes(); break;
        case 6: loyalty_analysis(); break;
        case 7: campaign_popularity(); break;
        case 8: surprise_menu(); break;
        case 9:
            printf("Exiting system...\n");
            exit(0);
        default:
            printf("Invalid selection. Please try again.\n");
        }
    }
    return 0;
}

void register_new_subscriber()
{
    int sub_count = get_subscriber_count();

    if (sub_count >= 1000)
    {
        printf("System full! Cannot add new subscriber.\n");
        return;
    }

    printf("\n--- NEW SUBSCRIBER REGISTRATION ---\n");

    while (1)
    {
        printf("TC Identity No: ");
        scanf("%s", people[sub_count].tc_no);

        if (!is_valid_tc(people[sub_count].tc_no))
        {
            printf("ERROR: TC must be 11 digits and numeric.\n");
            continue;
        }

        int exists = 0;
        for (int k = 0; k < sub_count; k++)
        {
            if (strcmp(people[k].tc_no, people[sub_count].tc_no) == 0)
                exists = 1;
        }

        if (exists)
        {
            printf("This TC is already registered! Try again.\n");
            continue;
        }
        break;
    }

    printf("Name: ");
    scanf("%s", people[sub_count].name);
    printf("Surname: ");
    scanf("%s", people[sub_count].surname);

    while (1)
    {
        printf("Age: ");
        scanf("%s", people[sub_count].age);
        if (!is_numeric_only(people[sub_count].age))
        {
            printf("ERROR: Age must be numeric.\n");
            continue;
        }
        break;
    }

    while (1)
    {
        printf("Phone No: ");
        scanf("%s", people[sub_count].phone_no);
        if (!is_numeric_only(people[sub_count].phone_no))
        {
            printf("ERROR: Phone number must be numeric.\n");
            continue;
        }
        break;
    }

    printf("Address: ");
    scanf(" %[^\n]s", people[sub_count].address);

    int op_choice;
    while (1)
    {
        printf("Operator (1:Turkcell 2:Vodafone 3:Bimcell 4:Turk Telekom): ");
        scanf("%d", &op_choice);

        if (op_choice == 1) strcpy(people[sub_count].op_name, "Turkcell");
        else if (op_choice == 2) strcpy(people[sub_count].op_name, "Vodafone");
        else if (op_choice == 3) strcpy(people[sub_count].op_name, "Bimcell");
        else if (op_choice == 4) strcpy(people[sub_count].op_name, "Turk Telekom");
        else
        {
            printf("ERROR: Invalid selection.\n");
            continue;
        }
        break;
    }

    printf("Campaign: ");
    scanf("%s", people[sub_count].campaign);

    while (1)
    {
        printf("Tariff Start (Day Month Year): ");
        scanf("%d %d %d",
            &people[sub_count].tariff_start.day,
            &people[sub_count].tariff_start.month,
            &people[sub_count].tariff_start.year);

        if (!is_valid_date(
            people[sub_count].tariff_start.day,
            people[sub_count].tariff_start.month,
            people[sub_count].tariff_start.year))
        {
            printf("ERROR: Invalid date.\n");
            continue;
        }
        break;
    }

    people[sub_count].old_op1[0] = '\0';
    people[sub_count].old_op2[0] = '\0';

    printf("\nSubscriber successfully added to the system!\n");
}

void remove_subscriber()
{
    char tc[12];
    int sub_count = get_subscriber_count();
    int i, k, found = 0;

    printf("Enter TC Identity No of subscriber to delete: ");
    scanf("%s", tc);

    if (!is_valid_tc(tc))
    {
        printf("Invalid TC entered.\n");
        return;
    }

    for (i = 0; i < sub_count; i++)
    {
        if (strcmp(people[i].tc_no, tc) == 0)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("No record found for this TC number.\n");
        return;
    }

    for (k = i; k < sub_count - 1; k++)
    {
        people[k] = people[k + 1];
    }
    people[sub_count - 1].tc_no[0] = '\0';

    printf("Subscriber successfully deleted.\n");
}

void update_phone_info()
{
    char phone[20];
    int sub_count = get_subscriber_count();
    int i, found = 0;

    printf("Enter phone number of subscriber to update: ");
    scanf("%s", phone);

    for (i = 0; i < sub_count; i++)
    {
        if (strcmp(people[i].phone_no, phone) == 0)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("No record found for this phone number.\n");
        return;
    }

    printf("New address: ");
    scanf(" %[^\n]s", people[i].address);

    int op_choice;
    printf("New operator (1:Turkcell 2:Vodafone 3:Bimcell 4:Turk Telekom): ");
    scanf("%d", &op_choice);

    char old_op[20];
    strcpy(old_op, people[i].op_name);

    if (op_choice == 1) strcpy(people[i].op_name, "Turkcell");
    else if (op_choice == 2) strcpy(people[i].op_name, "Vodafone");
    else if (op_choice == 3) strcpy(people[i].op_name, "Bimcell");
    else if (op_choice == 4) strcpy(people[i].op_name, "Turk Telekom");
    else
    {
        printf("Invalid operator choice.\n");
        return;
    }

    if (strcmp(old_op, people[i].op_name) != 0)
    {
        strcpy(people[i].old_op2, people[i].old_op1);
        strcpy(people[i].old_op1, old_op);
        people[i].op1_end.year = people[i].tariff_start.year;
    }

    printf("New campaign: ");
    scanf("%s", people[i].campaign);

    printf("Subscriber info updated successfully.\n");
}

void find_subscriber()
{
    int sub_count = get_subscriber_count();
    int choice, i, found = 0;
    char tc[20], name[30], surname[30];

    printf("Select Search Type:\n1. Search by TC\n2. Search by Name/Surname\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("TC Identity No: ");
        scanf("%s", tc);
        if (!is_valid_tc(tc)) { printf("Invalid TC.\n"); return; }
        for (i = 0; i < sub_count; i++)
        {
            if (strcmp(people[i].tc_no, tc) == 0) { found = 1; break; }
        }
    }
    else if (choice == 2)
    {
        printf("Name: "); scanf("%s", name);
        printf("Surname: "); scanf("%s", surname);
        for (i = 0; i < sub_count; i++)
        {
            if (strcmp(people[i].name, name) == 0 && strcmp(people[i].surname, surname) == 0)
            { found = 1; break; }
        }
    }
    else { printf("Invalid choice.\n"); return; }

    if (!found) { printf("Record not found.\n"); return; }

    printf("\nSUBSCRIBER DETAILS\n");
    printf("TC Identity No: %s\n", people[i].tc_no);
    printf("Name Surname: %s %s\n", people[i].name, people[i].surname);
    printf("Age: %s\n", people[i].age);
    printf("Phone: %s\n", people[i].phone_no);
    printf("Address: %s\n", people[i].address);
    printf("Operator: %s\n", people[i].op_name);
    printf("Campaign: %s\n", people[i].campaign);
    printf("Tariff Start: %02d/%02d/%d\n", people[i].tariff_start.day, people[i].tariff_start.month, people[i].tariff_start.year);

    if (people[i].old_op1[0] != '\0') printf("Old Operator 1: %s\n", people[i].old_op1);
    if (people[i].old_op2[0] != '\0') printf("Old Operator 2: %s\n", people[i].old_op2);
}

void list_operator_changes()
{
    int year;
    int sub_count = get_subscriber_count();
    int i, found = 0;

    printf("Enter the year to analyze: ");
    scanf("%d", &year);

    printf("\nOperator changes in %d:\n", year);
    for (i = 0; i < sub_count; i++)
    {
        if (people[i].op2_end.year == year)
        {
            printf("%s %s : %s -> %s\n", people[i].name, people[i].surname, people[i].old_op2, people[i].old_op1);
            found = 1;
        }
        if (people[i].op1_end.year == year)
        {
            printf("%s %s : %s -> %s\n", people[i].name, people[i].surname, people[i].old_op1, people[i].op_name);
            found = 1;
        }
    }
    if (!found) printf("No operator changes found for this year.\n");
}

void loyalty_analysis()
{
    int sub_count = get_subscriber_count();
    int tcell = 0, vdf = 0, bim = 0, tkom = 0;

    for (int i = 0; i < sub_count; i++)
    {
        if (people[i].old_op1[0] == '\0' && people[i].old_op2[0] == '\0')
        {
            if (strcmp(people[i].op_name, "Turkcell") == 0) tcell++;
            else if (strcmp(people[i].op_name, "Vodafone") == 0) vdf++;
            else if (strcmp(people[i].op_name, "Bimcell") == 0) bim++;
            else if (strcmp(people[i].op_name, "Turk Telekom") == 0) tkom++;
        }
    }

    printf("Turkcell : %d loyal subscribers\n", tcell);
    printf("Vodafone : %d loyal subscribers\n", vdf);
    printf("Bimcell : %d loyal subscribers\n", bim);
    printf("Turk Telekom : %d loyal subscribers\n", tkom);
}

void campaign_popularity()
{
    int sub_count = get_subscriber_count();
    int i, j;
    struct camp { char name[50]; int count; } list[50];
    int total_types = 0;

    for (i = 0; i < sub_count; i++)
    {
        int found = 0;
        for (j = 0; j < total_types; j++)
        {
            if (strcmp(list[j].name, people[i].campaign) == 0)
            { list[j].count++; found = 1; break; }
        }
        if (!found)
        {
            strcpy(list[total_types].name, people[i].campaign);
            list[total_types].count = 1;
            total_types++;
        }
    }

    for (i = 0; i < total_types - 1; i++)
    {
        for (j = 0; j < total_types - 1 - i; j++)
        {
            if (list[j].count < list[j + 1].count)
            {
                struct camp temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < total_types; i++) printf("%s : %d subscribers\n", list[i].name, list[i].count);
}

void surprise_menu()
{
    int choice;
    while (1)
    {
        printf("\n--- Surprise Menu ---\n");
        printf("1. Draw Lucky Subscriber\n");
        printf("2. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) draw_lucky_subscriber();
        else if (choice == 2) break;
        else printf("Invalid selection.\n");
    }
}

void draw_lucky_subscriber()
{
    int sub_count = get_subscriber_count();
    if (sub_count == 0) { printf("No subscribers in the system!\n"); return; }
    
    int rand_index;
    srand(time(NULL));
    rand_index = rand() % sub_count;

    printf("\nLucky Subscriber:\n");
    printf("%s %s\n", people[rand_index].name, people[rand_index].surname);
    printf("Phone: %s\n", people[rand_index].phone_no);
    printf("Operator: %s\n", people[rand_index].op_name);

    printf("Congratulations! You won a surprise gift.\n");

    int choice;
    while (1)
    {
        printf("Select to reveal your prize:\n1. Gift Option 1\n2. Gift Option 2\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) { printf("Prize: Tarkan Concert Ticket!\n"); break; }
        else if (choice == 2) { printf("Prize: iPhone 17 Pro!\n"); break; }
        else printf("Invalid choice. Try again.\n");
    }
}

int is_valid_tc(char tc[])
{
    int i = 0;
    while (tc[i] != '\0')
    {
        if (!isdigit(tc[i])) return 0;
        i++;
    }
    return (i == 11);
}

int is_valid_date(int day, int month, int year)
{
    if (year < 1 || month < 1 || month > 12 || day < 1) return 0;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) { if (day > 31) return 0; }
    else if (month == 4 || month == 6 || month == 9 || month == 11) { if (day > 30) return 0; }
    else if (month == 2) { if (day > 28) return 0; }
    return 1;
}

int is_numeric_only(char str[])
{
    int i = 0;
    while (str[i] != '\0') { if (!isdigit(str[i])) return 0; i++; }
    return 1;
}

int get_subscriber_count()
{
    int i = 0;
    while (i < 1000 && people[i].tc_no[0] != '\0') i++;
    return i;
}
