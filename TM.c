#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAPE_SIZE 1000
#define MAX_NUM_STATES 100
#define MAX_NUM_SYMBOLS 10
#define MAX_NUM_TRANSITIONS 1000

typedef struct {
    int current_state;
    int current_symbol;
    int next_state;
    int next_symbol;
    int direction;
} Transition;

typedef struct {
    int num_states;
    int start_state;
    int accept_state;
    int reject_state;
    int num_symbols;
    int tape_alphabet[MAX_NUM_SYMBOLS];
    Transition transitions[MAX_NUM_TRANSITIONS];
} TuringMachine;

void run_turing_machine(TuringMachine *tm, char *input) {
    int head_position = 0;
    int current_state = tm->start_state;
    char tape[MAX_TAPE_SIZE];
    int tape_size = strlen(input);

    strcpy(tape, input);

    while (1) {
        int i;

        // find transition for current state and current symbol
        Transition *t = NULL;

        for (i = 0; i < MAX_NUM_TRANSITIONS; i++) {
            if (tm->transitions[i].current_state == current_state &&
                tm->transitions[i].current_symbol == tape[head_position]) {
                t = &(tm->transitions[i]);
                break;
            }
        }

        if (t == NULL) {
            printf("Rejected\n");
            return;
        }

        // update tape
        tape[head_position] = t->next_symbol;

        // update head position
        if (t->direction == -1) {
            head_position--;
        } else if (t->direction == 1) {
            head_position++;
        }

        // check if tape is out of bounds
        if (head_position < 0 || head_position >= tape_size) {
            printf("Rejected\n");
            return;
        }

        // update current state
        current_state = t->next_state;

        // check if machine has halted
        if (current_state == tm->accept_state) {
            printf("Accepted\n");
            return;
        } else if (current_state == tm->reject_state) {
            printf("Rejected\n");
            return;
        }
    }
}

int main() {
    TuringMachine tm;

    // initialize tm with transitions for a simple two-state, one-symbol machine
    tm.num_states = 2;
    tm.start_state = 1;
    tm.accept_state = 2;
    tm.reject_state = 0;
    tm.num_symbols = 1;
    tm.tape_alphabet[0] = '0';

    // transition 1: (1, '0') -> (2, '0', R)
    tm.transitions[0].current_state = 1;
    tm.transitions[0].current_symbol = '0';
    tm.transitions[0].next_state = 2;
    tm.transitions[0].next_symbol = '0';
    tm.transitions[0].direction = 1;

    // run the machine with input "00000"
    run_turing_machine(&tm, "00000");

    return 0;
}
