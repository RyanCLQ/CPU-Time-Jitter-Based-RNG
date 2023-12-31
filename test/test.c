#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "jitterentropy/jitterentropy.h"
#include "entropy.h"
#include "sm3_rng.h"

void dump_hex(uint8_t * h, int len)
{
    while(len--)
    {   
        printf("%02hhx ",*h++);
        if(len%16==0) printf("\n");
    }
}

void jitterentropy_test()
{
	unsigned long size, rounds = 20;
	int ret = 0;
	unsigned int flags = 0, osr = 0, hash_mode = MODE_SM3;
	struct rand_data *ec_nostir;
	flags |= JENT_FORCE_FIPS;
	//flags |= JENT_FORCE_INTERNAL_TIMER;
	ret = jent_entropy_init_ex(osr, flags, hash_mode);
	if (ret) {
		printf("The initialization failed with error code %d\n", ret);
		return ret;
	}

	ec_nostir = jent_entropy_collector_alloc(osr, flags, hash_mode);
	if (!ec_nostir) {
		printf("Jitter RNG handle cannot be allocated\n");
		return 1;
	}

	for (size = 0; size < rounds; size++) {
		char tmp[32];

		if (0 > jent_read_entropy(ec_nostir, tmp, sizeof(tmp))) {//读取随机数
			fprintf(stderr, "FIPS 140-2 continuous test failed\n");
			return 1;
		}
		//dump_hex(tmp,32);
	}
}

void entropy_test()
{
	uint8_t entropy_buf[512] = {0};
	Get_entropy(entropy_buf,512,MODE_SM3);
	printf("Get entropy:\n");
	dump_hex(entropy_buf, 512);
}

void sm3_rng_test()
{
	uint8_t entropy_buf[32] = {0};
	sm3_rng *ctx;
	sm3_rng_alloc(&ctx);
	sm3_rng_init(ctx, NULL, 0, NULL, 0);
	sm3_rng_generate(ctx, NULL, 0, entropy_buf, 32);
	
	printf("SM3 rng generate:\n");
	dump_hex(entropy_buf, 32);

	sm3_rng_dealloc(ctx);
}

int main()
{
	jitterentropy_test();
	entropy_test();
	sm3_rng_test();

	return 0;
}
