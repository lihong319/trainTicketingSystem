#include "header.h"

//booking module
void bookingMode(char loggedInUsername[50]) {

	int choice;

	system("cls");

	do {
		printf("===================================================\n");
		printf("        Welcome To Train Booking System\n");
		printf("        Selamat datang ke Tempahan Tiket Kereta Api\n");
		printf("===================================================\n\n");

		printf("Please select an option:\n");
		printf("1. Make a Booking\n");
		printf("2. Cancellation\n");
		printf("3. View Booking History\n");
		printf("4. Create Account\n");
		printf("5. Exit\n");
		printf("---------------------------------------------------\n");
		printf("Enter your choice (1-5): ");

		scanf(" %d", &choice);
		while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
			rewind(stdin);
			printf("Error: Invalid choice.\n");
			printf("Enter your choice (1-6): ");
			scanf(" %d", &choice);
		}

		switch (choice) {
		case 1:
			
			Bookingfunction(loggedInUsername);
			break;
		case 2:
			cancellation(loggedInUsername);
			break;
		case 3:
			viewBookingwithusername(loggedInUsername);
			break;
		case 4:
			createAccount();
			break;
		case 5:
			printf("Exiting...\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}

	} while (choice != 5);
	system("cls");
}
void SeatFunction(int ticket, char trainID[10], char bookingID[10], char passtrip[20]) {
	FILE* fptr;
	TrainSchedule s[100];
	Seat seat;

	int choice, randomNumberOKU[MAX_SEATS], randomNumberNORMAL[MAX_SEATS], index = 0, index1 = 0;
	int NOFoku, NOFnormal, count = 0, countOKU = 0, countNORMAL = 0, totalSeat = 0, num[20] = { 0 }, num1[20] = { 0 };
	char ansSeat, confirmSeat;
	srand(time(NULL));

	fptr = fopen("trainSchedule.txt", "r");

	if (fptr == NULL) {
		printf("Error: Cannot open the file 'trainSchedule.txt' for reading.\n");
		exit(-1);
	}
	while (fscanf(fptr, "%3s|%9[^|]|%9[^|]|%*d-%d-%d|%4s|%4s|%3s|%d|%f\n", s[count].tripNo, s[count].departure, s[count].arrival, &s[count].month, &s[count].day, &s[count].dTime, &s[count].aTime, &s[count].trainID, &s[count].seats, &s[count].price) == 10) {


		if (strcmp(trainID, s[count].trainID) == 0 && strcmp(passtrip, s[count].tripNo) == 0) {
			index = count;

		}

		count++;
	}
	fclose(fptr);

	seat.numberofNORMAL = 0;
	seat.numberofOKU = 0;
	seat.seatAvailable = 0;

	do {

		printf("\nSeat Types | Jenis Tempat Duduk\n");
		printf("1 - OKU (1 PERSON): RM %.2f\n", OKU_PRICE);
		printf("2 - NORMAL (1 PERSON): RM %.2f\n\n", NORMAL_PRICE);
		printf("Enter your choice(1 or 2):\n");
		printf("Masukkan pilihan anda (1 atau 2): ");
		scanf(" %d", &choice);
		while (choice != 2 && choice != 1) {
			printf("Invalid choice!! | Pilihan tidak sah!\n");
			rewind(stdin);
			printf("Enter your choice:\n");
			printf("Masukkan pilihan anda: ");
			scanf(" %d", &choice);
		}
		switch (choice) {
		case 1:
			printf("\nEnter number of seats for OKU (maximum 5):\n");
			printf("Masukkan bilangan tempat duduk untuk OKU (maksimum 5): ");
			scanf(" %d", &NOFoku);

			while (NOFoku < 0 || NOFoku > 5) {
				printf("Invalid input. Please enter a number between 1 and 5:\n");
				printf("Input tidak sah. Sila masukkan nombor antara 1 dan 5: ");
				scanf(" %d", &NOFoku);
			}

			seat.numberofOKU += NOFoku;
			countOKU++;
			break;

		case 2:
			printf("\nEnter number of seats for NORMAL:\n");
			printf("Masukkan bilangan tempat duduk untuk NORMAL: ");
			scanf(" %d", &NOFnormal);

			while (NOFnormal < 0 || NOFnormal > 15) {
				printf("Invalid input. Please enter a number between 1 and 15:\n");
				printf("Input tidak sah.Sila masukkan nombor antara 1 dan 15:");
				int c;
				while ((c = getchar()) != '\n' && c != EOF); // Clear input buffer
				printf("Enter number of seats for NORMAL:\n");
				printf("Masukkan bilangan tempat duduk untuk NORMAL: ");
				scanf(" %d", &NOFnormal);
			}
			seat.numberofNORMAL += NOFnormal;
			countNORMAL++;
			break;

		default:
			printf("Invalid choice. Please try again. | Pilihan tidak sah. Sila cuba lagi.\n");
			break;
		}

		if (seat.numberofOKU > 5) {
			printf("Seat number for OKU only can have 5.\n");
			printf("Bilangan tempat duduk untuk OKU hanya boleh 5.\n");
			displaySeatingChart();
			printf("\n");
			Bookingfunction(NULL);

		}
		if (seat.numberofNORMAL > 15) {
			printf("Seat number for NORMAL only can have 15.\n");
			printf("Bilangan tempat duduk untuk NORMAL hanya boleh 15.\n");
			displaySeatingChart();
			printf("\n");
			Bookingfunction(NULL);

		}

		totalSeat = seat.numberofNORMAL + seat.numberofOKU;
		if (totalSeat > s[index].seats) {
			printf("Your Number of seats already over!!!\n");
			printf("Bilangan tempat duduk anda sudah melebihi!!!\n");
			displaySeatingChart();
			printf("\n");
			Bookingfunction(NULL);

		}

		printf("\nYou want to Add more Seat (Y/N):\n");
		printf("Anda ingin tambah tempat duduk lagi (Y/N): ");
		scanf(" %c", &ansSeat);
		while (toupper(ansSeat) != 'Y' && toupper(ansSeat) != 'N' && ansSeat != 1 && toupper(ansSeat) != 'T') {
			printf("Invalid input\n");
			printf("\nYou want to Add more Seat (Y/N):\n");
			printf("Anda ingin tambah tempat duduk lagi (Y/N): ");

			rewind(stdin);
			scanf(" %c", &ansSeat);
		}

	} while (toupper(ansSeat) == 'Y');

	rewind(stdin);
	printf("\nConfirm do you want to reset your Seat (Y/N): ");
	scanf(" %c", &confirmSeat);
	while (toupper(confirmSeat) != 'Y' && toupper(confirmSeat) != 'N' && confirmSeat != 1) {
		printf("Invalid input\n");

		printf("\nConfirm do you want to reset your Seat (Y/N): ");
		rewind(stdin);
		scanf(" %c", &confirmSeat);
	}
	if (toupper(confirmSeat) == 'Y') {
		seat.numberofNORMAL = 0;
		seat.numberofOKU = 0;
		totalSeat = 0;
		seat.seatAvailable = 0;
		countNORMAL = 0;
		countOKU = 0;
		printf("\n");
		do {

			printf("\nSeat Types | Jenis Tempat Duduk\n");
			printf("1 - OKU (1 PERSON): RM %.2f\n", OKU_PRICE);
			printf("2 - NORMAL (1 PERSON): RM %.2f\n\n", NORMAL_PRICE);
			printf("Enter your choice(1 or 2):\n");
			printf("Masukkan pilihan anda (1 atau 2): ");
			scanf(" %d", &choice);
			while (choice != 2 && choice != 1) {
				printf("Invalid choice!! | Pilihan tidak sah!\n");
				rewind(stdin);
				printf("Enter your choice:\n");
				printf("Masukkan pilihan anda: ");
				scanf(" %d", &choice);
			}
			switch (choice) {
			case 1:
				printf("\nEnter number of seats for OKU (maximum 5):\n");
				printf("Masukkan bilangan tempat duduk untuk OKU (maksimum 5): ");
				scanf(" %d", &NOFoku);

				while (NOFoku < 0 || NOFoku >5) {
					printf("Invalid input. Please enter a number between 1 and 5:\n");
					printf("Input tidak sah. Sila masukkan nombor antara 1 dan 5: ");
					scanf(" %d", &NOFoku);
				}

				seat.numberofOKU += NOFoku;
				countOKU++;
				break;

			case 2:
				printf("\nEnter number of seats for NORMAL:\n");
				printf("Masukkan bilangan tempat duduk untuk NORMAL: ");
				scanf(" %d", &NOFnormal);

				while (NOFnormal < 0 || NOFnormal > 15) {
					printf("Invalid input. Please enter a number between 1 and 15:\n");
					printf("Input tidak sah.Sila masukkan nombor antara 1 dan 15:");
					int c;
					while ((c = getchar()) != '\n' && c != EOF); // Clear input buffer
					printf("Enter number of seats for NORMAL:\n");
					printf("Masukkan bilangan tempat duduk untuk NORMAL: ");
					scanf(" %d", &NOFnormal);
				}
				seat.numberofNORMAL += NOFnormal;
				countNORMAL++;
				break;

			default:
				printf("Invalid choice. Please try again. | Pilihan tidak sah. Sila cuba lagi.\n");
				break;
			}

			if (seat.numberofOKU > 5) {
				printf("Seat number for OKU only can have 5.\n");
				printf("Bilangan tempat duduk untuk OKU hanya boleh 5.\n");
				displaySeatingChart();
				printf("\n");
				Bookingfunction(NULL);
			}
			if (seat.numberofNORMAL > 15) {
				printf("Seat number for NORMAL only can have 15.\n");
				printf("Bilangan tempat duduk untuk NORMAL hanya boleh 15.\n");
				displaySeatingChart();
				printf("\n");
				Bookingfunction(NULL);
			}

			totalSeat = seat.numberofNORMAL + seat.numberofOKU;
			if (totalSeat > s[index].seats) {
				printf("Your Number of seats already over!!!\n");
				printf("Bilangan tempat duduk anda sudah melebihi!!!\n");
				displaySeatingChart();
				printf("\n");
				Bookingfunction(NULL);

			}
			printf("\nYou want to Add more Seat (Y/N):\n");
			printf("Anda ingin tambah tempat duduk lagi (Y/N): ");
			scanf(" %c", &ansSeat);
			while (toupper(ansSeat) != 'Y' && toupper(ansSeat) != 'N' && ansSeat != 1 && toupper(ansSeat) != 'T') {
				printf("Invalid input\n");
				printf("\nYou want to Add more Seat (Y/N):\n");
				printf("Anda ingin tambah tempat duduk lagi (Y/N): ");
				rewind(stdin);
				scanf(" %c", &ansSeat);
			}

		} while (toupper(ansSeat) == 'Y');



		for (int i = 0; i < seat.numberofOKU; i++) {
			do {
				num[i] = rand() % 5;
				seat.storeSeat[num[i]] = 'X'; // Randomly assign 'X' initially
			} while (checkDuplicate(num[i], num, i) == 1);


		}
		printf("\nCurrent Seat Statuses | Status Tempat Duduk Semasa:\n");
		for (int i = 0; i < 5; i++) {
			if (seat.storeSeat[i] == 'X') {
				printf("%c ", seat.storeSeat[i]);
			}
			else {
				printf("O ");
			}

		}

		printf("\n");
		for (int j = 0; j < seat.numberofNORMAL; j++) {
			do {
				num1[j] = rand() % 15;
				seat.storeSeat1[num1[j]] = 'X'; // Randomly assign 'X' or 'O'
			} while (checkDuplicate(num1[j], num1, j) == 1);
		}

		for (int j = 0; j < 15; j++) {
			if (seat.storeSeat1[j] == 'X') {
				printf("%c ", seat.storeSeat1[j]);
			}
			else {
				printf("O ");
			}
			if ((1 + j) % 5 == 0) {
				printf("\n");
			}
		}

		if (countNORMAL > 0) {
			seat.price = 12.00 * seat.numberofNORMAL;

			strcpy(seat.seatTypes, "NORMAL");
			printf("Seat Normal | Tempat Duduk Normal:\n");
			for (int i = 0;i < seat.numberofNORMAL;i++) {
				printf("S%02d, ", num1[i] + 1);
			}
			printf("\n");
		}

		if (countOKU > 0) {
			seat.price = 6.00 * seat.numberofOKU;
			strcpy(seat.seatTypes, "OKU");
			printf("Seat OKU | Tempat Duduk OKU:\n");
			for (int i = 0;i < seat.numberofOKU;i++) {
				printf("O%02d, ", num[i] + 1);
			}
			printf("\n");
		}

		else if (countNORMAL == 1 && countOKU == 1) {
			strcpy(seat.seatTypes, "NORMAL OKU");
			seat.price = (6.00 * seat.numberofOKU) + (12.00 * seat.numberofNORMAL);
		}

		else if (countOKU > 1) {
			strcpy(seat.seatTypes, "OKU");
		}
		else if (countNORMAL > 1) {
			strcpy(seat.seatTypes, "NORMAL");
		}


		seat.seatAvailable = ticket - (seat.numberofNORMAL + seat.numberofOKU);
		strcpy(seat.storeBookingID, bookingID);
		strcpy(seat.storeTrainID, trainID);
		strcpy(seat.trip, passtrip);
		printf("Seat Types: %s\n", seat.seatTypes);
		printf("Number of seat for NORMAL Reserved | Bilangan tempat duduk untuk NORMAL telah ditempah: %d\n", seat.numberofNORMAL);
		printf("Number of seat for OKU Reserved | Bilangan tempat duduk untuk OKU telah ditempah: %d\n", seat.numberofOKU);

		fptr = fopen("Seatfile.txt", "a");

		if (fptr == NULL) {
			printf("Error opening file");
			exit(-1);
		}

		fprintf(fptr, "%s|%s|%d|%d|%d|%.2lf|%s|%s|", seat.trip,
			seat.seatTypes, seat.seatAvailable, seat.numberofNORMAL, seat.numberofOKU, seat.price,
			seat.storeTrainID, seat.storeBookingID);
		for (int i = 0;i < 5;i++) {
			fprintf(fptr, "%c", seat.storeSeat[i] == 'X' ? 'X' : 'O');

		}
		fprintf(fptr, "|");
		for (int j = 0; j < 15; j++) {
			fprintf(fptr, "%c", seat.storeSeat1[j] == 'X' ? 'X' : 'O');
		}
		fprintf(fptr, "\n");
		fclose(fptr);
	}
	else {
		printf("\n");
		for (int i = 0; i < seat.numberofOKU; i++) {
			do {
				num[i] = rand() % 5;
				seat.storeSeat[num[i]] = 'X'; // Randomly assign 'X' initially
			} while (checkDuplicate(num[i], num, i) == 1);


		}
		printf("Current Seat Statuses | Status Tempat Duduk Semasa:\n");
		for (int i = 0; i < 5; i++) {
			if (seat.storeSeat[i] == 'X') {
				printf("%c ", seat.storeSeat[i]);
			}
			else {
				printf("O ");
			}

		}

		printf("\n");
		for (int j = 0; j < seat.numberofNORMAL; j++) {
			do {
				num1[j] = rand() % 15;
				seat.storeSeat1[num1[j]] = 'X'; // Randomly assign 'X' or 'O'
			} while (checkDuplicate(num1[j], num1, j) == 1);
		}

		for (int j = 0; j < 15; j++) {
			if (seat.storeSeat1[j] == 'X') {
				printf("%c ", seat.storeSeat1[j]);
			}
			else {
				printf("O ");
			}
			if ((1 + j) % 5 == 0) {
				printf("\n");
			}
		}


		printf("\n");
		if (countNORMAL > 0) {
			seat.price = 12.00 * seat.numberofNORMAL;

			strcpy(seat.seatTypes, "NORMAL");
			printf("Seat Normal | Tempat Duduk Normal:\n");
			for (int i = 0;i < seat.numberofNORMAL;i++) {
				printf("S%02d, ", num1[i] + 1);
			}
			printf("\n");
		}

		if (countOKU > 0) {
			seat.price = 6.00 * seat.numberofOKU;
			strcpy(seat.seatTypes, "OKU");
			printf("Seat OKU | Tempat Duduk OKU:\n");
			for (int i = 0;i < seat.numberofOKU;i++) {
				printf("O%02d, ", num[i] + 1);
			}
			printf("\n");
		}

		if (countNORMAL == 1 && countOKU == 1) {
			strcpy(seat.seatTypes, "NORMAL OKU");
			seat.price = (6.00 * seat.numberofOKU) + (12.00 * seat.numberofNORMAL);
		}

		else if (countOKU > 1) {
			strcpy(seat.seatTypes, "OKU");
		}
		else if (countNORMAL > 1) {
			strcpy(seat.seatTypes, "NORMAL");
		}

		seat.seatAvailable = ticket - (seat.numberofNORMAL + seat.numberofOKU);
		strcpy(seat.storeBookingID, bookingID);
		strcpy(seat.storeTrainID, trainID);
		strcpy(seat.trip, passtrip);

		printf("Seat Types: %s\n", seat.seatTypes);
		printf("Number of seat for NORMAL Reserved | Bilangan tempat duduk untuk NORMAL telah ditempah: %d\n", seat.numberofNORMAL);
		printf("Number of seat for OKU Reserved | Bilangan tempat duduk untuk OKU telah ditempah: %d\n", seat.numberofOKU);

		fptr = fopen("Seatfile.txt", "a");

		if (fptr == NULL) {
			printf("Error opening file");
			exit(-1);
		}

		fprintf(fptr, "%s|%s|%d|%d|%d|%.2lf|%s|%s|", seat.trip,
			seat.seatTypes, seat.seatAvailable, seat.numberofNORMAL, seat.numberofOKU, seat.price,
			seat.storeTrainID, seat.storeBookingID);
		for (int i = 0;i < 5;i++) {
			fprintf(fptr, "%c", seat.storeSeat[i] == 'X' ? 'X' : 'O');

		}
		fprintf(fptr, "|");
		for (int j = 0; j < 15; j++) {
			fprintf(fptr, "%c", seat.storeSeat1[j] == 'X' ? 'X' : 'O');
		}
		fprintf(fptr, "\n");
		fclose(fptr);

	}
}

void generateNew(int seatavailable, char passTrainid[20], char tripno[20]) {
	FILE* inputFile;
	FILE* outputFile;
	TrainSchedule s[30];
	int index = 0, pass = -1;

	inputFile = fopen("trainSchedule.txt", "r");
	if (inputFile == NULL) {
		printf("Error: Cannot open the file 'trainSchedule.txt' for reading.\n");
		exit(-1);
	}

	while (fscanf(inputFile, "%19[^|]|%19[^|]|%19[^|]|%19[^|]|%19[^|]|%19[^|]|%19[^|]|%d|%f\n",
		s[index].tripNo, s[index].departure, s[index].arrival, s[index].date,
		s[index].dTime, s[index].aTime, s[index].trainID, &s[index].seats, &s[index].price) == 9) {

		if (strcmp(passTrainid, s[index].trainID) == 0 && strcmp(tripno, s[index].tripNo) == 0) {
			s[index].seats = seatavailable;
			pass = index;
		}
		index++;
	}

	fclose(inputFile);

	if (pass != -1) {

		outputFile = fopen("trainSchedule.txt", "w");
		if (outputFile == NULL) {
			printf("Error: Cannot open the file 'trainSchedule.txt' for writing.\n");
			exit(-1);
		}

		// Write data back to file
		for (int i = 0; i < index; i++) {
			fprintf(outputFile, "%s|%s|%s|%s|%s|%s|%s|%d|%.2f\n", s[i].tripNo, s[i].departure, s[i].arrival, s[i].date, s[i].dTime, s[i].aTime, s[i].trainID, s[i].seats, s[i].price);
		}

		fclose(outputFile);
	}
	else {
		printf("Error: Train schedule not found.\n");
	}
}
void encodeText(char qrCode[HEIGHT][WIDTH], const char* text) {
	int len = strlen(text);
	int pos = 0;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if ((y >= 4 && y <= 11 && x >= 5 && x <= 9) && (pos < len)) {
				qrCode[y][x] = text[pos++];
			}
			else {
				qrCode[y][x] = ' ';
			}
		}
	}
}
void drawQRCode(char qrCode[HEIGHT][WIDTH]) {
	for (int y = -1; y <= HEIGHT; y++) {
		for (int x = -1; x <= WIDTH; x++) {
			char ch;
			if ((y == -1 || y == HEIGHT) || (x == -1 || x == WIDTH)) {
				ch = '#';
			}
			else {
				ch = qrCode[y][x];
			}
			putchar(ch);
		}
		putchar('\n');
	}
}
void trainSchedule() {
	int count = 0;
	TrainSchedule s;


	FILE* fptr = fopen("trainSchedule.txt", "r");
	if (!fptr) {
		printf("Error: Cannot open the file.\n");
		exit(-1);
	}

	printf("%-15sTrain Schedule\n\n", "");
	printf("%-8s%-10s%-10s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Trip No", "Departure", "Arrival", "Date", "Departure Time", "Arrival Time", "Train ID", "Seat Available", "Trip Price(One person)");
	printf("%-8s%-10s%-10s%-15s%-15s%-15s%-15s%-15s%-15s\n", "-------", "---------", "-------", "---------------", "--------------", "-----------", "--------", "---------------", "-----------------");

	while (fscanf(fptr, "%3s|%9[^|]|%9[^|]|%*d-%d-%d|%4s|%4s|%3s|%d|%f\n", s.tripNo, s.departure, s.arrival, &s.month, &s.day, &s.dTime, &s.aTime, &s.trainID, &s.seats, &s.price) == 10) {
		count++;
		printf("%-8s%-10s%-10s2024-%02d-%02d%15s%15s%15s%15d%15.2f\n", s.tripNo, s.departure, s.arrival, s.month, s.day, s.dTime, s.aTime, s.trainID, s.seats, s.price);
	}
	printf("%-8s%-10s%-10s%-15s%-15s%-15s%-15s%-15s%-15s\n", "-------", "---------", "-------", "---------------", "--------------", "-----------", "--------", "---------------", "-----------------");
	printf("%-10s%d schedules listed.\n", "", count);

	fclose(fptr);

}
void displaySeatingChart() {
	bool seatingChart[ROWS][COLS] = {
	{false, false, false, false,false},
	{true, true, true, true, true},
	{true, true, true, true, true},
	{true, true, true, true, true}
	};
	printf("Seating Chart || Carta Tempat Duduk:\n");
	printf("%8sCol 1 Col 2 Col 3 Col 4 Col 5\n", "");
	printf("%8s+----- ----- ----- ----- -----+\n", "");
	for (int i = 0; i < ROWS; i++) {
		printf("Row %d: |", i + 1);
		for (int j = 0; j < COLS; j++) {

			if (seatingChart[i][j] == false) {
				printf(" [O] |");

			}
			else {
				printf(" [N] |");

			}
		}
		printf("\n");

	}
	printf("%8s+----- ----- ----- ----- -----+\n", "");
	printf("Attention:  O-> OKU    N-> NORMAL\n");
	printf("\n");
}
bool generateBKnumber(int generateNumber) {
	FILE* fptr;
	struct Booking BK;
	int num;
	char* token;
	fptr = fopen("BookingHistory.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file.\n");
		return false;
	}

	while (fscanf(fptr, "%9s | %10s | %d-%d-%*d | %lf | %19[^|] | %9s | %d\n",
		BK.bookingID,
		&BK.username,
		&BK.day,
		&BK.month,
		&BK.payment,
		BK.paymentMethod,
		BK.trip_no,
		&BK.numberOfTickets) == 8) {

		token = BK.bookingID;
		while (token && !isdigit(*token)) {
			token++;
		}
		if (*token) {
			num = atoi(token); // Convert the remaining part to integer

		}
		while (generateNumber == num) {
			return true;

		}

	}
	fclose(fptr);
	return false;
}
bool validation_AccountNumber(const char checkAccountNumber[]) {
	int hasUpperCase = 0;
	int hasLowerCase = 0;
	int hasDigit = 0;
	int hasSymbol = 0;

	for (int i = 0;i < strlen(checkAccountNumber);i++) {
		if (isdigit(checkAccountNumber[i])) {
			hasDigit = 1;

		}
		else if (islower(checkAccountNumber[i])) {
			hasLowerCase = 1;
		}
		else if (isupper(checkAccountNumber[i])) {
			hasUpperCase = 1;

		}
		else if (ispunct(checkAccountNumber[i])) {
			hasSymbol = 1;

		}
	}

	if (hasUpperCase && hasLowerCase && hasDigit && hasSymbol) {
		return false;
	}

	return true;

}
bool validation_shedule(const char checkInputDeparture[]) {
	const char* places[] = { "SINGAPORE", "JOHOR", "KUANTAN", "PENANG", "KL", "MIRI", "KUCHING", "IPOH", "PERLIS", "PERAK" };
	const char* abbreviations[] = { "SGP", "JHR", "KTN", "PNG", "KL", "MIRI", "KCH", "IPH", "PER", "PK" };


	for (int i = 0; i < 10; i++) {
		if (strcmp(checkInputDeparture, places[i]) == 0 || strcmp(checkInputDeparture, abbreviations[i]) == 0) {

			return false;
		}
	}


	return true;
}
void reloadmoney() {
	FILE* fptr;
	struct storeAccount accounts[100];
	int index = 0, choiceMethod;
	char checkUsername[20], checkAccountNumber[20];
	double addAmount;
	char qrCode[HEIGHT][WIDTH];
	int pass = 0;

	fptr = fopen("account.bin", "rb+");
	if (fptr == NULL) {
		printf("Error opening file\n");
		exit(-1);
	}

	while (fread(&accounts[index], sizeof(struct storeAccount), 1, fptr) == 1) {
		index++;
	}
	fclose(fptr);
	fseek(fptr, 0, SEEK_SET);
	printf("\n");
	printf("=========================================================================\n");
	printf("\tRELOAD MONEY\n");
	printf("=========================================================================\n\n");
	do {


		printf("Enter your Account Passwords (6 length):\n");
		printf("Masukkan Akaun Kata laluan Anda: ");
		scanf(" %[^\n]", checkAccountNumber);
		printf("\n");

		while (validation_AccountNumber(checkAccountNumber)) {
			printf("Enter your Account Passwords (6 length):\n");
			printf("Masukkan Akaun Kata laluan Anda: ");
			rewind(stdin);
			scanf(" %[^\n]", checkAccountNumber);

			checkCondition(checkAccountNumber);
		}
		for (int i = 0;i < index;i++) {
			if (strcmp(checkAccountNumber, accounts[i].accountNumber) == 0) {
				pass = i;
			}
		}
		printf("\n");
		printf("Account found.");
		printf("Akaun ditemui.\n");
		printf("Username | Nama Pengguna: %s\n", accounts[pass].username);
		printf("Account Number | Nombor Akaun: %s\n", accounts[pass].accountNumber);
		printf("Current Balance | Baki Semasa: %.2lf\n", accounts[pass].amount);

		printf("\nMethod of Transaction\n");
		printf("1. Debit Card | Kad Debit\n");
		printf("2. Credit Card | Kad Kredit\n");
		printf("3. TOUCH GO | TOUCH GO\n");
		printf("Enter your choice:\n");
		printf("Masukkan pilihan anda: ");
		scanf("%d", &choiceMethod);

		while (choiceMethod != 1 && choiceMethod != 2 && choiceMethod != 3) {
			printf("Invalid choice. Enter 1 for Debit Card and 2 for Credit Card:\n");
			printf("Enter your choice: ");
			scanf(" %d", &choiceMethod);
		}

		switch (choiceMethod) {
		case 1:
			strcpy(accounts[pass].payingMethod, "Debit Card");
			printf("Enter your PIN for Debit Card (4 digits): ");
			scanf(" %d", &accounts[pass].PINdebitcard);

			while (accounts[pass].PINdebitcard < 1000 || accounts[pass].PINdebitcard > 9999) {
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
				printf("Invalid PIN. Please enter a 4-digit numeric PIN:\n");
				printf("Enter your PIN for Debit Card (4 digits): ");
				rewind(stdin);
				scanf(" %d", &accounts[pass].PINdebitcard);
			}
			break;

		case 2:
			strcpy(accounts[pass].payingMethod, "Credit Card");
			printf("Enter your PIN for Credit Card (4 digits): ");
			scanf(" %d", &accounts[pass].PINcreditcard);
			while (accounts[pass].PINcreditcard < 1000 || accounts[pass].PINcreditcard > 9999) {
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
				printf("Invalid PIN. Please enter a 4-digit numeric PIN:\n");
				printf("Enter your PIN for Credit Card (4 digits): ");
				rewind(stdin);
				scanf(" %d", &accounts[pass].PINcreditcard);
			}

			break;
		case 3:
			strcpy(accounts[pass].payingMethod, "TOUCH GO");
			for (int y = 0; y < HEIGHT; y++) {
				for (int x = 0; x < WIDTH; x++) {
					qrCode[y][x] = ' ';
				}
			}
			encodeText(qrCode, TEXT);
			printf("\nTOUCH'S GO QR Code:\n");
			drawQRCode(qrCode);

			break;
		default:
			printf("Invalid input\n");
			break;
		}

		printf("\n");

		printf("Reload amount: ");
		scanf(" %lf", &addAmount);

		while (addAmount <= 0 || addAmount > 1000) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Error:The Amount should between 0 to 1000.\n");
			printf("Reload amount: ");
			scanf(" %lf", &addAmount);
		}
		printf("\n");
		accounts[pass].amount += addAmount;
		printf("Reload successful.\n");
		printf("New Balance: %.2lf\n", accounts[pass].amount);

		fptr = fopen("account.bin", "rb+");
		if (fptr == NULL) {
			printf("Error opening file\n");
			exit(-1);
		}

		fseek(fptr, pass * sizeof(struct storeAccount), SEEK_SET);
		fwrite(&accounts[pass], sizeof(struct storeAccount), 1, fptr);

		fclose(fptr);

		if (!checkDuplicateAccount(checkAccountNumber)) {
			printf("Account not found.\n");
		}
	} while (!checkDuplicateAccount(checkAccountNumber));
}
void createAccount() {
	FILE* fptr;
	struct storeAccount accounts;
	int index2 = 0;

	fptr = fopen("account.bin", "ab+");
	if (fptr == NULL) {
		printf("Error opening file\n");
		exit(-1);
	}

	while (fread(&accounts, sizeof(struct storeAccount), 1, fptr) != 0) {
		index2++;
	}
	printf("==== Account Wallet Creation System ====\n\n");
	printf("Enter your username to create an Account Wallet:\n");
	printf("Masukkan nama pengguna anda untuk mencipta Dompet Akaun: ");
	scanf(" %[^\n]", accounts.username);


	printf("\nEnter your Account Password(6 digit) to create an Account Wallet:\n");
	printf("Masukkan Kata Laluan Akaun (6 digit) anda untuk mencipta Dompet Akaun: ");
	scanf(" %[^\n]", accounts.accountNumber);

	while (validation_AccountNumber(accounts.accountNumber)) {
		printf("\nEnter your Account Password(6 digit) to create an Account Wallet:\n");
		printf("Masukkan Kata Laluan akaun anda untuk mencipta Dompet Akaun: ");
		rewind(stdin);
		scanf(" %[^\n]", accounts.accountNumber);

		checkCondition(accounts.accountNumber);
	}

	if (index2 > 0) {
		while (checkDuplicateAccount(accounts.accountNumber)) {
			printf("\nAccount Password %s already exists. Please choose a different Account Password.\n", accounts.accountNumber);
			printf("Kata Laluan Akaun %s sudah wujud. Sila pilih Kata Laluan Akaun yang berbeza.\n", accounts.accountNumber);
			printf("\nEnter your Account Password(6 digit) to create an Account Wallet:\n");
			printf("Masukkan Kata Laluan Akaun (6 digit) anda untuk mencipta Dompet Akaun: ");
			scanf(" %[^\n]", accounts.accountNumber);

			while (validation_AccountNumber(accounts.accountNumber)) {
				printf("\nEnter your Account Password(6 digit) to create an Account Wallet:\n");
				printf("Masukkan Kata Laluan Akaun (6 digit) anda untuk mencipta Dompet Akaun: ");
				rewind(stdin);
				scanf(" %[^\n]", accounts.accountNumber);

				checkCondition(accounts.accountNumber);
			}
		}

	}

	accounts.amount = 0.00;

	fwrite(&accounts, sizeof(struct storeAccount), 1, fptr);
	fclose(fptr);

	printf("\nWelcome, %s! Your account has been created.\n\n", accounts.username);
	printf("\nSelamat datang, %s! Akaun anda telah dicipta.\n\n", accounts.username);

	reloadmoney();
}
void viewBookingwithusername(char passUsername[50]) {
	FILE* fptr;
	struct Booking BK[30];
	Seat seat[20];
	int count = 0, storeCount[10] = { 0 }, count1 = 0, pass = 0, index = 0;
	char passSeat[21], Booking_id[20], passBooking[20];
	fptr = fopen("BookingHistory.txt", "r");

	if (fptr == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}


	printf("==========================================================================================================\n");
	printf("%55s\n", "View Booking History");
	printf("==========================================================================================================\n");
	printf("%-13s %-13s %-13s %-12s %-16s %-15s %-15s\n", "Booking ID", "Username", "Booking DATE", "Payment", "Payment Method", "Booking TripNo", "Number of Tickets");
	printf("------------- ------------ ------------  ------------ ---------------- -------------- ------------------\n");


	while (fscanf(fptr, "%9s | %10s | %d-%d-%*d | %lf | %19[^|] | %9s | %d\n",
		BK[count1].bookingID,
		&BK[count1].username,
		&BK[count1].day,
		&BK[count1].month,
		&BK[count1].payment,
		BK[count1].paymentMethod,
		BK[count1].trip_no,
		&BK[count1].numberOfTickets) == 8) {
		if (strcmp(passUsername, BK[count1].username) == 0) {
			printf("%-13s %-13s %02d-%02d-2024   RM%9.2lf   %-20s      %-15s %6d\n", BK[count1].bookingID, BK[count1].username, BK[count1].day, BK[count1].month, BK[count1].payment, BK[count1].paymentMethod, BK[count1].trip_no, BK[count1].numberOfTickets);

			strcpy(passBooking, BK[count1].bookingID);

			storeCount[count] = count1;
			count++;

		}


		count1++;

	}
	printf("==========================================================================================================\n");
	fclose(fptr);




	if (count > 1) {
		int found = 0;
		printf("Enter the which Booking ID to view the Seat: ");
		scanf(" %[^\n]", Booking_id);
		for (int i = 0;i < strlen(Booking_id);i++) {

			Booking_id[i] = toupper(Booking_id[i]);
		}

		for (int i = 0;i < count;i++) {
			if (strcmp(Booking_id, BK[storeCount[i]].bookingID) == 0) {
				found = 0;
				pass = storeCount[i];

				break;
			}
			else if (strcmp(Booking_id, BK[storeCount[i]].bookingID) != 0) {
				found = 1;
			}
		}

		if (found) {
			printf("Invalid Booking ID\n");
			rewind(stdin);
			for (int i = 0;i < count;i++) {
				printf("%s ", BK[storeCount[i]].bookingID);
			}
			printf("\n");
			printf("Enter the which Booking ID to view the Seat: ");
			scanf(" %[^\n]", Booking_id);
			for (int i = 0;i < strlen(Booking_id);i++) {

				Booking_id[i] = toupper(Booking_id[i]);
			}
		}

		fptr = fopen("Seatfile.txt", "r");
		while (fscanf(fptr, "%[^|]|%19[^|]|%d|%d|%d|%lf|%[^|]|%[^|]|%[^|]|%[^\n]\n", seat[index].trip,
			seat[index].seatTypes, &seat[index].seatAvailable,
			&seat[index].numberofNORMAL, &seat[index].numberofOKU,
			&seat[index].price, seat[index].storeTrainID, seat[index].storeBookingID,
			seat[index].storeSeat, seat[index].storeSeat1) == 10) {


			index++;
		}
		fclose(fptr);

		printf("Booking ID: %s\n", Booking_id);
		printf("Display Seat: \n");
		for (int i = 0;i < 5;i++) {
			printf("%c ", seat[pass].storeSeat[i]);

		}
		printf("\n");
		for (int i = 0;i < 15;i++) {
			printf("%c ", seat[pass].storeSeat1[i]);
			if ((1 + i) % 5 == 0) {
				printf("\n");
			}
		}
		printf("\n");


	}

	else {
		fptr = fopen("Seatfile.txt", "r");
		while (fscanf(fptr, "%[^|]|%19[^|]|%d|%d|%d|%lf|%[^|]|%[^|]|%[^|]|%[^\n]\n", seat[index].trip,
			seat[index].seatTypes, &seat[index].seatAvailable,
			&seat[index].numberofNORMAL, &seat[index].numberofOKU,
			&seat[index].price, seat[index].storeTrainID, seat[index].storeBookingID,
			seat[index].storeSeat, seat[index].storeSeat1) == 10) {

			if (strcmp(seat[index].storeBookingID, passBooking) == 0) {

				printf("Booking ID: %s\n", passBooking);
				printf("Display Seat: \n");
				for (int i = 0;i < 5;i++) {
					printf("%c ", seat[index].storeSeat[i]);

				}
				printf("\n");
				for (int i = 0;i < 15;i++) {
					printf("%c ", seat[index].storeSeat1[i]);
					if ((1 + i) % 5 == 0) {
						printf("\n");
					}
				}
				printf("\n");
			}
			index++;
		}

		fclose(fptr);
	}


}
void Bookingfunction(char username[50]) {
	SYSTEMTIME t;
	GetLocalTime(&t);
	char inputDeparture[30], checkInputDeparture[30];
	int  day, month, passIndex = 0, sAvailable = 0, pass = 0, storeIndex[20], j = 0, passIndexSchedule = 0, pass1 = 0;
	char confirm, passbookingID[20], ansConfirm;
	int count = 0, count1 = 0, choice1, choiceMethod, indexPayment = 0, bookingNumber = 1;
	float cprPrice = 0.00;
	char qrCode[HEIGHT][WIDTH];
	FILE* filePointer;
	FILE* fPtr;
	struct Booking BK;
	BK.payment = 0.00;
	TrainSchedule s[100];
	Seat seat[30];
	struct storeAccount accounts[20];
	const char* places[] = { "SINGAPORE", "JOHOR", "KUANTAN", "PENANG", "KL", "MIRI", "KUCHING", "IPOH", "PERLIS","PERAK" };
	const char* abbreviations[] = { "SGP", "JHR", "KTN", "PNG", "KL", "MIRI", "KCH", "IPH", "PER","PK" };

	trainSchedule();
	while (generateBKnumber(bookingNumber)) {

		bookingNumber++;
	}

	do {
		printf("Enter the day you want to book:\n");
		printf("Masukkan hari yang anda ingin tempah: ");
		scanf(" %d", &day);
		while (day <= 0 || day > 31) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Error: Day should be between 1 and 31.\n");
			printf("Ralat: Hari perlu antara 1 hingga 31.\n");
			printf("Enter the day you want to book:\n");
			printf("Masukkan hari yang anda ingin tempah: ");
			scanf(" %d", &day);
		}

		printf("Enter the month you want to book:\n");
		printf("Masukkan bulan yang anda ingin tempah: ");
		scanf(" %d", &month);
		while (month <= 0 || month > 12) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Error: Month should be between 1 and 12.\n");

			printf("Enter the Month you want to book: ");
			scanf(" %d", &month);
		}

		printf("+---------------------------+--------------+\n");
		printf("| Departure Place           | Abbreviation |\n");
		printf("| Tempat Berlepas           | Singkatan    |\n");
		printf("+---------------------------+--------------+\n");
		for (int i = 0; i < 10; i++) {
			printf("| %-25s | %-12s |\n", places[i], abbreviations[i]);
			printf("+---------------------------+--------------+\n");
		}

		printf("Enter your Departure Place:\n");
		printf("Masukkan Tempat Berlepas anda: ");
		scanf(" %[^\n]", inputDeparture);

		for (int i = 0; inputDeparture[i] != '\0'; i++) {
			inputDeparture[i] = toupper(inputDeparture[i]);
		}

		while (validation_shedule(inputDeparture)) {
			printf("Error:Input Departure Place\n");
			printf("Ralat: Input Tempat Berlepas\n");
			printf("+---------------------------+--------------+\n");
			printf("| Departure Place           | Abbreviation |\n");
			printf("| Tempat Berlepas           | Singkatan    |\n");
			printf("+---------------------------+--------------+\n");

			for (int i = 0; i < 10; i++) {
				printf("| %-25s | %-12s |\n", places[i], abbreviations[i]);
				printf("+---------------------------+--------------+\n");
			}
			rewind(stdin);
			printf("Enter the Departure Place you want to book:\n");
			printf("Masukkan Tempat Berlepas anda: ");
			scanf(" %[^\n]", inputDeparture);

			for (int i = 0; inputDeparture[i] != '\0'; i++) {
				inputDeparture[i] = toupper(inputDeparture[i]);
			}
		}
		if (!checkSchedule(inputDeparture, day, month)) {
			printf("No matching schedule found for the specified date and destination.\n");
			printf("Tiada jadual yang sepadan ditemui untuk tarikh dan destinasi yang dinyatakan.\n");
		}

	} while (!checkSchedule(inputDeparture, day, month));

	//CHECK SCHEDULE IF SEAT AVAILABLE 0 SELECTED BY MEMBER THEN RETIRN TO BOOKING
	fPtr = fopen("trainSchedule.txt", "r");
	while (fscanf(fPtr, "%3s|%9[^|]|%9[^|]|%*d-%d-%d|%4s|%4s|%3s|%d|%f\n", s[count].tripNo, s[count].departure, s[count].arrival,
		&s[count].month, &s[count].day, s[count].dTime, s[count].aTime, s[count].trainID, &s[count].seats, &s[count].price) == 10) {

		if (strcmp(inputDeparture, s[count].departure) == 0 && month == s[count].month && day == s[count].day) {
			if (s[count].seats < 0) {
				printf("Not seat Available\n");
				Bookingfunction(username);
			}
		}

		count++;
	}
	fclose(fPtr);


	sprintf(BK.bookingID, "B%03d", bookingNumber);

	for (int i = 0; i < count; i++) {

		if (s[count1].day == day &&
			s[count1].month == month &&
			strcmp(inputDeparture, s[count1].departure) == 0) {


			printf("====================================\n");
			printf("         Matching Trips              \n");
			printf("====================================\n");
			printf("Booking %d:\n", i + 1);
			printf("   Trip Number:     %-15s\n", s[count1].tripNo);
			printf("   Departure:       %-31s\n", s[count1].departure);
			printf("   Arrival:         %-31s\n", s[count1].arrival);
			printf("   Departure Time:  %-8s\n", s[count1].dTime);
			printf("   Arrival Time:    %-8s\n", s[count1].aTime);
			printf("   Train ID:        %-15s\n", s[count1].trainID);
			printf("   Seats Available: %02d\n", s[count1].seats);
			printf("   Price:           RM%.2lf\n", s[count1].price);
			printf("------------------------------------\n");
			printf("\n");
			printf("=====================================\n");
			printf("Perjalanan Padanan \n");
			printf("=====================================\n");
			printf("Tempahan %d:\n", i + 1);
			printf("Nombor Perjalanan: %-15s\n", s[count1].tripNo);
			printf("Berlepas: %-31s\n", s[count1].departure);
			printf("Ketibaan: %-31s\n", s[count1].arrival);
			printf("Masa Berlepas: %-8s\n", s[count1].dTime);
			printf("Masa Ketibaan: %-8s\n", s[count1].aTime);
			printf("ID Kereta Api: %-15s\n", s[count1].trainID);
			printf("Kerusi Tersedia: %02d\n", s[count1].seats);
			printf("Harga: RM%.2lf\n", s[count1].price);
			printf("------------------------------------------------\n");
			pass1 = count1;
		}
		count1++;
	}

	printf("Confirm your trip (Y/N):\n");
	printf("Sahkan tempahan anda (Y/T): ");
	scanf(" %c", &ansConfirm);
	while (toupper(ansConfirm) != 'Y' && toupper(ansConfirm) != 'N' && ansConfirm != 1 && toupper(ansConfirm) == 'T') {
		printf("Invalid input\n");
		printf("Confirm your trip (Y/N):\n");
		printf("Sahkan tempahan anda (Y/T): ");
		rewind(stdin);
		scanf(" %c", &ansConfirm);
	}

	if (toupper(ansConfirm) == 'Y') {

		SeatFunction(s[pass1].seats, s[pass1].trainID, BK.bookingID, s[pass1].tripNo, BK.username);

		int index1 = 0, passIndex1 = 0;
		fPtr = fopen("Seatfile.txt", "r");
		if (fPtr == NULL) {
			printf("Error opening file.\n");
			exit(-1);
		}

		while (fscanf(fPtr, "%[^|]|%19[^|]|%d|%d|%d|%lf|%[^|]|%[^|]|%[^|]|%[^\n]\n", seat[index1].trip,
			seat[index1].seatTypes, &seat[index1].seatAvailable,
			&seat[index1].numberofNORMAL, &seat[index1].numberofOKU,
			&seat[index1].price, seat[index1].storeTrainID, seat[index1].storeBookingID,
			seat[index1].storeSeat, seat[index1].storeSeat1) == 10) {

			if (strcmp(seat[index1].storeBookingID, BK.bookingID) == 0) {
				passIndex1 = index1;
			}
			index1++;
		}
		strcpy(BK.passTrainID, seat[passIndex1].storeTrainID);
		BK.passSeatavailable = seat[passIndex1].seatAvailable;
		BK.day = t.wDay;
		BK.month = t.wMonth;
		strcpy(BK.trip_no, s[pass1].tripNo);
		BK.numberOfTickets = seat[passIndex1].numberofNORMAL + seat[passIndex1].numberofOKU;
		BK.payment = seat[passIndex1].price + s[pass1].price;

		char  accountNumber[20], ansAccount;
		double reloadMoney;
		int choice5, index = 0;

		printf("\nSelect Payment Method\n");
		printf(" 1.Cash Payments\n");
		printf(" 2.Digital Payment\n");
		printf(" 3.Account Wallet\n");
		printf("Enter your choose:\n");
		printf("\n");
		printf("Pilih Kaedah Pembayaran\n");
		printf(" 1.Pembayaran Tunai Bayaran\n");
		printf(" 2.Digital\n");
		printf(" 3.Dompet Akaun\n");
		printf("Tekan pilihan anda:");
		scanf("%d", &choiceMethod);
		while (choiceMethod != 1 && choiceMethod != 2 && choiceMethod != 3) {
			printf("Enter your choose:");
			rewind(stdin);
			scanf("%d", &choiceMethod);
		}
		printf("\n");
		printf("Booking Code: %s\n", BK.bookingID);
		printf("Date: %02d-%02d-2024\n", BK.day, BK.month);
		printf("This is your Trip No > %s\n", BK.trip_no);

		switch (choiceMethod) {
		case 1:
			strcpy(BK.paymentMethod, "Cash Payments");
			printf("Your Trip Price: RM%.2lf\n\n", BK.payment);
			break;
		case 2:
			strcpy(BK.paymentMethod, "Digital Payment");
			printf("Your Trip Price: RM%.2lf\n\n", BK.payment);
			for (int y = 0; y < HEIGHT; y++) {
				for (int x = 0; x < WIDTH; x++) {
					qrCode[y][x] = ' ';
				}
			}
			encodeText(qrCode, TEXT);
			printf("\nTOUCH'S GO QR Code:\n");
			drawQRCode(qrCode);
			break;
		case 3:
			strcpy(BK.paymentMethod, "Account Wallet");
			printf("Your Trip Price: %.2lf\n", BK.payment);
			printf("Do you have exist Account(Y or N):");
			scanf(" %c", &ansAccount);
			while (toupper(ansAccount) != 'Y' && toupper(ansAccount) != 'N' && ansAccount != 1 && toupper(ansAccount) != 'T') {
				rewind(stdin);
				printf("Invalid input\n");
				printf("Do you have exist Account(Y/N):\n");
				printf("Adakah anda mempunyai Akaun wujud(Y/T)");
				scanf(" %c", &ansAccount);
			}
			if (toupper(ansAccount) == 'N' || toupper(ansAccount) == 'T') {
				struct storeAccount accounts;
				int index2 = 0;

				fPtr = fopen("account.bin", "ab+");
				if (fPtr == NULL) {
					printf("Error opening file\n");
					exit(-1);
				}

				while (fread(&accounts, sizeof(struct storeAccount), 1, fPtr) != 0) {
					index2++;
				}
				printf("==== Account Wallet Creation System ====\n\n");
				printf("Enter your username to create an Account Wallet:\n");
				printf("Masukkan nama pengguna anda untuk mencipta Dompet Akaun: ");
				scanf(" %[^\n]", accounts.username);


				printf("\nEnter your Account Password (6 length) to create an Account Wallet:\n");
				printf("Masukkan Kata Laluan Akaun anda untuk mencipta Dompet Akaun: ");
				scanf(" %[^\n]", accounts.accountNumber);

				while (validation_AccountNumber(accounts.accountNumber)) {
					printf("\nEnter your Account Password (6 length) to create an Account Wallet:\n");
					printf("Masukkan Kata Laluan akaun anda untuk mencipta Dompet Akaun: ");
					rewind(stdin);
					scanf(" %[^\n]", accounts.accountNumber);

					checkCondition(accounts.accountNumber);
				}

				if (index2 > 0) {
					while (checkDuplicateAccount(accounts.accountNumber)) {
						printf("\nAccount Password %s already exists. Please choose a different Account Password.\n", accounts.accountNumber);
						printf("Kata Laluan Akaun %s sudah wujud. Sila pilih Kata Laluan Akaun yang berbeza.\n", accounts.accountNumber);
						printf("\nEnter your Account Password (6 length) to create an Account Wallet:\n");
						printf("Masukkan Kata Laluan Akaun anda untuk mencipta Dompet Akaun: ");
						scanf(" %[^\n]", accounts.accountNumber);

						while (validation_AccountNumber(accounts.accountNumber)) {
							printf("\nEnter your Account Password (6 length) to create an Account Wallet:\n");
							printf("Masukkan Kata Laluan Akaun anda untuk mencipta Dompet Akaun: ");
							rewind(stdin);
							scanf(" %[^\n]", accounts.accountNumber);

							checkCondition(accounts.accountNumber);
						}
					}

				}

				accounts.amount = 0.00;

				fwrite(&accounts, sizeof(struct storeAccount), 1, fPtr);
				fclose(fPtr);

				printf("\nWelcome, %s! Your account has been created.\n\n", accounts.username);
				printf("\nSelamat datang, %s! Akaun anda telah dicipta.\n\n", accounts.username);

			}

			fPtr = fopen("account.bin", "rb");
			while (fread(&accounts[index], sizeof(struct storeAccount), 1, fPtr) == 1) {
				index++;
			}
			fclose(fPtr);

			printf("\n");

			printf("=========================================================================\n");
			printf("\tRELOAD MONEY\n");
			printf("=========================================================================\n\n");
			printf("Please enter your Account Passwords to approve your payment: ");
			scanf(" %[^\n]", accountNumber);

			while (validation_AccountNumber(accountNumber)) {
				printf("Enter your Account Passwords (6 length): ");
				rewind(stdin);
				scanf(" %[^\n]", accountNumber);

				checkCondition(accountNumber);
			}

			while (!checkDuplicateAccount(accountNumber)) {
				printf("Account not found\n");
				printf("Please enter your Account Passwords to approve your payment: ");
				rewind(stdin);
				scanf(" %[^\n]", accountNumber);


				while (validation_AccountNumber(accountNumber)) {
					printf("Enter your Account passwords (6 length): ");
					rewind(stdin);
					scanf(" %[^\n]", accountNumber);

					checkCondition(accountNumber);
				}
			}

			for (int i = 0;i < index;i++) {
				if (strcmp(accountNumber, accounts[i].accountNumber) == 0) {
					printf("Username Wallet: %s\n", accounts[i].username);
					printf("Acount Paawords wallet: %s\n", accountNumber);
					printf("Available Balance:%.2lf\n", accounts[i].amount);

					if (accounts[i].amount < BK.payment) {
						printf("Your Available balance is not enough to Pay the payment.Owe RM%.2lf\n", BK.payment - accounts[i].amount);
						printf("Reload!!!\n");
						printf("\nMethod of Transaction\n");
						printf("1. Debit Card\n");
						printf("2. Credit Card\n");
						printf("3. TOUCH GO\n");
						printf("Enter your choice: ");
						scanf(" %d", &choice5);
						while (choice5 != 1 && choice5 != 2 && choice5 != 3) {
							printf("Invalid choice. Enter 1 for Debit Card and 2 for Credit Card:\n");
							printf("Enter your choice: ");
							scanf(" %d", &choice5);
						}

						switch (choice5) {
						case 1:
							strcpy(accounts[i].payingMethod, "Debit Card");
							printf("Enter your PIN for Debit Card (4 digits): ");
							scanf(" %d", &accounts[i].PINdebitcard);

							while (accounts[i].PINdebitcard < 1000 || accounts[i].PINdebitcard > 9999) {
								int c;
								while ((c = getchar()) != '\n' && c != EOF);
								printf("Invalid PIN. Please enter a 4-digit numeric PIN:\n");
								printf("Enter your PIN for Debit Card (4 digits): ");
								rewind(stdin);
								scanf(" %d", &accounts[i].PINdebitcard);
							}
							break;

						case 2:
							strcpy(accounts[i].payingMethod, "Credit Card");
							printf("Enter your PIN for Credit Card (4 digits): ");
							scanf(" %d", &accounts[i].PINcreditcard);
							while (accounts[i].PINcreditcard < 1000 || accounts[i].PINcreditcard > 9999) {
								int c;
								while ((c = getchar()) != '\n' && c != EOF);
								printf("Invalid PIN. Please enter a 4-digit numeric PIN:\n");
								printf("Enter your PIN for Credit Card (4 digits): ");
								rewind(stdin);
								scanf(" %d", &accounts[i].PINcreditcard);
							}

							break;
						case 3:
							strcpy(accounts[pass].payingMethod, "TOUCH GO");
							for (int y = 0; y < HEIGHT; y++) {
								for (int x = 0; x < WIDTH; x++) {
									qrCode[y][x] = ' ';
								}
							}
							encodeText(qrCode, TEXT);
							printf("\nTOUCH'S GO QR Code:\n");
							drawQRCode(qrCode);
							break;
						default:
							printf("Invalid input\n");
							break;
						}
						printf("Enter the amount:");
						scanf(" %lf", &reloadMoney);
						while (reloadMoney <= 0 || reloadMoney > 1000) {
							printf("Invalid Input\n");
							int c;
							while ((c = getchar()) != '\n' && c != EOF);
							printf("Error:The Amount should between 0 to 1000.\n");
							printf("Reload amount: ");
							scanf(" %lf", &reloadMoney);
						}
						accounts[i].amount += reloadMoney;

					}
					printf("\n");
					accounts[i].amount -= BK.payment;
					//IF AFTER RELOAD STILL NOT ENOUGH
					while (accounts[i].amount < 0) {
						printf("Your amount not enough.Owe RM%.2lf\n", accounts[i].amount);
						printf("Enter the amount:");
						scanf(" %lf", &reloadMoney);
						while (reloadMoney <= 0 || reloadMoney > 1000) {
							printf("Invalid Input\n");
							int c;
							while ((c = getchar()) != '\n' && c != EOF);
							printf("Error:The Amount should between 0 to 1000.\n");
							printf("Reload amount: ");
							scanf(" %lf", &reloadMoney);
						}
						accounts[i].amount += reloadMoney;
					}

					printf("Your Wallet be minus %.2lf\n\n", BK.payment);
					printf("Current Balance:%.2lf\n", accounts[i].amount);
					printf("The system auto pay your payment\n.");

					fPtr = fopen("account.bin", "rb+");
					fseek(fPtr, i * sizeof(struct storeAccount), SEEK_SET);
					fwrite(&accounts[i], sizeof(struct storeAccount), 1, fPtr);
					fclose(fPtr);
				}
			}

			break;

		default:
			printf("Invalid choice. Please enter 1 or 2.\n");
			break;
		}
		printf("Payment Successful...\n");
		strcpy(BK.username, username);
		filePointer = fopen("BookingHistory.txt", "a");
		fprintf(filePointer, "%-12s | %10s | %02d-%02d-2024 | %-6.2lf | %-20s | %-6s | %d\n", BK.bookingID, BK.username, BK.day, BK.month, BK.payment, BK.paymentMethod, BK.trip_no, BK.numberOfTickets);

		fclose(filePointer);

		generateNew(BK.passSeatavailable, BK.passTrainID, BK.trip_no);

	}


	else {
		Bookingfunction(username);
	}

}
void cancellation(char username1[50]) {
	struct Booking BK[30];
	FILE* fptr;
	int count = 0, Pcount = 0, count1 = 0, storeCount[20] = { 0 }, found = 0, pass = 0, i = 0;
	char ansCancel, bookingID[20];
	system("cls");
	fptr = fopen("BookingHistory.txt", "r");
	while (fscanf(fptr, "%9s | %10s | %d-%d-%*d | %lf | %19[^|] | %9s | %d\n",
		BK[count].bookingID,
		&BK[count].username,
		&BK[count].day,
		&BK[count].month,
		&BK[count].payment,
		BK[count].paymentMethod,
		BK[count].trip_no,
		&BK[count].numberOfTickets) == 8) {
		if (strcmp(username1, BK[count].username) == 0) {
			printf("=====================================\n");
			printf("           Current Details           \n");
			printf("=====================================\n");
			printf("Booking ID:        %s\n", BK[count].bookingID);
			printf("Username:          %s\n", BK[count].username);
			printf("Trip Number:       %s\n", BK[count].trip_no);
			printf("Number of Tickets: %d\n", BK[count].numberOfTickets);
			printf("Booking Date:      %02d-%02d-2024\n", BK[count].day, BK[count].month);
			printf("Price:             RM%.2lf\n", BK[count].payment);
			printf("Payment Method:    %s\n", BK[count].paymentMethod);
			printf("=====================================\n");
			printf("\n");


			storeCount[count1] = count;
			count1++;

		}

		count++;
	}
	fclose(fptr);


	if (count1 > 1) {
		int found = 0;
		printf("Enter which Booking you want to cancel:");
		scanf(" %[^\n]", bookingID);

		for (int i = 0;i < 10;i++) {
			bookingID[i] = toupper(bookingID[i]);
		}

		for (int i = 0;i < count1;i++) {
			if (strcmp(bookingID, BK[storeCount[i]].bookingID) == 0) {
				found = 0;
				pass = storeCount[i];

				break;
			}
			else if (strcmp(bookingID, BK[storeCount[i]].bookingID) != 0) {
				found = 1;
			}
		}

		if (found) {
			printf("Invalid Booking ID\n");
			rewind(stdin);
			for (int i = 0;i < count1;i++) {
				printf("%s ", BK[storeCount[i]].bookingID);
			}
			printf("Enter which Booking you want to cancel:");
			scanf(" %[^\n]", bookingID);

			for (int i = 0;i < 10;i++) {
				bookingID[i] = toupper(bookingID[i]);
			}
		}

		printf("Confirm to cancel the Booking:");
		scanf(" %c", &ansCancel);
		printf("Cancel successful!!!\n");
		printf("\n");
		refundFunction(BK[pass].bookingID);

		for (int j = pass; j < count - 1; j++) {
			BK[j] = BK[j + 1];
		}
		count--;

		fptr = fopen("BookingHistory.txt", "w");
		if (fptr == NULL) {
			printf("Error opening file for writing.\n");
			exit(-1);
		}

		for (int i = 0; i < count; i++) {
			fprintf(fptr, "%-12s | %10s | %02d-%02d-2024 | %-6.2lf | %-20s | %-6s | %d\n",
				BK[i].bookingID, BK[i].username, BK[i].day, BK[i].month,
				BK[i].payment, BK[i].paymentMethod,
				BK[i].trip_no, BK[i].numberOfTickets);
		}

		fclose(fptr);
	}

	else {

		printf("Confirm to cancel the Booking:");
		scanf(" %c", &ansCancel);

		for (int i = 0;i < count;i++) {
			if (strcmp(bookingID, BK[i].bookingID) == 0) {
				Pcount = i;
			}
		}

		if (toupper(ansCancel) == 'Y') {

			printf("Cancel successful!!!\n");
			printf("\n");
			refundFunction(BK[Pcount].bookingID);

			for (int j = Pcount; j < count - 1; j++) {
				BK[j] = BK[j + 1];
			}
			count--;

			fptr = fopen("BookingHistory.txt", "w");
			if (fptr == NULL) {
				printf("Error opening file for writing.\n");
				exit(-1);
			}

			for (int i = 0; i < count; i++) {
				fprintf(fptr, "%-12s | %10s | %02d-%02d-2024 | %-6.2lf | %-20s | %-6s | %d\n",
					BK[i].bookingID, BK[i].username, BK[i].day, BK[i].month,
					BK[i].payment, BK[i].paymentMethod,
					BK[i].trip_no, BK[i].numberOfTickets);
			}

			fclose(fptr);
		}

	}

	system("pause");
	system("cls");
}

