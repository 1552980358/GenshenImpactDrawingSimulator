#include <iostream>
using std::cout;
using std::endl;
#include <windows.h>
#include <ctime>
#include "draw.h"

using std::default_random_engine;
using std::uniform_int_distribution;

bool check_has_safety_match_180(record *last) {
    int count = 179;
    record *ptr = last;
    while (count && ptr) {
        if (ptr->get_type() == TYPE_5_UP) {
            return true;
        }
        ptr = ptr->get_prev();
        count--;
    }
    return count;
}

bool check_has_safety_match_90(record *last) {
    int count = 89;
    record *ptr = last;
    while (count && ptr) {
        if (!(ptr->get_type() % TYPE_5)) {
            return true;
        }
        ptr = ptr->get_prev();
        count--;
    }
    return count;
}

bool check_has_safety_match_10(record *last) {
    int count = 9;
    record *ptr = last;
    int type;
    while (count && ptr) {
        type = ptr->get_type();
        if (!(type % TYPE_4) || !(type % TYPE_5)) {
            return true;
        }
        ptr = ptr->get_prev();
        count--;
    }

    return count;
}

void clear_list(char *draw_list, char *safety_match_list, char *draw_5_star_list, char *draw_4_start_list) {
    for (int i = 0; i < LIST_SIZE; ++i) {
        draw_list[i] = 0;
    }
    for (int i = 0; i < LIST_SIZE; ++i) {
        safety_match_list[i] = 0;
    }
    for (int i = 0; i < SIZE_5_STAR_NON_UP * 2; ++i) {
        draw_5_star_list[i] = 0;
    }
    for (int i = 0; i < SIZE_4_STAR_UP * SIZE_4_STAR_NON_UP * 2; ++i) {
        draw_4_start_list[i] = 0;
    }
}

void fill_draw_list(char *draw_list, default_random_engine &engine, uniform_int_distribution<int> &distribution) {
    // element address
    char *element;

    // 0.600%
    for (int i = 0; i < 6; ++i) {
        while (*(element = &(draw_list[distribution(engine)])));
        *element = TYPE_5;
    }

    // 5.100%
    for (int i = 0; i < 51; ++i) {
        while (*(element = &(draw_list[distribution(engine)])));
        *element = TYPE_4;
    }

    // 94.3%
    for (int i = 0; i < LIST_SIZE; ++i) {
        if (!(*(element = &(draw_list[i])))) {
            *element = TYPE_3;
        }
    }
}

void fill_safety_match(char *safety_match_list, default_random_engine &engine, uniform_int_distribution<int> &distribution) {
    // element address
    char *element;
    for (int i = 0; i < 60; ++i) {
        while (*(element = &(safety_match_list[distribution(engine)])));
        *element = TYPE_5;
    }
    for (int i = 0; i < LIST_SIZE; ++i) {
        if (!(*(element = &(safety_match_list[i])))) {
            *element = TYPE_4;
        }
    }
}

char draw_5_star(char *draw_5_star_list, default_random_engine &engine) {
    uniform_int_distribution distribution(0, SIZE_5_STAR_NON_UP * 2);
    char *element;
    for (int i = 0; i < SIZE_5_STAR_NON_UP; ++i) {
        while (*(element = &(draw_5_star_list[distribution(engine)])));
        *element = TYPE_5_UP;
    }
    for (int i = 0; i < SIZE_5_STAR_NON_UP * 2; ++i) {
        if (!(*(element = &(draw_5_star_list[i])))) {
            *element = TYPE_5_NON_UP;
        }
    }

    return draw_5_star_list[distribution(engine)];
}

char draw_4_star(char *draw_4_start_list, default_random_engine &engine) {
    uniform_int_distribution distribution(0, SIZE_4_STAR_UP * SIZE_4_STAR_NON_UP * 2 + 1);
    char *element;
    for (int i = 0; i < SIZE_4_STAR_UP * SIZE_4_STAR_NON_UP; ++i) {
        while (*(element = &(draw_4_start_list[distribution(engine)])));
        *element = TYPE_4_UP;
    }
    for (int i = 0; i < SIZE_4_STAR_UP * SIZE_4_STAR_NON_UP; ++i) {
        if (!(*(element = &(draw_4_start_list[i])))) {
            *element = TYPE_4_NON_UP;
        }
    }
    return draw_4_start_list[distribution(engine)];
}

char draw_safety_match_90(char *draw_5_star_list) {
    default_random_engine engine(time(nullptr));
    return draw_5_star(draw_5_star_list, engine);
}

char draw_safety_match(char *safety_match_list, default_random_engine &engine, uniform_int_distribution<int> &distribution) {
    fill_safety_match(safety_match_list, engine, distribution);
    return safety_match_list[distribution(engine)];
}

char draw_safety_match_10(char *safety_match_list, char *draw_5_star_list, char *draw_4_start_list) {
    uniform_int_distribution distribution(0, LIST_SIZE);
    default_random_engine engine(time(nullptr));
    return draw_safety_match(safety_match_list, engine, distribution) == TYPE_5 ?
           draw_5_star(draw_5_star_list, engine) : draw_4_star(draw_4_start_list, engine);
}

char draw_normal(char *draw_list, char *safety_match_list, char *draw_5_star_list, char *draw_4_start_list) {
    uniform_int_distribution distribution(0, LIST_SIZE);
    default_random_engine engine(time(nullptr));
    fill_draw_list(draw_list, engine, distribution);
    fill_safety_match(safety_match_list, engine, distribution);

    switch (draw_list[distribution(engine)]) {
        case TYPE_5:
            return draw_5_star(draw_5_star_list, engine);
        case TYPE_4:
            return draw_4_star(draw_4_start_list, engine);
        default:
            return TYPE_3;
    }
}

record *draw(record *head, char *draw_list, char *safety_match_list, char *draw_5_star_list, char *draw_4_start_list) {
    clear_list(draw_list, safety_match_list, draw_5_star_list, draw_4_start_list);
    record *ptr = head ? get_last(head) : nullptr;

    cout << "[";
    if (!check_has_safety_match_180(ptr)) {
        cout << "SAFETY_BIG ";
        ptr = new record(TYPE_5_UP, ptr);
    } else if (!check_has_safety_match_90(ptr)) {
        cout << "SAFETY_SMALL ";
        ptr = new record(draw_safety_match_90(draw_5_star_list), ptr);
    } else if (!check_has_safety_match_10(ptr)) {
        cout << "SAFETY_NORMAL ";
        ptr = new record(draw_safety_match_10(safety_match_list, draw_5_star_list, draw_4_start_list), ptr);
    } else {
        ptr = new record(draw_normal(draw_list, safety_match_list, draw_5_star_list, draw_4_start_list), ptr);
    }

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;

    switch (ptr->get_type()) {
        case TYPE_5_UP:
            SetConsoleTextAttribute(handle, 6);
            cout << "5* UP";
            break;
        case TYPE_5_NON_UP:
            SetConsoleTextAttribute(handle, 6);
            cout << "5*";
            break;
        case TYPE_4_UP:
            SetConsoleTextAttribute(handle,  5);
            cout << "4* UP";
            break;
        case TYPE_4_NON_UP:
            SetConsoleTextAttribute(handle,  5);
            cout << "4*";
            break;
        case TYPE_3:
            SetConsoleTextAttribute(handle, 1);
            cout << "3*";
            break;
    }

    SetConsoleTextAttribute(handle, 7);

    cout << "] ";

    return get_head(ptr);
}