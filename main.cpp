#include <iostream>
using std::cout;
using std::cin;
#include <random>
using std::default_random_engine;
#include <string>
using std::string;
using std::getline;
#include "record.h"
#include "draw.h"

#define FLAG_EXIT -1
#define FLAG_CLEAR_ALL -2
#define FLAG_DRAW_10 -3

/** prototype **/
bool is_numbers(const string &);
int str_to_int(const string&);
int get_input();

int main() {
    int input;
    record *head = nullptr;
    char *draw_list = (char *) malloc(LIST_SIZE * sizeof(char));
    char *safety_match = (char *) malloc(LIST_SIZE * sizeof(char));
    char *draw_5_star = (char *) malloc(SIZE_5_STAR_NON_UP * 2 * sizeof(char));
    char *draw_4_star = (char *) malloc(SIZE_4_STAR_UP * SIZE_4_STAR_NON_UP * 2 * sizeof(char));

    cout << LIST_SIZE + LIST_SIZE + SIZE_5_STAR_NON_UP * 2 + SIZE_4_STAR_UP * SIZE_4_STAR_NON_UP * 2;
    while ((input = get_input()) != FLAG_EXIT) {
        if (input == FLAG_CLEAR_ALL) {
            clear_all(head);
            continue;
        }
        if (input == FLAG_DRAW_10) {
            input = 10;
        }
        if (!(input % 10)) {
            default_random_engine engine(time_t(nullptr));
            for (int i = 0; i < input / 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    head = draw(head, draw_list, safety_match, draw_5_star, draw_4_star, engine);
                }
            }
            continue;
        }
        for (int i = 0; i < input; ++i) {
            head = draw(head, draw_list, safety_match, draw_5_star, draw_4_star, default_random_engine(time_t(nullptr)));
        }
    }

    cout << "Press any key to exit..."; getchar();

    return 0;
}

bool is_numbers(const string &str) {
    for (auto c_str: str) {
        if (c_str < '0' || c_str > '9') {
            return false;
        }
    }
    return true;
}

int str_to_int(const string& str) {
    int tmp = 0;
    for (auto c_str: str) {
        tmp = tmp * 10 + (c_str - 48);
    }
    return tmp;
}

int get_input() {
    string line;
    getline(cin, line);
    if (line == "-1") {
        return FLAG_EXIT;
    }
    if (line == "-2") {
        return FLAG_CLEAR_ALL;
    }
    if (line == "-3") {
        return FLAG_DRAW_10;
    }
    if (!is_numbers(line)) {
        return 0;
    }
    return str_to_int(line);
}