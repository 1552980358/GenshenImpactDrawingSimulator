#ifndef GENSHENIMPACTDRAWINGSIMULATOR_RECORD_H
#define GENSHENIMPACTDRAWINGSIMULATOR_RECORD_H

const int TYPE_5_UP = 55;
const int TYPE_5_NON_UP = 50;

const int TYPE_4_UP = 48;
const int TYPE_4_NON_UP = 44;

const int TYPE_5 = 5;
const int TYPE_4 = 4;
const int TYPE_3 = 3;

class record {

private:
    int _type;

    record *_prev = nullptr;
    record *_next = nullptr;

public:
    record(int, record *);

    [[nodiscard]] int get_type() const;

    void set_next(record *);

    record *get_next();
    record *get_prev();

};

record *get_head(record *);

record *get_last(record *);

void clear_all(record *);

#endif //GENSHENIMPACTDRAWINGSIMULATOR_RECORD_H
