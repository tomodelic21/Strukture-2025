#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 50

typedef struct Directory {
    char name[NAME_LENGTH];
    struct Directory* parent;
    struct Directory* child;
    struct Directory* sibling;
} Directory;


Directory* createDir(const char* name, Directory* parent) {
    Directory* d = (Directory*)malloc(sizeof(Directory));
    if (!d) return NULL;

    strcpy_s(d->name, NAME_LENGTH, name);
    d->parent = parent;
    d->child = NULL;
    d->sibling = NULL;

    return d;
}

int md(Directory* current, const char* name) {
    Directory* newD = createDir(name, current);
    if (!newD) return EXIT_FAILURE;

    if (current->child == NULL)
        current->child = newD;
    else {
        Directory* temp = current->child;
        while (temp->sibling != NULL)
            temp = temp->sibling;
        temp->sibling = newD;
    }
    return EXIT_SUCCESS;
}

Directory* cd(Directory* current, const char* name) {
    Directory* temp = current->child;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->sibling;
    }
    return NULL;
}

Directory* cdBack(Directory* current) {
    if (current->parent != NULL)
        return current->parent;
    return current;
}

int dir(Directory* current) {
    Directory* temp = current->child;

    printf("\nSadrzaj direktorija %s:\n", current->name);

    if (!temp) {
        printf("  <prazno>\n");
        return EXIT_SUCCESS;
    }

    while (temp != NULL) {
        printf("  %s\n", temp->name);
        temp = temp->sibling;
    }

    return EXIT_SUCCESS;
}


int freeTree(Directory* root) {
    if (root == NULL)
        return EXIT_SUCCESS;

    freeTree(root->child);
    freeTree(root->sibling);

    free(root);
    return EXIT_SUCCESS;
}


int printTree(Directory* dir, int level) {
    if (dir == NULL)
        return EXIT_SUCCESS;

    for (int i = 0; i < level; i++)
        printf("   "); 

    printf("%s\n", dir->name);

    printTree(dir->child, level + 1);
    printTree(dir->sibling, level);

    return EXIT_SUCCESS;
}


int main() {
    Directory* root = createDir("C:", NULL);
    Directory* current = root;

    int izbor;
    char ime[NAME_LENGTH];

    while (1) {
        printf("\n-----------------------------\n");
        printf("Trenutni direktorij: %s\n", current->name);
        printf("1 - md\n2 - cd dir\n3 - cd..\n4 - dir\n5 - izlaz\n6 - tree\n");
        printf("Odabir: ");
        scanf_s("%d", &izbor);

        if (izbor == 1) {
            printf("Unesite naziv direktorija: ");
            scanf_s("%s", ime, NAME_LENGTH);
            md(current, ime);
        }
        else if (izbor == 2) {
            printf("Unesite direktorij za ulazak: ");
            scanf_s("%s", ime, NAME_LENGTH);

            Directory* next = cd(current, ime);
            if (next == NULL)
                printf("Direktorij ne postoji!\n");
            else
                current = next;
        }
        else if (izbor == 3) {
            current = cdBack(current);
        }
        else if (izbor == 4) {
            dir(current);
        }
        else if (izbor == 5) {
            freeTree(root);
            return EXIT_SUCCESS;
        }
        else if (izbor == 6) {
            printf("\nStablo direktorija:\n");
            printTree(root, 0);
        }
        else {
            printf("Nepostojeca opcija!\n");
        }
    }

    return EXIT_SUCCESS;
}
