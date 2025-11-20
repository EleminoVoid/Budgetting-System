//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//prototypes
// This function prompts the user to input how much they have earned and updates their balance accordingly.
void newUserStart();

// This function displays the start menu which shows the user's current balance, monthly earnings, and monthly spending.
void startMenu(float condition, float balance, float earn, float spend);

// This function displays the list of earnings and allows the user to add or delete items from the list.
float display_earn_choice(struct earns earn[], int num_earn, float* earning);

// This function displays the list of spendings and allows the user to add or delete items from the list.
float display_spend_choice(struct spends spend[], int num_spend, float* spending);

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void logOut(){
	system("cls");
	printf("\n\n\t\t\t------------------------------------------------------------------\n");	
	printf("\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\tThank you for using the program\n");
	printf("\t\t\t\t\tSee you soon!");
	printf("\n\n\n\n\n\n\n\n");
	printf("\n\n\t\t\t------------------------------------------------------------------\n");	
}


void newUserStart(){
	char start[100];
	float bal;
	char check;
	createMonthDataFile();
	FILE *fp = fopen("DATA/balance.txt", "r+");
		do {
		printf("New User Detected!\n");
		printf("How much is your initial balance?\n");
		scanf(" %f", &bal);
		check = user_check();
			if (check == 1) {
				write_bal(&bal);
				printf("Balance updated!\n");
				break;
			}
			
		
	} while(1);
}


void startMenu(float condition, float balance, float earn, float spend, float add_minus_bal){
	printf("\n\n\t\t\t------------------------------------------------------------------\n");	
	
	if(balance < 0){
		red();
		printf("\t\t\t\t\t(Careful with your spending)\n");
		reset();
	}
		printf("\t\t\t\t\tCurrent Balance:\t\t\t %.2f\n", balance);	
	printf("\t\t\t\t\tMonthly Earning:\t\t\t %.2f\n", earn);
	printf("\t\t\t\t\tMonthly Spending:\t\t\t %.2f\n", spend);
	if(add_minus_bal > 0){
		green();
		printf("\t\t\t\t\t+:\t\t\t\t\t %.2f", add_minus_bal);
	}else if (add_minus_bal < 0){
		red();
		printf("\t\t\t\t\t-:\t\t\t\t\t %.2f", add_minus_bal);
	}
	reset();
	printf("\n\t\t\t------------------------------------------------------------------\n");
	printf("\n\n\t\t\t OPTIONS: \n\n");
	printf("\t\t\t\t\t1. Check Monthly Earnings\n");	
	printf("\t\t\t\t\t2. Check Monthly Spending\n");
	printf("\t\t\t\t\t3. Immediate Earned\n");
	printf("\t\t\t\t\t4. Immediate Spent\n");
	printf("\t\t\t\t\t0. Exit\n");
}

float display_earn_choice(struct earns earn[], int num_earn, float *earning){
	    int choice;
	while (1) {
		printf("EARNINGS\n");
        display_earn(earn, num_earn, earning);
        printf("1. Add item\n");
        printf("2. Delete item\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline character

        switch (choice) {
            case 1:
                if (num_earn == MAX_EARN) {
                    printf("Error: Max number of earn reached\n");
                } else {
                    struct earns new_earn;
                    printf("Enter item name: ");
                    fgets(new_earn.name, 50, stdin);
                    new_earn.name[strcspn(new_earn.name, "\n")] = 0; // remove newline character
                    printf("Enter item value: ");
                    scanf("%f", &new_earn.value); 
                    getchar(); // consume newline character
                    earn[num_earn++] = new_earn;
                    printf("Item added\n");
                    write_earn(earn, num_earn);
                }
                break;
            case 2:
                if (num_earn == 0) {
                    printf("Error: No earn to delete\n");
                } else {
                    int index;
                    printf("Enter item index: ");
                    scanf("%d", &index);
                    getchar(); // consume newline character
                    if (index < 1 || index > num_earn) {
                        printf("Error: Invalid index\n");
                    } else {
                        memmove(&earn[index - 1], &earn[index], (num_earn - index) * sizeof(struct earns));
                        num_earn--;
                        printf("Item deleted\n");
                        write_earn(earn, num_earn);
                    }
                }
                break;
            case 3:
            	system("cls");
                return 0;
            default:
                printf("Error: Invalid choice\n");
                break;
        }
         system("cls");
	}
}

float display_spend_choice(struct spends spend[], int num_spend, float *spending){
	    int choice;
	while (1) {
		printf("SPENDINGS\n");
        display_spend(spend, num_spend, spending);
        printf("1. Add item\n");
        printf("2. Delete item\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline character

        switch (choice) {
            case 1:
                if (num_spend == MAX_SPEND) {
                    printf("Error: Max number of spend reached\n");
                } else {
                    struct spends new_spend;
                    printf("Enter item name: ");
                    fgets(new_spend.name, 50, stdin);
                    new_spend.name[strcspn(new_spend.name, "\n")] = 0; // remove newline character
                    printf("Enter item value: ");
                    scanf("%f", &new_spend.value); 
                    getchar(); // consume newline character
                    spend[num_spend++] = new_spend;
                    printf("Item added\n");
                    write_spend(spend, num_spend);
                }
                break;
            case 2:
                if (num_spend == 0) {
                    printf("Error: No spend to delete\n");
                } else {
                    int index;
                    printf("Enter item index: ");
                    scanf("%d", &index);
                    getchar(); // consume newline character
                    if (index < 1 || index > num_spend) {
                        printf("Error: Invalid index\n");
                    } else {
                        memmove(&spend[index - 1], &spend[index], (num_spend - index) * sizeof(struct spends));
                        num_spend--;
                        printf("Item deleted\n");
                        write_spend(spend, num_spend);
                    }
                }
                break;
            case 3:
            	system("cls");;
                return 0;
            default:
                printf("Error: Invalid choice\n");
                break;
        }
         system("cls");;
	}
}
