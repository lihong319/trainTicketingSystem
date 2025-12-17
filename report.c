#include "header.h"

//report module
void reportModule() {
	int choice = 0;
	system("cls");
	while (1) {
		choice = reportMenu(choice);

		if (choice == 1) {
			staffReport();
		}
		else if (choice == 2) {
			memberGender();
		}
		else if (choice == 3) {
			tripSummary();
		}
		else if (choice == 4) {
			reportFunction();
		}
		else if (choice == -1) {
			break;
		}
		else {
			printf("Choice Invalid\n");
			printf("Pilihan anda tidak sah\n\n");

		}
	}
	system("cls");
}
int reportMenu(int choice) {
	printf("=========================================================================\n");
	printf("\REPORT MODULE / MODUL LAPORAN\n");
	printf("=========================================================================\n\n");

	printf("1. Staff Information Report\n");
	printf("2. Member Gender Distribution Report\n");
	printf("3. Trip Summary Report\n");
	printf("4. Ticket Sales Report\n");
	printf("Please enter your choice (-1 to exit)\n\n");

	printf("1. Laporan Maklumat Kakitangan\n");
	printf("2. Laporan Pengagihan Janita Ahli1\n");
	printf("3. Laporan Ringkasan Perjalanan\n");
	printf("4. Laporan Penjualan Tiket\n");
	printf("Sila masukkan pilihan anda (-1 untuk keluar)\n>");
	scanf("%d", &choice);
	rewind(stdin);
	return choice;
}

//staff
void staffReport() {
	int choice = 0;
	system("cls");

	while (1) {
		choice = staffReportMenu(choice);

		if (choice == 1) {
			staffGender();
		}
		else if (choice == 2) {
			staffAge();
		}
		else if (choice == -1) {
			break;
		}
		else {
			printf("Choice Invalid\n");
			printf("Pilihan anda tidak sah\n\n");
		}
	}
	system("cls");
}
int staffReportMenu(int choice) {
	printf("=========================================================================\n");
	printf("\tWELCOME TO STAFF INFORMATION REPORT\n");
	printf("\tSELAMAT DATANG KE LAPORAN MAKLUMAT KAKITANGAN\n");
	printf("=========================================================================\n\n");


	printf("1. Staff Gender Distribution\n");
	printf("2. Staff Age Distribution\n");
	printf("Please enter your choice (-1 to exit):\n\n");

	printf("1. Pengagihan Janita Kakitangan\n");
	printf("2. Pembahagian Umur Kakitangan\n");
	printf("Sila masukkan pilihan anda (-1 untuk keluar):\n>");
	scanf("%d", &choice);
	rewind(stdin);

	return choice;
}
void staffAge() {
	Staff s[MAX_STAFF];
	int min, max, sCount = 0;
	double median, firstQ, thirdQ;

	//open staff file for binary
	FILE* staffInfo;
	staffInfo = fopen("staff.dat", "rb");
	if (staffInfo == NULL) {
		printf("file opening error\n");
		exit(-1);
	}
	//read staff information from binary file
	while (fread(&s[sCount], sizeof(Staff), 1, staffInfo) != 0) {
		sCount++;
	}

	fclose(staffInfo);
	system("cls");
	printf("=========================================================================\n");
	printf("\t\tStaff Age distribution\n");
	printf("\t\tPembahagian Umur Kakitangan\n");
	printf("=========================================================================\n\n");

	//calculation
	for (int i = 0; i < sCount; i++) {
		for (int j = i + 1; j < sCount; j++) {
			if (s[i].age > s[j].age) {
				int temp = s[i].age;
				s[i].age = s[j].age;
				s[j].age = temp;
			}
		}
	}
	min = s[0].age;
	max = s[sCount - 1].age;

	if (sCount % 2 == 0) {
		median = (s[sCount / 2 - 1].age + s[sCount / 2].age) / 2.0;
	}
	else {
		median = s[sCount / 2].age;
	}

	int firstQIndex = sCount / 4;
	if (sCount % 4 == 0) {
		firstQ = (s[firstQIndex - 1].age + s[firstQIndex].age) / 2.0;
	}
	else {
		firstQ = s[firstQIndex].age;
	}

	int thirdQIndex = 3 * (sCount / 4);
	if (sCount % 4 == 0) {
		thirdQ = (s[thirdQIndex - 1].age + s[thirdQIndex].age) / 2.0;
	}
	else {
		thirdQ = s[thirdQIndex].age;
	}





	//output
	printf("Minimum Staff Age : %d\n", min);
	printf("First Quartile Staff Age: %.1f\n", firstQ);
	printf("Median Staff Age: %.1f\n", median);
	printf("Third Quartile Staff Age: %.1f\n", thirdQ);
	printf("Maximum Staff Age : %d\n\n", max);

	printf("Umur Minimum Kakitangan : %d\n", min);
	printf("Umur Kakitangan Kuartil Pertama: %.1f\n", firstQ);
	printf("Umur Kakitangan Median: %.1f\n", median);
	printf("Umur Kakitangan Kuartil Ketiga: %.1f\n", thirdQ);
	printf("Umur Maksimum Kakitangan : %d\n\n", max);

	system("pause");
	system("cls");
}
void staffGender() {
	//local declaration
	Staff s;
	int mCount = 0, fCount = 0, sCount = 0;

	//open staff file
	FILE* staffInfo;
	staffInfo = fopen("staff.dat", "rb");
	if (staffInfo == NULL) {
		printf("file opening error\n");
		exit(-1);
	}
	system("cls");

	//read staff information from file
	while (fread(&s, sizeof(Staff), 1, staffInfo) != 0 && sCount < MAX_STAFF) {
		if (s.gender == 'M') {
			mCount++;
		}
		else if (s.gender == 'F') {
			fCount++;
		}


		sCount++;
	}
	//output
	printf("=========================================================================\n");
	printf("\t\tStaff Gender distribution\n");
	printf("\t\tPengagihan Janita Kakitangan\n");
	printf("=========================================================================\n\n");

	printf("%-50s %02d \n", "Total Male Staff / Jumlah Kakitangan lelaki = ", mCount);
	printf("%-50s %02d \n\n", "Total Female Staff / Jumalah Kakitangan Wanita = ", fCount);


	printf("There are %.2lf %% of Male Staff\n", ((double)mCount / sCount) * 100);
	printf("There are %.2lf %% of Female Staff\n\n", ((double)fCount / sCount) * 100);

	printf("Terdapat %.2lf %% Kakitangan lelaki\n", ((double)mCount / sCount) * 100);
	printf("Terdapat %.2lf %% Kakitangan Wanita\n", ((double)fCount / sCount) * 100);

	fclose(staffInfo);
	system("pause");
	system("cls");
}

