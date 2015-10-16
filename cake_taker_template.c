#include <stdio.h>
#include <string.h>

// The next line is replaced by pack_cake.
// TEMPLATE GOES HERE

#ifndef CRYPTED_CAKE // Assume this is debugging mode.
    #define KEY 1234
    #define CRYPTED_PASSWORD "\262\302\323\072\171\200\276\141" // "password"
    #define CRYPTED_CAKE "\226\346\363\035\056\254\215\116\157\052"
    #define CAKE_SIZE 10 // MUST match.
    #define CAKE_FILENAME "testing.txt"
#endif


unsigned next_key(unsigned k) {
    // Linear conguential generator of form: k(n+1) = (a * k(n) + c) % m
    // We use params to match rand() in glibc
    unsigned a = 1103515245;
    unsigned m = 1 << 31;
    unsigned c = 12345;
    return (a * k + c) % m;
}


void crypt(unsigned char *buffer, unsigned key, unsigned size) {
    // XOR encryption is also decryption!
    while (size--) {
        *buffer = *buffer ^ (key & 0xef);
        key = next_key(key);
        buffer++;
    }
}


int main(int argc, char **argv) {

    if (argc != 2) {
        printf("usage: %s PASSWORD\n", argv[0]);
        return 1;
    }

    int debug = 0; // For testing.

    // Decrypt the password
    unsigned char password[32];
    strcpy((char*)&password[0], argv[1]);
    crypt(&password[0], KEY, 32);

    // Manually loop for no timing attacks.
    int password_is_correct = 1;
    unsigned char crypted_password[] = CRYPTED_PASSWORD;
    for (unsigned i = 0; CRYPTED_PASSWORD[i] != 0; i++) {
        if (password[i] != crypted_password[i]) {
            password_is_correct = 0;
        }
    }

    if (password_is_correct || debug) {

        printf("CORRECT!\nWriting cake to %s\n", CAKE_FILENAME);

        // Decrypt te cake.
        unsigned char cake[CAKE_SIZE];
        memcpy(cake, CRYPTED_CAKE, CAKE_SIZE);
        crypt(&cake[0], KEY, CAKE_SIZE);

        // Write the cake.
        FILE *f = fopen(CAKE_FILENAME, "w");
        fwrite(cake, CAKE_SIZE, 1, f);
        fclose(f);

    } else {
        printf("Wrong password.");
        return 2;
    }

    return 0;

}