//Marin Aske
//Lab Assignment 10
//CS1 Torosdagli


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count;
};

// Initializes a trie node
struct TrieNode *createNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            node->children[i] = NULL;
    }
    return node;
}

// Inserts the word into the trie
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            current->children[index] = createNode();
        current = current->children[index];
    }
    // Mark the end of the word
    current->count++;
}

// Counts the occurrences of a word in the trie
int numberOfOccurrences(struct TrieNode *root, char *word) {
    struct TrieNode *current = root;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            return 0;
        current = current->children[index];
    }
    return current->count;
}

// Deallocates the trie
void deallocateTrie(struct TrieNode *root) {
    if (root == NULL)
        return;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (root->children[i] != NULL)
            deallocateTrie(root->children[i]);
    }
    free(root);
}

// Reads the dictionary file and stores words in memory
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    int numWords = 0;
    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[numWords] = strdup(word);
        numWords++;
    }

    fclose(file);
    return numWords;
}

int main(void) {
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    struct TrieNode *root = createNode();
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }

    // Words to check occurrences
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }

    deallocateTrie(root);
    return 0;
}
