
#include <errno.h>

#include "stdio_cx.h"

typedef struct error_list
{
    errno_t value;
    const char * str;
} error_list_t;

static error_list_t str_err_list[]
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
    {EBADFD, "EBADFD"}
};


errno_t strerrno_s(char * const buf, const rsize_t buflen, const errno_t errnum)
{
    errno_t result = 0;
    size_t list_size = (sizeof(str_err_list) / sizeof(error_list_t));
    bool matched = false;

    if(buflen > 0)
    {
        buf[0] = '\0';
    }

    if(NULL == buf)
    {
        result = EFAULT;
    }
    else if(buflen < 20)
    {
        result = ERANGE;
    }
    else
    {
        /* Always terminate with NUL byte in case no other output */
        buf[0] = '\0';

        /* Find in the table */
        for(size_t i = 0; i != list_size; ++i)
        {
            if(errnum == str_err_list[i].value)
            {
                strncpy(buf, str_err_list[i].str, buflen);
                matched = true;
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


#if 0
          

ENOSR
ENONET
ENOPKG
EREMOTE


#define	EREMCHG		78	/* Remote address changed */
#define	ELIBACC		79	/* Can not access a needed shared library */
#define	ELIBBAD		80	/* Accessing a corrupted shared library */
#define	ELIBSCN		81	/* .lib section in a.out corrupted */
#define	ELIBMAX		82	/* Attempting to link in too many shared libraries */
#define	ELIBEXEC	83	/* Cannot exec a shared library directly */
#define	EILSEQ		84	/* Illegal byte sequence */
#define	ERESTART	85	/* Interrupted system call should be restarted */
#define	ESTRPIPE	86	/* Streams pipe error */
#define	EUSERS		87	/* Too many users */
#define	ENOTSOCK	88	/* Socket operation on non-socket */
#define	EDESTADDRREQ	89	/* Destination address required */
#define	EMSGSIZE	90	/* Message too long */
#define	EPROTOTYPE	91	/* Protocol wrong type for socket */
#define	ENOPROTOOPT	92	/* Protocol not available */
#define	EPROTONOSUPPORT	93	/* Protocol not supported */
#define	ESOCKTNOSUPPORT	94	/* Socket type not supported */
#define	EOPNOTSUPP	95	/* Operation not supported on transport endpoint */
#define	EPFNOSUPPORT	96	/* Protocol family not supported */
#define	EAFNOSUPPORT	97	/* Address family not supported by protocol */
#define	EADDRINUSE	98	/* Address already in use */
#define	EADDRNOTAVAIL	99	/* Cannot assign requested address */
#define	ENETDOWN	100	/* Network is down */
#define	ENETUNREACH	101	/* Network is unreachable */
#define	ENETRESET	102	/* Network dropped connection because of reset */
#define	ECONNABORTED	103	/* Software caused connection abort */
#define	ECONNRESET	104	/* Connection reset by peer */
#define	ENOBUFS		105	/* No buffer space available */
#define	EISCONN		106	/* Transport endpoint is already connected */
#define	ENOTCONN	107	/* Transport endpoint is not connected */
#define	ESHUTDOWN	108	/* Cannot send after transport endpoint shutdown */
#define	ETOOMANYREFS	109	/* Too many references: cannot splice */
#define	ETIMEDOUT	110	/* Connection timed out */
#define	ECONNREFUSED	111	/* Connection refused */
#define	EHOSTDOWN	112	/* Host is down */
#define	EHOSTUNREACH	113	/* No route to host */
#define	EALREADY	114	/* Operation already in progress */
#define	EINPROGRESS	115	/* Operation now in progress */
#define	ESTALE		116	/* Stale file handle */
#define	EUCLEAN		117	/* Structure needs cleaning */
#define	ENOTNAM		118	/* Not a XENIX named type file */
#define	ENAVAIL		119	/* No XENIX semaphores available */
#define	EISNAM		120	/* Is a named type file */
#define	EREMOTEIO	121	/* Remote I/O error */
#define	EDQUOT		122	/* Quota exceeded */

#define	ENOMEDIUM	123	/* No medium found */
#define	EMEDIUMTYPE	124	/* Wrong medium type */
#define	ECANCELED	125	/* Operation Canceled */
#define	ENOKEY		126	/* Required key not available */
#define	EKEYEXPIRED	127	/* Key has expired */
#define	EKEYREVOKED	128	/* Key has been revoked */
#define	EKEYREJECTED	129	/* Key was rejected by service */

/* for robust mutexes */
#define	EOWNERDEAD	130	/* Owner died */
#define	ENOTRECOVERABLE	131	/* State not recoverable */

#define ERFKILL		132	/* Operation not possible due to RF-kill */

#define EHWPOISON	133	/* Memory page has hardware error */
#endif

