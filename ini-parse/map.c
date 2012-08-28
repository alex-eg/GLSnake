#include "map.h"

void deleteEntry(mapEntry *entry)
{
    free(entry->name);
    free(entry->pointer);
    entry = NULL;
}

mapEntry* createStringEntry(const char* name, const char* string)
{
    mapEntry *entry = malloc(sizeof(mapEntry));
    entry->type = STRING;

    entry->pointer = malloc(sizeof(char)*strlen(string));
    entry->name = malloc(sizeof(char)*strlen(name));

    strcpy((char*)entry->pointer, string);    
    strcpy(entry->name, name);
    
    return entry;
}

mapEntry* createIntegerEntry(const char* name, const int value)
{
    mapEntry *entry = malloc(sizeof(mapEntry));
    entry->type = INT;

    entry->pointer = malloc(sizeof(int));
    entry->name = malloc(sizeof(char)*strlen(name));
    
    *((int*)entry->pointer) = value;
    strcpy(entry->name, name);
    
    return entry;
}

mapEntry* createBooleanEntry(const char* name, const bool value)
{
    mapEntry *entry = malloc(sizeof(mapEntry));
    entry->type = BOOL;

    entry->pointer = malloc(sizeof(bool));
    entry->name = malloc(sizeof(char)*strlen(name));

    *((int*)entry->pointer) = value;
    strcpy(entry->name, name);

    return entry;
}

void printEntry(const mapEntry *entry)
{
    switch (entry->type) {
    case INT:
	printf("%s = %d", entry->name, *((int*)entry->pointer));
	break;
    case STRING:
	printf("%s = %s", entry->name, (char*)entry->pointer);
	break;
    case BOOL:
	if (*((int*)entry->pointer) != 0)
	    printf("%s = TRUE", entry->name);
	else
	    printf("%s = FALSE", entry->name);
	break;
    default: break;
    }
    printf(" - %s\n", TYPES[entry->type]);
}

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

settings *createSettings(const char* filename)
{
    
    settings *set = malloc(sizeof(settings));
    
}

extern void deleteSettings(settings* set);
static void parseIniFile(const char* filename, settings* set);

static int countSections(FILE* inifile)
{
    
}

int main(int argc, char **argv)
{
    mapEntry *entry = createStringEntry("name", "Map or map - the question is");
    mapEntry *entry1 = createIntegerEntry("width", 800);
    mapEntry *entry2 = createBooleanEntry("compiles", true);

    printEntry(entry);
    printEntry(entry1);
    printEntry(entry2);

    deleteEntry(entry);
    deleteEntry(entry1);
    deleteEntry(entry2);
    return 0;
}
