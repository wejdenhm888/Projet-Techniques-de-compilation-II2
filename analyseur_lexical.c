#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"

#define MAX_LEX 128

static FILE *src = NULL;
static char lexeme[MAX_LEX];

typedef struct { const char *kw; int code; } KW;
static KW keywords[] = {
    {"program", program_},
    {"var", var_},
    {"integer", integer_},
    {"char", char_},
    {"begin", begin_},
    {"end", end_},
    {"if", if_},
    {"then", then_},
    {"else", else_},
    {"while", while_},
    {"do", do_},
    {"read", read_},
    {"readln", readln_},
    {"write", write_},
    {"writeln", writeln_},
    {NULL, 0}
};

static int keyword_code(const char *s) {
    for (int i = 0; keywords[i].kw != NULL; ++i)
        if (strcmp(s, keywords[i].kw) == 0) return keywords[i].code;
    return 0;
}

int init_lexer(const char *filename) {
    src = fopen(filename, "r");
    return (src != NULL);
}

void close_lexer(void) {
    if (src) fclose(src);
}

static int next_char(void) {
    if (!src) return EOF;
    return fgetc(src);
}

static void unget_char(int c) {
    if (c != EOF && src) ungetc(c, src);
}

int symbole_suivant() {
    int c, i;

    while (1) {
        c = next_char();
        if (c == EOF) {
            printf("TOKEN = fin\n");
            return fin;
        }
        if (isspace(c)) continue;

        // commentaires
        if (c == '/') {
            int d = next_char();
            if (d == '/') {
                while ((c = next_char()) != EOF && c != '\n');
                continue;
            } else if (d == '*') {
                int prev = 0;
                while ((c = next_char()) != EOF) {
                    if (prev == '*' && c == '/') break;
                    prev = c;
                }
                continue;
            } else {
                unget_char(d);
                printf("TOKEN = opmul | LEXEME = \"/\"\n");
                return opmul;
            }
        }
        break;
    }

    if (isalpha(c)) {
        i = 0;
        lexeme[i++] = (char)c;
        while (i < MAX_LEX-1) {
            c = next_char();
            if (isalnum(c) || c == '_') lexeme[i++] = (char)c;
            else { unget_char(c); break; }
        }
        lexeme[i] = '\0';
        int kc = keyword_code(lexeme);
        if (kc>0) {
          printf("TOKEN = %d | LEXEME = \"%s\"\n", kc, lexeme);
          return kc;
        }
        printf("TOKEN = id | LEXEME = \"%s\"\n", lexeme);
        return id;
    }

    if (isdigit(c)) {
        i = 0;
        lexeme[i++] = (char)c;
        while (i < MAX_LEX-1) {
            c = next_char();
            if (isdigit(c)) lexeme[i++] = (char)c;
            else { unget_char(c); break; }
        }
        lexeme[i] = '\0';
        printf("TOKEN = nb | LEXEME = \"%s\"\n", lexeme);
        return nb;
    }

    switch (c) {
        case ';': printf("TOKEN = pvirg\n"); return pvirg;
        case ',': printf("TOKEN = virgule\n"); return virgule;
        case '(' : printf("TOKEN = parouv\n"); return parouv;
        case ')' : printf("TOKEN = parfer\n"); return parfer;
        case '.': printf("TOKEN = point\n"); return point;
        case ':': {
            int d = next_char();
            if (d == '=') {
                printf("TOKEN = assign\n");
                return assign;
            }
            unget_char(d);
            printf("TOKEN = deux_points\n");
            return deux_points;
        }
        case '+': case '-': printf("TOKEN = opadd\n"); return opadd;
        case '*': printf("TOKEN = opmul\n"); return opmul;
        case '<': {
            int d = next_char();
            if (d == '=') { printf("TOKEN = oprel | LEXEME = \"<=\"\n"); return oprel; }
            else if (d == '>') { printf("TOKEN = oprel | LEXEME = \"<>\"\n"); return oprel; }
            else { unget_char(d); printf("TOKEN = oprel | LEXEME = \"<\"\n"); return oprel; }
        }
        case '>': {
            int d = next_char();
            if (d == '=') { printf("TOKEN = oprel | LEXEME = \">=\"\n"); return oprel; }
            else { unget_char(d); printf("TOKEN = oprel | LEXEME = \">\"\n"); return oprel; }
        }
        case '=': printf("TOKEN = oprel | LEXEME = \"=\"\n"); return oprel;
        default:
            printf("Symbole non reconnu : %c\n", c);
            return fin;

    }
}
