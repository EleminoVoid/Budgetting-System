

struct earns {
    char name[50];
    float value;
};

struct spends {
    char name[50];
    float value;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//prototypes

// Reads the total balance from file
float read_total_bal();

// Writes the total balance to file
float write_bal(float *balance);

// Asks user for confirmation and returns 1 if user inputs "Y", 0 otherwise
int user_check();

// Allows user to immediately enter earnings and updates balance
float immediate_earn(float *balance);

// Allows user to immediately enter spendings and updates balance
float immediate_spend(float *balance);

// Reads the total earnings from file
float read_total_earn();

// Writes the total earnings to file
void write_total_earn(float earning);

// Reads the earnings from file and stores them in an array of structures
float read_earn(struct earns earn[]);

// Writes the earnings to file from an array of structures
void write_earn(struct earns earn[], int num_earn);

// Displays the earnings stored in an array of structures
void display_earn(struct earns earn[], int num_earn, float *earning);

// Reads the total spendings from file
float read_total_spend();

// Writes the total spendings to file
void write_total_spend(float spending);

// Reads the spendings from file and stores them in an array of structures
float read_spend(struct spends spend[]);

// Writes the spendings to file from an array of structures
void write_spend(struct spends spend[], int num_spend);

// Displays the spendings stored in an array of structures
void display_spend(struct spends spend[], int num_spend, float *spending);

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float month_bal_update(int months, float *balance, float add_minus_bal){
    float bal, temp_bal, initial_balance;
    initial_balance = *balance;
    printf("Previous Balance : %.2f\n",initial_balance);
	temp_bal = float(months) * add_minus_bal;
	*balance += temp_bal;
	write_bal(balance);
	printf("Balance updated!\n");
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

float read_total_bal() {
    float balance = 0;
    FILE *fp = fopen("DATA/balance.txt", "r");
    if (fp == NULL) {
        printf("Failed to find balance.txt\n");
        return balance;
    }
    fscanf(fp, "%f", &balance);
    fclose(fp);
    return balance;
}

float write_bal(float *balance) {
    FILE *fp = fopen("DATA/balance.txt", "w");
    if (fp == NULL) {
        printf("Failed to find balance.txt\n");
        return -1;
    }
    fprintf(fp, "%.2f", *balance);
    fclose(fp);
    return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int user_check(){
	char check;
	printf("Are you sure? (Y/N)\n");
	do{
		scanf(" %c", &check);
		if (toupper(check) == 'Y'){
			system("cls");
			return 1;
		}
		else if (toupper(check) == 'N'){
			system("cls");
			return 0;
		}
	} while(1);
}


float immediate_earn(float *balance) {	
	char earned[100];
	float temp_bal, initial_balance;
	char check;
	
	initial_balance = *balance;
		do {
		printf("How much did you earn? Type out to exit\n");
		scanf(" %s", earned);
		if (strcmp(earned, "out") == 0 || strcmp(earned, "Out") == 0 || strcmp(earned, "OUT") == 0) {
			system("cls");
			break;
		}
		else {
			temp_bal = atof(earned);
			*balance += temp_bal;
			printf("New balance: %.2f\n", *balance);
			check = user_check();
			if (check == 1) {
				write_bal(balance);
				printf("Balance updated!\n");
				break;
			}
			else {
				*balance = initial_balance;
			}
		}
	} while(1);
		
	return 0;
}

//---------------------------------------------------------------------------------------------
float immediate_spend(float *balance) {	
	char spent[100];
	float bal, temp_bal, initial_balance;
	char check;
	
	initial_balance = *balance;
		do {
		printf("How much did you spend? Type out to exit\n");
		scanf(" %s", spent);
		if (strcmp(spent, "out") == 0 || strcmp(spent, "Out") == 0 || strcmp(spent, "OUT") == 0) {
			system("cls");
			break;
		}
		else {
			temp_bal = atof(spent);
			if(temp_bal > initial_balance){
				printf("This is over the budget are you sure? ");
			}
			*balance -= temp_bal;
			printf("New balance: %.2f\n", *balance);
			check = user_check();
			if (check == 1) {
				write_bal(balance);
				printf("Balance updated!\n");
				break;
			}
			else {
				*balance = initial_balance;
			}
		}
	} while(1);
		
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


float read_total_earn() {
	float earnings;
    FILE *fp = fopen("DATA/total_earn.txt", "r");
    if (fp == NULL) {
        printf("Failed to find earn.txt\n");
        return 0;
    }
    fscanf(fp, "%f", &earnings);
    fclose(fp);
    return earnings;
}

void write_total_earn(float earning) {
    FILE *fp = fopen("DATA/total_earn.txt", "w");
    fprintf(fp, "%f", earning);
    fclose(fp);
    }


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


float read_earn(struct earns earn[]) {
	int num_earn = 0;
    FILE *fp = fopen("DATA/earn.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%s %f", earn[num_earn].name, &earn[num_earn].value) == 2) {
            num_earn++;
        }
        fclose(fp);
    }
    return num_earn;
}

void write_earn(struct earns earn[], int num_earn) {
    FILE *fp = fopen("DATA/earn.txt", "w");
    if (fp != NULL) {
        for (int i = 0; i < num_earn; i++) {
            fprintf(fp, "%s %f\n", earn[i].name, earn[i].value);
        }
        fclose(fp);
    }
}

void display_earn(struct earns earn[], int num_earn, float *earning)  {
    float total_value;
	if (num_earn == 0) {
		total_value = 0;
        printf("No items\n");
        printf("Total value: %f\n", total_value);
    } 
	else {
		total_value = 0;
        printf("Items:\n");
        for (int i = 0; i < num_earn; i++) {
            printf("%d. %s (%f)\n", i + 1, earn[i].name, earn[i].value); /*"%d. %s (%f)\n" outputs for example 1. Rent (20,000)*/
            total_value += earn[i].value;
            *earning = total_value;/*Avoids redunduncy from previous trials*/
        }
        printf("Total value: %f\n", total_value);
    }
    write_total_earn(total_value);
}

////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float read_total_spend() {
	float spendings;
    FILE *fp = fopen("DATA/total_spend.txt", "r");
    if (fp == NULL) {
        printf("Failed to find spend.txt\n");
        return 0;
    }
    fscanf(fp, "%f", &spendings);
    fclose(fp);
    return spendings;
}

void write_total_spend(float spending) {
    FILE *fp = fopen("DATA/total_spend.txt", "w");
    fprintf(fp, "%f", spending);
    fclose(fp);
    }
////----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
float read_spend(struct spends spend[]) {
	int num_spend = 0;
    FILE *fp = fopen("DATA/spend.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%s %f", spend[num_spend].name, &spend[num_spend].value) == 2) {
            num_spend++;
        }
        fclose(fp);
    }
    return num_spend;
}

void write_spend(struct spends spend[], int num_spend) {
    FILE *fp = fopen("DATA/spend.txt", "w");
    if (fp != NULL) {
        for (int i = 0; i < num_spend; i++) {
            fprintf(fp, "%s %f\n", spend[i].name, spend[i].value);
        }
        fclose(fp);
    }
}

void display_spend(struct spends spend[], int num_spend, float *spending)  {
    float total_value;
	if (num_spend == 0) {
		total_value = 0;
        printf("No items\n");
        printf("Total value: %f\n", total_value);
    } 
	else {
		total_value = 0;
        printf("Items:\n");
        for (int i = 0; i < num_spend; i++) {
            printf("%d. %s (%f)\n", i + 1, spend[i].name, spend[i].value); /*"%d. %s (%f)\n" outputs for example 1. Rent (20,000)*/
            total_value += spend[i].value;
            *spending = total_value;/*Avoids redunduncy from previous trials*/
        }
        printf("Total value: %f\n", total_value);
    }
    write_total_spend(total_value);
}
