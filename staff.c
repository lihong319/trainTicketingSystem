#include "header.h"

//staff module
void staffMode() {
	//local declaration
	Staff s[MAX_STAFF];
	char tempId[5], tempPass[11];
	int i = 0, success = 0, choice = 0, staffCount = 0;

	//open file for reading and appending
	FILE* staffInfo;
	staffInfo = fopen("staff.dat", "ab+");
	if (staffInfo == NULL) {
		printf("File opening Error.\n");
		exit(-1);
	}
	system("cls");

	//pass parameter by using pointer
	staffLogin(tempId, tempPass);
	//if user typing wrong password over 4 times, automatically exit the program
	for (i = 0; i < 3; i++) {


		//read staff information from binary file
		while (fread(&s[staffCount], sizeof(Staff), 1, staffInfo) != 0) {
			staffCount++;

		}
		//verify staff ID and password
		for (staffCount = 0; staffCount < MAX_STAFF; staffCount++) {
			if (strcmp(s[staffCount].id, tempId) == 0 && strcmp(s[staffCount].password, tempPass) == 0) {
				success = 1;
				system("cls");
				//login successfully, display welcome message and menu
				printf("=========================================================================\n");
				printf("\tYou have login successfully\n");
				printf("\tAnda telah berjaya log masuk\n");
				printf("=========================================================================\n\n");


				while (1) {
					printf("Welcome / Selamat datang, %s\n", s[staffCount].name);
					printf("-------------------------------------------------------------------------------\n");
					printf("%-50s | %s\n", "Position / Kedudukan", (s[staffCount].position[0] == 'M') ? "Manager / Pengurus" : "Administrator / Pentadbir");
					printf("%-50s | %s\n", "Gender / Janita", (s[staffCount].gender == 'M') ? "Male / lelaki" : "Female / wanita");
					printf("%-50s | %s\n", "Email / E-mel", s[staffCount].email);
					printf("%-50s | %s\n", "Phone number / Nombor telefon", s[staffCount].tel);
					printf("%-50s | %d\n", "Age / Umur", s[staffCount].age);
					printf("%-50s | %d/%d/%d\n", "Date of birth / Tarikh lahir", s[staffCount].dob.day, s[staffCount].dob.month, s[staffCount].dob.year);
					printf("-------------------------------------------------------------------------------\n\n\n");

					//differentiate between manager and administrator
					if (strcmp(s[staffCount].position, "Manager") == 0) {
						printf("1. Staff Information Module\n");
						printf("2. Member Information Module\n");
						printf("3. Train Schedule Information Module\n");
						printf("4. Report Module\n");
						printf("5. Ticket Booking Information Module\n");
						printf("Please enter your choice (-1 to exit) \n\n");

						printf("1. Modul Maklumat Kakitangan\n");
						printf("2. Modul Maklumat Ahli\n");
						printf("3. Modul Maklumat Jadual Kereta Api\n");
						printf("4. Modul Laporan\n");
						printf("5. Modul Maklumat Tempahan Ticket\n");
						printf("Sila masukkan pilihan anda (1- untuk keluar) \n>");

						scanf("%d", &choice);
						rewind(stdin);

						if (choice == 1) {
							staffInfoMenu();
						}
						else if (choice == 2) {
							memberInfoMenu();
						}
						else if (choice == 3) {
							trainInfoMenu();
						}
						else if (choice == 4) {
							reportModule();
						}
						else if (choice == 5) {
							system("cls");
							bookingInfoMenu();
						}
						else if (choice == -1) {
							break;
						}
						else {
							printf("Sorry, your choice is invalid\n");
							printf("Minta maaf, pilihan anda tidak sah\n");
						}
					}
					else if (strcmp(s[staffCount].position, "Administrator") == 0) {

						printf("1. Member Information Module\n");
						printf("2. Train Schedule Information Module\n");
						printf("3. Booking Information Module\n");
						printf("Please enter your choice (-1 to exit) \n\n");


						printf("1. Modul Maklumat Ahli\n");
						printf("2. Modul Maklumat Jadual Kereta Api\n");
						printf("3. Modul Maklumat Tempahan Ticket\n");
						printf("Sila masukkan pilihan anda (-1 untuk keluar) \n>");

						scanf("%d", &choice);
						rewind(stdin);

						if (choice == 1) {
							memberInfoMenu();
						}
						else if (choice == 2) {
							trainInfoMenu();
						}
						else if (choice == 3) {
							bookingInfoMenu();
						}
						else if (choice == -1) {
							break;
						}
						else {
							printf("Sorry, your choice is invalid\n");
							printf("Minta maaf, pilihan anda tidak sah\n");
						}
					}
				}


			}
		}

		if (success) {
			fclose(staffInfo);
			break;
		}
		else {
			fclose(staffInfo);
			//display error message when user enter wrong staff ID and password
			printf("invalid ID or password\n");
			printf("ID dan kata laluan tidak sah\n");
		}

		staffLogin(tempId, tempPass);
	}
	if (i == 3) {
		//exit the program if user attempt exceed 4 times
		printf("Maximum login attempts reached. Exiting...\n");
		printf("Percubaan log masuk maksimum dicapai. Sedang keluarkan...\n");
		exit(-1);
	}





	system("cls");

}
void staffLogin(char* tempId, char* tempPass) {






	printf("=========================================================================\n");
	printf("\tWelcome to Staff Mode\n");
	printf("\tSelamat datang ke Mod Kakitangan\n");
	printf("=========================================================================\n\n");



	printf("Please enter your staff ID \n");
	printf("Sila masukkan ID kakitangan anda\n> ");
	scanf("%4s", tempId);
	rewind(stdin);

	printf("\nPlease enter your password \n");
	printf("Sila masukkan kata laluan anda \n>");
	scanf("%10s", tempPass);
	rewind(stdin);








}
void staffInfoMenu() {
	int choice;

	while (1) {
		system("cls");
		printf("=========================================================================\n");
		printf("\tWELCOME TO STAFF INFORMATION MODULE\n");
		printf("\tSELAMAT DATANG KE MODUL MAKLUMAT KAKITANGAN\n");
		printf("=========================================================================\n\n");

		printf("1. Search Staff Information\n");
		printf("2. View All Staff Information \n");
		printf("3. Edit Staff Information \n");
		printf("4. Add New Staff\n");
		printf("5. Delete Staff\n");
		printf("Please enter your choice (-1 to exit)\n\n");

		printf("1. Mencari Maklumat Kakitangan\n");
		printf("2. Memaparkan Semua Maklumat Kakitangan\n");
		printf("3. Mengubah Maklumat Kakitangan\n");
		printf("4. Menambah kakitangan Baharu\n");
		printf("5. Manghapuskan Kakitangan\n");
		printf("Sila masukkan pilihan anda (-1 untuk keluar)\n>");

		scanf("%d", &choice);
		rewind(stdin);


		if (choice == 1) {
			searchStaff();
		}
		else if (choice == 2) {
			displayStaff();
		}
		else if (choice == 3) {
			editStaff();
		}
		else if (choice == 4) {
			addStaff();
		}
		else if (choice == 5) {
			deleteStaff();
		}
		else if (choice == -1) {
			break;
		}
		else {
			printf("Sorry, your choice is invalid\n");
			printf("Minta maaf, pilihan anda tidak sah\n");
		}
	}
	system("cls");
}


