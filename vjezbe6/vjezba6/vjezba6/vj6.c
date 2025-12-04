#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_LINE 256

typedef struct _date{
    int year, month, day;
} Date;

typedef struct _article {
    char name[MAX_NAME];
    int quantity;
    double price;
    struct _article* next;
} Article;

typedef struct _receipt {
    Date date;
    Article* articles;
    struct _rceipt* next;
} Receipt;

// ---------------- COMPARE DATE -------------------

int compareDates(Date a, Date b) {
    if (a.year != b.year) return a.year - b.year;
    if (a.month != b.month) return a.month - b.month;
    return a.day - b.day;
}

int dateInRange(Date d, Date s, Date e) {
    return compareDates(d, s) >= 0 && compareDates(d, e) <= 0;
}

// ---------------- CREATE RECEIPT-------------------

Receipt* createReceipt(Date d) {
    Receipt* r = (Receipt*)malloc(sizeof(Receipt));
    if (!r) return NULL;
    r->date = d;
    r->articles = NULL;
    r->next = NULL;
    return r;
}

Article* createArticle(char* name, int q, double p) {
    Article* a = (Article*)malloc(sizeof(Article));
    if (!a) return NULL;
    strcpy(a->name, name);
    a->quantity = q;
    a->price = p;
    a->next = NULL;
    return a;
}

// ---------------- SORT INSERT -------------------

int insertArticleSorted(Article** head, Article* newA) {
    Article* curr = *head;
    Article* prev = NULL;

    while (curr && strcmp(curr->name, newA->name) < 0) {
        prev = curr;
        curr = curr->next;
    }

    newA->next = curr;
    if (!prev) *head = newA;
    else prev->next = newA;

    return 0;
}

int insertReceiptSorted(Receipt** head, Receipt* newR) {
    Receipt* curr = *head;
    Receipt* prev = NULL;

    while (curr && compareDates(curr->date, newR->date) < 0) {
        prev = curr;
        curr = curr->next;
    }

    newR->next = curr;
    if (!prev) *head = newR;
    else prev->next = newR;

    return 0;
}

// ---------------- LOAD ONE RECEIPT -------------------

int loadSingleReceipt(const char* filename, Receipt** root) {

    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Greska pri otvaranju %s\n", filename);
        return -1;
    }

    char line[MAX_LINE];
    Date d;

    if (!fgets(line, MAX_LINE, f)) {
        fclose(f);
        return -1;
    }

    if (sscanf(line, "%d-%d-%d", &d.year, &d.month, &d.day) != 3) {
        fclose(f);
        return -1;
    }

    Receipt* r = createReceipt(d);
    if (!r) return -1;

    while (fgets(line, MAX_LINE, f)) {
        char name[MAX_NAME];
        int q;
        double p;

        if (sscanf(line, "%99[^,],%d,%lf", name, &q, &p) == 3) {
            Article* a = createArticle(name, q, p);
            insertArticleSorted(&r->articles, a);
        }
    }

    insertReceiptSorted(root, r);
    fclose(f);
    return 0;
}

// ---------------- LOAD ALL RECEIPTS -------------------

int loadReceipts(const char* filename, Receipt** root) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Ne mogu otvoriti %s\n", filename);
        return -1;
    }

    char recFile[MAX_LINE];

    while (fgets(recFile, MAX_LINE, f)) {
        recFile[strcspn(recFile, "\n")] = 0;
        loadSingleReceipt(recFile, root);
    }

    fclose(f);
    return 0;
}

// ---------------- PRINT -------------------

int printReceipts(Receipt* root) {
    while (root) {
        printf("Datum: %04d-%02d-%02d\n", root->date.year, root->date.month, root->date.day);

        Article* a = root->articles;
        while (a) {
            printf("\t%s, %d, %.2f\n", a->name, a->quantity, a->price);
            a = a->next;
        }

        root = root->next;
    }
    return 0;
}

// ---------------- QUERY -------------------

int articleQuery(Receipt* root) {
    char name[MAX_NAME];
    Date s, e;

    printf("Unesite naziv artikla: ");
    scanf(" %99[^\n]", name);

    printf("Unesite pocetni datum (YYYY MM DD): ");
    scanf("%d %d %d", &s.year, &s.month, &s.day);

    printf("Unesite zavrsni datum (YYYY MM DD): ");
    scanf("%d %d %d", &e.year, &e.month, &e.day);

    double totalCost = 0;
    int totalQty = 0;

    while (root) {
        if (dateInRange(root->date, s, e)) {
            Article* a = root->articles;
            while (a) {
                if (strcmp(a->name, name) == 0) {
                    totalCost += a->price * a->quantity;
                    totalQty += a->quantity;
                }
                a = a->next;
            }
        }
        root = root->next;
    }

    printf("\nArtikl: %s\n", name);
    printf("Ukupna potrosnja: %.2f\n", totalCost);
    printf("Ukupna kolicina: %d\n", totalQty);

    return 0;
}

// ---------------- FREE -------------------

int freeAll(Receipt* root) {
    while (root) {
        Article* a = root->articles;
        while (a) {
            Article* tmp = a;
            a = a->next;
            free(tmp);
        }
        Receipt* tmpR = root;
        root = root->next;
        free(tmpR);
    }
    return 0;
}

// ---------------- MAIN -------------------

int main() {
    Receipt* root = NULL;

    loadReceipts("racuni.txt", &root);

    int choice = 0;
    do {
        printf("\n1 - Ispis racuna\n");
        printf("2 - Upit za artikl\n");
        printf("0 - Izlaz\n> ");
        scanf("%d", &choice);

        if (choice == 1) printReceipts(root);
        else if (choice == 2) articleQuery(root);

    } while (choice != 0);

    freeAll(root);
    return 0;
}


