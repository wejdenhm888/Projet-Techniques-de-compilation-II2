#include <stdio.h>
#include "tokens.h"


int symbole_suivant();
int init_lexer(const char *filename);
void close_lexer(void);

int symbole;

void erreur() {
    printf("Erreur syntaxique : symbole non accepté !\n");
}

void accepter(int T) {
    if (symbole == T)
        symbole = symbole_suivant();
    else
        erreur();
}


void P();
void Dcl();
void Liste_id();
void Type();
void Inst_composée();
void Liste_inst();
void I();
void Exp();
void Exp_simple();
void Terme();
void Facteur();

void P() {
    if (symbole == program_) {
        accepter(program_);
        accepter(id);
        accepter(pvirg);
        Dcl();
        Inst_composée();
        accepter(point);
    } else erreur();
}

void Dcl() {
    if (symbole == var_) {
        accepter(var_);
        Liste_id();
        accepter(deux_points);
        Type();
        accepter(pvirg);
        Dcl();
    }
}

void Liste_id() {
    if (symbole == id) {
        accepter(id);
        while (symbole == virgule) {
            accepter(virgule);
            accepter(id);
        }
    } else erreur();
}

void Type() {
    if (symbole == integer_) accepter(integer_);
    else if (symbole == char_) accepter(char_);
    else erreur();
}

void Inst_composée() {
    if (symbole == begin_) {
        accepter(begin_);
        Liste_inst();
        accepter(end_);
    } else erreur();
}

void I() {
    if (symbole == id) {
        accepter(id);
        accepter(assign);
        Exp_simple();
    } else if (symbole == if_) {
        accepter(if_);
        Exp();
        accepter(then_);
        I();
        accepter(else_);
        I();
    } else if (symbole == while_) {
        accepter(while_);
        Exp();
        accepter(do_);
        I();
    } else if (symbole == read_) {
        accepter(read_);
        accepter(parouv);
        accepter(id);
        accepter(parfer);
    } else if (symbole == readln_) {
        accepter(readln_);
        accepter(parouv);
        accepter(id);
        accepter(parfer);
    } else if (symbole == write_) {
        accepter(write_);
        accepter(parouv);
        accepter(id);
        accepter(parfer);
    } else if (symbole == writeln_) {
        accepter(writeln_);
        accepter(parouv);
        accepter(id);
        accepter(parfer);
    } else erreur();
}

void Liste_inst() {
    I();
    while (symbole == pvirg) {
        accepter(pvirg);
        if (symbole == id || symbole == if_ || symbole == while_ ||
            symbole == read_ || symbole == readln_ ||
            symbole == write_ || symbole == writeln_) {
            I();
        } else break;
    }
}

void Exp() {
    Exp_simple();
    if (symbole == oprel) {
        accepter(oprel);
        Exp_simple();
    }
}

void Exp_simple() {
    Terme();
    while (symbole == opadd) {
        accepter(opadd);
        Terme();
    }
}

void Terme() {
    Facteur();
    while (symbole == opmul) {
        accepter(opmul);
        Facteur();
    }
}

void Facteur() {
    if (symbole == id) accepter(id);
    else if (symbole == nb) accepter(nb);
    else if (symbole == parouv) {
        accepter(parouv);
        Exp();
        accepter(parfer);
    } else erreur();
}

int main() {
    printf("Analyse syntaxique descendante prédictive\n");

    if (!init_lexer("test.pas")) {
        printf("Impossible d'ouvrir test.pas\n");
        return 1;
    }

    symbole = symbole_suivant();
    P();

    if (symbole == fin)
        printf("Analyse terminée avec succès\n");
    else
        printf("Erreur : symbole restant non reconnu\n");

    close_lexer();


    return 0;
}

