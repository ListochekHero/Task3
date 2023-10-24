#include "main_s.h"
#include "mtools_commands.h"
#include "mtools.h"
#include "fs_operations.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage:  <filesystem_file.disk>\n");
		return 1;
	}

	const char *diskfile_path = argv[1];
	int default_buffer_size = 1024;
	char mount_line_for_mtools[default_buffer_size];
	char current_dir_path[default_buffer_size];
	strcpy(current_dir_path, "/");

	if (open_create_file_fisk(diskfile_path))
	{
		perror("Error: \n");
		exit(EXIT_FAILURE);
	}
	init_mtools(mount_line_for_mtools, diskfile_path);
	bool is_running = true;
	while (is_running)
	{
		int user_command_lenght = 32;
		char command_from_user[user_command_lenght];
		printf("%s>", current_dir_path);
		fgets(command_from_user, user_command_lenght, stdin);
		if (strcmp("exit\n", command_from_user) == 0)
		{
			is_running = false;
			break;
		}
		else if (strcmp("format\n", command_from_user) == 0)
		{
			if (format_fat32_fs(diskfile_path))
			{
				printf("Unable to format fs\n");
			}
			else
			{
				printf("Ok\n");
			}
			continue;
		}
		else if (strcmp("ls\n", command_from_user) == 0)
		{
			ls_command(current_dir_path);
			continue;
		}
		else if (strncmp("cd\n", command_from_user, 2) == 0)
		{
			char new_dir_path[default_buffer_size];
			if (sscanf(command_from_user, "cd %255s", new_dir_path) == 1)
			{
				cd_command(new_dir_path, current_dir_path);
			}
			else
			{
				printf("Usage:	cd <path>\n");
			}
			continue;
		}
		else if (strncmp("mkdir\n", command_from_user, 5) == 0)
		{
			char new_dir_name[default_buffer_size];
			if (sscanf(command_from_user, "mkdir %255s", new_dir_name) == 1)
			{
				if (!mkdir_command(current_dir_path, new_dir_name))
				{
					printf("Ok\n");
				}
			}
			else
			{
				printf("Usage:	mkdir <dir name>\n");
			}
			continue;
		}
		else if (strncmp("touch\n", command_from_user, 5) == 0)
		{
			char file_name[default_buffer_size];
			if (sscanf(command_from_user, "touch %255s", file_name) == 1)
			{
				touch_command(file_name, current_dir_path);
			}
			else
			{
				printf("Usage:	touch <file name>\n");
			}
			continue;
		}
		else
		{
			printf("Unknown command\n");
		}
	}
	deinit_mtools(mount_line_for_mtools);
	// remove(diskfile_path);
	return 0;
}