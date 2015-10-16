#include <stdio.h>
#include <string.h>

#ifndef CAKE // Assume this is debugging mode.
    #define KEY 1234
    #define CRYPTED_PASSWORD "\262\302\323\072\171\200\276\141" // "password"
    #define CRYPTED_CAKE "\226\346\363\035\056\254\215\116\157\052"
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


void crypt(char *buffer, unsigned key) {
    // XOR encryption is also decryption!
    while (*buffer) {
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
    char password[32];
    strcpy(&password[0], argv[1]);
    crypt(&password[0], KEY);

    // Manually loop for no timing attacks.
    int password_is_correct = 1;
    for (unsigned i = 0; CRYPTED_PASSWORD[i] != 0; i++) {
        if (password[i] != CRYPTED_PASSWORD[i]) {
            password_is_correct = 0;
        }
    }

    if (password_is_correct || debug) {

        printf("CORRECT!\nWriting cake to %s\n", CAKE_FILENAME);

        // Decrypt te cake.
        char *cake = strdup(CRYPTED_CAKE);
        crypt(cake, KEY);

        // Write the cake.
        FILE *f = fopen(CAKE_FILENAME, "w");
        fprintf(f, "%s", cake);
        fclose(f);

    } else {
        printf("Wrong password.");
        return 2;
    }

    return 0;

}
