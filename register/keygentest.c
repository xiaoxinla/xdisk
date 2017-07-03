#include <stdlib.h>
#include <stdio.h>
#include <sodium.h>
#include <string.h>

#define PASSWORD "123456"
#define KEY_LEN crypto_box_SEEDBYTES

unsigned char salt[crypto_pwhash_SALTBYTES];
unsigned char key[KEY_LEN];

int main() {
	randombytes_buf(salt, sizeof salt);
	if(crypto_pwhash(key, sizeof key, PASSWORD, strlen(PASSWORD), salt,crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE,crypto_pwhash_ALG_DEFAULT) != 0) {
		printf("error\n");
	} else {
		printf("salt: %s, key: %s\n", salt, key);
	}
	char hashed_password[crypto_pwhash_STRBYTES];
	if(crypto_pwhash_str(hashed_password, PASSWORD, strlen(PASSWORD), crypto_pwhash_OPSLIMIT_SENSITIVE, crypto_pwhash_MEMLIMIT_SENSITIVE)!=0) {
		printf("error\n");
	} else {
		printf("hashedpassword(%d): %s\n", strlen(hashed_password), hashed_password);
	}
	if(crypto_pwhash_str_verify(hashed_password, PASSWORD, strlen(PASSWORD))!=0) {
		printf("wrong\n");
	} else {
		printf("right\n");
	}
}
