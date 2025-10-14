#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct {
	char ime[15];
	char prezime[15];
	float broj_bodova;
}academic;

int main() {
	int i = 0;
	char red[100];
	int broj_redaka=0;	

	academic *student = NULL;

	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, "vjezba1.txt", "r");
	if (err) {
		printf("Pogreska pri otvaranju datoteke.\n");
		return 1;
	}
	
	while (fgets(red, sizeof(red), fp) != NULL) {
		broj_redaka++;
	}
	rewind(fp);

	student = (academic*)malloc(broj_redaka * sizeof(academic));



	if (student != NULL) {
		for (i = 0; i < broj_redaka; ++i) {
			fscanf_s(fp, "%s", &student[i].ime, sizeof(char) * 15);
			fscanf_s(fp, "%s", &student[i].prezime, sizeof(char) * 15);
			fscanf_s(fp, "%f", &student[i].broj_bodova);
		}
	}

	printf("Broj studenata: %d", broj_redaka);

	int max_br_bodova;
	printf("\n Unesite maksimalan broj bodova:");
	scanf_s("%d", &max_br_bodova);

	printf("Ispis studenata i ostvarenih bodova: \n");
	for (i = 0; i < broj_redaka; ++i) {
		float relativni_bodovi = student[i].broj_bodova / max_br_bodova * 100;
		printf("%s  %s ", student[i].ime, student[i].prezime);
		printf(" apsolutni broj bodova %.2f, ", student[i].broj_bodova);
		printf(" relativni broj bodova %.2f\n",relativni_bodovi);
	}
	
	free(student);
	fclose(fp);

return 0;
}