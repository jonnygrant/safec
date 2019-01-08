#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "stdio_cx.h"


errno_t fopen_s(FILE ** file, const char * const filename, const char * const mode)
{
    errno_t result = 0;

    if((NULL == file) || (NULL == filename) || (NULL == mode))
    {
        result = EFAULT;
    }
    else
    {
        *file = fopen(filename, mode);

        if(NULL == *file)
        {
            result = errno;
        }
    }

    return result;
}


errno_t fclose_s(FILE * file)
{
    errno_t result = 0;
    int fclose_ret;

    if(NULL == file)
    {
        result = EFAULT;
    }
    else
    {
        fclose_ret = fclose(file);
        if(-1 == fclose_ret)
        {
            result = errno;
        }
    }

    return result;
}


errno_t remove_s(const char * const path)
{
    errno_t result = 0;
    int remove_ret;

    if(NULL == path)
    {
        result = EFAULT;
    }
    else
    {
        remove_ret = remove(path);
        if(-1 == remove_ret)
        {
            result = errno;
        }
    }

    return result;
}


DIR * opendir_s(const char * const name)
{
    DIR * dir = NULL;

    if(NULL == name)
    {
        errno = EFAULT;
    }
    else
    {
        dir = opendir(name);
        if(NULL == dir)
        {
            if(ENOENT == errno)
            {
                errno = ENOTDIR;
            }
        }
    }

    return dir;
}


int closedir_s(DIR * dirp)
{
    int result = 0;

    if(NULL == dirp)
    {
        errno = EFAULT;
        result = -1;
    }
    else
    {
        result = closedir(dirp);
    }

    return result;
}


int diraccessible(const char * const name)
{
    DIR * dir = opendir_s(name);
    if(NULL == dir)
    {
        return 0;
    }
    else
    {
        closedir_s(dir);
        return 1;
    }
}


// calls stat() returns -1 on error
int filesize(const char * const name)
{
    struct stat statbuf;

    errno = 0;
    int result = stat(name, &statbuf);

    if(0 == result)
    {
        result = statbuf.st_size;
    }

    return result;
}


// Note system() returns 0 if shell command invokes return 0
errno_t system_s(const char * const cmd, int * shell_ret, int * actual_ret)
{
    errno_t result = 0;

    if((shell_ret == NULL) || (actual_ret == NULL) || (NULL == cmd))
    {
        result = EFAULT;
    }
    else
    {
        int sys_result = system(cmd);

        *shell_ret = sys_result;
        *actual_ret = WEXITSTATUS(sys_result);

        if(-1 == sys_result)
        {
            result = -1;
        }
    }

    return result;
}

#if 0
// Always NUL terminate
errno_t strncpy_s2(char * const dest, const char * const src, const size_t len)
{
    
}

#endif


