#ifndef MATRIX_HISTORY_H
#define MATRIX_HISTORY_H

void load_history();
void save_history();
void add_to_history(char *input);
int cmd_history(int argc, char **argv);

#endif//MATRIX_HISTORY_H
