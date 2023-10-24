#include "mtools.h"

void init_mtools(char *mount_line_for_mtools, const char *diskfile_path)
{
	const char *mtools_config_file_path = "/etc/mtools.conf";
	FILE *mtools_config_file = fopen(mtools_config_file_path, "a");
	snprintf(mount_line_for_mtools, 1024, "drive Z: file=\"%s\"\n", diskfile_path);
	if (mtools_config_file == NULL)
	{
		perror("Unable to open file\n");
		exit(EXIT_FAILURE);
	}
	fputs(mount_line_for_mtools, mtools_config_file);
	fclose(mtools_config_file);
	return;
}

void deinit_mtools(const char *mount_line_for_mtools)
{
	FILE *mtools_config_file = fopen("/etc/mtools.conf", "r");
	if (mtools_config_file == NULL)
	{
		perror("Unable to open file");
		exit(EXIT_FAILURE);
	}
	FILE *temp_mtools_config_file = fopen("/etc/temp_mtools.conf", "w");
	if (temp_mtools_config_file == NULL)
	{
		perror("Unable to open temp file");
		exit(EXIT_FAILURE);
	}

	char buffer[1024];
	int line_found = 0;

	while (fgets(buffer, sizeof(buffer), mtools_config_file))
	{
		if (strcmp(buffer, mount_line_for_mtools) == 0)
		{
			line_found = 1;
		}
		else
		{
			fputs(buffer, temp_mtools_config_file);
		}
	}
	fclose(mtools_config_file);
	fclose(temp_mtools_config_file);

	remove("/etc/mtools.conf");
	rename("/etc/temp_mtools.conf", "/etc/mtools.conf");

	if (line_found)
	{
		printf("Driver was unmounted\n");
	}
	else
	{
		printf("Unable to unmount driver\n");
	}
}