/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Anuj Verma
Student ID#: 180483216
Email      : averma100@myseneca.ca
Section    : NLL
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    displayPatientTableHeader();
    int loop1 = 0;
    int i;
    for (i = 0; i < max && loop1 == 0; i++)
    {
        if (patient[i].patientNumber < 0)
        {
            loop1++;
        }
        if (loop1 == 0 && patient[i].patientNumber > 0)
        {
            displayPatientData(&patient[i], fmt);
        }
    }
    clearInputBuffer();
    printf("\n");
}



// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    do
    {
        printf("Search Options\n");
        printf("==========================\n1) By patient number\n2) By phone number");

        printf("\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);

        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
            clearInputBuffer();
            printf("\n<ENTER> to continue...\n");
            clearInputBuffer();
        }
        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            clearInputBuffer();
            printf("\n<ENTER> to continue...\n");
            clearInputBuffer();
        }

    } while (selection);

    printf("\n");
}


// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max)
{
    int i, isAdded = 0;
    for (i = 0; i < max && isAdded == 0; i++)
    {
        int catchedLargestPatNum = nextPatientNumber(patient, max);

        if (patient[i].patientNumber == 0)
        {
            patient[i].patientNumber = catchedLargestPatNum;

            inputPatient(&patient[i]);

            printf("\n*** New patient record added ***\n\n");
            clearInputBuffer();
            isAdded = 1;
        }
        //if (i == (max-count))
        // menuPatient(patient, max);
    }
    if (isAdded == 0)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
        clearInputBuffer();
    }
}



// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max)
{
    int patientNumber;
    printf("Enter the patient number: ");
    scanf("%d", &patientNumber);
    printf("\n");
    int patientEditIndex = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (patientEditIndex > 0)
    {
        clearInputBuffer();
        menuPatientEdit(&patient[patientEditIndex]);
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
}


// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max)
{
    char selection[10] = { 0 };
    int patientNumber;
    int loop = 1;
    printf("Enter the patient number: ");
    scanf("%d", &patientNumber);
    printf("\n");

    int patientEditIndex = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (patientEditIndex >= 0)
    {
        displayPatientData(&patient[patientEditIndex], 1);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        clearInputBuffer();
        scanf("%s", selection);
        int i, count = 0;

        for (i = 0; selection[i] != '\0'; i++)
        {
            count++;
        }

        if (count <= 1)
        {

            if (selection[0] == 'n')
            {
                printf("Operation aborted.\n\n");
            }
            else if (selection[0] == 'y')
            {
                patient[patientEditIndex].patientNumber = 0;
                printf("Patient record has been removed!\n\n");
            }
            else
            {
                printf("ERROR: Character must be one of [yn]: ");
            }
        }

        else
        {
            while (loop == 1)
            {
                count = 0;
                printf("ERROR: Character must be one of [yn]: ");
                clearInputBuffer();
                scanf("%s", selection);
                
                int i;

                for (i = 0; selection[i] != '\0'; i++)
                {
                    count++;
                }

                if (count <= 1)
                {

                    if (selection[0] == 'n')
                    {
                        printf("Operation aborted.\n\n");
                        loop = 0;
                    }
                    else
                    {
                        patient[patientEditIndex].patientNumber = 0;
                        printf("Patient record has been removed!\n\n");
                        loop = 0;
                    }
                }

            }
        }
    }
    else
    printf("ERROR: Patient record not found!\n\n");
    clearInputBuffer();
}

void SwapApponitments(struct Appointment* appointments, int firstIndex, int secondIndex) {
    struct Appointment newappoint;
    newappoint = appointments[firstIndex];
    appointments[firstIndex] = appointments[secondIndex];
    appointments[secondIndex] = newappoint;
}

void SortAppointments(struct Appointment* appointments) {
    int f = 0, g = 0, h = 0;

    for (h = 0; h <= 4; h++) {
        for (f = 0; appointments[f + 1].patientNumber != 0; f++)
        {
            for (g = f + 1; appointments[g].patientNumber != 0; g++) {

                if (h == 0 && appointments[f].date.year > appointments[g].date.year) {
                    SwapApponitments(appointments, f, g);
                }
                else if (h == 1 && appointments[f].date.year == appointments[g].date.year && appointments[f].date.month > appointments[g].date.month) {
                    SwapApponitments(appointments, f, g);
                }
                else if (h == 2 && appointments[f].date.year == appointments[g].date.year && appointments[f].date.month == appointments[g].date.month && appointments[f].date.day > appointments[g].date.day) {
                    SwapApponitments(appointments, f, g);
                }
                else if (h == 3 && appointments[f].date.year == appointments[g].date.year && appointments[f].date.month == appointments[g].date.month && appointments[f].date.day == appointments[g].date.day && appointments[f].time.hour > appointments[g].time.hour) {
                    SwapApponitments(appointments, f, g);
                }
                else if (h == 4 && appointments[f].date.year == appointments[g].date.year && appointments[f].date.month == appointments[g].date.month && appointments[f].date.day == appointments[g].date.day && appointments[f].time.hour == appointments[g].time.hour && appointments[f].time.min > appointments[g].time.min) {
                    SwapApponitments(appointments, f, g);
                }
            }
        }
    }
}



// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
    displayScheduleTableHeader(&data->appointments->date, 1);
    int z;
    
    // Sort appointments

    SortAppointments(data->appointments);
   
    for (z = 0; (data->appointments[z].patientNumber != 0); z++)
    {
        int k = 0;
        for (k =0; (data->patients[k].patientNumber != data->appointments[z].patientNumber);)
        {
            k++;
        }
        displayScheduleData(&data->patients[k], &data->appointments[z], 1);
    }
    clearInputBuffer();

    
    printf("\n");
}

