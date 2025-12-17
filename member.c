#include "header.h"

void memberMode() {
	char loggedInUsername[50];

	int choice;


	system("cls");


	do {
		printf("=========================================================================\n");
		printf("Welcome to Member Mode\n");
		printf("Selamat datang ke Mod Ahli\n");
		printf("=========================================================================\n\n");
		printf("1. Sign In\n");
		printf("2. Log In\n");
		printf("3. Exit\n");
		printf("Enter your choice \n\n");

		printf("1. Daftar Masuk\n");
		printf("2. Log Masuk\n");
		printf("3. Keluar\n");
		printf("Sila masukkan pilihan anda\n>");
		scanf("%d", &choice);
		rewind(stdin);

		switch (choice) {
		case 1:
			registerMember();  // Register new member

			break;
		case 2:
			strcpy(loggedInUsername, loginMember());

			if (strcmp(loggedInUsername, "null") != 0) {
				memberMenu(loggedInUsername);
			}
			break;
		case 3:

			break;
		default:
			printf("=========================================================================\n");
			printf("Invalid choice. Please try again.\n");
			printf("Pilihan tidak sah. Sila cuba lagi.\n");
			printf("=========================================================================\n\n");
		}
	} while (choice != 3);
}
void registerMember() {
	FILE* file = fopen("members.dat", "ab");
	if (file == NULL) {
		perror("Error opening file for appending");
		return;
	}
	MemberInfo member;

	do {
		printf("Enter username\n");
		printf("Masukkan nama pengguna\n>");
		scanf("%[^\n]s", &member.username);
		rewind(stdin);

		if (duplicateUsername(member.username)) {
			printf("Username already exist, please use another username\n");
			printf("Nama pengguna telah wujud, Sila menggunakan nama pengguna yang lain\n");
		}
	} while (duplicateUsername(member.username));

	printf("Enter password\n");
	printf("Masukkan Kata Laluan\n>");
	scanf("%[^\n]s", &member.password);
	rewind(stdin);

	printf("Enter contact number\n");
	printf("Masukkan Nombor telefon\n>");
	scanf("%19s", &member.contact_number);
	rewind(stdin);

	printf("Enter your gender (M = Male / F = Female)\n");
	printf("Masukkan Janita anda (M = Lelaki / F = Perempuan)\n>");
	scanf("%c", &member.gender);
	rewind(stdin);
	member.gender = toupper(member.gender);

	printf("Enter email\n");
	printf("Masukkan E-mel\n>");
	scanf("%99s", &member.email);
	rewind(stdin);

	printf("Enter IC number\n");
	printf("Masukkan Nombor IC\n>");
	scanf("%14s", &member.ic);
	rewind(stdin);

	fwrite(&member, sizeof(MemberInfo), 1, file);

	printf("Sign up successfully\n");
	printf("Daftar Masuk berjaya\n");

	fclose(file);
	system("pause");
	system("cls");
}
char* loginMember() {
	char username[50];
	char password[50];
	static char loggedInUsername[50];
	MemberInfo member;
	int found = 0;

	system("cls");
	printf("====================================================================\n");
	printf("Log In\n");
	printf("Log Masuk\n");
	printf("====================================================================\n\n");

	printf("Enter username\n");
	printf("Masukkan Nama Pengguna\n>");
	scanf(" %[^\n]", username);

	printf("Enter password\n");
	printf("Masukkan Kata Laluan\n>");
	scanf(" %49s", password);

	FILE* file = fopen("members.dat", "rb");
	if (file == NULL) {
		perror("Error opening file");
		exit(-1);
	}

	while (fread(&member, sizeof(MemberInfo), 1, file) != 0) {
		if (strcmp(member.username, username) == 0 && strcmp(member.password, password) == 0) {
			found = 1;

			strcpy(loggedInUsername, username);
			break;
		}
	}

	fclose(file);

	if (!found) {
		printf("=========================================================================\n");
		printf("Invalid username or password.\n");
		printf("Nama pengguna atau kata laluan tidak sah.\n");
		printf("=========================================================================\n\n");

		strcpy(loggedInUsername, "null");
	}
	return loggedInUsername;
}
void memberMenu(char loggedInUsername[50]) {
	int choice, exit;
	system("cls");

	do {
		printf("=========================================================================\n");
		printf("Member Menu\n");
		printf("Menu Ahli\n");
		printf("=========================================================================\n\n");
		printf("1. Member profile\n");
		printf("2. Booking Module\n");
		printf("3. Train Schedule Mode\n");
		printf("4. Exit\n");
		printf("Enter your choice\n\n");

		printf("1. Profil Ahli\n");
		printf("2. Modul Tempahan\n");
		printf("3. Mod Kereta Api\n");
		printf("4. Keluar\n");
		printf("Masukkan pilihan anda\n>");

		scanf(" %d", &choice);

		switch (choice) {
		case 1:
			exit = memberProfile(loggedInUsername);
			if (exit) {
				return;
			}
			break;
		case 2:
			bookingMode(loggedInUsername);
			break;
		case 3:
			scheduleMode();
			break;
		case 4:
			break;
			// Return to the main menu
		default:
			printf("=========================================================================\n");
			printf("Invalid choice. Please try again.\n");
			printf("Pilihan tidak sah. Sila cuba lagi.\n");
			printf("=========================================================================\n\n");
		}
	} while (choice != 4);
}
int memberProfile(char loggedInUsername[50]) {
	int choice;
	system("cls");
	
	do {
		printf("=========================================================================\n");
		printf("Member Profile\n");
		printf("Profil Ahli\n");
		printf("=========================================================================\n\n");

		printf("1. Display Own Profile\n");
		printf("2. Edit Own Profile\n");
		printf("3. Delete Account\n");
		printf("4. Exit\n");
		printf("Enter your choice\n\n");

		printf("1. Memaparkan Profil Sendiri\n");
		printf("2. Menyuntingkan Profil Sendiri\n");
		printf("3. Memadamkan Account Sendiri\n");
		printf("4. Keluar\n");
		printf("Masukkan pilihan anda\n>");

		scanf(" %d", &choice);
		switch (choice) {
		case 1:
			displayMember(loggedInUsername);
			break;
		case 2:
			editMemberInfo(loggedInUsername);
			break;
		case 3:
			deleteMember(loggedInUsername);
			return 1;
		case 4:
			break;
		default:
			printf("=========================================================================\n");
			printf("Invalid choice. Please try again.\n");
			printf("Pilihan tidak sah. Sila cuba lagi.\n");
			printf("=========================================================================\n\n");
		}
	} while (choice != 4);

}
void displayMember(char loggedInUsername[50]) {
	MemberInfo m;

	// Open binary file for reading
	FILE* memberInfo = fopen("members.dat", "rb");
	if (memberInfo == NULL) {
		printf("members.dat file is unable to open\n");
		exit(-1);
	}

	system("cls");  // Clear the console window

	// Display header
	printf("====================================================================\n");
	printf("\tPROFILE\n");
	printf("\tPROFIL\n");
	printf("====================================================================\n\n");

	printf("%-50s %-20s %-50s %-15s %-20s\n", "Username", "Contact Number", "Email", "IC Number", "Gender");
	printf("%-50s %-20s %-50s %-15s %-20s\n", "Nama Pengguna", "Nombor Telefon", "E-mel", "Nombor IC", "Janita");
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	int found = 0;
	while (fread(&m, sizeof(MemberInfo), 1, memberInfo) != 0) {
		if (strcmp(m.username, loggedInUsername) == 0) {
			printf("%-50s %-20s %-50s %-15s %-20s\n",
				m.username,
				m.contact_number,
				m.email,
				m.ic,
				(m.gender == 'M') ? "Male / Lelaki" : "Female / Perempuan");
			found = 1;
			break;  // Since the user is found, no need to continue reading
		}
	}

	if (!found) {
		printf("No member information found for username: %s\n", loggedInUsername);
	}

	printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	fclose(memberInfo);
	system("pause");  // Wait for user input before closing or clearing the console
	system("cls");
}
void editMemberInfo(char username[50]) {
	MemberInfo m;
	int found = 0;
	FILE* file = fopen("members.dat", "rb+");
	if (file == NULL) {
		perror("Unable to open file");
		return;
	}
	system("cls");
	while (fread(&m, sizeof(MemberInfo), 1, file) == 1) {
		if (strcmp(m.username, username) == 0) {
			found = 1;
			break;
		}
	}

	if (!found) {
		printf("Member not found.\n");
		fclose(file);
		return;
	}

	// Clear buffer here to prevent fgets issues
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {} // Clear buffer

	char input[1024]; // Buffer to handle larger inputs
	printf("====================================================================\n");
	printf("Editing information for %s\n", username);
	printf("Menyunting maklumat ahli %s\n", username);
	printf("====================================================================\n\n");

	printf("Enter new password (press enter to skip)\n");
	printf("Masukkan kata laluan baharu (tekan enter untuk melangkau)\n>");
	fgets(input, sizeof(input), stdin);
	if (strcmp(input, "\n") != 0) {
		input[strcspn(input, "\n")] = 0; // Remove newline character
		strcpy(m.password, input);
	}

	printf("Enter new contact number (press enter to skip)\n");
	printf("Masukkan Nombor Telefon baharu (tekan enter untuk melangkau)\n>");
	fgets(input, sizeof(input), stdin);
	if (strcmp(input, "\n") != 0) {
		input[strcspn(input, "\n")] = 0; // Remove newline character
		strcpy(m.contact_number, input);
	}

	printf("Enter new email (press enter to skip)\n");
	printf("Masukkan E-mel baharu (tekan enter untuk melangkau)\n> ");
	fgets(input, sizeof(input), stdin);
	if (strcmp(input, "\n") != 0) {
		input[strcspn(input, "\n")] = 0; // Remove newline character
		strcpy(m.email, input);
	}

	printf("Enter new IC number (press enter to skip)\n");
	printf("Masukkan IC baharu (tekan enter untuk melangkau)\n>");
	fgets(input, sizeof(input), stdin);
	if (strcmp(input, "\n") != 0) {
		input[strcspn(input, "\n")] = 0; // Remove newline character
		strcpy(m.ic, input);
	}

	fseek(file, -((long)sizeof(MemberInfo)), SEEK_CUR);
	fwrite(&m, sizeof(MemberInfo), 1, file);

	printf("Member information updated successfully.\n");
	printf("Maklumat ahli telah berjaya dikemas kini\n");
	system("pause");
	system("cls");

	fclose(file);
}
void deleteMember(char loggedInUsername[50]) {
	MemberInfo members[MAX_MEMBERS];
	int memberCount = 0;
	int found = 0;
	char sure;

	// Open the members file for binary reading
	FILE* read = fopen("members.dat", "rb");
	if (read == NULL) {
		printf("File opening error\n");
		exit(-1);
	}
	printf("Are you sure you want to delete your account? (Y/N)\n");
	printf("Adakah anda pasti mahu memadamkan akaun anda? (Y/N)\n>");
	scanf(" %c", &sure);

	if (toupper(sure) == 'Y') {
		// Read member information from binary file
		while (fread(&members[memberCount], sizeof(MemberInfo), 1, read) != 0 && memberCount < MAX_MEMBERS) {
			memberCount++;
		}
		fclose(read);

		for (int i = 0; i < memberCount; i++) {
			if (strcmp(loggedInUsername, members[i].username) == 0) {
				found = 1;
				// Delete member information by shifting
				for (int j = i; j < memberCount - 1; j++) {
					members[j] = members[j + 1];
				}
				memberCount--;
				printf("Your account has been successfully deleted.\n");
				printf("Akaun anda telah berjaya dipadamkan\n");

				// Write updated member information into binary file
				FILE* write = fopen("members.dat", "wb");
				if (write == NULL) {
					printf("File opening error\n");
					exit(-1);
				}
				fwrite(members, sizeof(MemberInfo), memberCount, write);
				fclose(write);
				break;
			}
		}
		if (!found) {
			printf("Your member record was not found.\n");

		}
	}
	else {
		printf("Account deletion has been cancelled\n");
		printf("Padaman akaun telah dibatalkan\n");
	}



}


