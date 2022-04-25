#ifndef MATRIX_LS_H
#define MATRIX_LS_H

struct dirent;
int cmd_ls(int argc, char **argv);
void display_dir(char *s, int l, int a);
void handle_flags(char* path,struct dirent *dir_entry, int flag_l, int flag_a);
void handle_l(char* dir_arg,struct dirent *dir_entry);
int file_dir_exists(char *path);
int file_exists(char *path);
int dir_exists(char *path);

#endif//MATRIX_LS_H