int GetCorrectDay(int maxDay) {
    int day;
    printf("Day (1-%d)  : ", maxDay);
    do
    {
        scanf("%d", &day);
        if (day < 1 || day > maxDay)
        {
            printf("ERROR! Value must be between 1 and %d inclusive: ", maxDay);
        }
    } while (day < 1 || day > maxDay);

    return day;
}

int getMaxDayOfMonth(int month, int year) {
    int days = 30;
    if (month == 2 && year % 4 == 0)
    {
        days = 29;
    }
    else if (month == 2) {

        days = 28;
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        days = 31;
    }
    else
    {
        days = 30;
    }
    return days;
}


// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int year, month, day;
    printf("Year        : ");
    scanf("%d", &year);
    printf("Month (1-12): ");
    scanf("%d", &month);

    int maxDay = getMaxDayOfMonth(month, year);
    day = GetCorrectDay(maxDay);

    printf("\n");

    struct Date userDate = { year, month, day };

    SortAppointments(data->appointments);

    displayScheduleTableHeader(&userDate, 0);

    int j = 0;
    for (j=0; data->patients[j].patientNumber != 0; j++)
    {
        if (data->appointments[j].date.day == day && data->appointments[j].date.month == month && data->appointments[j].date.year == year)
        {
            int k = 0;
            for (k=0; (data->patients[k].patientNumber != data->appointments[j].patientNumber); k++)
            {
                ;
            }
            displayScheduleData(&data->patients[k], &data->appointments[j], 0);
        }
    }
    clearInputBuffer();
    printf("\n");
}


void AddNewAppointmentToList(struct Appointment* appointment, int patnum,int year, int month, int day,int hour,int  min) {

    appointment->patientNumber = patnum;
    appointment->date.year = year;
    appointment->date.month = month;
    appointment->date.day = day;
    appointment->time.hour = hour;
    appointment->time.min = min;
}


void GetCorrectTime(struct Time* time) {
    int hour, min, correctTimeFormat = 1;
    
    do {
        printf("Hour (0-23)  : ");
        scanf("%d", &hour);
        printf("Minute (0-59): ");
        scanf("%d", &min);

        if ((hour < STARTHOUR || hour > ENDHOUR) || (hour == ENDHOUR && min != 0) || min % APPOINT_INTERVAL != 0) {
            printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", STARTHOUR, ENDHOUR, APPOINT_INTERVAL);
            correctTimeFormat = 0;
        }
        else {
            correctTimeFormat = 1;
        }
    } while (correctTimeFormat == 0);

    time->hour = hour;
    time->min = min;
}

