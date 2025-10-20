#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct position{
	char name[15];
	char surname[15];
	int age;
	struct position* next;
}person;


person* InputList(person *head);
person* PrintList(person* head);
person* AddToBeginning(person* head);
person* AddToEnd(person* head);

int main() {

	person* head = (person*)malloc(sizeof(person));
	if (head == NULL) {
		printf("Greška pri alokaciji memorije!\n");
		return EXIT_FAILURE;
	}

	strcpy(head->name, "jure");
	strcpy(head->surname, "bacic");
	head->age = 1999;
	head->next = NULL;

	head = InputList(head);
	head = PrintList(head);

	head = AddToBeginning(head);
	head = PrintList(head);

	head = AddToEnd(head);
	head = PrintList(head);


	free(head);
	
	return EXIT_SUCCESS;
}

person* InputList(person* head) {
	int i, j;

	printf("Unesite koliki broj ljudi zelite unijeti: ");
	scanf_s("%d", &j);
	(void)getchar();

	for (i = 0; i < j; ++i) {
		person* novi = (person*)malloc(sizeof(person));
		if (novi == NULL) {
			printf("\nGreska pri alokaciji memorije!\n");
			return head;
		}
		printf("\nUnesi ime: ");
		fgets(novi->name, sizeof(novi->name), stdin);
		novi->name[strcspn(novi->name, "\n")] = 0;

		printf("Unesi prezime: ");
		fgets(novi->surname, sizeof(novi->surname), stdin);
		novi->surname[strcspn(novi->surname, "\n")] = 0;

		printf("Unesi godinu rodenja: ");
		scanf_s("%d", &novi->age);
		(void)getchar();

		novi->next = NULL;

		if (head == NULL) {
			head = novi;
		}
		else {
			person* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = novi;
		}

	}
	return head;
}
	
	person* PrintList(person * head) {
		person* temp = head;

		printf("Ispis Liste:\n");

		while (temp != NULL) {
			printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n", temp->name, temp->surname, temp->age);
			temp = temp->next;
		}

		return head;
	}
person* AddToBeginning(person* head){
	person* novi = (person*)malloc(sizeof(person));
	if (novi == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return head;
	}
	printf("\nDodavanje na vrh liste:");

	printf("\nUnesi ime: ");
	fgets(novi->name, sizeof(novi->name), stdin);
	novi->name[strcspn(novi->name, "\n")] = 0;

	printf("Unesi prezime: ");
	fgets(novi->surname, sizeof(novi->surname), stdin);
	novi->surname[strcspn(novi->surname, "\n")] = 0;

	printf("Unesi godinu rodenja: ");
	scanf_s("%d", &novi->age);
	(void)getchar();

	novi->next = head;

	head = novi;

	return head;
}
person* AddToEnd(person* head) {
	person* novi = (person*)malloc(sizeof(person));
	if (novi == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return head;
	}
	printf("\nDodavanje na kraj liste:");
	printf("\nUnesi ime: ");
	fgets(novi->name, sizeof(novi->name), stdin);
	novi->name[strcspn(novi->name, "\n")] = 0;

	printf("Unesi prezime: ");
	fgets(novi->surname, sizeof(novi->surname), stdin);
	novi->surname[strcspn(novi->surname, "\n")] = 0;

	printf("Unesi godinu rodenja: ");
	scanf_s("%d", &novi->age);
	(void)getchar();

	novi->next = NULL;

	if (head == NULL) {
		head = novi;
	}
	else {
		person* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = novi;
	}

	return head;

}
