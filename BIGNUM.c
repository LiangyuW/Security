#include <stdio.h>
#include <openssl/bn.h>

#define NBITS 256

void printBN(char *msg, BIGNUM * a)
{
	char * number_str = BN_bn2dec(a);
	printf("%s %s\n", msg, number_str);
	OPENSSL_free(number_str);
}

int main () 
{
	BN_CTX *ctx = BN_CTX_new();

	BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *c = BN_new();
	BIGNUM *n = BN_new();
	BIGNUM *res = BN_new();

	int outl;
	
	// convert decimal string to number
	BN_dec2bn(&a, "1637489035467283");

	// Generate a random number of 128 bits 
	BN_rand(b, NBITS, 0, 0);

	// Generate a random prime number of 128 bits
	BN_generate_prime_ex(c, 128, 1, NULL, NULL, NULL);

	// Assign a value from a hex number string
	BN_hex2bn(&n, "2A3B4C55FF77889AED3F9");

	BN_mul(res, a, b, ctx);
	BN_mul(res, res, c, ctx);

	printBN("a: ", a);
	printBN("b: ", b);
	printBN("c: ", c);
	printf("\n");

	printBN("a * b * c = : ",res);
	printf("\n");	

	
	BN_mod_exp(res, a, b, n, ctx);
	printBN("aˆc mod n = ", res);

}