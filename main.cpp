#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
using std::getline;
#include "record.h"
#include "draw.h"

#define FLAG_EXIT -1
#define FLAG_CLEAR_ALL -2
#define FLAG_DRAW_10 -3
#define FLAG_HELP -999

/** prototype **/
void draw_buddha();
bool is_numbers(const string &);
int str_to_int(const string&);
int get_input();

int main() {
    draw_buddha();
    int input;
    record *head = nullptr;
    char *draw_list = (char *) malloc(LIST_SIZE * sizeof(char));
    char *safety_match = (char *) malloc(LIST_SIZE * sizeof(char));
    char *draw_5_star = (char *) malloc(SIZE_5_STAR_NON_UP * 2 * sizeof(char));
    char *draw_4_star = (char *) malloc(SIZE_4_STAR_UP * SIZE_4_STAR_NON_UP * 2 * sizeof(char));

    while ((input = get_input()) != FLAG_EXIT) {
        if (input == FLAG_CLEAR_ALL) {
            head = clear_all(head);
            cout << "All records removed." << endl
                 << endl;
            continue;
        }
        if (input == FLAG_HELP) {
            cout << "\"-1\" to quit" << endl
                 << "\"-2\" to clear all drawing records" << endl
                 << "\"-3\" to draw 10 times" << endl
                 << "\"-999\" to show help message" << endl
                 << "Any positive number that will automatically identified as draw single or 10 times each" << endl
                 << endl;
            continue;
        }
        if (input == FLAG_DRAW_10) {
            input = 10;
        }
        if (!(input % 10)) {
            cout << "10 Draw: ";
            for (int i = 0; i < input / 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    head = draw(head, draw_list, safety_match, draw_5_star, draw_4_star);
                }
            }
            cout << endl;
            continue;
        }
        cout << "Draw: ";
        for (int i = 0; i < input; ++i) {
            head = draw(head, draw_list, safety_match, draw_5_star, draw_4_star);
            if (!((i + 1) % 10)) {
                cout << endl;
            }
        }
        cout << endl
             << endl;
    }

    cout << "Press any key to exit..."; getchar();

    return 0;
}

void draw_buddha() {
    cout << "////////////////////////////////////////////////////////////////////" << endl;
    cout << "//                          _ooOoo_                               //" << endl;
    cout << "//                         o8888888o                              //" << endl;
    cout << "//                         88\" . \"88                              //" << endl;
    cout << "//                         (| ^_^ |)                              //" << endl;
    cout << "//                         O\\  =  /O                              //" << endl;
    cout << "//                      ____/`---'\\____                           //" << endl;
    cout << "//                    .'  \\\\|     |//  `.                         //" << endl;
    cout << R"(//                   /  \\|||  :  |||//  \                        //)" << endl;
    cout << "//                  /  _||||| -:- |||||-  \\                       //" << endl;
    cout << R"(//                  |   | \\\  -  /// |   |                       //)" << endl;
    cout << "//                  | \\_|  ''\\---/''  |   |                       //" << endl;
    cout << "//                  \\  .-\\__  `-`  ___/-. /                       //" << endl;
    cout << "//                ___`. .'  /--.--\\  `. . ___                     //" << endl;
    cout << "//              ."" '<  `.___\\_<|>_/___.'  >'"".                      //" << endl;
    cout << "//            | | :  `- \\`.;`\\ _ /`;.`/ - ` : | |                 //" << endl;
    cout << R"(//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 //)" << endl;
    cout << "//      ========`-.____`-.___\\_____/___.-`____.-'========         //" << endl;
    cout << "//                           `=---='                              //" << endl;
    cout << "//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //" << endl;
    cout << "//               佛祖保佑      永无BUG      永不修改                  //" << endl;
    cout << "////////////////////////////////////////////////////////////////////" << endl;
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
    cout << "Input number of drawing or command <-999 to get help>: ";
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
    if (line == "-999") {
        return FLAG_HELP;
    }
    if (!is_numbers(line)) {
        return 0;
    }
    return str_to_int(line);
}