void bookingInfoMenu() {
	char username[20] = "M001";
	int choice = 0;
	system("cls");

	while (1) {
		printf("=========================================================================\n");
		printf("\tTICKET BOOKING INFORMATION MODULE\n");
		printf("\tMODUL MAKLUMAT TEMPAHAN TIKET\n");
		printf("=========================================================================\n\n");

		printf("1. View all booking information\n");
		printf("2. Search particular booking information\n");
		printf("3. Edit booking information\n");
		printf("4. Delete booking information\n");
		printf("Please enter your choice (-1 to exit)\n\n");

		printf("1. Memaparkan semua maklumat tempahan\n");
		printf("2. Mencari maklumat tempahan tertentu\n");
		printf("3. Pengubahan maklumat tempahan\n");
		printf("4. Memadamkan maklumat tempahan tiket\n");
		printf("Sila masukkan pilihan anda (-1 untuk keluar)\n>");
		scanf("%d", &choice);
		rewind(stdin);

		if (choice == 1) {
			viewBooking();
		}
		else if (choice == 2) {
			searchBookingfunction();
		}
		else if (choice == 3) {
			system("cls");
			modifybookingHistory();
		}
		else if (choice == 4) {
			deleteBookingFunction();
		}
		else if (choice == -1) {
			system("cls");
			break;
		}
		else {
			printf("=========================================================================\n");
			printf("\tChoice Invalid\n");
			printf("\tPilihan anda tidak sah\n");
			printf("=========================================================================\n");

		}
	}
}
void displayBOOKINGAvailable(char inputBooking[20]) {
	FILE* fPtr;
	struct Booking BK[20];
	int count = 0;
	fPtr = fopen("BookingHistory.txt", "r");
	if (fPtr == NULL) {
		printf("Error: Could not open the file.\n");
		exit(-1);
	}
	while (fscanf(fPtr, "%9s | %10s | %d-%d-%*d | %lf | %19[^|] | %9s | %d\n",
		BK[count].bookingID,
		&BK[count].username,
		&BK[count].day,
		&BK[count].month,
		&BK[count].payment,
		BK[count].paymentMethod,
		BK[count].trip_no,
		&BK[count].numberOfTickets) == 8) {


		count++;
	}
	printf("Booking Available:\n");
	printf("Tempahan Tersedia:\n");
	for (int i = 0;i < count;i++) {
		printf("%s, ", BK[i].bookingID);
		if ((i + 1) % 10 == 0) {
			printf("\n");
		}
	}
	printf("\n");
	fclose(fPtr);

}
void searchBookingfunction() {
	FILE* fptr;
	struct Booking BK[30];
	fptr = fopen("BookingHistory.txt", "r");
	int count = 0, passIndex = 0, i = 0, count1 = 0;
	char BookingID[20], ansSearch;

	fptr = fopen("BookingHistory.txt", "r");
	while (fscanf(fptr, "%9s | %10s | %d-%d-%*d | %lf | %19[^|] | %9s | %d\n",
		BK[count1].bookingID,
		&BK[count1].username,
		&BK[count1].day,
		&BK[count1].month,
		&BK[count1].payment,
		BK[count1].paymentMethod,
		BK[count1].trip_no,
		&BK[count1].numberOfTickets) == 8) {

		count1++;
	}
	fclose(fptr);
	printf("\n");
	do {
		system("cls");
		printf("==========================================================================================================\n");
		printf("%55s\n", "Booking History");
		printf("==========================================================================================================\n");
		printf("%-13s %-13s %-13s %-12s %-16s %-15s %-15s\n", "Booking ID", "Username", "Booking DATE", "Payment", "Payment Method", "Booking TripNo", "Number of Tickets");
		printf("------------- ------------ ------------  ------------ ---------------- -------------- ------------------\n");
		for (int i = 0;i < count1;i++) {
			printf("%-13s %-13s %02d-%02d-2024   RM%9.2lf   %-20s      %-15s %6d\n", BK[i].bookingID, BK[i].username, BK[i].day, BK[i].month, BK[i].payment, BK[i].paymentMethod, BK[i].trip_no, BK[i].numberOfTickets);
		}
		printf("==========================================================================================================\n");
		printf("\n");
		printf("Enter the Booking ID your want to Search:\n");
		printf("Masukkan ID Tempahan yang ingin anda cari:");
		scanf(" %[^\n]", BookingID);

		for (int i = 0;i < strlen(BookingID);i++) {
			BookingID[i] = toupper(BookingID[i]);
		}

		while (checkBookingID(BookingID)) {
			printf("Invalid Input\n");

			displayBOOKINGAvailable(BookingID);
			printf("Enter the Booking ID your want to Search:\n");
			printf("Masukkan ID Tempahan yang ingin anda cari:");
			rewind(stdin);
			scanf(" %[^\n]", BookingID);

			for (int i = 0;i < strlen(BookingID);i++) {
				BookingID[i] = toupper(BookingID[i]);
			}

		}
		for (int i = 0; i < count1; i++) {
			if (strcmp(BK[i].bookingID, BookingID) == 0) {
				passIndex = i;
				break;
			}
		}
		fclose(fptr);

		printf("==========================================================================================================\n");
		printf("%55s\n", "Search Booking History");
		printf("==========================================================================================================\n");
		printf("%-13s %-13s %-13s %-12s %-16s %-15s %-15s\n", "Booking ID", "Username", "Booking DATE", "Payment", "Payment Method", "Booking TripNo", "Number of Tickets");
		printf("------------- ------------ ------------  ------------ ---------------- -------------- ------------------\n");
		printf("%-13s %-13s %02d-%02d-2024   RM%9.2lf   %-20s      %-15s %6d\n", BK[passIndex].bookingID, BK[passIndex].username, BK[passIndex].day, BK[passIndex].month, BK[passIndex].payment, BK[passIndex].paymentMethod, BK[passIndex].trip_no, BK[passIndex].numberOfTickets);
		printf("------------- ------------ ------------  ------------ ---------------- -------------- ------------------\n");
		printf("Do you want Search Again (Y/N):\n");
		printf("Adakah anda ingin cari lagi (Y/T):");
		scanf(" %c", &ansSearch);
		while (toupper(ansSearch) != 'Y' && toupper(ansSearch) != 'N' && ansSearch != 1 && toupper(ansSearch) != 'T') {
			printf("Invalid input\n");
			printf("Do you want Search Again (Y/N):\n");
			printf("Adakah anda ingin cari lagi (Y/T):");
			rewind(stdin);
			scanf(" %c", &ansSearch);

		}

	} while (toupper(ansSearch) == 'Y');

	system("cls");
}