//train schedule
void tripSummary() {
	FILE* file;
	file = fopen("trainSchedule.txt", "r");
	if (file == NULL) {
		printf("Error opening the file.\n");
		return 1;
	}
	int totalTrips = 0;
	int tripsPerTrainID[4] = { 0 }; // Assuming there are four train IDs T01, T02, T03, T04
	double totalTripDuration = 0.0;

	char line[MAX_LINE_LENGTH];
	while (fgets(line, sizeof(line), file)) {
		TrainSchedule s;
		sscanf(line, "%19[^|]|%19[^|]|%19[^|]|%19[^|]|%19[^|]|%19[^|]|%19[^|]|%d|%f",
			s.tripNo, s.departure, s.arrival, s.date,
			s.dTime, s.aTime, s.trainID, &s.seats, &s.price);

		totalTrips++;
		if (strcmp(s.trainID, "T01") == 0) {
			tripsPerTrainID[0]++;
		}
		else if (strcmp(s.trainID, "T02") == 0) {
			tripsPerTrainID[1]++;
		}
		else if (strcmp(s.trainID, "T03") == 0) {
			tripsPerTrainID[2]++;
		}
		else if (strcmp(s.trainID, "T04") == 0) {
			tripsPerTrainID[3]++;
		}

		// Calculate trip duration (assuming time format HHMM)
		int departureTime = atoi(s.dTime);
		int arrivalTime = atoi(s.aTime);
		double tripDuration = (arrivalTime - departureTime) / 100 * 60 + (arrivalTime - departureTime) % 100;
		totalTripDuration += tripDuration;
	}

	double averageTripDuration = totalTripDuration / totalTrips / 60.0; // Convert minutes to hours
	system("cls");
	printf("=========================================================================\n");
	printf("\tTrip Summary Report\n");
	printf("\tLaporan Ringkasan Perjalanan \n");
	printf("=========================================================================\n\n");

	printf("Total number of trips scheduled: %d\n", totalTrips);
	printf("Number of trips per Train ID:\n");
	printf("T01: %d\n", tripsPerTrainID[0]);
	printf("T02: %d\n", tripsPerTrainID[1]);
	printf("T03: %d\n", tripsPerTrainID[2]);
	printf("T04: %d\n", tripsPerTrainID[3]);
	printf("Average trip duration: %.2f hours\n\n", averageTripDuration);

	printf("Jumlah Jaduan Perjalanan: %d\n", totalTrips);
	printf("Bilangan Perjalanan setiap ID Kereta Api:\n");
	printf("T01: %d\n", tripsPerTrainID[0]);
	printf("T02: %d\n", tripsPerTrainID[1]);
	printf("T03: %d\n", tripsPerTrainID[2]);
	printf("T04: %d\n", tripsPerTrainID[3]);
	printf("Purata tempoh perjalanan: %.2f jam\n\n", averageTripDuration);
	fclose(file);
	system("pause");
	system("cls");
}

