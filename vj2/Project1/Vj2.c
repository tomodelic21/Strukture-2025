#define CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student{
	char name[15];
	char surname[15];
	int age;
	struct student* next;
}Student;

Student* InputList(Student* head);
Student* PrintList(Student* head);
Student* AddToBeginning(Student* head);
Student* AddToEnd(Student* head);
Student* Search(Student* head);
Student* Delete(Student* head);

int main() {
	
	Student* head = NULL;

	head = InputList(head);
	head = PrintList(head);
	
	head = AddToBeginning(head);
	head = PrintList(head);

	head = AddToEnd(head);
	head = PrintList(head);

	head = Search(head);

	head = Delete(head);
	head = PrintList(head);

	free(head);

	return EXIT_SUCCESS;
}

Student* InputList(Student* head) {
	int i, j;

	printf("Unesite koliki broj ljudi zelite unijeti: ");
	scanf_s("%d", &j);
	(void)getchar();

	for (i = 0; i < j; i++) {
		Student* new = (Student*)malloc(sizeof(Student));
		if (new == NULL) {
			printf("\nGreska pri alkokaciji memorije");
			return head;
		}
		printf("\nUnesi ime: ");

		fgets(new->name, sizeof(new->name), stdin);
		new->name[strcspn(new->name, "\n")] = 0;

		printf("Unesi prezime: ");
		fgets(new->surname, sizeof(new->surname), stdin);
		new->surname[strcspn(new->surname, "\n")] = 0;

		printf("Unesi godinu rodenja: ");
		scanf_s("%d", &new->age);
		(void)getchar();

		new->next = NULL;

		if (head == NULL) {
			head = new;
		}
		else {
			Student* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = new;
		}

	}
	return head;
}

Student* PrintList(Student* head) {
	Student* temp = head;
	
	printf("Ispis Liste:\n");

	while (temp != NULL) {
		printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n", temp->name, temp->surname, temp->age);
		temp = temp->next;
	}

	return head;
}
Student* AddToBeginning(Student* head) {
	Student* new = (Student*)malloc(sizeof(Student));
	if (new == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return head;
	}
	printf("\nDodavanje na vrh liste:");

	printf("\nUnesi ime: ");
	fgets(new->name, sizeof(new->name), stdin);
	new->name[strcspn(new->name, "\n")] = 0;

	printf("Unesi prezime: ");
	fgets(new->surname, sizeof(new->surname), stdin);
	new->surname[strcspn(new->surname, "\n")] = 0;

	printf("Unesi godinu rodenja: ");
	scanf_s("%d", &new->age);
	(void)getchar();

	new->next = head;

	head = new;

	return head;
}
Student* AddToEnd(Student* head) {
	Student* new = (Student*)malloc(sizeof(Student));
	if (new == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return head;
	}
	printf("\nDodavanje na kraj liste:");
	printf("\nUnesi ime: ");
	fgets(new->name, sizeof(new->name), stdin);
	new->name[strcspn(new->name, "\n")] = 0;

	printf("Unesi prezime: ");
	fgets(new->surname, sizeof(new->surname), stdin);
	new->surname[strcspn(new->surname, "\n")] = 0;

	printf("Unesi godinu rodenja: ");
	scanf_s("%d", &new->age);
	(void)getchar();

	new->next = NULL;

	if (head == NULL) {
		head = new;
	}
	else {
		Student* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new;
	}
	return head;
}
Student* Search(Student* head) {
	char surname[15];
	int found = 0;
	
	printf("Unesite prezime koje zelite pronaci: ");
	fgets(surname, sizeof(surname), stdin);
	surname[strcspn(surname, "\n")] = 0;

	Student* temp = head;

	while (temp != NULL) {
		if (strcmp(temp->surname, surname) == 0) {
			printf("Student pronaden:\n");
			printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n", temp->name, temp->surname, temp->age);
			found = 1;
		}
		temp = temp->next;
	}
	if (!found) {
		printf("Student nije pronaden.\n");
	}
	return head;
}
Student* Delete(Student* head) {
	char surname[15];
	int found = 0;

	printf("Unesite prezime koje zelite izbrisati: ");
	fgets(surname, sizeof(surname), stdin);
	surname[strcspn(surname, "\n")] = 0; 

	Student* temp = head;
	Student* prev = NULL;

	while (temp != NULL) {
		if (strcmp(temp->surname, surname) == 0) {
			found = 1;
			if (prev == NULL) {
				head = temp->next;
				free(temp);
				temp = head;
			}
			else {
				prev->next = temp->next;
				free(temp);
				temp = prev->next;
			}
		}
		else {
			prev = temp;
			temp = temp->next;
		}
	}
	if (!found) {
		printf("Student sa prezimenom '%s' nije pronadjen.\n", surname);
	}
	else {
		printf("Svi studenti sa prezimenom '%s' su obrisani.\n", surname);
	}
	return head;
}