void modifybookingHistory() {
	FILE* fptr;
	int newDay, newMonth, newNumoftic, index = 0, newIndex = 0, count = 0, count1 = 0, newpayemntMethod;
	double newPrice;
	char newtripNo[30], matchBookingID[20];
	struct Booking BK[20];
	TrainSchedule s[20];
	char ansDay, confirmation, ansMonth, ansTripNo, ansNumoftic, anspaymentMethod, ansPrice;
	printf("%20s=========================================================================\n", "");
	printf("%40s\tMODIFY BOOKING\n", "");
	printf("%40s\tUBAH SUAI TEMPAHAN\n", "");
	printf("%20s=========================================================================\n\n", "");

	fptr = fopen("BookingHistory.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file.");
		exit(-1);
	}
	printf("%8s==========================================================================================================\n", "");
	printf("%60s\n", "Booking History");
	printf("%8s==========================================================================================================\n", "");
	printf("%8s%-13s %-13s %-13s %-12s %-16s %-15s %-15s\n", "", "Booking ID", "Username", "Booking DATE", "Payment", "Payment Method", "Booking TripNo", "Number of Tickets");
	printf("%8s------------- ------------ ------------  ------------ ---------------- -------------- ------------------\n", "");
	while (fscanf(fptr, "%9s | %10s | %d-%d-%*d | %lf | %19[^|] | %9s | %d\n",
		BK[index].bookingID,
		&BK[index].username,
		&BK[index].day,
		&BK[index].month,
		&BK[index].payment,
		BK[index].paymentMethod,
		BK[index].trip_no,
		&BK[index].numberOfTickets) == 8) {
		printf("%8s%-13s %-13s %02d-%02d-2024   RM%9.2lf   %-20s      %-15s %6d\n", "", BK[index].bookingID, BK[index].username, BK[index].day, BK[index].month, BK[index].payment, BK[index].paymentMethod, BK[index].trip_no, BK[index].numberOfTickets);

		index++;
	}
	fclose(fptr);
	printf("%8s==========================================================================================================\n", "");
	printf("\n");
	printf("Enter the which Booking ID you want to modify:\n");
	printf("Masukkan ID Tempahan yang ingin anda ubah:");
	scanf(" %[^\n]", matchBookingID);
	for (int i = 0;i < strlen(matchBookingID);i++) {
		matchBookingID[i] = toupper(matchBookingID[i]);
	}

	while (checkBookingID(matchBookingID)) {
		printf("Invalid Booking ID.\n");

		displayBOOKINGAvailable(matchBookingID);
		printf("Enter the which Booking ID you want to modify:\n");
		printf("Masukkan ID Tempahan yang ingin anda ubah:");
		scanf(" %[^\n]", matchBookingID);
		for (int i = 0;i < strlen(matchBookingID);i++) {
			matchBookingID[i] = toupper(matchBookingID[i]);
		}
	}




	for (int i = 0;i < index;i++) {

		if (strcmp(BK[i].bookingID, matchBookingID) == 0) {
			printf("=====================================\n");
			printf("           Current Details           \n");
			printf("=====================================\n");
			printf("Trip Number:       %s\n", BK[i].trip_no);
			printf("Number of Tickets: %d\n", BK[i].numberOfTickets);
			printf("Booking Date:      %02d-%02d-2024\n", BK[i].day, BK[i].month);
			printf("Price:             RM%.2lf\n", BK[i].payment);
			printf("Payment Method:    %s\n", BK[i].paymentMethod);
			printf("=====================================\n");
			newIndex = i;

		}
	}
	printf("\n");
	printf("Confirm to Modify (Y/N):\n");
	printf("Sahkan untuk Ubah (Y/T):");
	scanf(" %c", &confirmation);
	while (toupper(confirmation) != 'Y' && toupper(confirmation) != 'N' && confirmation != 1 && toupper(confirmation) != 'T') {
		printf("\n");
		printf("Confirm to Modify (Y or N):\n");
		printf("Sahkan untuk Ubah (Y/T):");
		rewind(stdin);
		scanf(" %c", &confirmation);
	}
	if (toupper(confirmation) == 'Y') {
		printf("\n");
		printf("Do you want to Modify Trip No (Y/N):\n");
		printf("Adakah anda ingin mengubah No. Perjalanan (Y/T):");
		scanf(" %c", &ansTripNo);
		while (toupper(ansTripNo) != 'Y' && toupper(ansTripNo) != 'N' && ansTripNo != 1 && toupper(ansTripNo) != 'T') {
			printf("\n");
			printf("Do you want to Modify Trip No (Y/N):\n");
			printf("Adakah anda ingin mengubah No. Perjalanan (Y/T):");
			rewind(stdin);
			scanf(" %c", &ansTripNo);
		}
		if (toupper(ansTripNo) == 'Y') {
			printf("\n");
			printf("Enter the Updated Trip No:\n");
			printf("Masukkan No. Perjalanan yang Dikemaskini:");
			scanf(" %[^\n]", newtripNo);

			while (checkTripNo(newtripNo)) {
				printf("\n");
				printf("Error:Available Trip No >");
				fptr = fopen("trainSchedule.txt", "r");
				while (fscanf(fptr, "%s|%[^|]|%[^|]|%*d-%d-%d|%s|%s|%s|%d|%f\n", s[count].tripNo, s[count].departure, s[count].arrival,
					&s[count].month, &s[count].day, s[count].dTime, s[count].aTime, s[count].trainID, &s[count].seats, &s[count].price) == 10) {

					if (strcmp(s[count1].tripNo, s[count1 - 1].tripNo) != 0) {
						printf("%s, ", s[count1].tripNo);
					}

					count1++;
				}
				fclose(fptr);
				printf("\n");
				printf("Enter the Updated Trip No:\n");
				printf("Masukkan No. Perjalanan yang Dikemaskini:");
				rewind(stdin);
				scanf(" %[^\n]", newtripNo);
			}

			strcpy(BK[newIndex].trip_no, newtripNo);
		}
		printf("\n");
		printf("Do you want to Modify Number of Ticket (Y/N):\n");
		printf("Adakah anda ingin mengubah Bilangan Tiket (Y/T):");
		scanf(" %c", &ansNumoftic);
		while (toupper(ansNumoftic) != 'Y' && toupper(ansNumoftic) != 'N' && ansNumoftic != 1 && toupper(ansNumoftic) != 'T') {
			printf("\n");
			printf("Invalid Input\n");
			printf("Do you want to Modify Number of Ticket (Y/N):\n");
			printf("Adakah anda ingin mengubah Bilangan Tiket (Y/T):");
			rewind(stdin);
			scanf(" %c", &ansNumoftic);
		}

		if (toupper(ansNumoftic) == 'Y') {
			printf("\n");
			printf("Enter the Updated total number of tickets:\n");
			printf("Masukkan jumlah tiket yang dikemaskini: ");
			scanf(" %d", &newNumoftic);
			while (newNumoftic <= 0 || newNumoftic > 20) {
				printf("The maximum for ticket is only 20.\n");
				printf("Maksimum tiket hanya 20.\n");
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
				printf("\n");
				printf("Enter the Updated total number of tickets:\n");
				printf("Masukkan jumlah tiket yang dikemaskini: ");
				scanf(" %d", &newNumoftic);
			}
			BK[newIndex].numberOfTickets = newNumoftic;
		}
		printf("\n");
		printf("Do you want to Modify Day (Y/N):\n");
		printf("Adakah anda ingin mengubah Hari (Y/T):");
		scanf(" %c", &ansDay);
		while (toupper(ansDay) != 'Y' && toupper(ansDay) != 'N' && ansDay != 1 && toupper(ansDay) != 'T') {
			printf("\n");
			printf("Do you want to Modify Day (Y/N):\n");
			printf("Adakah anda ingin mengubah Hari (Y/T):");
			rewind(stdin);
			scanf(" %c", &ansDay);
		}
		if (toupper(ansDay) == 'Y') {
			printf("\n");
			printf("Enter the Updated Day:\n");
			printf("Masukkan Hari yang Dikemaskini:");
			scanf(" %d", &newDay);
			while (newDay <= 0 || newDay > 31) {
				printf("Error: Day should be between 1 and 31.\n");
				printf("Ralat: Hari harus antara 1 dan 31.\n");
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
				printf("\n");
				printf("Enter the day you want to book:\n");
				printf("Masukkan hari yang ingin anda tempah: ");
				scanf(" %d", &newDay);
			}
			BK[newIndex].day = newDay;

		}
		printf("\n");
		printf("Do you want to Modify Month (Y/N):\n");
		printf("Adakah anda ingin mengubah Bulan (Y/T):");
		scanf(" %c", &ansMonth);
		while (toupper(ansMonth) != 'Y' && toupper(ansMonth) != 'N' && ansMonth != 1 && toupper(ansMonth) != 'T') {
			printf("\n");
			printf("Do you want to Modify Month (Y/N):\n");
			printf("Adakah anda ingin mengubah Bulan (Y/T):");
			rewind(stdin);
			scanf(" %c", &ansMonth);
		}
		if (toupper(ansMonth) == 'Y') {
			printf("\n");
			printf("Enter the Updated Month:\n");
			printf("Masukkan Bulan yang Dikemaskini: ");
			scanf(" %d", &newMonth);
			while (newMonth <= 0 || newMonth > 31) {
				printf("Error: Month should be between 1 and 12.\n");
				printf("Ralat: Bulan harus antara 1 dan 12.\n");
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
				printf("\n");
				printf("Enter the Updated Month:\n");
				printf("Masukkan Bulan yang Dikemaskini: ");
				scanf(" %d", &newMonth);
			}
			BK[newIndex].month = newMonth;
		}

		printf("\n");
		printf("Do you want to Modify Payment Method (Y/N):\n");
		printf("Adakah anda ingin mengubah Kaedah Pembayaran (Y/T):");
		scanf(" %c", &anspaymentMethod);
		while (toupper(anspaymentMethod) != 'Y' && toupper(anspaymentMethod) != 'N' && anspaymentMethod != 1 && toupper(anspaymentMethod) != 'T') {
			printf("\n");
			printf("Do you want to Modify Payment Method (Y/N):\n");
			printf("Adakah anda ingin mengubah Kaedah Pembayaran (Y/T):");
			rewind(stdin);
			scanf(" %c", &anspaymentMethod);
		}
		if (toupper(anspaymentMethod) == 'Y') {
			printf("\n");
			printf("Selection:\n");
			printf(" 1.Cash Payment\n");
			printf(" 2.Account Wallet\n");
			printf(" 3.Digital Wallet\n");
			printf("Enter the Updated Payment Method:\n");
			printf("\n");
			printf("Pilihan:\n");
			printf(" 1. Pembayaran Tunai\n");
			printf(" 2. Baki Akaun\n");
			printf(" 3. Dompet Digital\n");
			printf("Masukkan Kaedah Pembayaran yang Dikemaskini:");
			scanf(" %d", &newpayemntMethod);

			while (newpayemntMethod != 1 && newpayemntMethod != 2 && newpayemntMethod != 3) {

				rewind(stdin);
				printf("Selection:\n");
				printf(" 1.Cash Payment\n");
				printf(" 2.Account Wallet\n");
				printf(" 3.Digital Wallet\n");
				printf("Enter the Updated Payment Method:\n");
				printf("\n");
				printf("Pilihan:\n");
				printf(" 1.Bayaran Tunai\n");
				printf(" 2.Dompet Akaun Dompet\n");
				printf(" 3.Digital\n");
				printf("Masukkan Kaedah Pembayaran Terkini: ");
				scanf(" %d", &newpayemntMethod);
			}
			switch (newpayemntMethod) {
			case 1:
				strcpy(BK[newIndex].paymentMethod, "Cash Payment");
				break;
			case 2:
				strcpy(BK[newIndex].paymentMethod, "Account Wallet");
				break;
			case 3:
				strcpy(BK[newIndex].paymentMethod, "Digital Payment");
				break;
			default:
				printf("Error: Payment Method should be 1 or 2 and 3.\n\n");
				break;
			}


		}
		printf("\n");
		printf("Do you want to Modify Amount (Y/N):\n");
		printf("Adakah anda ingin mengubah Jumlah (Y/T):");
		scanf(" %c", &ansPrice);
		while (toupper(ansPrice) != 'Y' && toupper(ansPrice) != 'N' && ansPrice != 1 && toupper(ansPrice) != 'T') {
			printf("\n");
			printf("Do you want to Modify Amount (Y/N):\n");
			printf("Adakah anda ingin mengubah Jumlah (Y/T):");
			rewind(stdin);
			scanf(" %c", &ansPrice);
		}
		if (toupper(ansPrice) == 'Y') {
			printf("\n");
			printf("Enter the Updated Amount:\n");
			printf("Masukkan Jumlah yang Dikemaskini:");
			scanf(" %lf", &newPrice);
			while (newPrice < 50 || newPrice>1000) {
				printf("Error: Amount should be between 50 to 1000.\n");
				printf("Ralat: Jumlah harus antara 50 hingga 1000.\n");
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
				printf("\n");
				printf("Enter the Updated Amount:\n");
				printf("Masukkan Jumlah yang Dikemaskini: ");
				scanf(" %lf", &newPrice);
			}
			BK[newIndex].payment = newPrice;
		}


		fptr = fopen("BookingHistory.txt", "w");
		for (int i = 0;i < index;i++) {

			fprintf(fptr, "%-12s | %10s | %02d-%02d-2024 | %-6.2lf | %-20s | %-6s | %d\n", BK[i].bookingID, BK[i].username, BK[i].day, BK[i].month, BK[i].payment, BK[i].paymentMethod, BK[i].trip_no, BK[i].numberOfTickets);
		}

		fclose(fptr);

	}
	else {
		return;
	}
	system("cls");
}
void refundFunction(char bookingIDrefund[20]) {
	FILE* fptr;
	struct Booking BK[20];
	Refund Rf;
	Rf.totalRefund = 0.00;
	Rf.seatNORMALRefund = 0;
	Rf.seatOKURefund = 0;
	SYSTEMTIME t;
	GetLocalTime(&t);

	Seat seat[30];
	int index = 0, choice, refundCount, pass = 0, index1 = 0, pass1 = 0;
	char ansRefund, bookingID[20];


	fptr = fopen("BookingHistory.txt", "r");

	if (fptr == NULL) {
		printf("Error: Could not open the file.\n");
		exit(-1);
	}

	while (fscanf(fptr, "%9s | %10s | %d-%d-%*d | %lf | %19[^|] | %9s | %d\n",
		BK[index1].bookingID,
		&BK[index1].username,
		&BK[index1].day,
		&BK[index1].month,
		&BK[index1].payment,
		BK[index1].paymentMethod,
		BK[index1].trip_no,
		&BK[index1].numberOfTickets) == 8) {

		if (strcmp(bookingIDrefund, BK[index1].bookingID) == 0) {
			pass1 = index1;
		}

		index1++;
	}
	fclose(fptr);

	fptr = fopen("Seatfile.txt", "r");
	while (fscanf(fptr, "%[^|]|%19[^|]|%d|%d|%d|%lf|%[^|]|%[^|]|%[^|]|%[^\n]\n", seat[index].trip,
		seat[index].seatTypes, &seat[index].seatAvailable,
		&seat[index].numberofNORMAL, &seat[index].numberofOKU,
		&seat[index].price, seat[index].storeTrainID, seat[index].storeBookingID,
		seat[index].storeSeat, seat[index].storeSeat1) == 10) {

		if (strcmp(bookingIDrefund, seat[index].storeBookingID) == 0) {
			pass = index;
		}
		index++;
	}
	fclose(fptr);


	strcpy(Rf.BookingIDRefund, bookingIDrefund);
	sprintf(Rf.dateRefund, "%02d-%02d-2024", t.wDay, t.wMonth);
	Rf.seatNORMALRefund = seat[pass].numberofNORMAL;
	Rf.seatOKURefund = seat[pass].numberofOKU;
	Rf.totalRefund = NORMAL_PRICE * seat[pass].numberofNORMAL + OKU_PRICE * seat[pass].numberofOKU + BK[pass1].payment;

	printf("Booking ID: %s\n", Rf.BookingIDRefund);
	printf("Date Refund: %s\n", Rf.dateRefund);
	printf("Total Refund: %.2lf\n", Rf.totalRefund);
	printf("\n\n");
	printf("Tempahan ID: %s\n", Rf.BookingIDRefund);
	printf("Tarikh Bayaran balik: %s\n", Rf.dateRefund);
	printf("Jumlah Bayaran Balik: %.2lf\n", Rf.totalRefund);

	fptr = fopen("storerefundInformation.bin", "ab");
	fwrite(&Rf, sizeof(Refund), 1, fptr);


	fclose(fptr);

}
void deleteBookingFunction() {
	struct Booking BK[30];
	FILE* fptr;
	int count = 0, Pcount = 0, count1 = 0;
	char BookingID[20], confirm, ansDelete;
	system("cls");
	fptr = fopen("BookingHistory.txt", "r");
	if (fptr == NULL) {
		printf("Error: Could not open the file.\n");
		exit(-1);
	}
	while (fscanf(fptr, "%9s | %10s | %d-%d-%*d | %lf | %19[^|] | %9s | %d\n",
		BK[count1].bookingID,
		&BK[count1].username,
		&BK[count1].day,
		&BK[count1].month,
		&BK[count1].payment,
		BK[count1].paymentMethod,
		BK[count1].trip_no,
		&BK[count1].numberOfTickets) == 8) {
		count1++;

	}
	fclose(fptr);


	printf("%20s=========================================================================\n", "");
	printf("%40s\tDELETE BOOKING\n", "");
	printf("%40s\tMEMADAMKAN TEMPAHAN\n", "");
	printf("%20s=========================================================================\n\n", "");

	do {
		printf("%8s==========================================================================================================\n", "");
		printf("%60s\n", "Booking History");
		printf("%8s==========================================================================================================\n", "");
		printf("%8s%-13s %-13s %-13s %-12s %-16s %-15s %-15s\n", "", "Booking ID", "Username", "Booking DATE", "Payment", "Payment Method", "Booking TripNo", "Number of Tickets");
		printf("%8s------------- ------------ ------------  ------------ ---------------- -------------- ------------------\n", "");
		for (int i = 0;i < count1;i++) {
			printf("%8s%-13s %-13s %02d-%02d-2024   RM%9.2lf   %-20s      %-15s %6d\n", "", BK[i].bookingID, BK[i].username, BK[i].day, BK[i].month, BK[i].payment, BK[i].paymentMethod, BK[i].trip_no, BK[i].numberOfTickets);
		}
		printf("%8s==========================================================================================================\n", "");
		printf("\n");
		printf("Enter the Booking ID you want to delete:\n");
		printf("Masukkan ID Tempahan yang ingin anda padam: ");
		scanf(" %[^\n]", BookingID);

		for (int i = 0; i < strlen(BookingID); i++) {
			BookingID[i] = toupper(BookingID[i]);
		}

		while (checkBookingID(BookingID)) {
			printf("Invalid Booking ID.\n");
			printf("ID Tempahan tidak sah.\n");
			displayBOOKINGAvailable(BookingID);
			printf("Enter the Booking ID you want to delete:\n");
			printf("Masukkan ID Tempahan yang ingin anda padam: ");
			scanf(" %[^\n]", BookingID);
			for (int i = 0;i < strlen(BookingID);i++) {
				BookingID[i] = toupper(BookingID[i]);
			}
		}
		Pcount = 0;
		count = 0;

		for (int i = 0; i < count1; i++) {
			if (strcmp(BookingID, BK[i].bookingID) == 0) {
				Pcount = i;

				printf("=====================================\n");
				printf("           Current Details           \n");
				printf("=====================================\n");
				printf("Trip Number:       %s\n", BK[Pcount].trip_no);
				printf("Number of Tickets: %d\n", BK[Pcount].numberOfTickets);
				printf("Booking Date:      %02d-%02d-2024\n", BK[Pcount].day, BK[Pcount].month);
				printf("Price:             RM%.2lf\n", BK[Pcount].payment);
				printf("Payment Method:    %s\n", BK[Pcount].paymentMethod);
				printf("=====================================\n");
				printf("\n");
				printf("=====================================\n");
				printf("            Butiran Semasa           \n");
				printf("=====================================\n");
				printf("Nombor Perjalanan: %s\n", BK[Pcount].trip_no);
				printf("Bilangan Tiket:    %d\n", BK[Pcount].numberOfTickets);
				printf("Tarikh Tempahan:   %02d-%02d-2024\n", BK[Pcount].day, BK[Pcount].month);
				printf("Harga:             RM%.2lf\n", BK[Pcount].payment);
				printf("Payment Method:    %s\n", BK[Pcount].paymentMethod);
				printf("=====================================\n");

				printf("Are you sure you want to delete this Booking Record? (Y/N):\n");
				printf("Adakah anda pasti ingin memadam rekod Tempahan ini? (Y/T): ");
				scanf(" %c", &confirm);

				while (toupper(confirm) != 'Y' && toupper(confirm) != 'N' && confirm != 1 && toupper(confirm) != 'T') {
					printf("Invalid input\n");
					rewind(stdin);
					printf("Are you sure you want to delete this Booking Record? (Y/N):\n");
					printf("Adakah anda pasti ingin memadam rekod Tempahan ini? (Y/T): ");
					scanf(" %c", &confirm);
				}

			}

		}

		if (toupper(confirm) == 'Y') {

			refundFunction(BK[Pcount].bookingID);
			for (int j = Pcount; j < count1 - 1; j++) {
				BK[j] = BK[j + 1];
			}
			count1--;
			printf("Booking Record deleted successfully.\n");
			printf("Berjaya memadam rekod Tempahan.\n\n");


			// Update the file with the remaining records
			fptr = fopen("BookingHistory.txt", "w");
			if (fptr == NULL) {
				printf("Error opening file for writing.\n");
				exit(-1);
			}


			for (int i = 0; i < count1; i++) {
				fprintf(fptr, "%-12s | %10s | %02d-%02d-2024 | %-6.2lf | %-20s | %-6s | %d\n",
					BK[i].bookingID, BK[i].username, BK[i].day, BK[i].month,
					BK[i].payment, BK[i].paymentMethod,
					BK[i].trip_no, BK[i].numberOfTickets);
			}

			fclose(fptr);

		}

		printf("Do you want to delete Again (Y/N):\n");
		printf("Adakah anda mahu memadam lagi (Y/T):");
		scanf(" %c", &ansDelete);
		while (toupper(ansDelete) != 'Y' && toupper(ansDelete) != 'N' && ansDelete != 1 && toupper(ansDelete) != 'T') {
			printf("Invalid input\n");
			printf("Do you want to delete Again (Y/N):\n");
			printf("Adakah anda mahu memadam lagi (Y/T):");
			rewind(stdin);
			scanf(" %c", &ansDelete);
		}


	} while (toupper(ansDelete) == 'Y');


}
void viewBooking() {

	FILE* fptr;
	struct Booking BK;
	Seat seat[30];
	int index1 = 0;
	char passSeat[21], passBooking[20];
	printf("%20s=========================================================================\n", "");
	printf("%40s\tVIEW BOOKING\n", "");
	printf("%37s\tLIHAT TEMPAHAN\n", "");
	printf("%20s=========================================================================\n\n", "");
	fptr = fopen("BookingHistory.txt", "r");

	if (fptr == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}
	system("cls");
	printf("==========================================================================================================\n");
	printf("%55s\n", "View Booking History");
	printf("==========================================================================================================\n");
	printf("%-13s %-13s %-13s %-12s %-16s %-15s %-15s\n", "Booking ID", "Username", "Booking DATE", "Payment", "Payment Method", "Booking TripNo", "Number of Tickets");
	printf("------------- ------------ ------------  ------------ ---------------- -------------- ------------------\n");


	while (fscanf(fptr, "%9s | %10s | %d-%d-%*d | %lf | %19[^|] | %9s | %d\n",
		BK.bookingID,
		&BK.username,
		&BK.day,
		&BK.month,
		&BK.payment,
		BK.paymentMethod,
		BK.trip_no,
		&BK.numberOfTickets) == 8) {

		printf("%-13s %-13s %02d-%02d-2024   RM%9.2lf   %-20s      %-15s %6d\n", BK.bookingID, BK.username, BK.day, BK.month, BK.payment, BK.paymentMethod, BK.trip_no, BK.numberOfTickets);
		strcpy(passBooking, BK.bookingID);


	}
	printf("==========================================================================================================\n");
	fclose(fptr);

	fptr = fopen("Seatfile.txt", "r");
	while (fscanf(fptr, "%[^|]|%19[^|]|%d|%d|%d|%4[^|]|%4[^|]|%lf|%[^\n]\n", seat[index1].trip,
		seat[index1].seatTypes, &seat[index1].seatAvailable,
		&seat[index1].numberofNORMAL, &seat[index1].numberofOKU,
		seat[index1].storeTrainID, seat[index1].storeBookingID,
		&seat[index1].price, seat[index1].storeSeat) == 9) {

		if (strcmp(seat[index1].storeBookingID, passBooking) == 0) {

			printf("Booking ID: %s\n", passBooking);
			printf("Display Seat: \n");
			for (int i = 0;i < 20;i++) {

				printf("%c ", seat[index1].storeSeat[i]);
				if ((i + 1) % 5 == 0) {
					printf("\n");
				}
			}
		}
		index1++;
	}
	fclose(fptr);
	system("pause");
	system("cls");
}
