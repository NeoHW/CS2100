#include <stdio.h>

int main (void) {
    char operation;
    int flag = 1;
    float firstNum;
    float secondNum;
    
    while(flag) { // while true
        printf("Please enter an operation (+, -, *, / or q to quit): ");
        scanf(" %c", &operation);

        switch(operation) {
            case '+':
                printf("\nEnter the first number: ");
                scanf("%f", &firstNum);
                printf("\nEnter the second number: ");
                scanf("%f", &secondNum);
                printf("\n%f + %f = %.2f\n\n", firstNum, secondNum, firstNum+secondNum);
                break;
            case '-':
                printf("Enter the first number: ");
                scanf("%f", &firstNum);
                printf("Enter the second number: ");
                scanf("%f", &secondNum);
                printf("\n%f - %f = %.2f\n\n", firstNum, secondNum, firstNum-secondNum);
                break;
            case '*':
                printf("Enter the first number: ");
                scanf("%f", &firstNum);
                printf("Enter the second number: ");
                scanf("%f", &secondNum);
                printf("\n%f * %f = %.2f\n\n", firstNum, secondNum, firstNum*secondNum);
                break;
            case '/':
                printf("Enter the first number: ");
                scanf("%f", &firstNum);
                printf("Enter the second number: ");
                scanf("%f", &secondNum);
                printf("\n%f / %f = %.2f\n\n", firstNum, secondNum, firstNum/secondNum);
                break;
            case 'q':
                flag = 0;
                break;
            default:
                printf("Unrecognized operation \n");
        }   
    }
    printf("Bye! \n");
}