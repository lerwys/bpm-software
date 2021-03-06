/*
 * Copyright (C) 2014 LNLS (www.lnls.br)
 * Author: Lucas Russo <lucas.russo@lnls.br>
 *
 * Released according to the GNU LGPL, version 3 or any later version.
 */

#ifndef _DEV_MNGR_CORE_H_
#define _DEV_MNGR_CORE_H_

#include "czmq.h"
#include "dev_mngr_err.h"

/* Signal handler function pointer */
typedef void (*sig_handler_fp)(int sig, siginfo_t *siginfo, void *context);
/* Wait child handler function pointer */
typedef int (*wait_chld_handler_fp)(void);
/* Spawn child handler function pointer */
typedef int (*spawn_chld_handler_fp)(const char *program, char *const argv[]);
/* Spawn broker handler function pointer */
typedef int (*spawn_broker_handler_fp)(const char *program, char *const argv[]);

/* Node of sig_ops list */
struct _dmngr_sig_handler_t {
    int signal;         /* Signal identifier, e.g., SIGINT, SIGKILL, etc... */
    sig_handler_fp dmngr_sig_h;
};

struct _dmngr_ops_t {
    wait_chld_handler_fp dmngr_wait_chld;       /* Called to wait a all child process */
    spawn_chld_handler_fp dmngr_spawn_chld;     /* Called to spawn a new process to handle device */
    spawn_broker_handler_fp dmngr_spawn_broker; /* Called to spawn (or respawn a zeroMQ broker */

    /* List of dmngr_sig_handler_t */
    zlist_t *sig_ops;
};

struct _dmngr_t {
    /* General information */
    zctx_t *ctx;                /* zeroMQ context */
    void *dealer;               /* zeroMQ Dealer socket */
    char *name;                 /* Identification of this dmngr instance */
    char *endpoint;             /* Endpoint to connect to */
    int verbose;                /* Print activity to stdout */

    /* General management operations */
    struct _dmngr_ops_t *ops;

    /* zeroMQ broker management */
    bool broker_running;         /* true if broker is already running */

    /* Device managment */
};

/* Opaque class signal handler structure */
typedef struct _dmngr_sig_handler_t dmngr_sig_handler_t;
/* Opaque operations handler structure */
typedef struct _dmngr_ops_t dmngr_ops_t;
/* Opaque class structure */
typedef struct _dmngr_t dmngr_t;

/***************** Our methods *****************/

/* Creates a new instance of the Device Manager */
dmngr_t * dmngr_new (char *name, char * endpoint, int verbose);
/* Destroy an instance of the Device Manager */
dmngr_err_e dmngr_destroy (dmngr_t **self_p);

/* Register signals to Device Manager instance */
dmngr_err_e dmngr_set_sig_handler (dmngr_t *self, dmngr_sig_handler_t *sig_handler);
/* Register all signal handlers previously set */
dmngr_err_e dmngr_register_sig_handlers (dmngr_t *self);
/* Register function to wait a all child process */
dmngr_err_e dmngr_set_wait_clhd_handler (dmngr_t *self, wait_chld_handler_fp fp);
/* Execute function to wait a all child process */
dmngr_err_e dmngr_wait_chld (dmngr_t *self);
/* Register function to spawn a all child process */
dmngr_err_e dmngr_set_spawn_clhd_handler (dmngr_t *self, spawn_chld_handler_fp fp);
/* Execute function to spawn a all child process */
dmngr_err_e dmngr_spawn_chld (dmngr_t *self, const char *program, char *const argv[]);
/* Execute function to spawn a broker process */
dmngr_err_e dmngr_spawn_broker (dmngr_t *self, const char *program, char *const argv[]);

/* Setting all operations at once */
dmngr_err_e dmngr_set_ops (dmngr_t *self, dmngr_ops_t *dmngr_ops);
/* Is broker Running? */
bool dmngr_is_broker_running (dmngr_t *self);

#endif
