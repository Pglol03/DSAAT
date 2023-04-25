#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAPE_SIZE 1000
#define MAX_NUM_STATES 100
#define MAX_NUM_SYMBOLS 10
#define MAX_NUM_TRANSITIONS 1000

char inputtape[1000];
FILE *filePointer;
int pointer = 0;

typedef struct
{
    int current_state;
    int current_symbol;
    int next_state;
    int next_symbol;
    int direction;
} Transition;

typedef struct
{
    int num_states;
    int start_state;
    int accept_state;
    int reject_state;
    int num_symbols;
    int tape_alphabet[MAX_NUM_SYMBOLS];
    Transition transitions[MAX_NUM_TRANSITIONS];
} TuringMachine;

void run_turing_machine(TuringMachine *tm, char *input)
{
    int head_position = 0;
    int current_state = tm->start_state;
    char tape[MAX_TAPE_SIZE];
    int tape_size = strlen(input);

    strcpy(tape, input);

    while (1)
    {
        int i;

        // find transition for current state and current symbol
        Transition *t = NULL;

        for (i = 0; i < MAX_NUM_TRANSITIONS; i++)
        {
            if (tm->transitions[i].current_state == current_state &&
                tm->transitions[i].current_symbol == tape[head_position])
            {
                t = &(tm->transitions[i]);
                break;
            }
        }

        if (t == NULL)
        {
            printf("Rejected\n");
            return;
        }

        // update tape
        tape[head_position] = t->next_symbol;

        // update head position
        if (t->direction == -1)
        {
            head_position--;
        }
        else if (t->direction == 1)
        {
            head_position++;
        }

        // check if tape is out of bounds
        if (head_position < 0 || head_position >= tape_size)
        {
            printf("Rejected\n");
            return;
        }

        // update current state
        current_state = t->next_state;

        // check if machine has halted
        if (current_state == tm->accept_state)
        {
            printf("Accepted\n");
            return;
        }
        else if (current_state == tm->reject_state)
        {
            printf("Rejected\n");
            return;
        }
    }
}

int chartoint(char ch)
{
    return (ch - '0');
}

int main()
{
    char temp;
    TuringMachine tm;
    char Fname[200] ="";
    printf("Do You want to Load a file or create a new one for 'Turing Machine' ? \n");
    printf("1 : 'Load File' \n");
    printf("2 : 'Make New File' \n");
    int menu;
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            printf("Enter File Name : \n");
            
            scanf("%s", Fname);
            filePointer = fopen(Fname,"r");
            if(filePointer == NULL){
                printf("\n\"%s\" File NOT FOUND!",Fname);
		        exit(1);
            }
            fscanf(filePointer, "%s", &inputtape);
            printf("The input tape is - %s", inputtape);
            tm.num_states = chartoint(inputtape[pointer++]);
            tm.start_state = chartoint(inputtape[pointer++]);
            tm.accept_state = chartoint(inputtape[pointer++]);
            tm.reject_state = chartoint(inputtape[pointer++]);
            tm.num_symbols = chartoint(inputtape[pointer++]);
            for (int i = 0; i < tm.num_symbols; i++){
                temp = inputtape[pointer++];
                tm.tape_alphabet[i] = (int)temp;
            }
            for (int i = 0; i < (tm.num_states * tm.num_symbols); i++){
                tm.transitions[i].current_state = chartoint(inputtape[pointer++]);
                temp = inputtape[pointer++];

                tm.transitions[i].current_symbol = (int)temp;

                tm.transitions[i].next_state = chartoint(inputtape[pointer++]);

                temp = inputtape[pointer++];

                tm.transitions[i].next_symbol = (int)temp;

                tm.transitions[i].direction = chartoint(inputtape[pointer++]);

            }
            printf("\nDo you want to run the default condition or define ur own?\n");
            printf("0 : Run Default\n");
            printf("1 : User Defind\n");
            int uchoice;
            scanf("%d",&uchoice);
            if(uchoice) break;
            char dinput[MAX_TAPE_SIZE];
            int dx = 1;
            while(dx){
                int dchoice;
                dchoice = chartoint(inputtape[pointer++]);
                // printf("\nChoice Entered: %d\n", choice);
                int dlocalpointer = 0;
                switch (dchoice)
                {
                case 1:
                    // printf("Enter input: ");

                    // fscanf(filePointer, "%s", input);

                    while (inputtape[pointer] != 'B')
                    {
                        dinput[dlocalpointer++] = inputtape[pointer++];
                    }

                    dinput[dlocalpointer++] = inputtape[pointer++];
                    // printf("\n Input is - ");
                    // puts(input);
                    run_turing_machine(&tm, dinput);
                    exit(0);
                    break;
                case 2:
                    dx = 0;
                    break;
                default:
                    break;
                }
            }
            break;

        case 2:
            printf("Enter File Name : \n");
            scanf("%s", Fname);
            filePointer = fopen(Fname,"w");
            if(filePointer == NULL){
                printf("\n%s\" File NOT FOUND!",Fname);
		        exit(1);
            }
            printf("\nEnter number of states : \n");
            scanf("%d", &tm.num_states);
            temp = tm.num_states+'0';
            fputs(&temp, filePointer) ;
            printf("Enter Start State : \n");
            scanf("%d", &tm.start_state);
            temp = tm.start_state+'0';
            fputs(&temp, filePointer) ;
            printf("Enter Accept State : \n");
            scanf("%d", &tm.accept_state);
            temp = tm.accept_state+'0';
            fputs(&temp, filePointer) ;
            printf("Enter Reject State : \n");
            scanf("%d", &tm.reject_state);
            temp = tm.reject_state+'0';
            fputs(&temp, filePointer) ;
            printf("Enter number of symbols : \n\n");
            scanf("%d", &tm.num_symbols);
            temp = tm.num_symbols+'0';
            fputs(&temp, filePointer) ;

            for (int i = 0; i < tm.num_symbols; i++)
            {
                printf("Enter the '%d' symbol : \n", i + 1);
                scanf(" %c", &temp);
                // temp = getchar();
                tm.tape_alphabet[i] = (int)temp;
                scanf("%d", &tm.num_symbols);
            }

            for (int i = 0; i < (tm.num_states * tm.num_symbols); i++)
            {
                printf("Enter 'current state' for transition %d : \n", i);
                scanf("%d", &tm.transitions[i].current_state);
                printf("Enter 'current symbol' for transition %d : \n", i);
                scanf(" %c", &temp);
                // temp = getchar();
                tm.transitions[i].current_symbol = (int)temp;
                printf("Enter 'next state' for transition %d : \n", i);
                scanf("%d", &tm.transitions[i].next_state);
                printf("Enter 'next symbol' for transition %d : \n", i);
                scanf(" %c", &temp);
                // temp = getchar();
                tm.transitions[i].next_symbol = (int)temp;
                printf("Enter 'direction' for transition %d : \n", i);
                scanf("%d", &tm.transitions[i].direction);
                printf("\n\n");
            }
            break;
        default:
            break;
        }

    

    