//booking
void reportFunction() {
	FILE* fptr;
	struct Booking BK[MAX_BOOKINGS];
	double monthlyTotalPayment[12] = { 0.0 };
	int countNumberofSeat[12] = { 0 };
	int month[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	double highestPayment = 0.0;
	int highestMonth = -1;

	fptr = fopen("BookingHistory.txt", "r");
	if (fptr == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}

	int count = 0;
	while (fscanf(fptr, "%9s | %10s | %d-%d-%*d | %lf | %19[^|] | %9s | %d\n",
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
	fclose(fptr);

	for (int i = 0; i < count; i++) {
		int currentMonth = BK[i].month - 1;
		monthlyTotalPayment[currentMonth] += BK[i].payment;
		countNumberofSeat[currentMonth]++;
	}
	system("cls");
	printf("===========================================================================================\n");
	printf("%-55sReport Booking System\n\n", "");
	printf("===========================================================================================\n");
	for (int i = 0; i < 12; i++) {
		printf("Monthly Booking Summary for Month %d:\n", month[i]);
		printf("Number of Bookings: %d\n", countNumberofSeat[i]);
		printf("Total Payment: RM%.2lf\n", monthlyTotalPayment[i]);
		printf("\n");
		printf("Ringkasan Tempahan Bulanan untuk Bulan %d:\n", month[i]);
		printf("Bilangan Tempahan: %d\n", countNumberofSeat[i]);
		printf("Jumlah bayaran: RM%.2lf\n", monthlyTotalPayment[i]);
		printf("\n");
		if (monthlyTotalPayment[i] > highestPayment) {
			highestPayment = monthlyTotalPayment[i];
			highestMonth = month[i];
		}
	}
	printf("===========================================================================================\n\n");

	if (highestMonth != -1) {
		printf("Month with the Highest Total Payment: Month %d\n", highestMonth);
		printf("Total Payment: RM%.2lf\n", highestPayment);
		printf("\n");
		printf("Bulan dengan Jumlah Bayaran Tertinggi: Bulan %d\n", highestMonth);
		printf("Jumlah bayaran: RM%.2lf\n", highestPayment);
		printf("\n");
	}
	else {
		printf("No bookings found.\n");
		printf("Tiada tempahan ditemui.\n");

	}
	system("pause");
	system("cls");
}


//member
void memberGender() {
	// Local declaration
	MemberInfo m;
	int mCount = 0, fCount = 0, mTotal = 0;

	// Open member file
	FILE* memberInfo;
	memberInfo = fopen("members.dat", "rb");
	if (memberInfo == NULL) {
		printf("Error opening file\n");
		exit(-1);
	}

	system("cls");

	// Read member information from file
	while (fread(&m, sizeof(MemberInfo), 1, memberInfo) != 0 && mTotal < MAX_MEMBERS) {
		if (m.gender == 'M') {
			mCount++;
		}
		else if (m.gender == 'F') {
			fCount++;
		}
		mTotal++;
	}

	// Output
	printf("=========================================================================\n");
	printf("\t\tMember Gender Distribution\n");
	printf("\t\tPengagihan Janita member\n");
	printf("=========================================================================\n\n");

	printf("%-50s %02d \n", "Total Male Members = ", mCount);
	printf("%-50s %02d \n\n", "Total Female Members = ", fCount);

	printf("There are %.2lf %% of Male Members\n", ((double)mCount / mTotal) * 100);
	printf("There are %.2lf %% of Female Members\n\n", ((double)fCount / mTotal) * 100);

	printf("Terdapat %.2lf %% member lelaki\n", ((double)mCount / mTotal) * 100);
	printf("Terdapat %.2lf %% member Wanita\n", ((double)fCount / mTotal) * 100);

	fclose(memberInfo);
	system("pause");  // Pause to view results
	system("cls");    // Clear the screen after viewing
}