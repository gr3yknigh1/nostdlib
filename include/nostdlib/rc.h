#ifndef NOSTDLIB_RC_H_
#define NOSTDLIB_RC_H_

typedef enum {
    RC_OK,
    RC_UNKNOWN_ERROR,
    RC_NOTHING_TODO,

    // I/O
    RC_UNABLE_TO_READ,
    RC_UNABLE_TO_WRITE,
} noc_rc;

#endif // NOSTDLIB_RC_H_
