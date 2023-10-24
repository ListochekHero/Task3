#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ls_command(char *current_dir_path);
void cd_command(char *new_dir_path, char *current_dir_path);
int mkdir_command(char *current_dir_path, char *new_dir_name);
void touch_command(char *file_name, char *current_dir_path);