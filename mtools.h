#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init_mtools(char *mount_line_for_mtools, const char *diskfile_path);
void deinit_mtools(const char *mount_line_for_mtools);