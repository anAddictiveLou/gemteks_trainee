#ifndef _HTTPS_H
#define _HTTPS_H

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#include "lou.h"

void https_init(void);

#endif