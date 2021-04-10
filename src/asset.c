#include <stdbool.h>
#include <sys/stat.h>

struct stat buffer; 

bool asset_does_file_exist(char *path)
{
    bool exists = (stat (path, &buffer) == 0);
    return exists;
}