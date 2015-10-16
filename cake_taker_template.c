#include <stdio.h>
#include <string.h>

// The next line is replaced by pack_cake.py
// TEMPLATE GOES HERE

// For development, here is a test cake.
#ifndef CRYPTED_CAKE
    #define KEY 1234
    #define CRYPTED_PASSWORD "\262\302\323\072\171\200\276\141" // "password"
    #define CRYPTED_CAKE "\226\346\363\035\056\254\215\116\157\052"
    #define CAKE_SIZE 10 // MUST match above.
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


void crypt(char *buffer, unsigned key, unsigned size) {
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
    char password[32];
    strcpy((char*)&password[0], argv[1]);
    crypt(&password[0], KEY, 32);

    // Check every character so there are no timing attacks.
    int password_is_correct = 1;
    char crypted_password[] = CRYPTED_PASSWORD;
    for (unsigned i = 0; crypted_password[i] != 0; i++) {
        if (password[i] != crypted_password[i]) {
            password_is_correct = 0;
        }
    }

    if (password_is_correct || debug) {

        char cake_filename[] = CAKE_FILENAME;
        printf("Password is correct!\nWriting cake to %s\n", cake_filename);

        // Decrypt the cake.
        char cake[CAKE_SIZE];
        memcpy(cake, CRYPTED_CAKE, CAKE_SIZE);
        crypt(&cake[0], KEY, CAKE_SIZE);

        // Write the cake.
        FILE *f = fopen(cake_filename, "w");
        fwrite(cake, CAKE_SIZE, 1, f);
        fclose(f);

    } else {
        printf("Incorrect password; please try again!\n");
        return 2;
    }

    return 0;

}