int GetSlotAvailable(struct Appointment* appointments, int day, int month, int year, struct Time time) {
    int p=0, appointmentIndex = -1;
    for (p = 0; appointments[p].patientNumber != 0 && appointmentIndex <=0; p++)
    {
        if (appointments[p].date.day == day && appointments[p].date.month == month && appointments[p].date.year == year && appointments[p].time.hour == time.hour && appointments[p].time.min == time.min)
        {
            printf("\nERROR: Appointment timeslot is not available!\n\n");
            return -1;
        }
    }
    appointmentIndex = p;
    return appointmentIndex;
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patient, int maxPatient)
{
    int patnum, year, month, day;;
    printf("Patient Number: ");
    scanf("%d", &patnum);
    int isAppointmentBooked = 0;
    int availableSlot = 0;

    while (isAppointmentBooked == 0 || availableSlot < 1)
    {
        printf("Year        : ");
        scanf("%d", &year);
        printf("Month (1-12): ");
        scanf("%d", &month);


        int maxDay = getMaxDayOfMonth(month, year);
        day = GetCorrectDay(maxDay);

        struct Time time;
        GetCorrectTime(&time);

        availableSlot = GetSlotAvailable(appointments, day, month, year, time);

        if (availableSlot >= 0)
        {
            AddNewAppointmentToList(&appointments[availableSlot], patnum, year, month, day, time.hour, time.min);
            printf("\n*** Appointment scheduled! ***\n\n");
            clearInputBuffer();
            isAppointmentBooked = 1;
        }
    }
}


// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patient, int maxPatient)
{
    int year, month, day;
    int patientNum;
    printf("Patient Number: ");
    clearInputBuffer();
    scanf("%d", &patientNum);
    int g = 0, found = 0;

    for (g=0; patient[g].patientNumber != 0; g++)
    {
        if (patient[g].patientNumber == patientNum)
        {
            found = 1;
            printf("Year        : ");
            scanf("%d", &year);
            printf("Month (1-12): ");
            scanf("%d", &month);

            int maxDay = getMaxDayOfMonth(month, year);

            day = GetCorrectDay(maxDay);

            printf("\n");
        }
    }

    if(found == 0)
    {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
    else {
        int s = 0, apptIndex = -1;
        for (s=0; appointments[s].patientNumber != 0 && apptIndex == -1; s++)
        {
            if (appointments[s].patientNumber == patientNum && appointments[s].date.year == year && appointments[s].date.month == month && appointments[s].date.day == day)
            {
                apptIndex = s;
            }
        }

        int patientIndex = -1;
        for (patientIndex=0; (patient[patientIndex].patientNumber != patientNum); patientIndex++)
        {
            ;
        }

        if (apptIndex >=0 && patientIndex >=0 )
        {
            char decision;

            printf("Name  : %s", patient[patientIndex].name);
            printf("\nNumber: %05d", patient[patientIndex].patientNumber);
            printf("\nPhone : ");
            displayFormattedPhone(patient[patientIndex].phone.number);
            printf(" (%s)\n", patient[patientIndex].phone.description);


            printf("Are you sure you want to remove this appointment (y,n): ");
            clearInputBuffer();
            scanf("%c", &decision);

            if (decision == 'y')
            {
                for (s = apptIndex; appointments[s + 1].patientNumber != 0; s++)
                {
                    appointments[s] = appointments[s + 1];
                }

                appointments[s].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
                clearInputBuffer();
            }

        }
        else {
            printf("Appointment not found!");
        }

    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)

void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber, catchedValue;
    printf("\nSearch by patient number: ");
    scanf("%d", &patientNumber);
    printf("\n");

    catchedValue = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (catchedValue >= 0)
    {
        displayPatientData(&patient[catchedValue], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
}


int samePhoneNumbers(char *number,const char *number2) {
    int i = 0, isSame = 1;
    for (i = 0; i < 10; i++) {
        if (number[i] != number2[i])
        {
            isSame = 0;
        }
    }
    return isSame;
}


// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNumber[20] = { 0 };
    int recordFound = 0;
    int initial_record = 0;

    printf("\nSearch by phone number: ");
    scanf("%s", phoneNumber);
    printf("\n");
    displayPatientTableHeader();
    int i;

    for (i = 0; i <= max && recordFound >= 0; i++) // check the 5 here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {
        if (samePhoneNumbers(phoneNumber, patient[i].phone.number) == 1)
        {
            displayPatientData(&patient[i], 0);
            recordFound ++;
        }
    }

    if (recordFound == initial_record)
    {
        printf("\n");
        printf("*** No records found ***\n");
    }
}


// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int largest = 0, i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > largest)
        {
            largest = patient[i].patientNumber;
        }
    }
    largest = largest + 1;
    return largest;
}



// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    //  int loop2 = 0;
    int i;
    for (i = 0; i <= max; i++) // check the 5 here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {
        if (patient[i].patientNumber == patientNumber)
        {
            return i;
        }
    }
    return -1;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n------------------\n");
    printf("Number: %05d", patient->patientNumber);
    printf("\nName  : ");
    inputCString(patient->name, 0, NAME_LEN);
   // scanf("%[^\n]s", patient->name);
    printf("\n");
    inputPhoneData(&patient->phone); ////??????????????????
}


void CopyString(char* destination, char* source, int max) {
    int i = 0; 

    for (i = 0; i < max; i++)
    {
        destination[i] = source[i];
    }
}


// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone)
{

    int selection;
    printf("Phone Information\n-----------------\nHow will the patient like to be contacted?\n");
    printf("1. Cell\n2. Home\n3. Work\n4. TBD");
    printf("\nSelection: ");
    selection = inputIntRange(1, 4);
    switch (selection)
    {
    case 1:
        printf("\n");
        printf("Contact: CELL\nNumber : ");
        CopyString(phone->description, "CELL", 4);
        scanf("%s", phone->number);
        break;
    case 2:
        printf("\n");
        printf("Contact: HOME\nNumber : ");
        CopyString(phone->description, "HOME", 4);
        scanf("%s", phone->number);
        break;
    case 3:
        printf("\n");
        printf("Contact: WORK\nNumber : ");
        CopyString(phone->description, "WORK", 4);
        scanf("%s", phone->number);
        printf("\n");
        break;
    case 4:
        CopyString(phone->description, "TBD", 3);
        break;
    }

    while (phone->number[10] != '\0')
    {
        //for (test = 0; phone->number[test] == "\n"; test++)
        //{
        //    count++;
        //}

        //if (count < 10 || count > 10)
        //{
            printf("Invalid 10-digit number! Number: ");
            scanf("%s", phone->number);
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE* fp;
    int i = 0;

    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        for (i = 0; i < max; i++)
        {
            int count = 0;
            char temp = '\0';

            fscanf(fp, "%05d|", (&patients[i].patientNumber));

            fscanf(fp, "%c", &temp);

            //fgets(fp, )*/
            for (count = 0; temp != '|'; count++)
            {
                patients[i].name[count] = temp;
                fscanf(fp, "%c", &temp);
            }

            fscanf(fp, "%c", &temp);

            for (count = 0; temp != '|'; count++)
            {
                patients[i].phone.description[count] = temp;
                fscanf(fp, "%c", &temp);
            }

            if (patients[i].phone.description[0] != 'T' && patients[i].phone.description[1] != 'B' && patients[i].phone.description[2] != 'D')
            {
                fscanf(fp, "%10s", patients[i].phone.number);
            }

        }
    }
    else
    {
        printf("ERROR, NULL");
    }

    fclose(fp);
    fp = NULL;
    return i;
}


// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE* fp;
    int i = 0;
    int check = 0;

    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        for (i = 0; i <= max && check != EOF; i++)
        {
            check = fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min);
          //  printf("%d,%d,%d,%d,%d,%d\n", appoints[i].patient.patientNumber, appoints[i].date.year, appoints[i].date.month, appoints[i].date.day, appoints[i].time.hour, appoints[i].time.min);
           // check = fscanf(fp, "%d,", &temp);
        }
    }
    else
    {
        printf("Error, NULL");
    }


    fclose(fp);
    fp = NULL;
    return i-1;
}