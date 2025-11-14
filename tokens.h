#ifndef TOKENS_H
#define TOKENS_H


enum {
    fin = 0,


    program_ = 1,
    var_     = 2,
    integer_ = 3,
    char_    = 4,
    begin_   = 5,
    end_     = 6,
    if_      = 7,
    then_    = 8,
    else_    = 9,
    while_   = 10,
    do_      = 11,
    read_    = 12,
    readln_  = 13,
    write_   = 14,
    writeln_ = 15,

    pvirg      = 20,
    virgule    = 21,
    parouv     = 22,
    parfer     = 23,
    point      = 24,
    deux_points= 25,
    assign     = 26,
    opadd      = 27,
    opmul      = 28,
    oprel      = 29,

    id = 100,
    nb = 101
};

#endif