void displayMembers() {
	// Local declaration
	MemberInfo m;
	int memberCount = 0;

	// Open binary file for reading
	FILE* memberInfo;
	memberInfo = fopen("members.dat", "rb");
	if (memberInfo == NULL) {
		printf("members.dat file is unable to open\n");
		exit(-1);
	}

	system("cls");

	// Display output
	printf("====================================================================\n");
	printf("\tDISPLAY ALL MEMBER INFORMATION\n");
	printf("\tMEMAPARKAN SEMUA MAKLUMAT AHLI\n");
	printf("====================================================================\n\n");

	printf("%-50s %-20s %-20s %-50s %-15s %-10s\n", "Username", "Password", "Contact Number", "Email", "IC Number", "Gender");
	printf("%-50s %-20s %-20s %-50s %-15s %-10s\n", "Nama Pengguna", "Kata Laluan", "Nombor Telefon", "Email", "IC Number", "Gender");

	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	while (fread(&m, sizeof(MemberInfo), 1, memberInfo) != 0) {
		printf("%-50s %-20s %-20s %-50s %-15s %-10s\n",
			m.username,
			"*****", // Replace password display with masked characters for security
			m.contact_number,
			m.email,
			m.ic,
			(m.gender == 'M') ? "Male" : "Female");
	}
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	fclose(memberInfo);
	system("pause");
	system("cls");
}


