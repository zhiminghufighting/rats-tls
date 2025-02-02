/* Copyright (c) 2021 Intel Corporation
 * Copyright (c) 2020-2021 Alibaba Cloud
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SGX_ECDSA_H
#define _SGX_ECDSA_H

#include <sgx_urts.h>

#define ECDSA_QUOTE_OID "1.2.840.113741.1337.6"

typedef struct {
	sgx_enclave_id_t eid;
} sgx_ecdsa_ctx_t;

#endif
