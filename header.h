#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#pragma warning(disable:4996)

//staff define constant 
#define MAX_STAFF 20

//member defind constant
#define MAX_MEMBERS 20

//train schedule define constant
#define MAX_FIELD_LENGTH 20
#define MAX_LINE_LENGTH 100

//booking define constant
#define WIDTH 16  
#define HEIGHT 10 
#define TEXT "TOUCH GO" 
#define MAX_BOOKINGS 100
#define ROWS 4   
#define COLS 5
#define OKU_PRICE 6.00
#define NORMAL_PRICE 12.00
#define MAX_FIELD_LENGTH 20
#define MAX_SEATOKU 4;
#define MAX_SEATS 20


//structure declaration
typedef struct {
	int day, month, year;
}Date;

//staff
typedef struct {
	char id[5], password[11], gender, position[15], email[51], tel[15], name[51];
	int age;
	Date dob;
}Staff;

//member
typedef struct {
	char username[50];
	char password[20];
	char contact_number[20];
	char email[51];
	char ic[15];
	char gender;
} MemberInfo;


// train schedule
typedef struct {
	char date[MAX_FIELD_LENGTH];
	char tripNo[MAX_FIELD_LENGTH];
	char departure[MAX_FIELD_LENGTH];
	char arrival[MAX_FIELD_LENGTH];
	int  day, month;
	char dTime[MAX_FIELD_LENGTH];
	char aTime[MAX_FIELD_LENGTH];
	char trainID[MAX_FIELD_LENGTH];
	int seats;
	float price;
} TrainSchedule;

//ticket booking

struct Booking {
	char bookingID[6];
	char bookingDate[40];
	double payment;
	char trip_no[10], username[20];
	int numberOfTickets, day, month, passSeatavailable;
	int tempIndex, countDeleterecord, number;
	char paymentMethod[50], passTrainID[10];
	float amount;

};
typedef struct {
	int seatAvailable, seatReserved, seat_No;
	char storeBookingID[20], storeSeat[20], storeSeat1[20], trip[20];
	char seatTypes[20], storeTrainID[20];
	int  numberofOKU, numberofNORMAL;
	double price;

}Seat;
struct storeAccount {
	int  PINdebitcard, PINcreditcard;
	char cardHolderName[100], username[20], payingMethod[20], accountNumber[20];
	double amount;

};
typedef struct {
	char BookingIDRefund[20];
	double totalRefund;
	char dateRefund[20];
	int seatOKURefund, seatNORMALRefund;

}Refund;


//function declaration
int mainMenu(int);

//main module
void staffMode();
void memberMode();
void scheduleMode();
void bookingMode(char loggedInUsername[50]);

//for staff module
void staffLogin(char* tempId, char* tempPass);
void staffInfoMenu();
void searchStaff();
void displayStaff();
void editStaff();
void addStaff();
void deleteStaff();

//report function
void reportModule();
int reportMenu(int choice);
void staffReport();
int staffReportMenu(int choice);
void staffAge();
void staffGender();
void tripSummary();
void reportFunction();
void memberGender();

//member module
void registerMember();
char* loginMember();
void memberMenu(char loggedInUsername[50]);
int memberProfile(char loggedInUsername[50]);
void displayMember(char loggedInUsername[50]);
void editMemberInfo(char username[50]);
void deleteMember(char loggedInUsername[50]);

void memberInfoMenu();
void displayMembers();
void searchMemberStaff();
void editMemberStaff();
MemberInfo addMemberStaff();
void deleteMemberStaff();
void saveMemberToFile(const MemberInfo* member);

//train schedule module
void trainScheduleMenu();
void displaySchedule();
void searchSchedule();
void addTrainSchedule();
void modifyTrainSchedule();
void deleteEntry(const char* tripID);

void trainInfoMenu();


//booking module
void bookingInfoMenu();
void modifybookingHistory();
void searchBookingfunction();
void refundFunction(char bookingIDrefund[20]);
void deleteBookingFunction();
void displayBOOKINGAvailable(char inputBooking[20]);
void reportFunction();
void viewBooking();
void SeatFunction(int ticket, char trainID[10], char bookingID[10], char passtrip[20]);
void encodeText(char qrCode[HEIGHT][WIDTH], const char* text);
void drawQRCode(char qrCode[HEIGHT][WIDTH]);
void trainSchedule();
void displaySeatingChart();
bool generateBKnumber(int generateNumber);
bool validation_AccountNumber(const char checkAccountNumber[]);
bool validation_shedule(const char checkInputDeparture[]);
void reloadmoney();

void createAccount();
void Bookingfunction(char username[50]);
void viewBookingwithusername(char passUsername[50]);
void cancellation(char username1[50]);

//validation checking 
int isLeapYear(int year);
int isValidDate(Date date);
int isValidEmail(const char* email);
int isDuplicateStaffID(char staffID[5]);
int isDuplicateTripID(const char* tripID, const char* fileName);
int isValidTrainID(const char* trainID);
void convertToUpper(char str[]);
int duplicateUsername(char username[50]);
int  checkTripNo(char cprTripNo[20]);
int  checkBookingID(char cprBookingID[20]);
int checkSchedule(const char departurePlace[30], int checkday, int checkmonth);
void checkCondition(char accountNumber[20]);
int  checkDuplicateAccount(char passwords1[]);
void generateNew(int seatavailable, char passTrainid[20], char tripno[20]);
int checkDuplicate(int passNumber, int number[], int size);