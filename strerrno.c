
#include <errno.h>

#include "stdio_cx.h"

typedef struct error_list
{
    errno_t value;
    const char * str;
} error_list_t;

const error_list_t str_err_list[] =
{
    {EPERM, "EPERM"},
    {ENOENT, "ENOENT"},
    {ESRCH, "ESRCH"},
    {EINTR, "EINTR"},
    {EIO, "EIO"},
    {ENXIO, "ENXIO"},
    {E2BIG, "E2BIG"},
    {ENOEXEC, "ENOEXEC"},
    {EBADF, "EBADF"},
    {ECHILD, "ECHILD"},
    {EAGAIN, "EAGAIN"},
    {ENOMEM, "ENOMEM"},
    {EACCES, "EACCES"},
    {EFAULT, "EFAULT"},
    {ENOTBLK, "ENOTBLK"},
    {EBUSY, "EBUSY"},
    {EEXIST, "EEXIST"},
    {EXDEV, "EXDEV"},
    {ENODEV, "ENODEV"},
    {ENOTDIR, "ENOTDIR"},
    {EISDIR, "EISDIR"},
    {EINVAL, "EINVAL"},
    {ENFILE, "ENFILE"},
    {EMFILE, "EMFILE"},
    {ENOTTY, "ENOTTY"},
    {ETXTBSY, "ETXTBSY"},
    {EFBIG, "EFBIG"},
    {ENOSPC, "ENOSPC"},
    {ESPIPE, "ESPIPE"},
    {EROFS, "EROFS"},
    {EMLINK, "EMLINK"},
    {EPIPE, "EPIPE"},
    {EDOM, "EDOM"},
    {ERANGE, "ERANGE"},
    {EDEADLK, "EDEADLK"},
    {ENAMETOOLONG, "ENAMETOOLONG"},
    {ENOLCK, "ENOLCK"},
    {ENOSYS, "ENOSYS"},
    {ENOTEMPTY, "ENOTEMPTY"},
    {ELOOP, "ELOOP"},
    {ENOMSG, "ENOMSG"},
    {EBADR, "EBADR"},
    {EXFULL, "EXFULL"},
    {ENOANO, "ENOANO"},
    {EBADRQC, "EBADRQC"},
    {EBADSLT, "EBADSLT"},
    {EBFONT, "EBFONT"},
    {ENOSTR, "ENOSTR"},
    {ENODATA, "ENODATA"},
    {ETIME, "ETIME"},
    {ENOLINK, "ENOLINK"},
    {EADV, "EADV"},
    {ESRMNT,"ESRMNT"},
    {ECOMM, "ECOMM"},
    {EPROTO, "EPROTO"},
    {EMULTIHOP, "EMULTIHOP"},
    {EDOTDOT, "EDOTDOT"},
    {EBADMSG, "EBADMSG"},
    {EOVERFLOW, "EOVERFLOW"},
    {ENOTUNIQ, "ENOTUNIQ"},
    {EBADFD, "EBADFD"},
    {ENOSR, "EREMOTE"},
    {ENONET, "ENONET"},
    {ENOPKG, "ENOPKG"},
    {EREMOTE, "EREMOTE"},
    {EREMCHG, "EREMCHG"},
    {ELIBACC, "ELIBACC"},
    {ELIBBAD, "ELIBBAD"},
    {ELIBSCN, "ELIBSCN"},
    {ELIBMAX, "ELIBMAX"},
    {ELIBEXEC, "ELIBEXEC"},
    {EILSEQ, "EILSEQ"},
    {ERESTART, "ERESTART"},
    {ESTRPIPE, "ESTRPIPE"},
    {EUSERS, "EUSERS"},
    {ENOTSOCK, "ENOTSOCK"},
    {EDESTADDRREQ, "EDESTADDRREQ"},
    {EMSGSIZE, "EMSGSIZE"},
    {EPROTOTYPE, "EPROTOTYPE"},
    {ENOPROTOOPT, "ENOPROTOOPT"},
    {EPROTONOSUPPORT, "EPROTONOSUPPORT"},
    {ESOCKTNOSUPPORT, "ESOCKTNOSUPPORT"},
    {EOPNOTSUPP, "EOPNOTSUPP"},
    {EPFNOSUPPORT, "EPFNOSUPPORT"},
    {EAFNOSUPPORT, "EAFNOSUPPORT"},
    {EADDRINUSE, "EADDRINUSE"},
    {EADDRNOTAVAIL, "EADDRNOTAVAIL"},
    {ENETDOWN, "ENETDOWN"},
    {ENETUNREACH, "ENETUNREACH"},
    {ENETRESET, "ENETRESET"},
    {ECONNABORTED, "ECONNABORTED"},
    {ECONNRESET, "ECONNRESET"},
    {ENOBUFS, "ENOBUFS"},
    {EISCONN, "EISCONN"},
    {ENOTCONN, "ENOTCONN"},
    {ESHUTDOWN, "ESHUTDOWN"},
    {ETOOMANYREFS, "ETOOMANYREFS"},
    {ETIMEDOUT, "ETIMEDOUT"},
    {ECONNREFUSED, "ECONNREFUSED"},
    {EHOSTDOWN, "EHOSTDOWN"},
    {EHOSTUNREACH, "EHOSTUNREACH"},
    {EALREADY, "EALREADY"},
    {EINPROGRESS, "EINPROGRESS"},
    {ESTALE, "ESTALE"},
    {EUCLEAN, "EUCLEAN"},
    {ENOTNAM, "ENOTNAM"},
    {ENAVAIL, "ENAVAIL"},
    {EISNAM, "EISNAM"},
    {EREMOTEIO, "EREMOTEIO"},
    {EDQUOT, "EDQUOT"},
    {ENOMEDIUM, "ENOMEDIUM"},
    {EMEDIUMTYPE, "EMEDIUMTYPE"},
    {ECANCELED, "ECANCELED"},
    {ENOKEY, "ENOKEY"},
    {EKEYEXPIRED, "EKEYEXPIRED"},
    {EKEYREVOKED, "EKEYREVOKED"},
    {EKEYREJECTED, "EKEYREJECTED"},
    {EOWNERDEAD, "EOWNERDEAD"},
    {ENOTRECOVERABLE, "ENOTRECOVERABLE"},
    {ERFKILL, "ERFKILL"},
    {EHWPOISON, "EHWPOISON"},
    {0, NULL}
};

#define E_FALSE 0
#define E_TRUE 1

const size_t strerrno_min_buf_size = 20;

errno_t strerrno_s(char * const buf, const rsize_t buflen, const errno_t errnum)
{
    errno_t result = 0;
    size_t list_size = (sizeof(str_err_list) / sizeof(error_list_t));
    int matched = E_FALSE;

    if(NULL == buf)
    {
        result = EFAULT;
    }
    else if(buflen < strerrno_min_buf_size)
    {
        result = ERANGE;
    }
    else if(buflen > 0)
    {
        /* Always terminate with NUL byte in case no other output */
        buf[0] = '\0';
    }
    /* Note, the above could be simplified, but the compiler will optimise the order */

    if(0 == result)
    {
        /* Find in the table */
        for(size_t i = 0; i != list_size; ++i)
        {
            if(errnum == str_err_list[i].value)
            {
                strncpy(buf, str_err_list[i].str, buflen);
                matched = E_TRUE;

                break;
            }
        }

        if(!matched)
        {
            snprintf(buf, buflen, "errno_t_%d_unknown\n", errnum);
            buf[buflen-1] = '\0';

            result = EINVAL;
        }
    }

    return result;
}
