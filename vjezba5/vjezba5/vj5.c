#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024

typedef struct _postfix* Position;

typedef struct _postfix {
    double number;
    Position next;
} postfix;

Position createElement(double value);
int push(Position head, double value);
double pop(Position head);
int isOperator(char c);
double performOperation(double a, double b, char op);
int calculateFromFile(const char* filename, double* result);

int main() {
    double result = 0;

    if (calculateFromFile("postfix.txt", &result) == 0) {
        printf("Rezultat izraza je: %.2lf\n", result);
    }
    else {
        printf("Dogodila se greska prilikom racunanja.\n");
    }

    return 0;
}

Position createElement(double value) {
    Position newElement = (Position)malloc(sizeof(postfix));
    if (!newElement) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }
    newElement->number = value;
    newElement->next = NULL;
    return newElement;
}

int push(Position head, double value) {
    Position newElement = createElement(value);
    if (!newElement) return EXIT_FAILURE;

    newElement->next = head->next;
    head->next = newElement;
    return EXIT_SUCCESS;
}


double pop(Position head) {
    if (head->next == NULL) {
        printf("Stog je prazan!\n");
        return EXIT_FAILURE;
    }

    Position temp = head->next;
    double value = temp->number;

    head->next = temp->next;
    free(temp);

    return value;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double performOperation(double a, double b, char op) {
    switch (op) {
    case '+': return b + a;
    case '-': return b - a;
    case '*': return b * a;
    case '/':
        if (a == 0) {
            printf("Dijeljenje s nulom!\n");
            return EXIT_SUCCESS;
        }
        return b / a;
    default:
        printf("Nepoznat operator: %c\n", op);
        EXIT_SUCCESS;
    }
}

int calculateFromFile(const char* filename, double* result) {

    FILE* file = NULL;
    errno_t err = fopen_s(&file, "Vjezba5.txt", "r");
    if (err) {
        printf("Pogreska pri otvaranju datoteke.\n");
        return EXIT_FAILURE;
    }

    char buffer[MAX_LINE];
    if (!fgets(buffer, MAX_LINE, file)) {
        printf("Greska pri citanju datoteke!\n");
        fclose(file);
        return EXIT_FAILURE;
    }
    fclose(file);

    postfix head;
    head.next = NULL;

    char* context = NULL;
    char* token = strtok_s(buffer, " \n", &context);
    while (token != NULL) {

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            double num = atof(token);
            push(&head, num);
        }

        else if (isOperator(token[0]) && strlen(token) == 1) {
            double a = pop(&head);
            double b = pop(&head);
            double rez = performOperation(a, b, token[0]);
            push(&head, rez);
        }
        else {
            printf("Nepoznat token: %s\n", token);
            return EXIT_FAILURE;
        }

        token = strtok_s(NULL, " \n", &context);

    }

    if (head.next == NULL || head.next->next != NULL) {
        printf("Pogresan postfix izraz!\n");
        return EXIT_FAILURE;
    }

    *result = pop(&head);
    return EXIT_SUCCESS;
}