void searchStaff() {
	//local declaration
	Staff s[MAX_STAFF];
	char staffId[5], confirm;
	int found = 0, staffCount = 0;

	//open binary file for reading
	FILE* staffInfo;
	staffInfo = fopen("staff.dat", "rb");
	if (staffInfo == NULL) {
		printf("staff.dat file is unable to open\n");
		exit(-1);
	}

	//read staff information from binary file
	while (fread(&s[staffCount], sizeof(Staff), 1, staffInfo) != 0) {

		staffCount++;
	}
	system("cls");
	printf("=========================================================================\n");
	printf("\tSEARCH STAFF\n");
	printf("\tPENCARIAN KAKITANGAN\n");
	printf("=========================================================================\n\n");

	do {
		while (1) {
			//prompt user to enter particular staff ID
			printf("Please enter Staff ID to search\n");
			printf("Sila masukkan ID Kakitangan yang kamu ingin cari \n >");
			scanf("%s", &staffId);
			rewind(stdin);


			//display output
			for (staffCount = 0; staffCount < MAX_STAFF; staffCount++) {
				if (strcmp(s[staffCount].id, staffId) == 0) {
					found = 1;
					printf("-------------------------------------------------------------------------------------------------\n");
					printf("%-50s | %s\n", "Name / Nama", s[staffCount].name);
					printf("%-50s | %s\n", "Position / Kedudukan", (s[staffCount].position[0] == 'M') ? "Manager / Pengurus" : "Administrator / Pentadbir");
					printf("%-50s | %s\n", "Gender / Janita", (s[staffCount].gender == 'M') ? "Male / lelaki" : "Female / wanita");
					printf("%-50s | %s\n", "Email / E-mel", s[staffCount].email);
					printf("%-50s | %s\n", "Phone number / Nombor telefon", s[staffCount].tel);
					printf("%-50s | %d\n", "Age / Umur", s[staffCount].age);
					printf("%-50s | %d/%d/%d\n", "Date of birth / Tarikh lahir", s[staffCount].dob.day, s[staffCount].dob.month, s[staffCount].dob.year);
					printf("-------------------------------------------------------------------------------------------------\n\n");
				}
			}
			if (!found) {
				//display error message when staff is not found
				printf("=========================================================================\n");
				printf("Staff ID provided does not exist\n");
				printf("ID Kakitangan yang diberikan tidak wujud\n");
				printf("=========================================================================\n\n");
			}
			else {
				break;

			}



		}
		while (1) {
			//asking user confirmation to continue search staff
			printf("Do you want to continue your searching? (Y = yes | N = No)\n");
			printf("Adakah anda mahu meneruskan pencarian anda? (Y = ya | N = Tidak)\n >  ");
			scanf("%c", &confirm);
			rewind(stdin);
			confirm = toupper(confirm);

			if (confirm != 'Y' && confirm != 'N') {
				printf("Confirmation invalid\n");
				printf("Pengesahan tidak sah\n\n");
			}
			else {
				break;
			}
		}
		printf("\n");
	} while (toupper(confirm) != 'N');

	fclose(staffInfo);

}
void displayStaff() {
	//local declaration
	Staff s;
	int staffCount = 0;

	//open binary file for reading
	FILE* staffInfo;
	staffInfo = fopen("staff.dat", "rb");
	if (staffInfo == NULL) {
		printf("staff.dat file is unable to open\n");
		exit(-1);
	}

	system("cls");

	//display output
	printf("=========================================================================\n");
	printf("\tSTAFF INFORMATION\n");
	printf("\tMAKLUMAT KAKITANGAN\n");
	printf("=========================================================================\n\n");

	printf("%-5s %-50s %-30s %-15s %-50s %-15s %-5s %s\n", "ID", "Name", "Position", "Gender", "Email", "Phone Number", "Age", "Date of Birth");
	printf("%-5s %-50s %-30s %-15s %-50s %-15s %-5s %s\n", "ID", "Nama", "Kedudukan", "Janita", "E-mel", "Nombor Telefon", "Umur", "Tarikh Lahir");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	while (fread(&s, sizeof(Staff), 1, staffInfo) != 0) {
		printf("%-5s %-50s %-30s %-15s %-50s %-15s %-5d %02d/%02d/%04d\n", s.id, s.name, (s.position[0] == 'M') ? "Manager / Pengurus" : "Administrator / Pentadbir", (s.gender == 'M') ? "Male / lelaki" : "Female / wanita", s.email, s.tel, s.age, s.dob.day, s.dob.month, s.dob.year);
		staffCount++;
	}
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("%d staff(s) listed\n", staffCount);
	fclose(staffInfo);
	system("pause");
}
void editStaff() {
	//local declaration
	Staff s[MAX_STAFF];
	int sCount = 0, found = 0, sAge, sDay, sMonth, sYear, dateTrue;
	char sID[5], sure = 'N', sName[51], sGender, sPosition[15], sTel[15], sEmail[51], confirm, sPassword[11];
	Date d;

	//open file for reading
	FILE* read;
	read = fopen("staff.dat", "rb");
	if (read == NULL) {
		printf("file opening error\n");
		exit(-1);
	}
	//read staff information from binary file
	while (fread(&s[sCount], sizeof(Staff), 1, read) != 0 && sCount < MAX_STAFF) {
		sCount++;
	}
	fclose(read);
	system("cls");
	printf("=========================================================================\n");
	printf("\tEDIT STAFF INFORMATION\n");
	printf("\tPENGUBAHAN MAKLUMAT KAKITANGAN\n");
	printf("=========================================================================\n\n");


	do {
		//enter staff ID to identify particular staff
		printf("Please enter Staff ID to modify \n");
		printf("Sila masukkan ID Kakitangan yang kamu ingin berubah \n>");
		scanf("%s", &sID);
		rewind(stdin);

		//find particular staff
		for (int i = 0; i < sCount;i++) {
			if (strcmp(sID, s[i].id) == 0) {
				found = 1;
				//display current staff information
				printf("Current Staff Information / Maklumat Kakitangan Semasa\n");
				printf("---------------------------------------------------------------------\n");
				printf("%-30s | %s\n", "ID", s[i].id);
				printf("%-30s | %s\n", "Password / Kata Laluan", s[i].password);
				printf("%-30s | %s\n", "Name / Nama", s[i].name);
				printf("%-30s | %s\n", "Gender / Janita", (s[i].gender == 'M') ? "Male / lelaki" : "Female / wanita");
				printf("%-30s | %s\n", "Position Kedudukan", (s[i].position[0] == 'M') ? "Manager / Pengurus" : "Administrator / Pentadbir");
				printf("%-30s | %s\n", "Email / E-mel", s[i].email);
				printf("%-30s | %s\n", "Phone number / Nomber telefon", s[i].tel);
				printf("%-30s | %d\n", "Age / Umur", s[i].age);
				printf("%-30s | %d/%d/%d\n\n", "Date of Birth / Tarikh Lahir", s[i].dob.day, s[i].dob.month, s[i].dob.year);

				//prompt user to enter new staff information to edit with validation checking
				do {
					printf("%-80s : ", "New Name / Nama Baharu");
					scanf("%[^\n]", &sName);
					rewind(stdin);

					if (strlen(sName) > 50) {
						printf("Staff name cannot exceed 50 characters\n");
						printf("Nama Kakitangan tidak boleh melebihi 50 watak\n\n");
					}
				} while (strlen(sName) > 50);

				do {
					printf("%-80s : ", "New Password / Kata Laluan Baharu");
					scanf("%s", &sPassword);
					rewind(stdin);

					if (strlen(sPassword) >= 11) {
						printf("Password cannot exceed 10 characters\n");
						printf("Kata Laluan tidak boleh melebihi 10 watak\n\n");
					}

				} while (strlen(sPassword) >= 11);

				do {
					printf("%-80s : ", "New Gender / Janita Baharu (M = Male / Lelaki | F = Female / Perempuan)");
					scanf("%c", &sGender);
					rewind(stdin);
					sGender = toupper(sGender);
					if (sGender != 'M' && sGender != 'F') {
						printf("Staff Gender can only be Male 'M' or Female 'F'\n");
						printf("Janita Kakitangan hanya boleh menjadi Lelaki 'M' atau Perempuan 'F'\n\n");
					}
				} while (sGender != 'M' && sGender != 'F');

				do {
					printf("%-80s : ", "New Position / Kedudukan Baharu (Administrator / Manager)");
					scanf("%s", &sPosition);
					rewind(stdin);

					if (strcmp(sPosition, "Manager") != 0 && strcmp(sPosition, "Administrator") != 0) {
						printf("Staff position can only be Manager or Administrator\n");
						printf("Kedudukan Kakitangan hanya boleh menjadi Pengurus atau Pentadbir\n\n");
					}
				} while (strcmp(sPosition, "Manager") != 0 && strcmp(sPosition, "Administrator") != 0);

				do {
					printf("%-80s : ", "New Email / E-mel Baharu");
					scanf("%s", &sEmail);
					rewind(stdin);

					if (strlen(sEmail) > 50) {
						printf("Email cannot exceed 50 characters\n");
						printf("E-mel tidak boleh melebihi 50 watak\n\n");
					}
					else if (!isValidEmail(sEmail)) {
						printf("Invalid email format. Please include the '@' character.\n");
						printf("Format e-mel tidak sah. Sila masukkan aksara '@'.\n");
					}
				} while (strlen(sEmail) > 50 || !isValidEmail(sEmail));

				do {
					printf("%-80s : ", "New Phone number / Nombor Telefon Baharu");
					scanf("%s", &sTel);
					rewind(stdin);
					if (strlen(sTel) > 14) {
						printf("Phone number cannot exceed 14 characters\n");
						printf("Nombor telefon tidak boleh melebihi 14 watak\n\n");
					}
				} while (strlen(sTel) > 14);

				do {
					printf("%-80s : ", "New Age / Umur Baharu");
					scanf("%d", &sAge);
					rewind(stdin);
					if (sAge < 18 || sAge >65) {
						printf("Staff age must between 18 and 65\n");
						printf("Umur Kakitangan mesti antara 18 dan 65\n\n");
					}
				} while (sAge < 18 || sAge >65);

				do {
					printf("%-80s : ", "New Date of Birth / Tarikh Lahir Baharu (DD/MM/YYYY)");
					scanf("%d/%d/%d", &d.day, &d.month, &d.year);
					rewind(stdin);
					dateTrue = isValidDate(d);

					if (!dateTrue) {
						printf("Date Invalid\n");
						printf("Tarikh tidak sah\n\n");
					}

				} while (!dateTrue);

				//asking user confirmation to edit this staff
				printf("Are you sure for editing this Staff information? (Y = yes)\n");
				printf("Adakah anda pasti menukar maklumat Kakitangan ini? (Y = Ya)\n>");
				scanf("%c", &sure);
				rewind(stdin);
				sure = toupper(sure);

				if (sure == 'Y') {
					//assign value into array structure
					strcpy(s[i].name, sName);
					strcpy(s[i].password, sPassword);
					s[i].gender = sGender;
					strcpy(s[i].position, sPosition);
					strcpy(s[i].email, sEmail);
					strcpy(s[i].tel, sTel);
					s[i].age = sAge;
					s[i].dob.day = d.day;
					s[i].dob.month = d.month;
					s[i].dob.year = d.year;

				}
			}
		}
		//display message when staff is not found
		if (!found) {
			printf("\n=========================================================================\n");
			printf("Staff ID given not found\n");
			printf("ID Kakitangan yang diberikan tidak ditemui\n");
			printf("=========================================================================\n\n");

		}
		//asking user confirmation for continue add this staff
		printf("Do you want to continue edit Staff Information? (Y = yes)\n");
		printf("Adakah anda ingin meneruskan mengedit maklumat kakitangan? (Y = Ya)\n>");
		scanf("%c", &confirm);
		rewind(stdin);
		confirm = toupper(confirm);
		printf("\n");
	} while (confirm == 'Y');



	if (sure == 'Y') {
		//write edited staff information into binary file
		FILE* write;
		write = fopen("staff.dat", "wb");
		if (write == NULL) {
			printf("file opening error\n");
			exit(-1);
		}
		for (int i = 0; i < sCount; i++) {
			fwrite(&s[i], sizeof(Staff), 1, write);
		}
		fclose(write);

	}

}
void addStaff() {
	//local declaration
	Staff s;
	char confirm, sure, a;
	int dateTrue = 0, repeatID = 0;

	//open binary file for appending
	FILE* staffInfo;
	staffInfo = fopen("staff.dat", "ab");
	if (staffInfo == NULL) {
		printf("file opening error\n");
		exit(-1);
	}

	system("cls");

	printf("=========================================================================\n");
	printf("\tADD STAFF\n");
	printf("\tKAKITANGAN PENAMBAHAN\n");
	printf("=========================================================================\n\n");

	do {
		//prompt user to enter new staff information with validation checking
		do {
			printf("%-80s : ", "Staff ID / ID Kakitangan");
			scanf("%s", &s.id);
			rewind(stdin);

			if (strlen(s.id) >= 5) {
				printf("\nStaff ID cannot exceed 4 characters\n");
				printf("ID Kakitangan tidak boleh melebihi 4 watak\n\n");
			}

			repeatID = isDuplicateStaffID(s.id);
			if (repeatID) {
				printf("\nThe staff ID already exist. Please enter a different staff ID\n");
				printf("ID kakitangan sudah wujud. Sila masukkan ID kakitangan yang berbeza\n\n");
			}
		} while (strlen(s.id) >= 5 || repeatID == 1);

		do {
			printf("%-80s : ", "Staff Password / Kata Laluan Kakitangan");
			scanf("%[^\n]", &s.password);
			rewind(stdin);

			if (strlen(s.password) >= 11) {
				printf("Password cannot exceed 10 characters\n");
				printf("Kata Laluan tidak boleh melebihi 10 watak\n\n");
			}

		} while (strlen(s.password) >= 11);

		do {
			printf("%-80s : ", "Staff Name / Name Kakitangan");
			scanf("%[^\n]", s.name);
			rewind(stdin);

			if (strlen(s.name) > 50) {
				printf("Staff name cannot exceed 50 characters\n");
				printf("Nama Kakitangan tidak boleh melebihi 50 watak\n\n");
			}
		} while (strlen(s.name) > 50);
		do {
			printf("%-80s : ", "Staff Position / Kedudukan Kakitangan (Administrator / Manager) ");
			scanf("%s", &s.position);
			rewind(stdin);

			if (strcmp(s.position, "Manager") != 0 && strcmp(s.position, "Administrator") != 0) {
				printf("Staff position can only be Manager or Administrator\n");
				printf("Kedudukan Kakitangan hanya boleh menjadi Pengurus atau Pentadbir\n\n");
			}
		} while (strcmp(s.position, "Manager") != 0 && strcmp(s.position, "Administrator") != 0);

		do {
			printf("%-80s : ", "Staff Gender / Janita Kakitangan (M = Male / Lelaki) | (F = Female / Perempuan)");
			scanf("%c", &s.gender);
			rewind(stdin);
			s.gender = toupper(s.gender);
			if (s.gender != 'M' && s.gender != 'F') {
				printf("Staff Gender can only be Male 'M' or Female 'F'\n");
				printf("Janita Kakitangan hanya boleh menjadi Lelaki 'M' atau Perempuan 'F'\n\n");
			}
		} while (s.gender != 'M' && s.gender != 'F');

		do {
			printf("%-80s : ", "Staff Email / E-mel Kakitangan");
			scanf("%[^\n]", &s.email);
			rewind(stdin);

			if (strlen(s.email) > 50) {
				printf("Email cannot exceed 50 characters\n");
				printf("E-mel tidak boleh melebihi 50 watak\n\n");
			}
			else if (!isValidEmail(s.email)) {
				printf("Invalid email format. Please include the '@' character.\n");
				printf("Format e-mel tidak sah. Sila masukkan aksara '@'.\n");
			}
		} while (strlen(s.email) > 50 || !isValidEmail(s.email));

		do {
			printf("%-80s : ", "Staff Phone number / Nomber Telefon Kakitangan");
			scanf("%[^\n]", &s.tel);
			rewind(stdin);
			if (strlen(s.tel) > 14) {
				printf("Phone number cannot exceed 14 characters\n");
				printf("Nombor telefon tidak boleh melebihi 14 watak\n\n");
			}
		} while (strlen(s.tel) > 14);

		do {
			printf("%-80s : ", "Staff Age / Umur Kakitangan");
			scanf("%d", &s.age);
			rewind(stdin);

			if (s.age < 18 || s.age >65) {
				printf("Staff age must between 18 and 65\n");
				printf("Umur Kakitangan mesti antara 18 dan 65\n\n");
			}
		} while (s.age < 18 || s.age >65);

		do {
			printf("%-80s : ", "Staff Date of Birth / Tarikh Lahir Kakitangan (DD/MM/YYYY)");
			scanf("%d/%d/%d", &s.dob.day, &s.dob.month, &s.dob.year);
			rewind(stdin);

			dateTrue = isValidDate(s.dob);

			if (!dateTrue) {
				printf("Date Invalid\n");
				printf("Tarikh tidak sah\n\n");
			}

		} while (!dateTrue);

		//asking user confirmation about appending this new staff information into binary file
		printf("\n\nAre you sure Adding this Staff? (Y = yes)\n");
		printf("Adakah kamu pastikan menambah kakitangan ini? (Y = yes)\n>");
		scanf("%c", &sure);
		rewind(stdin);
		sure = toupper(sure);

		if (sure == 'Y') {
			//append staff information into binary file
			fwrite(&s, sizeof(Staff), 1, staffInfo);
			printf("=========================================================================\n");
			printf("\tStaff Adding successfully\n");
			printf("\tPenambahan Kakitangan Berjaya\n");
			printf("=========================================================================\n");

		}

		//asking user confirmation about continue add staff
		printf("\n\nDo you want to continue add Staff? (Y = yes)\n");
		printf("Adakah kamu ingin meneruskan menambah Kakitangan Baharu? (Y = yes)\n>");
		scanf("%c", &confirm);
		rewind(stdin);
		confirm = toupper(confirm);

	} while (confirm == 'Y');

	fclose(staffInfo);

}
void deleteStaff() {
	//local declaration
	Staff s[MAX_STAFF];
	int sCount = 0, sure = 'N';
	char sID[5], found = 0;

	//open staff file for binary
	FILE* read;
	read = fopen("staff.dat", "rb");
	if (read == NULL) {
		printf("file opening error\n");
		exit(-1);
	}

	// read staff information from binary file
	while (fread(&s[sCount], sizeof(Staff), 1, read) != 0 && sCount < MAX_STAFF) {
		sCount++;
	}
	fclose(read);

	system("cls");
	printf("=========================================================================\n");
	printf("\tDELETE STAFF INFORMATION\n");
	printf("\tPEMADAMAN MAKLUMAT KAKITANGAN\n");
	printf("=========================================================================\n\n");

	printf("Enter Staff ID to delete\n");
	printf("Sila masukkan ID kakitangan yang kamu ingin padamkan\n>");
	scanf("%s", &sID);
	rewind(stdin);

	for (int i = 0; i < sCount; i++) {
		if (strcmp(sID, s[i].id) == 0) {
			found = 1;
			printf("Staff Information / Maklumat Kakitangan \n");
			printf("---------------------------------------------------------------------\n");
			printf("%-30s | %s\n", "ID", s[i].id);
			printf("%-30s | %s\n", "Password / Kata Laluan", s[i].password);
			printf("%-30s | %s\n", "Name / Nama", s[i].name);
			printf("%-30s | %s\n", "Gender / Janita", (s[i].gender == 'M') ? "Male / lelaki" : "Female / wanita");
			printf("%-30s | %s\n", "Position Kedudukan", (s[i].position[0] == 'M') ? "Manager / Pengurus" : "Administrator / Pentadbir");
			printf("%-30s | %s\n", "Email / E-mel", s[i].email);
			printf("%-30s | %s\n", "Phone number / Nomber telefon", s[i].tel);
			printf("%-30s | %d\n", "Age / Umur", s[i].age);
			printf("%-30s | %d/%d/%d\n\n", "Date of Birth / Tarikh Lahir", s[i].dob.day, s[i].dob.month, s[i].dob.year);

			printf("Are you sure for delete this Staff information? (Y = yes)\n");
			printf("Adakah anda pasti memadamkan maklumat Kakitangan ini? (Y = Ya)\n>");
			scanf("%c", &sure);
			rewind(stdin);
			sure = toupper(sure);

			if (sure == 'Y') {
				//delete staff information by using shifting
				for (int j = i; j < sCount - 1; j++) {
					s[j] = s[j + 1];
				}
				sCount--;
				printf("\n=========================================================================\n");
				printf("Staff information deleted successfully\n ");
				printf("Maklumat kakitangan telah berjaya dipadamkan\n");
				printf("=========================================================================\n");

				break;
			}
			else {
				printf("\n=========================================================================\n");
				printf("\tStaff information deletion canelled\n");
				printf("\tPemadaman maklumat kakitangan telah dibatalkan\n");
				printf("=========================================================================\n");

			}
		}
	}



	if (!found) {
		printf("The Staff ID %s is not found\n", sID);
		printf("ID Kakitangan yang kamu masukkan %s tidak ditemui\n", sID);

	}
	if (sure == 'Y') {
		//write staff information into binary file
		FILE* write;
		write = fopen("staff.dat", "wb");
		if (write == NULL) {
			printf("file opening error\n");
			exit(-1);
		}
		fwrite(&s, sizeof(Staff), sCount, write);


		fclose(write);
	}
	system("pause");
}