#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAPE_SIZE 1000
#define MAX_NUM_STATES 100
#define MAX_NUM_SYMBOLS 10
#define MAX_NUM_TRANSITIONS 1000

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

int main()
{
    TuringMachine tm;
    printf("Enter number of states : \n");
    scanf("%d", &tm.num_states);
    printf("Enter Start State : \n");
    scanf("%d", &tm.start_state);
    printf("Enter Accept State : \n");
    scanf("%d", &tm.accept_state);
    printf("Enter Reject State : \n");
    scanf("%d", &tm.reject_state);
    printf("Enter number of symbols : \n");
    scanf("%d", &tm.num_symbols);

    for (int i = 0; i < tm.num_symbols; i++)
    {
        printf("Enter the '%d' symbol : \n", i + 1);
        scanf("%d", &tm.tape_alphabet[i]);
    }

    for (int i = 0; i < (tm.num_states * 2); i++)
    {
        printf("Enter 'current state' for transition %d : \n", i);
        scanf("%d", &tm.transitions[i].current_state);
        printf("Enter 'current symbol' for transition %d : \n", i);
        scanf("%d", &tm.transitions[i].current_symbol);
        printf("Enter 'next state' for transition %d : \n", i);
        scanf("%d", &tm.transitions[i].next_state);
        printf("Enter 'next symbol' for transition %d : \n", i);
        scanf("%d", &tm.transitions[i].next_symbol);
        printf("Enter 'direction' for transition %d : \n", i);
        scanf("%d", &tm.transitions[i].current_state);
        printf("\n\n");
    }
    // // initialize tm with transitions for a simple two-state, one-symbol machine
    // tm.num_states = 2;
    // tm.start_state = 1;
    // tm.accept_state = 2;
    // tm.reject_state = 0;
    // tm.num_symbols = 1;
    // tm.tape_alphabet[0] = '0';

    // // transition 1: (1, '0') -> (2, '0', R)
    // tm.transitions[0].current_state = 1;
    // tm.transitions[0].current_symbol = '0';
    // tm.transitions[0].next_state = 2;
    // tm.transitions[0].next_symbol = '0';
    // tm.transitions[0].direction = 1;

    // // run the machine with input "00000"
    // run_turing_machine(&tm, "111");

    // initialize tm with transitions for a simple two-state, one-symbol machine
    // tm.num_states = 4;
    // tm.start_state = 1;
    // tm.accept_state = 4;
    // tm.reject_state = 0;
    // tm.num_symbols = 2;
    // tm.tape_alphabet[0] = '0';
    // tm.tape_alphabet[1] = '1';

    // // transition 1: (1, '1') -> (2, '1', R)
    // tm.transitions[0].current_state = 1;
    // tm.transitions[0].current_symbol = '1';
    // tm.transitions[0].next_state = 2;
    // tm.transitions[0].next_symbol = '1';
    // tm.transitions[0].direction = 1;

    // // transition 2: (2, '1') -> (2, '1', R)
    // tm.transitions[1].current_state = 2;
    // tm.transitions[1].current_symbol = '1';
    // tm.transitions[1].next_state = 2;
    // tm.transitions[1].next_symbol = '1';
    // tm.transitions[1].direction = 1;

    // // transition 3: (2, '0') -> (3, '0', L)
    // tm.transitions[2].current_state = 2;
    // tm.transitions[2].current_symbol = '0';
    // tm.transitions[2].next_state = 3;
    // tm.transitions[2].next_symbol = '0';
    // tm.transitions[2].direction = -1;

    // // transition 4: (3, '1') -> (4, '1', R)
    // tm.transitions[3].current_state = 3;
    // tm.transitions[3].current_symbol = '1';
    // tm.transitions[3].next_state = 4;
    // tm.transitions[3].next_symbol = '1';
    // tm.transitions[3].direction = 1;

    // // transition 5: (3, '0') -> (3, '0', L)
    // tm.transitions[4].current_state = 3;
    // tm.transitions[4].current_symbol = '0';
    // tm.transitions[4].next_state = 3;
    // tm.transitions[4].next_symbol = '0';
    // tm.transitions[4].direction = -1;

    // // transition 6: (4, '0') -> (4, '0', R)
    // tm.transitions[5].current_state = 4;
    // tm.transitions[5].current_symbol = '0';
    // tm.transitions[5].next_state = 4;
    // tm.transitions[5].next_symbol = '0';
    // tm.transitions[5].direction = 1;

    // // transition 7: (4, '1') -> (4, '1', R)
    // tm.transitions[6].current_state = 4;
    // tm.transitions[6].current_symbol = '1';
    // tm.transitions[6].next_state = 4;
    // tm.transitions[6].next_symbol = '1';
    // tm.transitions[6].direction = 1;

    char input[MAX_TAPE_SIZE];

    printf("Enter input: ");
    scanf("%s", input);

    run_turing_machine(&tm, input);

    return 0;
}
