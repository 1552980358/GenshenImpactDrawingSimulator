#include "record.h"

/** Class functions **/
record::record(int type, record *prev) {
    _type = type;
    if (prev) {
        _prev = prev;
        _prev->set_next(this);
    }
}

int record::get_type() const {
    return _type;
}

void record::set_next(record *next) {
    _next = next;
}

record *record::get_next() {
    return _next;
}

record *record::get_prev() {
    return _prev;
}

/** Static functions **/
record *get_head(record *record_ptr) {
    record *ptr = record_ptr;
    while (ptr->get_prev()) {
        ptr = ptr->get_prev();
    }
    return ptr;
}

record *get_last(record *head) {
    record *ptr = head;
    while (ptr->get_next()) {
        ptr = ptr->get_next();
    }
    return ptr;
}

void clear_all(record *head) {
    record *ptr_current = head;
    record *ptr_tmp;
    while (ptr_current != nullptr) {
        ptr_tmp = ptr_current->get_next();
        delete ptr_current;
        ptr_current = ptr_tmp;
    }
}