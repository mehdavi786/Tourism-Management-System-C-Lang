#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

enum status{menu, loggedIn};
enum status currentStatus = menu;

typedef struct user
{
    char username[100];
    char password[100];
    char place[100];
    float price;
    int numberTicket;
    struct user *next;
}user;

void showMenu(void);
user* initializeUser(user*);
user* addUser(user*);
user* login(user*);
void booking(user*);
void cancellation(user*);
void changePassword(user*);
void logout(void);
void checkTicket(user*);
void filing(user*);
void exitProgram(void);
void developers(void);
void delay(float);

char currentUser[100];

int main()
{
	system("COLOR FC");
	
	developers();

	unsigned int choice1, choice2;
    
	user *userptr = NULL;
    userptr = initializeUser(userptr);
    
	while (1)
    {
    	
        if(currentStatus == menu)
        {
        	system("CLS");
        	
        	printf("\nWelcome to Muhammad*Muhammad*Muhammad Travels!\n");
        	
            printf("\n1. Add User\n2. Login User\n3. Menu\n4. Exit\n");
            
			printf("\nEnter: ");
            scanf("%u", &choice1);
            
            switch(choice1)
            {
                case 1:
                    userptr = addUser(userptr);
                    
                    break;
                    
                case 2:
                    userptr = login(userptr);
                    
                    break;
                    
                case 3:
                    showMenu();
                    
                    break;
                
				case 4:
                    exitProgram();
                    exit(0);
                
				    break;
                
				default:
                    printf("\nInvalid input!\n");
            }
        }
        
        else if(currentStatus == loggedIn)
        {
	        system("CLS");
	        
			printf("\nWelcome %s!\n", userptr->username);
				
            printf("\n1. Booking \n2. Check Total \n3. Cancel Booking \n4. Change Password \n5. Logout User \n6. Menu \n7. Exit \n");
            printf("\nEnter choice: ");
			scanf("%u", &choice2);
            
            switch(choice2)
            {
                case 1:
                    booking(userptr);
                    
                    system("PAUSE");
                    system("CLS");
                    
					break;
                
				case 2:
                    checkTicket(userptr);
                
				    system("PAUSE");
                    system("CLS");
                
				    break;
                
                case 3:
                    cancellation(userptr);
                
				    system("PAUSE");
                    system("CLS");
                
				    break;
                
				case 4:	
                    changePassword(userptr);
                    
                    system("PAUSE");
                    system("CLS");
                    
					break;
                
				case 5:
                    logout();
                
				    system("PAUSE");
                    system("CLS");
                
				    break;
                
				case 6:
                    showMenu();

                    system("CLS");
                
				    break;
                
				case 7:
					exitProgram();
                    exit(0);
                
				    break;
                
				default:
                    printf("\nInvalid input!\n");
            }
        }
    }
    
    return 0;
}

user* initializeUser(user *userptr)
{
    user *tempptr, *ptr, temp;
    FILE *fp;
    
	fp = fopen("users.txt", "r");

    if(fp == NULL)
        return NULL;

    if(fgetc(fp) == EOF)
        return NULL;

    rewind(fp);
	while(fscanf(fp, "%s %s %s %f %d", temp.username, temp.password, temp.place, &temp.price, &temp.numberTicket) != EOF)
	{
		ptr = (user*)malloc(sizeof(user));
		
		strcpy(ptr->username, temp.username);
		strcpy(ptr->password, temp.password);
		strcpy(ptr->place, temp.place);
		
		ptr->price = temp.price;
		
		ptr->numberTicket = temp.numberTicket;
		
		ptr->next = NULL;

		if(userptr == NULL)
            userptr = tempptr = ptr;
		
		else
		{
			userptr->next = ptr;
			userptr = ptr;
		}
	}
	
	fclose(fp);
    
	return tempptr;
}

void filing(user *userptr)
{
    FILE *fp;
    
	fp = fopen("users.txt", "w");
    
	while(userptr != NULL)
    {
        fprintf(fp, "%s %s %s %f %d\n", userptr->username, userptr->password, userptr->place, userptr->price, userptr->numberTicket);
        
		userptr = userptr->next;
    }
    
	fclose(fp);
}

void showMenu(void)
{
	system("CLS");
    
	printf("\nMENU\n\n1. Paris, France - Rs 400000\n2. Tokyo, Japan - Rs 600000\n3. Bangkok, Thailand - Rs 250000\n4. Abu Dhabi, UAE - Rs 380000\n5. Miami, USA - Rs 120000\n6. Rome, Italy - Rs 100000\n7. Munich, Germany - Rs 300000\n8. Madrid, Spain - Rs 320000\n9. Istanbul, Turkey - Rs 450000\n10. Gilgit, Pakistan - Rs 75000\n");
	
	system("PAUSE");
}

