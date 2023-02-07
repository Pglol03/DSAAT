#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int BLANK_SYMBOL = -1;

struct Transition {
    int current_state;
    int current_symbol;
    int next_state;
    int next_symbol;
    int direction;
};

struct TuringMachine {
    int start_state;
    int accept_state;
    int reject_state;
    vector<int> tape_alphabet;
    vector<Transition> transitions;
};

map<int, char> int_to_char;
map<char, int> char_to_int;

void init_alphabet(vector<int> &alphabet, string str) {
    int counter = 0;
    for (char c : str) {
        if (char_to_int.count(c) == 0) {
            char_to_int[c] = counter;
            int_to_char[counter] = c;
            counter++;
        }
        alphabet.push_back(char_to_int[c]);
    }
    int_to_char[BLANK_SYMBOL] = '_';
}

int get_symbol(vector<int> &tape, int tape_head) {
    if (tape_head >= 0 && tape_head < tape.size()) {
        return tape[tape_head];
    }
    return BLANK_SYMBOL;
}

bool run_tm(TuringMachine &tm, vector<int> &input) {
    vector<int> tape(input);
    tape.push_back(BLANK_SYMBOL);
    int state = tm.start_state;
    int tape_head = 0;
    while (state != tm.accept_state && state != tm.reject_state) {
        int current_symbol = get_symbol(tape, tape_head);
        bool transition_found = false;
        for (Transition transition : tm.transitions) {
            if (transition.current_state == state && transition.current_symbol == current_symbol) {
                state = transition.next_state;
                tape[tape_head] = transition.next_symbol;
                if (transition.direction == -1) {
                    tape_head--;
                } else if (transition.direction == 1) {
                    tape_head++;
                }
                transition_found = true;
                break;
            }
        }
        if (!transition_found) {
            return false;
        }
    }
    return state == tm.accept_state;
}

int main() {
    string tape_alphabet_str = "01";
    vector<int> tape_alphabet;
    init_alphabet(tape_alphabet, tape_alphabet_str);

    TuringMachine tm;
    tm.start_state = 0;
    tm.accept_state = 2;
    tm.reject_state = 3;
    tm.tape_alphabet = tape_alphabet;

    tm.transitions.push_back({0, 0, 1, 1, 1});
    tm.transitions.push_back({0, 1, 1, 0, 1});
    tm.transitions.push_back({1, 0, 2, 0, -1});
    tm.transitions.push_back({1, 1, 1, 1, 1});
    tm.transitions.push_back({2, 0, 2, 0, -1});
    tm.transitions.push_back({2, 1, 3, 1, 1});

    string input_str = "0101";
    vector<int> input;
    for (char c : input_str) {
        input.push_back(char_to_int[c]);
    }

    if (run_tm(tm, input)) {
        cout << "Accepted" << endl;
    } else {
        cout << "Rejected" << endl;
    }

    return 0;
}

