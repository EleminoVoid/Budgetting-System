//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//prototypes
// Returns the name of a month given its number (1-12)
char *monthName(int month);

// Returns the number of months that have passed since the date represented by prevDate
int monthsPassed(struct tm prevDate);

// Updates the program based on the current month
// Reads the lastMonth and lastDate from a file
// If the current month is different from the last month, updates the program and writes currentMonth and lastDate to file
int updateMonthData();


void createMonthDataFile();
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

char *monthName(int month) {
    switch (month) {
        case 1:
            return "January";
        case 2:
            return "February";
        case 3:
            return "March";
        case 4:
            return "April";
        case 5:
            return "May";
        case 6:
            return "June";
        case 7:
            return "July";
        case 8:
            return "August";
        case 9:
            return "September";
        case 10:
            return "October";
        case 11:
            return "November";
        case 12:
            return "December";
        default:
            return "Invalid month";
    }
}

int monthsPassed(struct tm prevDate) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    double diff = difftime(mktime(&tm), mktime(&prevDate));
    int months = (int) (diff / (60 * 60 * 24 * 30.44)); // Average number of seconds in a month

    return months;
}

void createMonthDataFile() {
	int year, month, day;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentMonth = tm.tm_mon + 1;
    FILE *fp;
   	year = tm.tm_year + 1900; 
    month = currentMonth;
    day = tm.tm_mday;

    fp = fopen("DATA/monthData.txt", "w");
    fprintf(fp, "%d %d %d", year, month, day);
    fclose(fp);
}

int updateMonthData() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentMonth = tm.tm_mon + 1;
    
    printf("The current month is: %s\n", monthName(currentMonth));

    int lastMonth = 0;

    // Read lastMonth and lastDate from file
    int lastYear = 0;
    int lastDay = 0;
    FILE *fp;
    fp = fopen("DATA/monthData.txt", "r");
    if (fp != NULL) {
        fscanf(fp, "%d %d %d", &lastYear, &lastMonth, &lastDay);
        fclose(fp);
    }

    // Create struct representing the previous date
    struct tm prevDate = {0};
    prevDate.tm_year = lastYear - 1900;  // Convert to year since 1900
    prevDate.tm_mon = lastMonth - 1;     // Convert to 0-indexed month
    prevDate.tm_mday = lastDay;

    int months = monthsPassed(prevDate);
	if (currentMonth<lastMonth){
		return 0;
	}
    if (lastMonth != currentMonth) {
        printf("%d months have passed since the last update.\n", months);
        printf("Updating program...\n");


        lastYear = tm.tm_year + 1900; // Convert to year since 1900
        lastMonth = currentMonth;
        lastDay = tm.tm_mday;

        // Write currentMonth and lastDate to file
        fp = fopen("DATA/monthData.txt", "w");
        fprintf(fp, "%d %d %d", lastYear, lastMonth, lastDay);
        fclose(fp);
    } else {
        printf("Not much has changed\n", monthName(prevDate.tm_mon + 1));
    }

    return months;
}
