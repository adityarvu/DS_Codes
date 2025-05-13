#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PIN_LENGTH 10
#define HASH_LENGTH 64  // We're using a custom hash length for simplicity
#define SALT_LENGTH 8
#define MAX_ATTEMPTS 3

// Generate a random salt
void generate_salt(char* salt) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < SALT_LENGTH; i++) {
        salt[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    salt[SALT_LENGTH] = '\0';
}

// Simple custom hash function (not cryptographically secure, but for demonstration purposes)
void simple_hash(const char* input, const char* salt, char* outputHash) {
    int hash = 0;
    for (int i = 0; i < strlen(input); i++) {
        hash = (hash * 31 + input[i]) % HASH_LENGTH;  // Simple hash logic
    }
    for (int i = 0; i < strlen(salt); i++) {
        hash = (hash * 31 + salt[i]) % HASH_LENGTH;  // Include salt in the hash
    }

    // Convert integer hash to hex string
    snprintf(outputHash, HASH_LENGTH + 1, "%x", hash);
}

// Hash the PIN using salt
void hash_pin(const char* pin, const char* salt, char* outputHash) {
    simple_hash(pin, salt, outputHash);
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    char user_pin[PIN_LENGTH];
    char salt[SALT_LENGTH + 1];
    char stored_hash[HASH_LENGTH + 1];

    // Account setup: User sets their PIN
    printf(" --- ACCOUNT SETUP ---\n");
    printf(" Set your new 4-10 digit PIN: ");
    scanf("%s", user_pin);

    generate_salt(salt); // Generate a random salt
    hash_pin(user_pin, salt, stored_hash); // Hash the PIN with the salt

    printf(" PIN securely stored (hashed with salt).\n");
    printf(" Salt used: %s\n", salt); // (Shown here for demonstration)
    printf(" Stored Hash: %s\n", stored_hash); // (Also for demonstration)

    printf("\n --- SECURE BANK LOGIN --- \n");

    int attempts = 0;
    char login_pin[PIN_LENGTH];
    char login_hash[HASH_LENGTH + 1];

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter your PIN: ");
        scanf("%s", login_pin);

        hash_pin(login_pin, salt, login_hash); // Hash login input with the same salt

        if (strcmp(stored_hash, login_hash) == 0) {
            printf(" Access granted! Welcome to your account.\n");
            return 0;
        } else {
            attempts++;
            printf(" Incorrect PIN. Attempts left: %d\n", MAX_ATTEMPTS - attempts);
        }
    }

    printf("\nToo many failed attempts. Your account has been temporarily locked.\n");
    return 1;
}