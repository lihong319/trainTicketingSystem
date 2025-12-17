#include "header.h"

void main() {

	int choice = 0;

	while (1) {
		choice = mainMenu(choice);

		if (choice == 1) {
			staffMode();
		}
		else if (choice == 2) {
			memberMode();
		}
		else if (choice == 3) {
			scheduleMode();
		}
		else if (choice == -1) {
			printf("=========================================================================\n");
			printf("(^O^)\tThank you for your visit. Bye bye                           (^O^)\n");
			printf("(^O^)\tTerima kasih atas kunjungan anda. Selamat tinggal           (^O^)\n");
			printf("=========================================================================\n\n\n");

			exit(-1);
		}

		else {
			printf("=========================================================================\n");
			printf("(@_@)\tSorry, your choice is invalid                               (@_@)\n");
			printf("(@_@)\tMinta maaf, pilihan anda tidak sah                          (@_@)\n");
			printf("=========================================================================\n");

		}
	}
}

//main menu
int mainMenu(int choice) {
	printf("=========================================================================\n");

	printf("                                                              === === ===\n");
	printf("                                                           _  _|______| |_\n");
	printf("                                                  -------| |_|           |\n");
	printf("Welcome to TRAIN TICKETING SYSTEM                 ------   |           O |\n");
	printf("Selamat Datang ke SISTEM TIKET KERETA API         -----    |___________|\n");
	printf("                                                  ----     |  [] [] []  |\n");
	printf("                                                  ---      |____________|\n");
	printf("                                                  -        (__O__O__O__)\n");

	printf("=========================================================================\n\n");

	printf("1. Staff Mode\n");
	printf("2. Member Mode\n");
	printf("3. Train Schedule Information\n");
	printf("Please enter your choice (-1 to exit)\n\n");

	printf("1. Mod Kakitangan\n");
	printf("2. Mod Ahli\n");
	printf("3. Informasi Jadual Kereta Api\n");
	printf("Sila Masukkan Pilihan Anda (-1 untuk keluar)\n\n");

	printf(">");
	scanf("%d", &choice);
	rewind(stdin);


	return choice;





}