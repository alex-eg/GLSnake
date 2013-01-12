#include "targa.h"

static int isNewTga(char *filename)
{
    FILE *in;
    STGAFooter footer;

    if (!sizeof(STGAFooter) == 26) return 1;   // sizeof footer is not equal 26 bytes
    in = fopen(filename, "rb");
    if (!in) return 2; // cannot open file
    if (fseek(in, -26L, SEEK_END)) return 3;     // cannot FSEEK to the EOF for some reason
    fread(&footer, sizeof(STGAFooter), 1, in);
    if (memcmp("TRUEVISION-XFILE", footer.signature, 16)) return 4; // signature differs
    printf("TGA signature contains:\n%s\n", footer.signature);
    
    fclose(in);
    return 0;
}

/* Compile with -DTGA_TEST into executable to perform tests */
#ifdef TGA_TEST
int main(int argc, char **argv)
{
    if (argc == 1) {
	printf("No tga file provided for test, aborting.\n");
	return 0;
    }
    int r = isNewTga(argv[1]);
    if (r) {
	printf("Failed to recognize file, errno %d\n", r);
	return 0;
    }

    printf("File %s has a valid New TGA footer.\n", argv[1]);
    return 0;
}
#endif
