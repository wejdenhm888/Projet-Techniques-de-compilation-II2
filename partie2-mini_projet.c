#include <stdio.h>

#define program_ 1
#define id 2
#define pvirg 3
#define var_ 4
#define deux_points 5
#define virgule 6
#define integer_ 7
#define char_ 8
#define begin_ 9
#define end_ 10
#define assign 11
#define if_ 12
#define then_ 13
#define else_ 14
#define while_ 15
#define do_ 16
#define read_ 17
#define readln_ 18
#define write_ 19
#define writeln_ 20
#define oprel 21
#define opadd 22
#define opmul 23
#define nb 24
#define parouv 25
#define parfer 26
#define point 27
#define fin 99

int symbole;

int symbole_suivant() {
    int s;
    printf("Donner le symbole suivant : ");
    scanf("%d", &s);
    return s;
}

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
void Inst();
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
    } else
        erreur();
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
    } else
        erreur();
}

void Type() {
    if (symbole == integer_)
        accepter(integer_);
    else if (symbole == char_)
        accepter(char_);
    else
        erreur();
}

void Inst_composée() {
    if (symbole == begin_) {
        accepter(begin_);
        Inst();
        accepter(end_);
    } else
        erreur();
}

void Inst() {
    if (symbole == id || symbole == if_ || symbole == while_ ||
        symbole == read_ || symbole == readln_ ||
        symbole == write_ || symbole == writeln_) {
        Liste_inst();
    }
}

void Liste_inst() {
    if (symbole == id || symbole == if_ || symbole == while_ ||
        symbole == read_ || symbole == readln_ ||
        symbole == write_ || symbole == writeln_) {

        I();
        while (symbole == pvirg) {
            accepter(pvirg);
            if (symbole == id || symbole == if_ || symbole == while_ ||
                symbole == read_ || symbole == readln_ ||
                symbole == write_ || symbole == writeln_) {
                I();
            } else {
                break;
            }
        }
    }

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
    }

    else
        erreur();
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
    if (symbole == id)
        accepter(id);
    else if (symbole == nb)
        accepter(nb);
    else if (symbole == parouv) {
        accepter(parouv);
        Exp();
        accepter(parfer);
    } else
        erreur();
}


int main() {
    printf("Analyse syntaxique descendante prédictive\n");
    printf("Entrez les codes des symboles terminaux (fin = 99)\n");
    symbole = symbole_suivant();
    P();
    if (symbole == fin)
        printf("Analyse terminée avec succès \n");
    else
        printf("Erreur : symbole restant non reconnu \n");
    return 0;
}
