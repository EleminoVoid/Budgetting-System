#define MAX_SPEND 100
#define MAX_EARN 100
#define MAX_USERS 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include "color.h"
#include "month.h"
#include "login.h"
#include "budgeting.h"
#include "menu.h"
#include "folder.h"


int main() {
	int exit = 0;
	make_directory();
	exit = loginMenu();
	if(exit == 1) {
		logOut();
		return 0;
	}
	if (read_total_bal() == NULL && read_total_earn() == NULL && read_total_earn() == NULL){
		newUserStart();
		
	};
	

	float condition, balance, initial_balance, add_minus_bal;
	float earning, spending;
	int optChoice;
	int months;
	
	months = updateMonthData();
	balance = read_total_bal();
	earning = read_total_earn();
	spending = read_total_spend();
	add_minus_bal= earning - spending;
	if (months != 0){
		month_bal_update(months, &balance, add_minus_bal);
	}
	
	do{  
	struct earns earn[MAX_EARN];
    int num_earn = read_earn(earn);
	struct spends spend[MAX_SPEND];
    int num_spend = read_spend(spend);
    add_minus_bal= earning - spending;
	
		startMenu(condition, balance, earning, spending, add_minus_bal);
	    scanf(" %d", &optChoice);
		switch (optChoice){
			case 1:
				system("cls");
				exit = display_earn_choice(earn, num_earn, &earning);
				break;
			
			case 2:
				system("cls");
				exit = display_spend_choice(spend, num_spend, &spending);
				break;
			
			case 3:
				system("cls");
				immediate_earn(&balance);
				break;
			
			case 4:
				system("cls");	
				immediate_spend(&balance);
				break;
			
			case 0:
				logOut();
				exit = 1;
				break;
				
			default: system("cls"); exit = 0;	
			
			}
			
	}while (exit != 1);
	
	return 0;
}
    


