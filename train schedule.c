#include "header.h"

//train schedule module
void scheduleMode() {


	int choice;
	system("cls");
	while (1) {
		trainScheduleMenu();
		scanf("%d", &choice);
		rewind(stdin);

		if (choice == 1) {
			displaySchedule();
		}
		else if (choice == 2) {
			searchSchedule();
		}
		else if (choice == -1) {
			system("cls");
			break;
		}
		else {
			printf("=========================================================================\n");
			printf("Choice Invalid\n");
			printf("Pilihan anda tidak sah\n");
			printf("=========================================================================\n\n");
		}
	}

}
void trainInfoMenu() {

	int choice = 0;
	char tripID[MAX_FIELD_LENGTH];
	do {
		system("cls");
		printf("=========================================================================\n");
		printf("\tWELCOME TO TRAIN INFORMATION MODULE\n");
		printf("\tSELAMAT DATANG KE MODUL MAKLUMAT KERETA API\n");
		printf("=========================================================================\n\n");

		printf("1. Search train schedule\n");
		printf("2. Display all train schedule\n");
		printf("3. Edit train schedule\n");
		printf("4. Add new train schedule\n");
		printf("5. Delete train schedule\n");
		printf("Please enter your choice (-1 to exit)\n\n");

		printf("1. Mencari jadual kereta api\n");
		printf("2. Memaparkan semua jadual kereta api\n");
		printf("3. Mengubahkan jadual kereta api\n");
		printf("4. Manambah jadual kereta api baharu\n");
		printf("5. Memadamkan jadual kerete api\n");
		printf("Sila masukkan pilihan anda (-1 untuk keluar)\n>");
		scanf("%d", &choice);
		rewind(stdin);

		if (choice == 1) {
			searchSchedule();
		}
		else if (choice == 2) {
			displaySchedule();
		}
		else if (choice == 3) {
			modifyTrainSchedule();
		}
		else if (choice == 4) {
			addTrainSchedule();
		}
		else if (choice == 5) {
			system("cls");
			printf("=========================================================================\n");
			printf("\tDELETE TRAIN SCHEDULE\n");
			printf("\tMEMADAMKAN JADUAL KERETA API\n");
			printf("=========================================================================\n\n");

			printf("Enter Trip ID to delete\n");
			printf("Masukkan ID perjalanan untuk memadamkan\n>");
			scanf("%s", tripID);
			rewind(stdin);
			deleteEntry(tripID);
		}
		else if (choice == -1) {
			system("cls");
		}
		else {
			printf("=========================================================================\n\n");
			printf("\tInvalid choice\n");
			printf("\tPilihan anda tidak sah\n");
			printf("=========================================================================\n\n");

		}
	} while (choice != -1);
}
void trainScheduleMenu() {
	printf("=========================================================================\n");
	printf("Welcome to Train Schedule information\n");
	printf("Selamat datang ke Informasi Jadual Kereta Api\n");
	printf("=========================================================================\n\n");

	printf("1. Display all train schedule\n");
	printf("2. Search train schedule\n");
	printf("Please enter your choice (-1 to exit)\n\n");

	printf("1. Memaparkan semua jadual kereta api\n");
	printf("2. Mencari jadual Kereta api\n");
	printf("Sila masukkan pilihan anda (-1 untuk keluar)\n>");



}
void displaySchedule() {

	int count = 0;
	TrainSchedule s;

	FILE* fptr = fopen("trainSchedule.txt", "r");
	if (!fptr) {
		printf("Error: Cannot open the file.\n");
		return 0;
	}
	system("cls");
	printf("=========================================================================\n");
	printf("%-15sTrain Schedule\n", "");
	printf("%-15sMemaparkan Jadual Kereta Api\n", "");
	printf("=========================================================================\n\n");

	printf("%-15s%-40s%-40s%-15s%-15s%-15s%-15s%-25s%-25s\n", "Trip No", "Departure", "Arrival", "Date", "Departure Time", "Arrival Time", "Train ID", "Seat Available", "Trip Price(One person)");
	printf("%-15s%-40s%-40s%-15s%-15s%-15s%-15s%-25s%-25s\n", "Perjalanan No", "Berlepas", "ketibaan", "Tarikh", "Masa berlepas", "Masa Ketibaan", "ID Kereta Api", "tempat duduk Disediakan", "Harga Perjalanan(seorang)");
	printf("%-15s%-40s%-40s%-15s%-15s%-15s%-15s%-25s%-25s\n", "-------------", "----------------------------------------", "----------------------------------------", "---------------", "----------------", "-----------", "--------------", "-----------------------", "--------------------------");

	while (fscanf(fptr, "%3s|%[^|]|%[^|]|%11[^|]|%4s|%4s|%3s|%d|%f\n", s.tripNo, s.departure, s.arrival, s.date, s.dTime, s.aTime, s.trainID, &s.seats, &s.price) != EOF) {
		count++;
		printf("%-15s%-40s%-40s%-15s%-15s%-15s%-15s%-25d%-25.2f\n", s.tripNo, s.departure, s.arrival, s.date, s.dTime, s.aTime, s.trainID, s.seats, s.price);
	}
	printf("%-15s%-40s%-40s%-15s%-15s%-15s%-15s%-25s%-25s\n", "-------------", "----------------------------------------", "----------------------------------------", "---------------", "----------------", "-----------", "--------------", "-----------------------", "--------------------------");
	printf("\n%-10s%d schedules listed.\n", "", count);
	printf("%-10s%d jadual dipaparkan.\n", "", count);


	fclose(fptr);
	system("pause");
	system("cls");
}
void searchSchedule() {
	FILE* file;
	TrainSchedule schedule;
	char searchDeparture[MAX_FIELD_LENGTH], searchArrival[MAX_FIELD_LENGTH];
	int resultCount = 0;

	file = fopen("trainSchedule.txt", "r");
	if (file == NULL) {
		printf("Error: Cannot open the file.\n");
		return 1;
	}

	system("cls");
	printf("=========================================================================\n");
	printf("\t\tSearch Train Schedule\n");
	printf("\t\tMencari Jadual Kereta Api\n");
	printf("=========================================================================\n\n");

	printf("Please enter departure station \n");
	printf("Sila masukkan stesen berlepas\n>");
	scanf("%[^\n]", searchDeparture);
	convertToUpper(searchDeparture);
	rewind(stdin);

	printf("\nEnter arrival station \n");
	printf("Sila masukkan stesen ketibaan\n>");
	scanf("%[^\n]", searchArrival);
	convertToUpper(searchArrival);
	rewind(stdin);

	if (strlen(searchDeparture) == 0 || strlen(searchArrival) == 0) {
		printf("Error: Departure and arrival stations cannot be empty.\n");
		fclose(file);
		return 1;
	}

	printf("\n");
	printf("%-15s %-25s %-25s %-12s %-15s %-15s %-15s %-15s %-10s\n",
		"Trip No", "Departure", "Arrival", "Date", "Departure Time",
		"Arrival Time", "Train ID", "Seats", "Trip Price(One person)");
	printf("%-15s %-25s %-25s %-12s %-15s %-15s %-15s %-15s %-10s\n",
		"Perjalanan No", "Berlepas", "Ketibaan", "Tarikh", "Masa berlepasan",
		"Masa Ketibaan", "ID Kereta Api", "Tempat duduk", "Harga Perjalanan(seorang)");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f\n",
		schedule.tripNo, schedule.departure, schedule.arrival, schedule.date,
		schedule.dTime, schedule.aTime, schedule.trainID, &schedule.seats, &schedule.price) != EOF) {

		convertToUpper(schedule.departure);
		convertToUpper(schedule.arrival);

		if (strcmp(schedule.departure, searchDeparture) == 0 && strcmp(schedule.arrival, searchArrival) == 0) {
			printf("%-15s %-25s %-25s %-12s %-15s %-15s %-15s %-15d %-10.2f\n",
				schedule.tripNo, schedule.departure, schedule.arrival, schedule.date,
				schedule.dTime, schedule.aTime, schedule.trainID, schedule.seats, schedule.price);
			resultCount++;
		}
	}

	if (resultCount == 0) {
		printf("\nNo schedules found for the specified stations.\n");
		printf("Tiada Jadual ditemui untuk stasen yang ditentukan.\n\n");
	}
	else {
		printf("\n%d results displayed.\n", resultCount);
		printf("%d keputusan dipaparkan.\n", resultCount);

	}

	fclose(file);
	system("pause");
	system("cls");
}
void addTrainSchedule() {
	TrainSchedule s;

	FILE* fptr = fopen("trainSchedule.txt", "a+");
	if (!fptr) {
		printf("Error: Cannot open the file.\n");
		return 1;
	}

	char tripIDs[MAX_FIELD_LENGTH];
	int numTripIDs = 0;

	while (fscanf(fptr, "%[^|]|%*[^\\n]", tripIDs) == 1) {
		numTripIDs++;
	}
	system("cls");
	printf("=========================================================================\n");
	printf("\tADD TRAIN SCHEDULE\n");
	printf("\tPENAMBAHAN JADUAL KERETA API\n");
	printf("=========================================================================\n\n");

	do {
		printf("Enter Trip ID (000 to stop)\n");
		printf("Masukkan ID kereta api (000 untuk keluar)\n>");
		scanf("%s", s.tripNo);
		rewind(stdin);

		if (strcmp(s.tripNo, "000") != 0) {
			if (isDuplicateTripID(s.tripNo, "trainSchedule.txt")) {
				printf("Trip ID already exists. Please enter a different Trip ID.\n");
				printf("ID perjalanan sudah wujud. Sila masukkan ID perjalanan yang berbeza\n\n");
				continue;
			}

			printf("\nEnter Departure\n");
			printf("Masukkan stesen berlepas\n>");
			scanf(" %[^\n]", s.departure);
			rewind(stdin);
			convertToUpper(s.departure);

			printf("\nEnter Arrival\n");
			printf("Masukkan stesen ketibaan\n>");
			scanf(" %[^\n]", s.arrival);
			rewind(stdin);
			convertToUpper(s.arrival);

			printf("\nEnter date (YYYY-MM-DD)\n");
			printf("Masukkan Tarikh (YYYY-MM-DD)\n>");
			scanf("%s", s.date);
			rewind(stdin);

			printf("\nEnter Departure Time (in 24 hour time format)\n");
			printf("Masukkan masa berlepas (dalam format 24 jam)\n>");
			scanf("%s", s.dTime);
			rewind(stdin);

			printf("\nEnter Arrival Time (in 24 hour time format)\n");
			printf("Masukkan masa ketibaan (dalam format 24 jam)\n>");
			scanf("%s", s.aTime);
			rewind(stdin);

			do {
				printf("\nEnter Train ID (T01 to T04)\n");
				printf("Masukkan ID kereta api (T01 hingga T04)\n>");
				scanf("%s", s.trainID);
				rewind(stdin);
			} while (!isValidTrainID(s.trainID));

			s.seats = 20;

			do {
				printf("\nEnter Trip Price\n");
				printf("Masukkan harga perjalanan\n>");
			} while (scanf("%f", &s.price) != 1);

			fprintf(fptr, "%s|%s|%s|%s|%s|%s|%s|%d|%.2f\n", s.tripNo, s.departure, s.arrival, s.date, s.dTime, s.aTime, s.trainID, s.seats, s.price);
			numTripIDs++;
			printf("\n");
		}
	} while (strcmp(s.tripNo, "000") != 0);

	fclose(fptr);
}
void modifyTrainSchedule() {
	FILE* file;
	char line[MAX_LINE_LENGTH];
	TrainSchedule s;
	char searchTripNo[MAX_FIELD_LENGTH];
	int found = 0;

	file = fopen("trainSchedule.txt", "r");
	if (file == NULL) {
		printf("Error opening the file.\n");
		return 1;
	}
	system("cls");
	printf("=========================================================================\n");
	printf("\tMODIFY TRAIN SCHEDULE\n");
	printf("\tMENGUBAH JAUDAL KERETA API\n");
	printf("=========================================================================\n\n");

	printf("Enter trip number to modify\n");
	printf("Masukkan nombor perjalanan untuk mengubah suai\n>");
	scanf("%s", searchTripNo);
	rewind(stdin);

	FILE* tempFile = fopen("temp.txt", "w");
	if (tempFile == NULL) {
		printf("Error creating temporary file.\n");
		fclose(file);
		return 1;
	}

	while (fgets(line, sizeof(line), file)) {//read the line
		sscanf(line, "%19[^|]|%19[^|]|%19[^|]|%19[^|]|%19[^|]|%19[^|]|%19[^|]|%d|%f",// formatted string so use sscanf
			s.tripNo, s.departure, s.arrival, s.date,
			s.dTime, s.aTime, s.trainID, &s.seats, &s.price);

		convertToUpper(s.tripNo);

		if (strcmp(s.tripNo, searchTripNo) == 0) {
			found = 1;

			printf("\nCurrent Details:\n");
			printf("Trip No: %s\n", s.tripNo);
			printf("Departure: %s\n", s.departure);
			printf("Arrival: %s\n", s.arrival);
			printf("Date: %s\n", s.date);
			printf("Departure Time: %s\n", s.dTime);
			printf("Arrival Time: %s\n", s.aTime);
			printf("Train ID: %s\n", s.trainID);
			printf("Available Seats: %d\n", s.seats);
			printf("Price: %.2f\n\n", s.price);

			printf("Butiran Semasa:\n");
			printf("Nombor Perjalanan: %s\n", s.tripNo);
			printf("Stesen berlepas: %s\n", s.departure);
			printf("Stesen Ketibaan: %s\n", s.arrival);
			printf("Tarikh: %s\n", s.date);
			printf("Masa Berlepas: %s\n", s.dTime);
			printf("Masa Ketibaan: %s\n", s.aTime);
			printf("ID Kereta Api: %s\n", s.trainID);
			printf("Tempat duduk yang tersedia: %d\n", s.seats);
			printf("Harga: %.2f\n\n", s.price);

			printf("Enter new departure station\n");
			printf("Stesen berlepas baharu\n>");
			scanf("%[^\n]", s.departure);
			rewind(stdin);
			convertToUpper(s.departure);

			printf("\nEnter new arrival station\n");
			printf("Stesen ketibaan baharu\n>");
			scanf("%[^\n]", s.arrival);
			rewind(stdin);
			convertToUpper(s.arrival);

			printf("\nEnter new date (YYYY-MM-DD)\n");
			printf("Tarikh baharu (YYYY-MM-DD)\n>");
			scanf("%s", s.date);
			rewind(stdin);

			printf("\nEnter new departure time\n");
			printf("Masa berlepas baharu\n>");
			scanf("%s", s.dTime);
			rewind(stdin);

			printf("\nEnter new arrival time\n");
			printf("Masa ketibaan baharu\n>");
			scanf("%s", s.aTime);
			rewind(stdin);

			do {
				printf("\nEnter new train ID (T01, T02, T03, T04)\n");
				printf("ID kereta api baharu (T01, T02, T03, T04)\n>");
				scanf("%s", s.trainID);
			} while (!isValidTrainID(s.trainID));

			printf("\nEnter new price\n");
			printf("Harga baharu\n>");
			scanf("%f", &s.price);

			fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%d|%.2f\n", s.tripNo, s.departure, s.arrival, s.date, s.dTime, s.aTime, s.trainID, s.seats, s.price);
		}
		else {
			fprintf(tempFile, "%s", line);
		}
	}

	fclose(file);
	fclose(tempFile);

	if (!found) {
		printf("Entry not found for modification.\n");
		printf("Entri tidak dijumpai untuk pengubahsuaian\n\n");
		remove("temp.txt"); // Delete temporary file
		return 1;
	}

	remove("trainSchedule.txt"); // Delete original file
	rename("temp.txt", "trainSchedule.txt"); // Rename temporary file to original

	printf("Modification successful.\n");
	printf("Pengubahsuaian berjaya.\n");
	system("pause");
	system("cls");
}
void deleteEntry(const char* tripID) {
	FILE* file, * tempFile;
	char line[MAX_LINE_LENGTH];
	TrainSchedule schedule;
	int found = 0;
	char confirm;

	file = fopen("trainSchedule.txt", "r");
	tempFile = fopen("tempTrainSchedule.txt", "w");

	if (file == NULL || tempFile == NULL) {
		printf("Error opening the file.\n");
		return;
	}

	while (fgets(line, sizeof(line), file)) {
		sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f", schedule.tripNo, schedule.departure, schedule.arrival, schedule.date, schedule.dTime, schedule.aTime, schedule.trainID, &schedule.seats, &schedule.price);
		convertToUpper(schedule.tripNo);

		if (strcmp(schedule.tripNo, tripID) == 0) {
			found = 1;
			printf("\nEntry found:\n");
			printf("Trip No: %s\n", schedule.tripNo);
			printf("Departure: %s\n", schedule.departure);
			printf("Arrival: %s\n", schedule.arrival);
			printf("Date: %s\n", schedule.date);
			printf("Departure Time: %s\n", schedule.dTime);
			printf("Arrival Time: %s\n", schedule.aTime);
			printf("Train ID: %s\n", schedule.trainID);
			printf("Available Seats: %d\n", schedule.seats);
			printf("Trip Price(One person): %.2f\n\n", schedule.price);

			printf("Entri ditemui:\n");
			printf("Nombor perjalanan: %s\n", schedule.tripNo);
			printf("Stesen Berlepas: %s\n", schedule.departure);
			printf("Stesen ketibaan: %s\n", schedule.arrival);
			printf("Tarikh: %s\n", schedule.date);
			printf("Masa berlepas: %s\n", schedule.dTime);
			printf("Masa ketibaan: %s\n", schedule.aTime);
			printf("ID kereta api: %s\n", schedule.trainID);
			printf("Tempat duduk yang tersedia: %d\n", schedule.seats);
			printf("Harga perjalanan(seorang): %.2f\n\n", schedule.price);


			printf("Are you sure you want to delete this entry? (Y/N)\n");
			printf("Adakah anda pasti mahu memadamkan entri ini? (Y/N)\n>");
			scanf(" %c", &confirm);
			rewind(stdin);
			if (toupper(confirm) == 'Y') {
				printf("\nDeleting entry...\n");
				printf("Entry deleted successfully.\n");
			}
			else {
				printf("Deletion cancelled.\n");
				fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%d|%.2f\n", schedule.tripNo, schedule.departure, schedule.arrival, schedule.date, schedule.dTime, schedule.aTime, schedule.trainID, schedule.seats, schedule.price);
			}
		}
		else {
			fprintf(tempFile, "%s|%s|%s|%s|%s|%s|%s|%d|%.2f\n", schedule.tripNo, schedule.departure, schedule.arrival, schedule.date, schedule.dTime, schedule.aTime, schedule.trainID, schedule.seats, schedule.price);
		}
	}

	fclose(file);
	fclose(tempFile);

	remove("trainSchedule.txt");
	rename("tempTrainSchedule.txt", "trainSchedule.txt");


	if (!found) {
		printf("Entry not found for deletion.\n");
	}
	system("pause");
}