//     // Even Length Program
//     // initialize tm with transitions
//     tm.num_states = 2;
//     tm.start_state = 1;
//     tm.accept_state = 3;
//     tm.reject_state = 0;
//     tm.num_symbols = 3;
//     tm.tape_alphabet[0] = '0';
//     tm.tape_alphabet[1] = '1';
//     tm.tape_alphabet[2] = 'B';
//     // ##########################################
//     // Transition 1: (1, '0') -> (2, '0', R)
//     tm.transitions[0].current_state = 1;
//     tm.transitions[0].current_symbol = '0';
//     tm.transitions[0].next_state = 2;
//     tm.transitions[0].next_symbol = '0';
//     tm.transitions[0].direction = 1;

//      //Transition 2: (1, '1') -> (2, '1', R)
//     tm.transitions[1].current_state = 2;
//     tm.transitions[1].current_symbol = '0';
//     tm.transitions[1].next_state = 1;
//     tm.transitions[1].next_symbol = '0';
//     tm.transitions[1].direction = 1;

//      //Transition 3: (2, '0') -> (1, '0', L)
//     tm.transitions[2].current_state = 1;
//     tm.transitions[2].current_symbol = '1';
//     tm.transitions[2].next_state = 1;
//     tm.transitions[2].next_symbol = '1';
//     tm.transitions[2].direction = 1;

//      //Transition 4: (2, '1') -> (2, '1', l)
//     tm.transitions[3].current_state = 2;
//     tm.transitions[3].current_symbol = '1';
//     tm.transitions[3].next_state = 2;
//     tm.transitions[3].next_symbol = '1';
//     tm.transitions[3].direction = 1;

// // transition 5: (1, B) -> (4, B, N)
// tm.transitions[4].current_state = 1;
// tm.transitions[4].current_symbol = 'B';
// tm.transitions[4].next_state = 3;
// tm.transitions[4].next_symbol = 'B';
// tm.transitions[4].direction = 0;

// // transition 6: (2, B) -> (0, B, N)
// tm.transitions[5].current_state = 2;
// tm.transitions[5].current_symbol = 'B';
// tm.transitions[5].next_state = 0;
// tm.transitions[5].next_symbol = 'B';
// tm.transitions[5].direction = 0;


    char input[MAX_TAPE_SIZE];
    int x = 1;
    while (x)
    {
        printf("enter 1 to continue or 2 to exit :");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter input: ");
            scanf("%s", input);
            run_turing_machine(&tm, input);
            break;
        case 2:
            x = 0;
            break;
        default:
            break;
        }
    }
    return 0;
}
