/* Copyright (c) 2021 Intel Corporation
 * Copyright (c) 2020-2021 Alibaba Cloud
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <rats-tls/attester.h>
#include <rats-tls/log.h>
#include "tdx_ecdsa.h"

extern enclave_attester_err_t enclave_attester_register(enclave_attester_opts_t *opts);
extern enclave_attester_err_t tdx_ecdsa_attester_pre_init(void);
extern enclave_attester_err_t tdx_ecdsa_attester_init(enclave_attester_ctx_t *ctx,
						      rats_tls_cert_algo_t algo);
extern enclave_attester_err_t tdx_ecdsa_collect_evidence(enclave_attester_ctx_t *ctx,
							 attestation_evidence_t *evidence,
							 rats_tls_cert_algo_t algo, uint8_t *hash,
							 uint32_t hash_len);
extern enclave_attester_err_t tdx_ecdsa_attester_cleanup(enclave_attester_ctx_t *ctx);

static enclave_attester_opts_t tdx_ecdsa_attester_opts = {
	.api_version = ENCLAVE_ATTESTER_API_VERSION_DEFAULT,
	.flags = ENCLAVE_ATTESTER_OPTS_FLAGS_TDX_GUEST,
	.name = "tdx_ecdsa",
        .oid = TDX_QUOTE_OID,
	.priority = 42,
	.pre_init = tdx_ecdsa_attester_pre_init,
	.init = tdx_ecdsa_attester_init,
	.collect_evidence = tdx_ecdsa_collect_evidence,
	.cleanup = tdx_ecdsa_attester_cleanup,
};

void __attribute__((constructor)) libattester_tdx_ecdsa_init(void)
{
	RTLS_DEBUG("called\n");

	enclave_attester_err_t err = enclave_attester_register(&tdx_ecdsa_attester_opts);
	if (err != ENCLAVE_ATTESTER_ERR_NONE)
		RTLS_DEBUG("failed to register the enclave attester 'tdx_ecdsa' %#x\n", err);
}
