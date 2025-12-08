#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define MAX_LEN 100

// Function to load banned usernames
int loadBanned(char banned[][MAX_LEN]) {
    FILE *file = fopen("banned.txt", "r");
    if (!file) {
        printf("Error: banned.txt not found!\n");
        return 0;
    }

    int count = 0;
    while (fgets(banned[count], MAX_LEN, file)) {
        banned[count][strcspn(banned[count], "\n")] = '\0';  // remove newline
        count++;
    }
    fclose(file);
    return count;
}

// Check if username is banned
int isBanned(char username[], char banned[][MAX_LEN], int bannedCount) {
    for (int i = 0; i < bannedCount; i++) {
        if (strcasecmp(username, banned[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if only letters, numbers, underscore
int validCharacters(char username[]) {
    for (int i = 0; username[i] != '\0'; i++) {
        if (!isalnum(username[i]) && username[i] != '_')
            return 0;
    }
    return 1;
}

// Check no triple repeated characters
int hasRepeats(char username[]) {
    for (int i = 0; username[i+2] != '\0'; i++) {
        if (username[i] == username[i+1] && username[i+1] == username[i+2])
            return 1;
    }
    return 0;
}

// Check simple sequences
int hasSequence(char username[]) {
    char *sequences[] = {"abc", "abcd", "123", "1234", "qwerty"};
    int seqCount = 5;
    
    for (int i = 0; i < seqCount; i++) {
        if (strcasestr(username, sequences[i])) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char banned[MAX][MAX_LEN];
    int bannedCount = loadBanned(banned);

    char username[MAX_LEN];
    
    printf("===== Username Availability Checker (C Version) =====\n");
    printf("Enter a username: ");
    scanf("%s", username);

    printf("\n--- Result ---\n");

    int len = strlen(username);

    // Validations:
    if (len < 5) {
        printf("✘ Username must be at least 5 characters.\n");
        return 0;
    }

    if (len > 20) {
        printf("✘ Username cannot be longer than 20 characters.\n");
        return 0;
    }

    if (isdigit(username[0])) {
        printf("✘ Username cannot start with a number.\n");
        return 0;
    }

    if (!validCharacters(username)) {
        printf("✘ Only letters, numbers, and underscore (_) allowed.\n");
        return 0;
    }

    if (hasRepeats(username)) {
        printf("✘ Avoid repeating same character 3+ times.\n");
        return 0;
    }

    if (hasSequence(username)) {
        printf("✘ Avoid simple patterns like abc, 123, qwerty.\n");
        return 0;
    }

    if (isBanned(username, banned, bannedCount)) {
        printf("✘ This username is banned or already taken.\n");
        return 0;
    }

    // Passed all rules
    printf("✔ Username is available and valid!\n");

    return 0;
}