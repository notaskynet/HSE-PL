#include <stdio.h>

#define TRUE 1

#define SUM      1
#define DIFFENCE 2
#define MULTIPLY 3
#define DEVIDE   4


#define CLEAN_BUFFER() { int ch; while ((ch = getchar()) != EOF && ch != '\n') {} }


int make_choice(const char **options, size_t options_size) {
    int choice, input_size;
    int i;

    for(i = 0; i < options_size; i++) {
        printf("%s\n", options[i]);
    }

    while (TRUE) {
        input_size = scanf("%d", &choice);
        CLEAN_BUFFER()

        if((input_size != 1) || !( (1 <= choice) && (choice <= options_size))) {
            printf("Error! Try again!\n");
        }
        else {
            break;
        }
    }
    return choice;
}


void enter_nums(int* first_num, int* second_num) {
    int input_size;

    printf("Enter 2 nums:\n");
    while (TRUE) {
        input_size = scanf("%d %d", first_num, second_num);
        CLEAN_BUFFER()

        if(input_size != 2) {
            printf("Error! Try again!\n");
        }
        else {
            return;
        }
            printf("Error! Try again!\n");

    }
}


void calculate(int operation_type, int first_num, int second_num) {   
     switch(operation_type) {
        case SUM: {
            printf("%d + %d = %d\n", first_num, second_num,first_num + second_num);
            break;
        }
        case DIFFENCE: {
            printf("%d - %d = %d\n", first_num, second_num, first_num - second_num);
            break;
        }
        case MULTIPLY: {
            printf("%d * %d = %d\n", first_num, second_num, first_num * second_num);
            break;
        }
        case DEVIDE: {
            printf("%d / %d = %d, remainder is %d\n", first_num, second_num,
                   first_num / second_num, first_num % second_num);
            break;
        }
    }
}


int main() {
    int choice, first_num, second_num;
    const char *options[4] = {
        "1. Sum two nums" ,
        "2. Subtraction from one number to another",
        "3. Multiple two nums",
        "4. Divide one number by another"
    };
    size_t options_size = 4;
    const char *welcome_text  = "Hi! This program can do some operations and display the result on the screen.\nPlease, choose one option from this list:\n";;

    printf("%s", welcome_text);
    choice = make_choice(options, options_size);
    enter_nums(&first_num, &second_num);
    calculate(choice, first_num, second_num);
    scanf("%s");
}

