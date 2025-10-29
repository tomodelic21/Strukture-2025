#define CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct student {
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
Student* AddInFront(Student* head);
Student* AddBehind(Student* head);
Student* Sort(Student* head);
Student* ListInFile(Student* head);
Student* ReadListInFile(Student* head);

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

	head = AddInFront(head);
	head = PrintList(head);

	head = AddBehind(head);
	head = PrintList(head);

	head = Sort(head);
	head = PrintList(head);

	head = ListInFile(head);

	head = ReadListInFile(head);

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

Student* AddInFront(Student* head) {
	char surname[15];

	printf("Unesite ispred kojeg studenta zelite upisati novog studenta: ");
	fgets(surname, sizeof(surname), stdin);
	surname[strcspn(surname, "\n")] = 0;

	Student* new = (Student*)malloc(sizeof(Student));
	if (new == NULL) {
		printf("Greska pri alokaciji memorije!\n");
		return head;
	}

	printf("\nDodavanje ispred zadanog studenta:");
	printf("\nUnesi ime: ");
	fgets(new->name, sizeof(new->name), stdin);
	new->name[strcspn(new->name, "\n")] = 0;

	printf("Unesi prezime: ");
	fgets(new->surname, sizeof(new->surname), stdin);
	new->surname[strcspn(new->surname, "\n")] = 0;

	printf("Unesi godinu rodenja: ");
	scanf_s("%d", &new->age);
	(void)getchar();

	Student* temp = head;
	Student* prev = NULL;
	
	while (temp != NULL) {
		if (strcmp(temp->surname, surname) == 0) {
			if (prev == NULL) {
				new->next = head;
				head = new;
				return head;
			}
			else {
				prev->next = new;
				new->next = temp;
				temp = new;
				return head;
			}
		}
		prev = temp;
		temp = temp->next;
	}	
}


Student* AddBehind(Student* head) {
    char surname[15];
    printf("Unesite iza kojeg studenta zelite upisati novog studenta: ");
    fgets(surname, sizeof(surname), stdin);
    surname[strcspn(surname, "\n")] = 0;

    Student* new = (Student*)malloc(sizeof(Student));
    if (!new) {
        printf("Greska pri alokaciji memorije!\n");
        return head;
    }

    printf("\nDodavanje iza zadanog studenta:");
    printf("\nUnesi ime: ");
    fgets(new->name, sizeof(new->name), stdin);
    new->name[strcspn(new->name, "\n")] = 0;

    printf("Unesi prezime: ");
    fgets(new->surname, sizeof(new->surname), stdin);
    new->surname[strcspn(new->surname, "\n")] = 0;

    printf("Unesi godinu rodenja: ");
    scanf_s("%d", &new->age);
    (void)getchar();

    Student* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->surname, surname) == 0) {
            new->next = temp->next;
            temp->next = new;
            return head;
        }
        temp = temp->next;
    }

    printf("Student sa prezimenom '%s' nije pronaden.\n", surname);
    free(new);
    return head;
}

Student* Sort(Student* head) {
	if (head == NULL) return NULL;

	Student* i;
	Student* j;
	Student temp; 
	Student* tempNext;

	for (i = head; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if (strcmp(i->surname, j->surname) > 0) {
				temp = *i;
				*i = *j;
				*j = temp;

				tempNext = i->next;
				i->next = j->next;
				j->next = tempNext;
			}
		}
	}
	return head;
}
Student* ListInFile(Student* head) {

	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, "vjezba3.txt", "w");
	if (err) {
		printf("Pogreska pri otvaranju datoteke.\n");
		return 1;
	}

	Student* temp = head;

	fprintf(fp,"Ispis studenata: \n");
	while (temp != NULL) {
		fprintf(fp, "%s %s %d", temp->name, temp->surname, temp->age);
		fprintf(fp, "\n");
		temp = temp->next;
	}

	fclose(fp);
	return head;
}
Student* ReadListInFile(Student* head) {
	int i = 0;
	char line[100];


	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, "vjezba3.txt", "r");
	if (err) {
		printf("Pogreska pri otvaranju datoteke.\n");
		return 1;
	}

	Student* temp = NULL;
	Student* last = NULL;

	while (fgets(line, sizeof(line), fp) != NULL) {
		Student* newStudent = (Student*)malloc(sizeof(Student));
		if (newStudent == NULL) {
			printf("Greska pri alokaciji memorije.\n");
			fclose(fp);
			return temp;
		}
		fscanf_s(fp, "%s", newStudent->name, sizeof(newStudent->name));
		fscanf_s(fp, "%s", newStudent->surname, sizeof(newStudent->surname));
		fscanf_s(fp, "%d", &newStudent->age);
		newStudent->next = NULL;

		if (temp == NULL) {
			temp = newStudent;
		}
		else {
			last->next = newStudent;
		}
		last = newStudent;
	}
	fclose(fp);

	printf("Ispis studenata:\n");

	Student* temp2 = temp;

	while (temp2 != NULL) {
		printf("%s %s %d\n", temp2->name, temp2->surname, temp2->age);
		temp2 = temp2->next;
	}

	return temp;
}

	