void checkTicket(user *userptr)
{
    while(userptr != NULL)
    {
		if(!strcmp(userptr->username, currentUser))
            break;
        
		userptr = userptr->next;
    }
    
	if(!strcmp(userptr->place, "\0") || userptr->price == 0.0 || userptr->numberTicket == 0)
    {
        printf("\nNo ticket booked!\n");
        
		return;
    }
    
	float total = 0.0;
    
	total = (userptr->price) * (userptr->numberTicket);
    
	printf("\n%d tickets booked for a total of Rs %.0f for %s.\n", userptr->numberTicket, total, userptr->place);
}

user* addUser(user* userptr)
{
    user *tempptr;
    
	tempptr = userptr;
    
	user *newptr;	
    
	newptr = (user*)malloc(sizeof(user));
    
	fflush(stdin);
	
	printf("\nEnter username: ");
    scanf("%s", newptr->username);	
    
	while(userptr != NULL)
    {
        if(!strcmp(userptr->username, newptr->username))
        {
            printf("\nUsername already exists!\n");
            delay(2.0);
            return tempptr;
        }
    
	    userptr = userptr->next;
    }
    
	userptr = tempptr;
    
	fflush(stdin);
    printf("\nEnter password: ");
    scanf(" %[^\n]s", &newptr->password);
    	    
    printf("\nUsername created!\n");
    system("PAUSE");
    
	newptr->next = NULL;
    
	strcpy(newptr->place, "N/A");
    
	newptr->price = 0.0;
    
	newptr->numberTicket = 0;

    if(userptr == NULL)
    {
        userptr = tempptr = newptr;
    }
    
	else
    {
        while(userptr->next != NULL)
        {
            userptr = userptr->next;
        }
    
	    userptr->next = newptr;
    }
    
    filing(tempptr);
    
	return tempptr;
}

user* login(user* userptr)
{
    char username[100];
    char password[100];
    
	fflush(stdin);

    printf("\nEnter Username: ");
    scanf(" %s", username);
    
	fflush(stdin);
    printf("\nEnter Password: ");
    scanf(" %[^\n]s", password);
    
	while(userptr != NULL)
    {
        if((!strcmp(userptr->username, username)) && (!strcmp(userptr->password, password)))
        {
            currentStatus = loggedIn;
            
			strcpy(currentUser, username);
            
            printf("\nLogin successful!\n");
            
			system("PAUSE");
            
			return userptr;
        }
        
		else if((!strcmp(userptr->username, username)) && (strcmp(userptr->password, password)))
        {
            printf("\nWrong Password!\n");
        
		    return userptr;
        }
        
		userptr = userptr->next;
    }
    
	printf("\nUser not found!\n");
    
	delay(2.0);
}

void booking(user *userptr)
{
    user *tempptr = userptr;
    
    char place[100];
    char placeList[10][100] = {"Paris, France", "Tokyo, Japan", "Bangkok, Thailand", "Abu Dhabi, UAE", "Miami, USA", "Rome, Italy", "Munich, Germany", "Madrid, Spain", "Istanbul, Turkey", "Gilgit, Pakistan"};
	
	while(userptr != NULL)
    {
        if(!strcmp(userptr->username, currentUser))
            break;
            
        userptr = userptr->next;
    }
    
    if(userptr == NULL)
        return;
    
    if(userptr->price != 0.0)
    {
        printf("\nCancel your previous ticket!\n");
        
        return;
    }
    
    showMenu();
    
    float priceList[] = {400000.0, 600000.0, 250000.0, 380000.0, 120000.0, 100000.0, 300000.0, 320000.0, 450000.0, 75000.0};
    
	fflush(stdin);
    printf("\nEnter code number: ");
    scanf(" %[^\n]s", place);
    
	char choice;
    
	fflush(stdin);
    printf("\nWould You Like to Confirm Booking?\n1. Yes\n2. No\n");
    printf("\nEnter choice: ");
    scanf(" %c", &choice);
    
	float price;
	
    if(choice != '1')
        return;
        
    if(strcmp(place, "1") == 0)
	{
        price = priceList[0];
     	strcpy(place, placeList[0]);
	}
	
    else if(strcmp(place, "2") == 0)
    {
    	price = priceList[1];
		strcpy(place, placeList[1]);
	}
	
    else if(strcmp(place, "3") == 0)
    {
        price = priceList[2];
     	strcpy(place, placeList[2]);
	}
	
    else if(strcmp(place, "4") == 0)
    {
        price = priceList[3];
      	strcpy(place, placeList[3]);
	}
        
    else if(strcmp(place, "5") == 0)
    {
		price = priceList[4];
		strcpy(place, placeList[4]);
	}
    
	else if(strcmp(place, "6") == 0)
	{
        price = priceList[5];
    	strcpy(place, placeList[5]);
	}
	
    else if(strcmp(place, "7") == 0)
    {
        price = priceList[6];
    	strcpy(place, placeList[7]);
	}
	
	else if(strcmp(place, "8") == 0)
	{
        price = priceList[7];
    	strcpy(place, placeList[7]);
	}
		
	else if(strcmp(place, "9") == 0)
	{
        price = priceList[8];
    	strcpy(place, placeList[8]);
	}
	
	else if(strcmp(place, "10") == 0)
	{
    	price = priceList[9];
		strcpy(place, placeList[9]);
    }
    
	else
    {
        printf("\nCode number doesn't exist!\n");
        
        return;
    }
    
    printf("\nEnter the number of tickets for booking: ");
    scanf("%d", &userptr->numberTicket);
    
    if(userptr->numberTicket == 0)
        return;
    
    strcpy(userptr->place, place);
    
    userptr->price = price;
    
    filing(tempptr);
    
    printf("\nBooking completed!\n");
}

