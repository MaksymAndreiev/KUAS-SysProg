#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


// 1) define stringHash(string) here

size_t stringHash(const char *string) {
    size_t hash = 5381;
    int c;
    while ((c = *string++)) {
        hash = hash * 33 + c;
    }
    return hash;
}

// 2a) define struct Assoc here

struct Assoc {  // a structure that associates a key with a value
    char *key; // the key and ...
    int value; // its corresponding value
    struct Assoc *next; // a pointer to the next association
};

// 2b) define newAssoc(key) here

struct Assoc *newAssoc(const char *key) {
    struct Assoc *assoc = calloc(1, sizeof(struct Assoc));
    assoc->key = strdup(key);  // key might be a temporary string
    return assoc;  // calloc() clears the value to zeroes
}

// 3a) define struct Map here

struct Map {  // holds many keys and corresponding values
    struct Assoc **assocs;  // an array of key-value associations
    size_t size;  // association index is: stringHash(key) % size
};

// 3b) define newMap() here

struct Map *newMap(size_t size) {
    struct Map *map = calloc(1, sizeof(struct Map));
    map->assocs = calloc(size, sizeof(struct Assoc *)); // preallocated
    map->size = size;  // must not change after initialization
    return map;
}

// 4) define Map_find() here

struct Assoc *Map_find(struct Map *map, char *key) {
    size_t h = stringHash(key) % map->size;
    struct Assoc *current = map->assocs[h];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }

    struct Assoc *new_assoc = newAssoc(key);
    new_assoc->next = map->assocs[h];
    map->assocs[h] = new_assoc;
    return new_assoc;
}
// 5) add getWord() here

char *getWord(FILE *in) {
    static char word[64];
    int c = getc(in);
    while (!isalpha(c) && c != EOF) c = getc(in);
    if (c == EOF) return 0;
    size_t index = 0;
    do {
        word[index++] = tolower(c);
        c = getc(in);
    } while (isalpha(c) && index < sizeof(word));
    word[index] = '\0';
    return word;
}

void Map_remove(struct Map *map, char *key) {
    size_t h = stringHash(key) % map->size;
    struct Assoc *current = map->assocs[h];
    struct Assoc *prev = 0;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                map->assocs[h] = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int main(int argc, char **argv) {
    // 1. test stringHash()

    assert((stringHash("") % 8) == 5);
    assert((stringHash("hello") % 8) == 1);
    assert((stringHash("left") % 8) == 0);
    assert((stringHash("low") % 8) == 7);

    // for exercise below, replace "/*" with "//" to enable the tests for that exercise

    // 2. implement and test Assoc

    struct Assoc *assoc = newAssoc("hello");

    assert(0 == strcmp(assoc->key, "hello"));

    // 3. implement and test Map

    struct Map *map = newMap(8);

    assert(8 == map->size);
    for (int i = 0; i < 8; ++i) assert(0 == map->assocs[i]);

    // 4. implement and test Map_find()

    struct Assoc *empty = Map_find(map, "");
    assert(empty == Map_find(map, ""));
    struct Assoc *hello = Map_find(map, "hello");
    assert(hello == Map_find(map, "hello"));
    struct Assoc *left = Map_find(map, "left");
    assert(left == Map_find(map, "left"));
    struct Assoc *low = Map_find(map, "low");
    assert(low == Map_find(map, "low"));

    // 5. test Assoc with integer value

    map = newMap(400);

    FILE *words = fopen("words.txt", "r");
    if (!words)perror("fopen");
    if (0 == words) {
        fprintf(stderr, "cannot open words10000.txt\n");
        exit(1);
    }
    char *word;
    while ((word = getWord(words))) {
        struct Assoc *assoc = Map_find(map, word);
        assert(0 != assoc);
        assoc->value += 1;
    }
    fclose(words);

    assert(Map_find(map, "all") && (10 == Map_find(map, "all")->value));
    assert(Map_find(map, "that") && (10 == Map_find(map, "that")->value));
    assert(Map_find(map, "in") && (11 == Map_find(map, "in")->value));
    assert(Map_find(map, "is") && (12 == Map_find(map, "is")->value));
    assert(Map_find(map, "for") && (13 == Map_find(map, "for")->value));
    assert(Map_find(map, "world") && (14 == Map_find(map, "world")->value));
    assert(Map_find(map, "you") && (14 == Map_find(map, "you")->value));
    assert(Map_find(map, "a") && (17 == Map_find(map, "a")->value));
    assert(Map_find(map, "to") && (24 == Map_find(map, "to")->value));
    assert(Map_find(map, "of") && (27 == Map_find(map, "of")->value));
    assert(Map_find(map, "and") && (30 == Map_find(map, "and")->value));
    assert(Map_find(map, "the") && (44 == Map_find(map, "the")->value));

    // 6. test lists to handle collisions (uses same tests as above)

    /* since comments do not nest you can leave these lines here to
       terminate any of the above comments */
    // 7. test Map_remove()

    Map_remove(map, "all");
    assert(Map_find(map, "all")->value == 0);
    Map_remove(map, "that");
    assert(Map_find(map, "that")->value == 0);

    fprintf(stderr, "all tests passed\n");

    return 0;
}
