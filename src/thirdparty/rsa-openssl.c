#include "rsa.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>

#if !defined(WITH_RSA_BIGINT) && !defined(WITH_RSA_LIBTOM) && defined(WITH_RSA_OPENSSL)
/* from RSC Sundae. Public domain. */

int rsa_init(struct rsa *rsa, const char *exponent, const char *modulus) {
    rsa->ctx = BN_CTX_new();
    if (!rsa->ctx) {
        return -1;
    }

    if (BN_hex2bn(&rsa->exponent, exponent) == 0) {
        return -1;
    }

    if (BN_hex2bn(&rsa->modulus, modulus) == 0) {
        return -1;
    }

    return 0;
}

int rsa_crypt(struct rsa *rsa, void *buffer, size_t len,
              void *out, size_t outlen) {
    BIGNUM *encrypted;
    BIGNUM *result;
    int r;

    (void)outlen;

    encrypted = BN_bin2bn(buffer, (int)len, NULL);
    if (!encrypted) {
        assert(0);
        return -1;
    }

    result = BN_new();
    BN_mod_exp(result, encrypted,
               rsa->exponent, rsa->modulus, rsa->ctx);

    BN_free(encrypted);

    r = BN_bn2bin(result, out);
    BN_free(result);

    if (r == 0) {
        assert(0);
        return -1;
    }
    return r;
}
#endif
