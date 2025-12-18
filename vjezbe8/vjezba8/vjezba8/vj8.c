#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Tree* treePos;

typedef struct Tree {
    int value;
    treePos left;
    treePos right;
} Tree;

/* ---------- PROTOTIPI ---------- */
treePos insertTree(treePos root, int value);
treePos findTree(treePos root, int value);
treePos deleteTree(treePos root, int value);
treePos findMin(treePos root);

int inorder(treePos root);
int preorder(treePos root);
int postorder(treePos root);
int levelOrder(treePos root);
int freeTree(treePos root);


int menu(void);

/* ---------- QUEUE ZA LEVEL ORDER ---------- */
typedef struct QueueNode* queuePos;
typedef struct QueueNode {
    treePos data;
    queuePos next;
} QueueNode;

int enqueue(queuePos* front, queuePos* rear, treePos data);
int dequeue(queuePos* front, queuePos* rear, treePos* data);

/* ---------- MAIN ---------- */
int main(void)
{
    treePos root = NULL;
    int choice = 0, value = 0;

    do {
        choice = menu();

        switch (choice) {
        case 1:
            printf("Unesite vrijednost: ");
            scanf_s("%d", &value);
            root = insertTree(root, value);
            break;

        case 2:
            printf("Unesite vrijednost za trazenje: ");
            scanf_s("%d", &value);
            if (findTree(root, value))
                printf("Element %d je pronaden.\n", value);
            else
                printf("Element %d nije pronaden.\n", value);
            break;

        case 3:
            printf("Unesite vrijednost za brisanje: ");
            scanf_s("%d", &value);
            root = deleteTree(root, value);
            break;

        case 4:
            printf("Inorder: ");
            inorder(root);
            printf("\n");
            break;

        case 5:
            printf("Preorder: ");
            preorder(root);
            printf("\n");
            break;

        case 6:
            printf("Postorder: ");
            postorder(root);
            printf("\n");
            break;

        case 7:
            printf("Level order: ");
            levelOrder(root);
            printf("\n");
            break;
        }

    } while (choice != 0);

    freeTree(root);
    root = NULL;

    return EXIT_SUCCESS;
}

/* ---------- FUNKCIJE ---------- */

treePos insertTree(treePos root, int value)
{
    if (root == NULL) {
        root = (treePos)malloc(sizeof(Tree));
        if (!root) {
            printf("Greska pri alokaciji memorije!\n");
            return NULL;
        }
        root->value = value;
        root->left = NULL;
        root->right = NULL;
    }
    else if (value < root->value) {
        root->left = insertTree(root->left, value);
    }
    else if (value > root->value) {
        root->right = insertTree(root->right, value);
    }

    return root;
}

treePos findTree(treePos root, int value)
{
    if (root == NULL)
        return NULL;

    if (value < root->value)
        return findTree(root->left, value);
    else if (value > root->value)
        return findTree(root->right, value);
    else
        return root;
}

treePos deleteTree(treePos root, int value)
{
    if (root == NULL)
        return NULL;

    if (value < root->value) {
        root->left = deleteTree(root->left, value);
    }
    else if (value > root->value) {
        root->right = deleteTree(root->right, value);
    }
    else {
        if (root->left == NULL) {
            treePos temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            treePos temp = root->left;
            free(root);
            return temp;
        }
        else {
            treePos temp = findMin(root->right);
            root->value = temp->value;
            root->right = deleteTree(root->right, temp->value);
        }
    }
    return root;
}

treePos findMin(treePos root)
{
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

/* ---------- ISPISI ---------- */

int inorder(treePos root)
{
    if (root == NULL)
        return EXIT_SUCCESS;

    inorder(root->left);
    printf("%d ", root->value);
    inorder(root->right);

    return EXIT_SUCCESS;
}

int preorder(treePos root)
{
    if (root == NULL)
        return EXIT_SUCCESS;

    printf("%d ", root->value);
    preorder(root->left);
    preorder(root->right);

    return EXIT_SUCCESS;
}

int postorder(treePos root)
{
    if (root == NULL)
        return EXIT_SUCCESS;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->value);

    return EXIT_SUCCESS;
}

/* ---------- LEVEL ORDER ---------- */

int levelOrder(treePos root)
{
    queuePos front = NULL, rear = NULL;
    treePos temp = NULL;

    if (root == NULL)
        return EXIT_FAILURE;

    enqueue(&front, &rear, root);

    while (front != NULL) {
        dequeue(&front, &rear, &temp);
        printf("%d ", temp->value);

        if (temp->left)
            enqueue(&front, &rear, temp->left);
        if (temp->right)
            enqueue(&front, &rear, temp->right);
    }

    return EXIT_SUCCESS;
}

/* ---------- QUEUE ---------- */

int enqueue(queuePos* front, queuePos* rear, treePos data)
{
    queuePos newNode = (queuePos)malloc(sizeof(QueueNode));
    if (!newNode)
        return EXIT_FAILURE;

    newNode->data = data;
    newNode->next = NULL;

    if (*rear)
        (*rear)->next = newNode;
    else
        *front = newNode;

    *rear = newNode;
    return EXIT_SUCCESS;
}

int dequeue(queuePos* front, queuePos* rear, treePos* data)
{
    if (*front == NULL)
        return EXIT_FAILURE;

    queuePos temp = *front;
    *data = temp->data;
    *front = temp->next;

    if (*front == NULL)
        *rear = NULL;

    free(temp);
    return EXIT_SUCCESS;
}

int freeTree(treePos root)
{
    if (root == NULL)
        return EXIT_SUCCESS;

    freeTree(root->left);
    freeTree(root->right);
    free(root);

    return EXIT_SUCCESS;
}


/* ---------- MENU ---------- */

int menu(void)
{
    int choice;
    printf("\n--- BST MENU ---\n");
    printf("1 - Unos elementa\n");
    printf("2 - Traznje elementa\n");
    printf("3 - Brisanje elementa\n");
    printf("4 - Inorder ispis\n");
    printf("5 - Preorder ispis\n");
    printf("6 - Postorder ispis\n");
    printf("7 - Level order ispis\n");
    printf("0 - Izlaz\n");
    printf("Odabir: ");
    scanf_s("%d", &choice);

    return choice;
}
