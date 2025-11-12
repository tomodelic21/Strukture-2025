#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _poly* Position;

typedef struct _poly {
    int coeff;
    int pow;
    Position next;
} poly;

Position ReadPolyFromFile(const char* filename, Position head);
Position PrintPoly(Position head);
Position AddPoly(Position firstP, Position secondP, Position head);
Position MultiplyPoly(Position firstP, Position secondP, Position head);

int main() {
    poly head = { 0,0,NULL };

    poly firstPoly = head;
    poly secondPoly = head;

    poly sumHead = { 0,0,NULL };
    poly productHead = { 0,0,NULL };

    Position poly1 = ReadPolyFromFile("FirstPoly.txt", &firstPoly);
    Position poly2 = ReadPolyFromFile("SecondPoly.txt", &secondPoly);

    printf("Polinom 1:\n");
    PrintPoly(poly1);

    printf("\nPolinom 2:\n");
    PrintPoly(poly2);

    AddPoly(&firstPoly, &secondPoly, &sumHead);
    printf("\nZbroj polinoma:\n");
    PrintPoly(&sumHead);

    MultiplyPoly(&firstPoly, &secondPoly, &productHead);
    printf("\nUmnozak polinoma:\n");
    PrintPoly(&productHead);

    return EXIT_SUCCESS;
}

Position ReadPolyFromFile(const char* filename, Position head) {
    FILE* fp = NULL;
    if (fopen_s(&fp, filename, "r") != 0 || fp == NULL) {
        perror("Greska pri otvaranju datoteke");
        return EXIT_FAILURE;
    }

    char line[256];
    if (fgets(line, sizeof(line), fp)) {
        char* ptr = line;
        while (*ptr) {
            while (*ptr && isspace(*ptr)) ptr++;
            if (*ptr == '\0') break;

            int sign = 1;
            if (*ptr == '+') { sign = 1; ptr++; }
            else if (*ptr == '-') { sign = -1; ptr++; }

            char* endPtr;
            long coeff = strtol(ptr, &endPtr, 10);
            if (ptr == endPtr) coeff = 1; 
            coeff *= sign;
            ptr = endPtr;

            int pow = 0;
            if (*ptr == 'x') {
                ptr++;
                pow = 1; 
                if (*ptr == '^') {
                    ptr++;
                    pow = (int)strtol(ptr, &endPtr, 10);
                    ptr = endPtr;
                }
            }

            Position newNode = (Position)malloc(sizeof(poly));
            if (!newNode) {
                perror("Greska pri alokaciji memorije");
                fclose(fp);
                return EXIT_FAILURE; 
            }

            newNode->coeff = (int)coeff;
            newNode->pow = pow;
            newNode->next = NULL;

            Position prev = head;
            Position p = head->next;

            while (p != NULL && p->pow > newNode->pow) {
                prev = p;
                p = p->next;
            }
            if (p != NULL && p->pow == newNode->pow) {
                p->coeff += newNode->coeff;
                free(newNode);
            }
            else {
                newNode->next = p;
                prev->next = newNode;
            }

        }
    }

    fclose(fp);
    return head;
}

Position PrintPoly(Position head) {
    Position temp = head->next;
    if (!temp) {
        printf("Polinom je prazan.\n");
        return EXIT_FAILURE;
    }

    int first = 1;
    while (temp) {
        if (!first) {
            if (temp->coeff >= 0)
                printf(" + ");
            else
                printf(" - ");
        }
        else {
            if (temp->coeff < 0)
                printf("-");
        }

        printf("%d", abs(temp->coeff));

        if (temp->pow > 1)
            printf("x^%d", temp->pow);
        else if (temp->pow == 1)
            printf("x");
        else if (temp->pow == 0)
            printf(""); 

        first = 0;
        temp = temp->next;
    }

    printf("\n");
    return head;
}

Position AddPoly(Position firstP, Position secondP, Position head) {
    Position p1 = firstP->next;
    Position p2 = secondP->next;

    while (p1 != NULL && p2 != NULL) {
        Position newEl = (Position)malloc(sizeof(poly));
        if (!newEl) {
            perror("Greska pri alokaciji memorije");
            return NULL;
        }
        newEl->next = NULL;

        if (p1->pow == p2->pow) {
            newEl->coeff = p1->coeff + p2->coeff;
            newEl->pow = p1->pow;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->pow > p2->pow) {
            newEl->coeff = p1->coeff;
            newEl->pow = p1->pow;
            p1 = p1->next;
        }
        else {
            newEl->coeff = p2->coeff;
            newEl->pow = p2->pow;
            p2 = p2->next;
        }

        Position last = head;
        while (last->next != NULL)
            last = last->next;
        last->next = newEl;
    }

    while (p1 != NULL) {
        Position newEl = (Position)malloc(sizeof(poly));
        newEl->coeff = p1->coeff;
        newEl->pow = p1->pow;
        newEl->next = NULL;

        Position last = head;
        while (last->next != NULL)
            last = last->next;
        last->next = newEl;

        p1 = p1->next;
    }

    while (p2 != NULL) {
        Position newEl = (Position)malloc(sizeof(poly));
        newEl->coeff = p2->coeff;
        newEl->pow = p2->pow;
        newEl->next = NULL;

        Position last = head;
        while (last->next != NULL)
            last = last->next;
        last->next = newEl;

        p2 = p2->next;
    }

    return head;
}

Position MultiplyPoly(Position firstP, Position secondP, Position head) {
    for (Position p1 = firstP->next; p1 != NULL; p1 = p1->next) {
        for (Position p2 = secondP->next; p2 != NULL; p2 = p2->next) {
            int coeff = p1->coeff * p2->coeff;
            int pow = p1->pow + p2->pow;

            Position newEl = (Position)malloc(sizeof(poly));
            if (!newEl) {
                perror("Greska pri alokaciji memorije");
                return NULL;
            }
            newEl->coeff = coeff;
            newEl->pow = pow;
            newEl->next = NULL;

            Position prev = head;
            Position q = head->next;

            while (q != NULL && q->pow > pow) {
                prev = q;
                q = q->next;
            }

            if (q != NULL && q->pow == pow) {
                q->coeff += coeff;
                free(newEl);
            }
            else {
                newEl->next = q;
                prev->next = newEl;
            }
        }
    }

    return head;
}