//staff access member information
void memberInfoMenu() {
	int choice;
	system("cls");
	while (1) {
		printf("=========================================================================\n");
		printf("\tMEMBER INFORMATION MODULE\n");
		printf("\tMODUL MAKUMAT AHLI\n");
		printf("=========================================================================\n\n");

		printf("1. Search Member Information\n");
		printf("2. View All Member Information\n");
		printf("3. Edit Member Information\n");
		printf("4. Add Member Information\n");
		printf("5. Delete Member Information\n");
		printf("Please enter your choice (-1 to exit)\n\n");

		printf("1. Mencari Maklumat Ahli\n");
		printf("2. Memaparkan Semua Maklumat Ahli\n");
		printf("3. Mengubah Maklumat Ahli\n");
		printf("4. Menambah Maklumat Ahli\n");
		printf("5. Memadamkan Maklumat Ahli\n");
		printf("Sila masukkan pilihan anda (-1 untuk keluar)\n>");
		scanf("%d", &choice);
		rewind(stdin);

		if (choice == 1) {
			searchMemberStaff();
		}
		else if (choice == 2) {
			displayMembers();
		}
		else if (choice == 3) {
			editMemberStaff();
		}
		else if (choice == 4) {
			MemberInfo member = addMemberStaff();
			saveMemberToFile(&member);
		}
		else if (choice == 5) {
			deleteMemberStaff();
		}
		else if (choice == -1) {
			system("cls");
			break;
		}
		else {
			printf("=========================================================================\n");
			printf("Choice Invalid\n");
			printf("Pilihan tidak sah\n");
			printf("=========================================================================\n");
		}
	}
}
void saveMemberToFile(const MemberInfo* member) {
	FILE* file = fopen("members.dat", "ab");
	if (file == NULL) {
		perror("Error opening file for appending");
		return;
	}

	printf("Writing this data to file / Sedangkan menyimpan maklumat ahli ke dalam fail:\n");
	printf("Username / Nama ahli: %s\n", member->username);
	printf("Password / kata laluan: %s\n", member->password);
	printf("Contact Number / Nombor Telefon: %s\n", member->contact_number);
	printf("Email / E-mel: %s\n", member->email);
	printf("IC Number / Nombor IC: %s\n", member->ic);
	printf("Gender / Janita: %s\n", (member->gender == 'M') ? "Male" : "Female");

	if (fwrite(member, sizeof(MemberInfo), 1, file) != 1) {
		perror("Failed to write member data\n Gagal menyimpan maklumat ahli\n");
	}
	else {
		printf("Successfully saved member data.\n");
		printf("Berjaya menyimpan maklumat ahli.\n");
	}

	fclose(file);
	system("pause");
	system("cls");
}
MemberInfo addMemberStaff() {
	MemberInfo member;
	system("cls");
	printf("=========================================================================\n");
	printf("\tADD NEW MEMBER\n");
	printf("\tMENAMBAH AHLI BAHARU\n");
	printf("=========================================================================\n\n");

	printf("Enter username\n");
	printf("Masukkan nama ahli\n>");
	scanf("%[^\n]s", member.username);  // Ensures input does not exceed buffer size
	rewind(stdin);

	printf("Enter password\n");
	printf("Masukkan kata laluan\n>");
	scanf("%49s", member.password);
	rewind(stdin);

	printf("Enter contact number\n");
	printf("Masukkan Nombor Telefon\n>");
	scanf("%19s", member.contact_number);
	rewind(stdin);

	printf("Enter email\n");
	printf("Masukkan E-mel\n>");
	scanf("%99s", member.email);
	rewind(stdin);

	printf("Enter IC number\n");
	printf("Masukkan Nombor IC\n>");
	scanf("%14s", member.ic);
	rewind(stdin);

	printf("Enter gender (M = Male / F = Female)\n");
	printf("Masukkan Janita (M = Lelaki / F = perempuan)\n>");
	scanf("%c", &member.gender);
	member.gender = toupper(member.gender);
	rewind(stdin);

	while (getchar() != '\n');

	return member;
}
void editMemberStaff() {
	MemberInfo members[MAX_MEMBERS];
	int memberCount = 0, found = 0;
	char memberUsername[51], confirm, newEmail[101], newContact[21], newPassword[51], newGender;
	int changesMade = 0;

	FILE* read = fopen("members.dat", "rb");
	if (read == NULL) {
		printf("File opening error\n");
		exit(-1);
	}

	while (fread(&members[memberCount], sizeof(MemberInfo), 1, read) != 0 && memberCount < MAX_MEMBERS) {
		memberCount++;
	}
	fclose(read);

	system("cls");

	printf("=========================================================================\n");
	printf("\tEDIT MEMBER INFORMATION\n");
	printf("\tMENGEDIT MAKLUMAT AHLI\n");
	printf("=========================================================================\n\n");

	do {
		found = 0;
		printf("Please enter Member Username to modify\n");
		printf("Sila masukkan nama ahli untuk mengubah suai\n>");
		scanf(" %[^\n]", memberUsername);
		rewind(stdin); // Clear the input buffer

		for (int i = 0; i < memberCount; i++) {
			if (strcmp(memberUsername, members[i].username) == 0) {
				found = 1;

				printf("Current Member Information / Maklumat ahli semasa:\n");
				printf("---------------------------------------------------------------------\n");
				printf("%-40s | %s\n", "Username / Nama Ahli", members[i].username);
				printf("%-40s | %s\n", "Contact Number / Nombor Telefon", members[i].contact_number);
				printf("%-40s | %s\n", "Email / E-mel", members[i].email);
				printf("%-40s | %s\n", "IC Number / Nombor IC", members[i].ic);
				printf("%-40s | %s\n\n", "Gender / Janita", (members[i].gender == 'M') ? "Male / Lelaki" : "Female / Perempuan");

				printf("%-60s \n", "New Password (Press enter to skip)");
				printf("%-60s \n>", "Kata Laluan Baharu (Tekan enter untuk melangkau)");
				fgets(newPassword, sizeof(newPassword), stdin);
				newPassword[strcspn(newPassword, "\n")] = 0;

				printf("%-60s \n", "New Contact Number (Press enter to skip)");
				printf("%-60s \n>", "Nombor Telefon Baharu (Tekan enter untuk melangkau)");
				fgets(newContact, sizeof(newContact), stdin);
				newContact[strcspn(newContact, "\n")] = 0;

				printf("%-60s \n", "New Email (Press enter to skip");
				printf("%-60s \n>", "E-mel baharu (Tekan enter untuk melangkau)");
				fgets(newEmail, sizeof(newEmail), stdin);
				newEmail[strcspn(newEmail, "\n")] = 0;


				printf("%-60s \n", "New Gender");
				printf("%-60s \n>", "Janita baharu");
				scanf(" %c", &newGender);


				printf("Are you sure you want to edit this Member information? (Y/N)\n");
				printf("Adakah anda pasti mahu mengedit maklumat ahli ini? (Y/N)\n>");
				scanf(" %c", &confirm);
				rewind(stdin);
				confirm = toupper(confirm);

				if (confirm == 'Y') {
					if (strlen(newPassword) > 0) {
						strcpy(members[i].password, newPassword);
						changesMade = 1;
					}
					if (strlen(newContact) > 0) {
						strcpy(members[i].contact_number, newContact);
						changesMade = 1;
					}
					if (strlen(newEmail) > 0) {
						strcpy(members[i].email, newEmail);
						changesMade = 1;
					}
					if (newGender != '\n') {
						// If the user entered a new gender, update it
						members[i].gender = newGender;
						changesMade = 1;
					}
				}
				break;
			}
		}

		if (!found) {
			printf("=========================================================================\n");
			printf("Member Username '%s' not found.\n", memberUsername);
			printf("Nama ahli '%s' tidak ditemui.\n", memberUsername);
			printf("=========================================================================\n\n");


		}

		printf("Do you want to continue editing Member Information? (Y/N)\n");
		printf("Adakah anda ingin terus menyunting maklumat ahli? (Y/N)\n>");
		scanf(" %c", &confirm);
		rewind(stdin);
		confirm = toupper(confirm);
		printf("\n");

	} while (confirm == 'Y');

	if (changesMade) {
		FILE* write = fopen("members.dat", "wb");
		if (write == NULL) {
			printf("File opening error\n");
			exit(-1);
		}
		for (int i = 0; i < memberCount; i++) {
			fwrite(&members[i], sizeof(MemberInfo), 1, write);
		}
		fclose(write);
		printf("=========================================================================\n");
		printf("Member information updated successfully.\n");
		printf("Maklumat ahli berjaya dikemas kini\n");
		printf("=========================================================================\n\n");
		system("pause");
		system("cls");
	}
}
void deleteMemberStaff() {
	MemberInfo members[MAX_MEMBERS];
	int memberCount = 0;
	char sure = 'N';
	char usernameToDelete[50];
	int found = 0;

	FILE* read = fopen("members.dat", "rb");
	if (!read) {
		printf("File opening error\n");
		exit(-1);
	}

	while (fread(&members[memberCount], sizeof(MemberInfo), 1, read) && memberCount < MAX_MEMBERS) {
		memberCount++;
	}
	fclose(read);
	system("cls");
	printf("=========================================================================\n");
	printf("\tDELETE MEMBER\n");
	printf("\tMEMADAMKAN AHLI\n");
	printf("=========================================================================\n\n");

	printf("Enter Member Username to delete\n");
	printf("Masukkan Nama Ahli untuk memadamkan\n>");
	scanf(" %49s", usernameToDelete);

	for (int i = 0; i < memberCount; i++) {
		if (strcmp(usernameToDelete, members[i].username) == 0) {
			found = 1;
			printf("Are you sure you want to delete this member? (Y/N)\n");
			printf("Adakah anda pasti mahu memadamkan ahli in? (Y/N)\n>");
			scanf(" %c", &sure);
			if (toupper(sure) == 'Y') {
				for (int j = i; j < memberCount - 1; j++) {
					members[j] = members[j + 1];
				}
				memberCount--;
				FILE* write = fopen("members.dat", "wb");
				for (int k = 0; k < memberCount; k++) {
					fwrite(&members[k], sizeof(MemberInfo), 1, write);
				}
				fclose(write);
				printf("=========================================================================\n");
				printf("Member deleted successfully\n");
				printf("Ahli mamadam berjaya\n");
				printf("=========================================================================\n\n");
				break;
			}
			else {
				printf("=========================================================================\n");
				printf("Deletion cancelled\n");
				printf("Pemadaman dibatalkan\n");
				printf("=========================================================================\n\n");
				break;
			}
		}
	}

	if (!found) {
		printf("=========================================================================\n");
		printf("Member not found\n");
		printf("Ahli tidak ditemui\n");
		printf("=========================================================================\n\n");
	}
	system("pause");
	system("cls");
}
void searchMemberStaff() {
	MemberInfo s[MAX_MEMBERS];
	char username[50], confirm;
	int found = 0, memberCount = 0;

	FILE* memberInfo = fopen("members.dat", "rb");
	if (memberInfo == NULL) {
		printf("Unable to open members.dat file\n");
		exit(-1);
	}

	while (fread(&s[memberCount], sizeof(MemberInfo), 1, memberInfo) && memberCount < MAX_MEMBERS) {
		memberCount++;
	}
	fclose(memberInfo);

	system("cls");  // Consider using a portable clear screen method

	printf("=========================================================================\n");
	printf("\tSEARCH MEMBER\n");
	printf("\tAHLI CARIAN\n");
	printf("=========================================================================\n\n");

	do {
		printf("Enter the member's username to search\n");
		printf("Masukkan nama Ahli untuk mencari\n>");
		scanf("%49s", username);

		for (int i = 0; i < memberCount; i++) {
			if (strcmp(s[i].username, username) == 0) {
				found = 1;
				printf("-------------------------------------------------------------------------------------------------\n");
				printf("%-60s | %s\n", "Username / Nama Ahli", s[i].username);
				printf("%-60s | %s\n", "Contact Number / Nombor Telefon", s[i].contact_number);
				printf("%-60s | %s\n", "Email / E-mel", s[i].email);
				printf("%-60s | %s\n", "IC Number / Nombor IC", s[i].ic);
				printf("%-60s | %s\n", "Gender / Janita", (s[i].gender == 'M') ? "Male / Lelaki" : "Female / Perempuan");
				printf("-------------------------------------------------------------------------------------------------\n\n");
				break;
			}
		}

		if (!found) {
			printf("=========================================================================\n");
			printf("Username does not exist.\n");
			printf("Nama ahli tidak wujud\n");
			printf("=========================================================================\n\n");
		}

		printf("Do you want to continue your search? (Y/N)\n");
		printf("Adakah anda ingin meneruskan pencarian anda? (Y/N)\n>");
		scanf(" %c", &confirm);
	} while (toupper(confirm) == 'Y');
	system("pause");
	system("cls");
}