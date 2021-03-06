/*
 * Copyright (C) 2014 LNLS (www.lnls.br)
 * Author: Lucas Russo <lucas.russo@lnls.br>
 *
 * Released according to the GNU LGPL, version 3 or any later version.
 */

#include <stdlib.h>
#include <assert.h>
#include <czmq.h>

#include "sm_io_fmc130m_4ch_core.h"
#include "sm_io_err.h"
#include "hal_assert.h"

/* Undef ASSERT_ALLOC to avoid conflicting with other ASSERT_ALLOC */
#ifdef ASSERT_TEST
#undef ASSERT_TEST
#endif
#define ASSERT_TEST(test_boolean, err_str, err_goto_label)  \
    ASSERT_HAL_TEST(test_boolean, SM_IO, "[sm_io_fmc130m_4ch_core]", \
            err_str, err_goto_label)

#ifdef ASSERT_ALLOC
#undef ASSERT_ALLOC
#endif
#define ASSERT_ALLOC(ptr, err_goto_label)                   \
    ASSERT_HAL_ALLOC(ptr, SM_IO, "[sm_io_fmc130m_4ch_core]", \
            smio_err_str(SMIO_ERR_ALLOC),                   \
            err_goto_label)

#ifdef CHECK_ERR
#undef CHECK_ERR
#endif
#define CHECK_ERR(err, err_type)                            \
    CHECK_HAL_ERR(err, SM_IO, "[sm_io_fmc130m_4ch_core]",   \
            smio_err_str (err_type))

/* Creates a new instance of Device Information */
smio_fmc130m_4ch_t * smio_fmc130m_4ch_new (uint32_t dummy)
{
    smio_fmc130m_4ch_t *self = (smio_fmc130m_4ch_t *) zmalloc (sizeof *self);
    ASSERT_ALLOC(self, err_self_alloc);

    self->dummy = dummy;

    return self;

err_self_alloc:
    return NULL;
}

/* Destroy an instance of the Device Information */
smio_err_e smio_fmc130m_4ch_destroy (smio_fmc130m_4ch_t **self_p)
{
    assert (self_p);

    if (*self_p) {
        smio_fmc130m_4ch_t *self = *self_p;

        free (self);
        *self_p = NULL;
    }

    return SMIO_SUCCESS;
}