void cancellation(user *userptr)
{
    user *tempptr = userptr;
    
	while(userptr != NULL)
    {
        if(!strcmp(userptr->username, currentUser))
            break;
    
	    userptr = userptr->next;
    }

    int flag = -1;

    if(userptr == NULL)
        printf("\nUser not found!\n");

    if(strcmp(userptr->place, "Paris, France") == 0)
        flag++;
    
	else if(strcmp(userptr->place, "Tokyo, Japan") == 0)
        flag++;
    
	else if(strcmp(userptr->place, "Bangkok, Thailand") == 0)
        flag++;
    
	else if(strcmp(userptr->place, "Abu Dhabi, UAE") == 0)
        flag++;
    
	else if(strcmp(userptr->place, "Miami, USA") == 0)
        flag++;
    
	else if(strcmp(userptr->place, "Rome, Italy") == 0)
        flag++;
    
	else if(strcmp(userptr->place, "Munich, Germany") == 0)
        flag++;
    
	else if(strcmp(userptr->place, "Madrid, Spain") == 0)
        flag++;
    
	else if(strcmp(userptr->place, "Istanbul, Turkey") == 0)
        flag++;
    
	else if(strcmp(userptr->place, "Gilgit, Pakistan") == 0)
        flag++;
    
	else
    {
        printf("\nTour not booked!\n");
        return;
    }
    
	if(flag == 0)
    {
        printf("\nBookings have been cancelled. A refund of Rs %.0f for %s (%d tickets).\n", userptr->price * userptr->numberTicket, userptr->place, userptr->numberTicket);
        
		strcpy(userptr->place, "N/A");
        
		userptr->price = 0.0;
        userptr->numberTicket = 0;
        
		filing(tempptr);
    }
}

void changePassword(user *userptr)
{
    user *tempptr = userptr;
    char passCurrent[100];
    
	fflush(stdin);
    printf("\nEnter your current password to continue: ");
    scanf(" %[^\n]s", passCurrent);
    
	while(userptr != NULL)
    {
        if(!strcmp(userptr->username, currentUser))
            break;
    	
    	printf("\nInvalid credentials!\n");
    	
	    userptr = userptr->next;
    }
    
	if(userptr == NULL)
        return;
    
	if(!strcmp(passCurrent, userptr->password))
    {
        printf("\nEnter new password: ");
        scanf(" %[^\n]s", userptr->password);
        printf("\nPassword Changed!\n");
    }
    
    else
    {
    	printf("\nIncorrect password!\n");
	}
    
	filing(tempptr);
}

void logout(void)
{
    
	if(currentStatus == menu || strcmp(currentUser, "\0") == 0)
    {
        printf("\nLog in first!\n");
    
	    return;
    }
    
	strcpy(currentUser, "\0");
    
	currentStatus = menu;
    
	printf("\nSuccessfully logged out.\n");
}

void exitProgram(void)
{
	printf("\nProgramming Fundamentals Laboratory Project BS(CS)-1E\n");
	printf("\nMuhammad Talha--> 21K-3349\n");
	printf("\nMuhammad Hamza--> 21K-4579\n");
	printf("\nMuhammad Hasan--> 21K-4885\n");
	system("PAUSE");
}

void developers(void)
{
	printf("\nProject: Tourism Management System\n");
	printf("\nDevelopers: Talha, Hamza, and Hasan\n");
	
	delay(3.5);
    system("CLS");
}

void delay(float t)
{
    clock_t start = 0;
    start = clock();

    while((clock() - start) < (t * 1000));

    return;
}
