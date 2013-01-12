#include "targa.h"

char * getErrorDescription(int errorCode)
{
    return STGAErrorDescription[errorCode].errorMessage;
}

int readTgaFromFile(char *filename, STGAFile *file)
{
    FILE *in;
    if (isNotNewTga(filename)) return E_NOT_A_TGA;
    if (!(in = fopen(filename, "rb"))) return E_INVALID_FILE;
    if (readFooter(&file->footer, in)) return E_INVALID_FOOTER;
    if (readHeader(&file->header, in)) return E_INVALID_HEADER;
    if (readImage(file, in)) return E_IMAGE_TYPE_NOT_SUPPORTED;

    return E_SUCCESS;
}

static int isNotNewTga(char *filename)
{
    FILE *in;
    STGAFooter footer;

    int error;

    if (!(in = fopen(filename, "rb"))) return E_INVALID_FILE;
    if (error = readFooter(&footer, in)) return error;
    if (memcmp("TRUEVISION-XFILE", footer.signature, sizeof(TGAbyte)*16)) return E_NOT_A_TGA;
    
    fclose(in);
    return E_SUCCESS;
}

static int readFooter(STGAFooter *footer, FILE *from)
{
    if (fseek(from, -sizeof(STGAFooter), SEEK_END)) return E_INVALID_FILE;
    if (fread(footer, sizeof(STGAFooter), 1, from) != 1) return E_INVALID_FOOTER;
    return E_SUCCESS;
}

static int readHeader(STGAHeader *header, FILE *from)
{
    rewind(from);
    if (fread(header, sizeof(STGAHeader), 1, from) != 1) return E_INVALID_HEADER;
    return E_SUCCESS;
}

static int readImage(STGAFile *file, FILE *from)
{
    STGAHeader *header = &file->header;
    STGAImage *image = &file->image;
    if (fseek(from, sizeof(STGAHeader), SEEK_SET)) return E_INVALID_FILE;
    if (header->imageType != 2) return E_IMAGE_TYPE_NOT_SUPPORTED;
    TGAshort w = header->width, h = header->height;
    TGAbyte bpp = header->pixelDepth;
    image->imageData = malloc(w * h * bpp * sizeof(TGAbyte));
    fread(image->imageData, w * h * bpp * sizeof(TGAbyte), 1, from);
    image->imageID = image->colorMapData = image->imageData;
    return E_SUCCESS;
}

static TGAASCII const * printBits(TGAbyte num)
{
    static TGAASCII res[11];
    TGAASCII stride = 128;
    res[0] = '\0';
    for (int i = 0; i < 10; i++) {
	if (i == 2 || i == 4) {
	    strcat(res, " ");
	    continue;
	}
	strcat(res, ((num & stride) == stride) ? "1" : "0");
	stride >>= 1;
    }
    return res;
}

static void printFooter(STGAFooter *footer)
{
    printf(" 28 Extension Area Offset:\t%d\n", footer->extAreaOffset);
    printf(" 29 Developer Directory Offset: %d\n", footer->devDirectoryOffset);
    char buf[17];
    memcpy(buf, footer->signature, 16);
    buf[16] = '\0';
    printf(" 30 Signature:\t\t\t%s\n", buf);
    printf(" 31 Reserved Character:\t\t%c\n", footer->reservedChar);
    printf(" 32 Null terminator:\t\t$(%d)\n", footer->terminator);
}

static void printHeader(STGAHeader *header)
{
    printf("  1 ID Length:\t\t\t%d\n", header->IDlength);
    printf("  2 Color Map Type:\t\t%d\n", header->colorMapType);
    printf("  3 Image Type:\t\t\t%d\n", header->imageType);

    printf("---=== 4. Color Map Specification ===---\n");
    printf("4.1 First Entry Index:\t\t%d\n", header->firstEntryIndex);
    printf("4.2 Color Map Length:\t\t%d\n", header->colorMapLength);
    printf("4.3 Color Map Entry Size:\t%d\n", header->colorMapEntrySize);

    printf("---===   5. Image Specification   ===---\n");
    printf("5.1 X Origin:\t\t\t%d\n", header->xOrigin);
    printf("5.2 Y Origin:\t\t\t%d\n", header->yOrigin);
    printf("5.3 Width:\t\t\t%d\n", header->width);
    printf("5.4 Height:\t\t\t%d\n", header->height);
    printf("5.5 Pixel Color Depth:\t\t%d\n", header->pixelDepth);
    printf("5.6 Image Descriptor:\t\t%s\n", printBits(header->imageDescriptor));
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
    if (result = isNotNewTga(argv[1])) {
	printf("Failed to recognize file, error: %s\n", getErrorDescription(result));
	return 0;
    }

    printf("File %s has a valid New TGA footer\n", argv[1]);

    STGAFooter f;
    STGAHeader h;
    
    FILE *in;
    in = fopen(argv[1], "rb");
    
    readHeader(&h, in);
    readFooter(&f, in);
    
    printHeader(&h);
    printf("<....>\n");
    printFooter(&f);
    return 0;
}
#endif
