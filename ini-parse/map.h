#ifndef _MAP
#define _MAP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define stringify(name) # name

/* Settings entry */

typedef enum {
    INT,
    STRING,
    BOOL
} entryType;

const char* TYPES[3] = {
    stringify(INT),
    stringify(STRING),
    stringify(BOOL)
};

typedef struct {
    char *name;
    void *pointer;
    entryType type;
} mapEntry;

void printEntry(const mapEntry*);

static mapEntry* createStringEntry(const char*, const char*);
static mapEntry* createIntegerEntry(const char*, const int);
static mapEntry* createBooleanEntry(const char*, const bool);

static void deleteEntry(mapEntry*);

/* Whole settings structure */

typedef struct {
    char *section;
    mapEntry *map;
} section;

typedef section* settings;

extern settings* createSettings(const char*);
extern void deleteSettings(settings*);
static void parseIniFile(const char*, settings*);

/* Helper functions */
static int countSections(FILE*);

#undef stringify
#endif
