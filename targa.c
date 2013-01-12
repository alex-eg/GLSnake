#include "targa.h"

int isNewTga(char *filename)
{
    FILE *in;
    STGAFooter footer;

    if (!(in = fopen(filename, "rb"))) return E_INVALID_FILE;
    if (fseek(in, -sizeof(STGAFooter), SEEK_END)) return E_INVALID_FILE;
    if (readFooter(&footer, in)) return E_INVALID_FOOTER;
    if (memcmp("TRUEVISION-XFILE", footer.signature, sizeof(TGAbyte)*16)) return E_NOT_A_TGA;
    
    fclose(in);
    return 0;
}

char * getErrorDescription(int errorCode)
{
    return STGAErrorDescription[errorCode].errorMessage;
}

static int readFooter(STGAFooter *footer, FILE *from)
{
    if (fread(footer, sizeof(STGAFooter), 1, from) != 1) return 1;
    printFooter(footer);
    return 0;
}

static int readHeader(STGAHeader *header, FILE *from)
{
    rewind(from);
    if (fread(header, sizeof(STGAHeader), 1, from) != 1) return 1;
    return 0;
}

void printFooter(STGAFooter *footer)
{
    printf("28: %d\n", footer->extAreaOffset);
    printf("29: %d\n", footer->devDirectoryOffset);
    printf("30: %s\n", footer->signature);
    printf("31: %c\n", footer->reservedChar);
    printf("32: $(%d)\n", footer->terminator);
}

/* Compile with -DTGA_TEST into executable to perform tests */
#ifdef TGA_TEST
int main(int argc, char **argv)
{
    int result;
    if (argc == 1) {
	printf("No tga file provided for test, aborting.\n");
	return 0;
    }
    if (result = isNewTga(argv[1])) {
	printf("Failed to recognize file, error: %s\n", getErrorDescription(result));
	return 0;
    }

    printf("File %s has a valid New TGA footer\n", argv[1]);
    return 0;
}
#endif
