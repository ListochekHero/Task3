#include "mtools_commands.h"

void ls_command(char *current_dir_path)
{
    char mtools_command_for_fat32_fs[1024];
    snprintf(mtools_command_for_fat32_fs, sizeof(mtools_command_for_fat32_fs), "sudo mdir Z:%s 2>&1", current_dir_path);
    FILE *pipe_for_mtools_output = popen(mtools_command_for_fat32_fs, "r");
    if (pipe_for_mtools_output == NULL)
    {
        perror("Unable to execute command: \n");
        pclose(pipe_for_mtools_output);
        return;
    }
    char buffer_for_mtools_output[128];
    while (fgets(buffer_for_mtools_output, sizeof(buffer_for_mtools_output), pipe_for_mtools_output) != NULL)
    {
        if ((strstr(buffer_for_mtools_output, "Can't open") != NULL) || (strstr(buffer_for_mtools_output, "init") != NULL))
        {
            printf("Unknown disk format\n");
            pclose(pipe_for_mtools_output);
            return;
        }
        printf("%s\n", buffer_for_mtools_output);
    }
    pclose(pipe_for_mtools_output);
    return;
}

void cd_command(char *new_dir_path, char *current_dir_path)
{
    char mtools_command_for_fat32_fs[1024];
    snprintf(mtools_command_for_fat32_fs, sizeof(mtools_command_for_fat32_fs), "sudo mcd %s 2>&1", new_dir_path);
    FILE *pipe_for_mtools_output = popen(mtools_command_for_fat32_fs, "r");
    if (pipe_for_mtools_output == NULL)
    {
        perror("Unable to execute command: \n");
        pclose(pipe_for_mtools_output);
        return;
    }
    char buffer_for_mtools_output[128];
    while (fgets(buffer_for_mtools_output, sizeof(buffer_for_mtools_output), pipe_for_mtools_output) != NULL)
    {
        if ((strstr(buffer_for_mtools_output, "Can't open") != NULL) || (strstr(buffer_for_mtools_output, "init") != NULL))
        {
            printf("Unknown disk format\n");
            pclose(pipe_for_mtools_output);
            return;
        }
    }
    char error_string[1024];
    snprintf(error_string, sizeof(error_string), "mcd: File \"%s\" not found\n", new_dir_path);
    if (strcmp(buffer_for_mtools_output, error_string) == 0)
    {
        printf("%s\n", buffer_for_mtools_output);
        pclose(pipe_for_mtools_output);
        return;
    }
    else
    {
        strcpy(current_dir_path, new_dir_path);
    }
    pclose(pipe_for_mtools_output);
    return;
}

int mkdir_command(char *current_dir_path, char *new_dir_name)
{

    char mtools_command_for_fat32_fs[1024];
    snprintf(mtools_command_for_fat32_fs, sizeof(mtools_command_for_fat32_fs), "sudo mmd Z:%s/%s 2>&1", current_dir_path, new_dir_name);
    FILE *pipe_for_mtools_output = popen(mtools_command_for_fat32_fs, "w");
    if (pipe_for_mtools_output == NULL)
    {
        perror("Unable to execute command: \n");
        pclose(pipe_for_mtools_output);
        return 1;
    }
    pclose(pipe_for_mtools_output);
    return 0;
}

void touch_command(char *file_name, char *current_dir_path)
{
    char mtools_command_for_fat32_fs[1024];
    snprintf(mtools_command_for_fat32_fs, sizeof(mtools_command_for_fat32_fs), "touch %s &&sudo mcopy %s Z:%s 2>&1", file_name, file_name, current_dir_path);
    FILE *pipe_for_mtools_output = popen(mtools_command_for_fat32_fs, "w");
    if (pipe_for_mtools_output == NULL)
    {
        perror("Unable to execute command: \n");
        pclose(pipe_for_mtools_output);
        return;
    }
    pclose(pipe_for_mtools_output);
    char path[1024];
    ssize_t count = readlink("/proc/self/exe", path, sizeof(path) - 1);
    count--;
    path[count] = '\0';
    char command[1027];
    snprintf(command, sizeof(command), "rm %s%s", path, file_name);
    system(command);
}