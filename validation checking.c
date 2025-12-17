#include "header.h"

//validation
//staff validation
int isLeapYear(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}
int isValidDate(Date date) {
	int daysInMonth[] = { 31, 28 + isLeapYear(date.year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (date.year < 0) {
		return 0; // Invalid year
	}
	if (date.month < 1 || date.month > 12) {
		return 0; // Invalid month
	}
	if (date.day < 1 || date.day > daysInMonth[date.month - 1]) {
		return 0; // Invalid day
	}

	return 1; // Date is valid
}
int isValidEmail(const char* email) {
	const char* atSign = strchr(email, '@');
	return atSign && (atSign != email) && (*(atSign + 1) != '\0');
}
int isDuplicateStaffID(char staffID[5]) {
	Staff s;
	FILE* staffInfo = fopen("staff.dat", "rb");
	if (!staffInfo) {
		printf("file opening error\n");
		exit(-1);
	}

	char tempId[5];

	while (fread(&s, sizeof(Staff), 1, staffInfo) != 0) {
		if (strcmp(s.id, staffID) == 0) {
			return 1;
		}
	}
	return 0;
}

//train schedule validation
void convertToUpper(char str[]) {
	for (int i = 0; str[i] != '\0'; i++) {
		str[i] = toupper(str[i]);
	}
}
int isDuplicateTripID(const char* tripID, const char* fileName) {//CHECK IS THE TRIP ID SAME
	FILE* fptr = fopen(fileName, "r");
	if (!fptr) {
		printf("Error: Cannot open the file.\n");
		return 1;
	}

	char line[MAX_FIELD_LENGTH * 9];
	while (fgets(line, sizeof(line), fptr) != NULL) {
		char storedTripID[MAX_FIELD_LENGTH];
		sscanf(line, "%[^|]", storedTripID);

		if (strcmp(storedTripID, tripID) == 0) {
			fclose(fptr);
			return 1;
		}
	}

	fclose(fptr);
	return 0;
}
int isValidTrainID(const char* trainID) {
	const char* validTrainIDs[] = { "T01", "T02", "T03", "T04" };
	for (int i = 0; i < sizeof(validTrainIDs) / sizeof(validTrainIDs[0]); i++) {
		if (strcmp(trainID, validTrainIDs[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

//booking validation
int  checkBookingID(char cprBookingID[20]) {
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

		if (strcmp(cprBookingID, BK[count].bookingID) == 0) {
			return 0;
		}
		count++;
	}
	fclose(fPtr);
	return 1;
}
int  checkTripNo(char cprTripNo[20]) {
	TrainSchedule s[20];
	FILE* fptr;
	int count = 0;
	fptr = fopen("trainSchedule.txt", "r");
	while (fscanf(fptr, "%3s|%9[^|]|%9[^|]|%*d-%d-%d|%4s|%4s|%3s|%d|%f\n",
		s[count].tripNo, s[count].departure, s[count].arrival, &s[count].month,
		&s[count].day, s[count].dTime, s[count].aTime, s[count].trainID, &s[count].seats, &s[count].price) == 10) {

		if (strcmp(cprTripNo, s[count].tripNo) == 0) {
			return 0;
		}

		count++;
	}
	fclose(fptr);
	return 1;

}
int checkSchedule(const char departurePlace[30], int checkday, int checkmonth) {
	FILE* fPtr;
	TrainSchedule s[100];
	int count = 0;

	fPtr = fopen("trainSchedule.txt", "r");
	if (fPtr == NULL) {
		printf("Error opening train schedule file\n");
		exit(-1);
	}

	while (fscanf(fPtr, "%3s|%[^|]|%[^|]|%*d-%d-%d|%4s|%4s|%3s|%d|%f\n", &s[count].tripNo, s[count].departure, s[count].arrival, &s[count].month, &s[count].day, &s[count].dTime, &s[count].aTime, &s[count].trainID, &s[count].seats, &s[count].price) == 10) {

		if (strcmp(departurePlace, "PK") == 0) {
			strcpy(departurePlace, "PERAK");
		}
		else if (strcmp(departurePlace, "PER") == 0) {
			strcpy(departurePlace, "PERLIS");
		}
		else if (strcmp(departurePlace, "SGP") == 0) {
			strcpy(departurePlace, "SINGAPORE");
		}
		else if (strcmp(departurePlace, "KTN") == 0) {
			strcpy(departurePlace, "KUANTAN");
		}
		else if (strcmp(departurePlace, "JHR") == 0) {
			strcpy(departurePlace, "JOHOR");
		}
		else if (strcmp(departurePlace, "KL") == 0) {
			strcpy(departurePlace, "KL");
		}
		else if (strcmp(departurePlace, "PNG") == 0) {
			strcpy(departurePlace, "PENANG");
		}
		else if (strcmp(departurePlace, "MIRI") == 0) {
			strcpy(departurePlace, "MIRI");
		}
		else if (strcmp(departurePlace, "KCH") == 0) {
			strcpy(departurePlace, "KUCHING");
		}
		else if (strcmp(departurePlace, "IPH") == 0) {
			strcpy(departurePlace, "IPOH");
		}
		if (strcmp(departurePlace, s[count].departure) == 0 &&
			s[count].day == checkday &&
			s[count].month == checkmonth) {
			return 1;
		}
		count++;
	}
	fclose(fPtr);
	return 0;
}
void checkCondition(char accountNumber[20]) {
	int hasUpperCase = 0;
	int hasLowerCase = 0;
	int hasDigit = 0;
	int hasSymbol = 0;

	if (strlen(accountNumber) < 6) {
		printf("Your account number should at least 6 character.\n");
	}
	for (int i = 0; i < 6; i++) {
		if (isupper(accountNumber[i])) {
			hasUpperCase = 1;
		}
		else if (islower(accountNumber[i])) {
			hasLowerCase = 1;
		}
		else if (isdigit(accountNumber[i])) {
			hasDigit = 1;
		}
		else if (ispunct(accountNumber[i])) {
			hasSymbol = 1;
		}
	}
	if (!hasUpperCase) {
		printf("Your account number is missing an uppercase letter.\n");
	}
	if (!hasLowerCase) {
		printf("Your account number is missing a lowercase letter.\n");
	}
	if (!hasDigit) {
		printf("Your account number is missing a digit.\n");
	}
	if (!hasSymbol) {
		printf("Your account number is missing a symbol.\n");
	}
	if (hasUpperCase && hasLowerCase && hasDigit && hasSymbol) {
		printf("Your account number meets all validation criteria.\n");
	}

}
int  checkDuplicateAccount(char passwords1[]) {
	struct storeAccount accounts[20];
	FILE* fptr;
	int ckIndex = 0;

	fptr = fopen("account.bin", "rb");
	if (fptr == NULL) {
		printf("Error opening file for reading\n");
		exit(-1);
	}

	while (fread(&accounts[ckIndex], sizeof(struct storeAccount), 1, fptr) != 0) {
		ckIndex++;
	}
	fclose(fptr);

	for (int i = 0;i < ckIndex;i++) {
		if (strcmp(passwords1, accounts[i].accountNumber) == 0) {
			return 1;
		}
	}

	return 0;
}
int checkDuplicate(int passNumber, int number[], int size) {
	for (int i = 0; i < size; i++) {
		if (passNumber == number[i]) {
			return 1;
		}
	}
	return 0;
}

//member validation
int duplicateUsername(char username[50]) {
	MemberInfo m;
	FILE* check = fopen("members.dat", "rb");
	if (!check) {
		printf("file opening error\n");
		exit(-1);
	}
	while (fread(&m, sizeof(MemberInfo), 1, check)) {
		if (strcmp(m.username, username) == 0) {
			return 1;
		}
	}

	return 0;
}
