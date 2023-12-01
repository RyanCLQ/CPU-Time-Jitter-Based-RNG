#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "jitterentropy.h"

void dump_hex(uint8_t * h, int len)
{
    while(len--)
    {   
        printf("%02hhx ",*h++);
        if(len%16==0) printf("\n");
    }
}

int main()
{
	unsigned long size, rounds = 20;
	int ret = 0;
	unsigned int flags = 0, osr = 0;
	struct rand_data *ec_nostir;
	flags |= JENT_FORCE_FIPS;
	ret = jent_entropy_init_ex(osr, flags);
	if (ret) {
		printf("The initialization failed with error code %d\n", ret);
		return ret;
	}

	ec_nostir = jent_entropy_collector_alloc(osr, flags);
	if (!ec_nostir) {
		printf("Jitter RNG handle cannot be allocated\n");
		return 1;
	}

	for (size = 0; size < rounds; size++) {
		char tmp[32];

		if (0 > jent_read_entropy_safe(&ec_nostir, tmp, sizeof(tmp))) {
			fprintf(stderr, "FIPS 140-2 continuous test failed\n");
			return 1;
		}
		dump_hex(tmp,32);
	}

	jent_entropy_collector_free(ec_nostir);

	return 0;
}
