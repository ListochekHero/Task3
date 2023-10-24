#include "fs_operations.h"

int open_create_file_fisk(const char *diskfile_path)
{
	FILE *fat32_diskfile = fopen(diskfile_path, "rb");
	if (fat32_diskfile == NULL)
	{
		fat32_diskfile = fopen(diskfile_path, "wb");
		if (fat32_diskfile == NULL)
		{
			printf("Unable to create the file.\n");
			return 1;
		}

		long fat32_diskfile_size = 33 * 1024 * 1024;

		for (long i = 0; i < fat32_diskfile_size; i++)
		{
			fputc(0, fat32_diskfile);
		}
		fclose(fat32_diskfile);
		printf("File created: %s\n", diskfile_path);
	}
	else
	{
		fclose(fat32_diskfile);
		printf("File exists: %s\n", diskfile_path);
	}
    return 0;
}

int format_fat32_fs(const char *diskfile_path)
{
	char mkfs_command_to_create_fat32_fs[1024];
	snprintf(mkfs_command_to_create_fat32_fs, sizeof(mkfs_command_to_create_fat32_fs), "mkfs.vfat -F 32 -n FAT32FS -s 1 -S 512 %s", diskfile_path);
	int result = system(mkfs_command_to_create_fat32_fs);
	if (result != 0)
	{
		printf("Error executing mkfs.vfat.\n");
		return 1;
	}
	else
	{
		printf("File system created on: %s\n", diskfile_path);
	}
    return 0;
}
