#include<stdio.h>
#include<string.h>
#define espresso_price 3.5
#define cappuccino_price 4.5
#define mocha_price 5.5
#define espresso_grams 8
#define espresso_water 30
#define espresso_milk 0
#define espresso_chocolate 0
#define cappuccino_grams 8
#define cappuccino_water 30
#define cappuccino_milk 70
#define cappuccino_chocolate 0
#define mocha_grams 8
#define mocha_water 39
#define mocha_milk 160
#define mocha_chocolate 30

int beans = 100, water = 50, milk = 400, chocolate = 60;
float total_sales = 0;
const char admin_pw[] = "1234";
const char user_pw[] = "1234";

void displayMenu(){
    printf("\nMenu:\n");
    printf("1. Espresso - %.2f AED\n",espresso_price);
    printf("2. Cappuccino - %.2f AED\n",cappuccino_price);
    printf("3. Mocha - %.2f AED\n",mocha_price);
}

void orderCoffee(){
    int choice;
    displayMenu();
    printf("Select your coffee (1-3), or 0 to exit: ");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            if(beans >= espresso_grams && water >= espresso_water){
                beans -= espresso_grams;
                water -= espresso_water;
                total_sales += espresso_price;
                printf("You ordered Espresso. Total price: %.2f AED\n", total_sales);
            } else {
                printf("Not enough ingredients for Espresso.\n");
            }
            break;
        case 2:
            if(beans >= cappuccino_grams && water >= cappuccino_water && milk >= cappuccino_milk){
                beans -= cappuccino_grams;
                water -= cappuccino_water;
                milk -= cappuccino_milk;
                total_sales += cappuccino_price;
                printf("You ordered Cappuccino. Total price: %.2f AED\n", total_sales);
            } else {
                printf("Not enough ingredients for Cappuccino.\n");
            }
            break;
        case 3:
            if(beans >= mocha_grams && water >= mocha_water && milk >= mocha_milk && chocolate >= mocha_chocolate){
                beans -= mocha_grams;
                water -= mocha_water;
                milk -= mocha_milk;
                chocolate -= mocha_chocolate;
                total_sales += mocha_price;
                printf("You ordered Mocha. Total price: %.2f AED\n", total_sales);
            } else {
                printf("Not enough ingredients for Mocha.\n");
            }
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice, please select 1-3, or 0 to exit.\n");
    }
}

int authenticate(int user_type){
    char input_password[20];
    if(user_type == 1){
        printf("Enter admin password: ");
    } else {
        printf("Enter user password: ");
    }
    scanf("%s", input_password);
    
    if(user_type == 1 && strcmp(input_password, admin_pw) == 0){
        printf("Admin login successful!\n");
        return 1;
    } else if(user_type == 2 && strcmp(input_password, user_pw) == 0){
        printf("User login successful!\n");
        return 1;
    } else {
        printf("Invalid password.\n");
        return 0;
    }
}

void adminMenu(){
    printf("\nAdmin Menu:\n");
    printf("Total sales: %.2f AED\n", total_sales);
    printf("Remaining ingredients: Beans: %d g, Water: %d ml, Milk: %d ml, Chocolate: %d g\n", beans, water, milk, chocolate);
}

int main(){
    int user_type;
    printf("Choose account type: 1 for Admin, 2 for User: ");
    scanf("%d", &user_type);
    
    if(user_type == 1){
        if(authenticate(1)){
            adminMenu();
        }
    } else if(user_type == 2){
        if(authenticate(2)){
            orderCoffee();
        }
    } else {
        printf("Invalid account type selected.\n");
    }
    
    return 0;
}
