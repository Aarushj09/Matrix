#ifndef MATRIX_TOKENISER_H
#define MATRIX_TOKENISER_H

void prompt();
char **tokenise_input(char* input, char* del);
int break_input(char *input);
int execute_commands(int argc, char **agrv);

#endif//MATRIX_TOKENISER_H
