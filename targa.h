#ifndef _S_TGA
#define _S_TGA

/* Collection of utils for working with new-tga images */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---== TGA typedefs ==---*/
typedef uint8_t TGAbyte;
typedef uint16_t TGAshort;
typedef uint32_t TGAlong;
typedef uint8_t TGAASCII;

#pragma pack(1) /* No padding is needed! */
/*---== TGA Header ==---*/ /* Field numbers according to the specification */
struct STGAHeader {
    TGAbyte IDlength;      /* 1 */
    TGAbyte colorMapType;  /* 2; 0 - color map is not included, 1 - color map is included */
    TGAbyte imageType;     /* 3 */
    
    /*-= Color Map Spec - 5 bytes =-*/
    TGAshort firstEntryIndex;   /* 4.1 */
    TGAshort colorMapLength;    /* 4.2 */
    TGAbyte colorMapEntrySize;  /* 4.3 */
    
    /*-= Image Specification - 10 bytes  =-*/
    TGAshort xOrigin;           /* 5.1 */
    TGAshort yOrigin;           /* 5.2 */
    TGAshort width;             /* 5.3 */
    TGAshort height;            /* 5.4 */
    TGAbyte pixelDepth;         /* 5.5 */
    TGAbyte imageDescriptor;    /* 5.6 */
};
typedef struct STGAHeader STGAHeader;

/*---== TGA Image/Color Map Data ==---*/
struct STGAImage {
    TGAbyte *imageID;      /* 6; length - field 1 */
    TGAbyte *colorMapData; /* 7; type - field 2   */
                           /*    number of entries - filed 4.2   */
                           /*    width of each entry - filed 4.3 */
    TGAbyte *imageData;    /* 8; length = 5.3 * 5.4 pixels.      */
                           /*    number of attribute and color-definition bits for each pixel are defined in fields 5.5 and 5.6. So, byte length is 5.3 * 5.4 * 5.5 */
                           /*    each pixel is stored as an integral number of bytes */
};
typedef struct STGAImage STGAImage;
    
/*---== TGA Developer Area ==---*/
struct STGADevArea {
    TGAbyte *devData; /* 9; Size and format are totally up to developer */
                      /*    Recommended to be used only for application specific information */
    /* Developer Directory */
    TGAshort numberOfTags;
    struct STGADevTag {
	TGAshort tagNumber;
	TGAlong byteOffset;
	TGAlong fieldSize;
    } *devTags;
};
typedef struct STGADevArea STGADevArea;

/*---== TGA Extension Area ==---*/
struct STGAExtArea {
    void *pass; /* fields 10 - 27 */
    /* TODO (or not to do) */
};
typedef struct STGAExtArea STGAExtArea;

/*---== TGA Footer ==---*/
struct STGAFooter {
    /*4*/    TGAlong extAreaOffset;      /* 28; if 0, no Extnsion Area */ 
    /*4*/    TGAlong devDirectoryOffset; /* 29; if 0, no Developer Area */
    /*16*/   TGAASCII signature[16];     /* 30 */
    /*1*/    TGAASCII reservedChar;      /* 31 */
    /*1*/    TGAASCII terminator;        /* 32 */
    /*26 bytes total*/
};
typedef struct STGAFooter STGAFooter;

#pragma pack() /* was pack(1) */

/*---== TGA File ==---*/
struct STGAFile {
    STGAHeader header;
    STGAImage image;
    STGADevArea devArea;
    STGAExtArea extArea;
    STGAFooter footer;
};
typedef struct STGAFile STGAFile;

/*---== Error enumerators ==---*/
enum STGAError {
    E_SUCCESS = 0, /* No error */
    E_INVALID_FILE,
    E_INVALID_FOOTER,
    E_INVALID_HEADER,
    E_NOT_A_TGA,
    E_IMAGE_TYPE_NOT_SUPPORTED
};

static struct _STGAErrorDescription {
    int errorCode;
    char *errorMessage;
} STGAErrorDescription [] = {
    { E_SUCCESS,                  "No error"                },
    { E_INVALID_FILE,             "Cannot read file"        },
    { E_INVALID_FOOTER,           "Cannot read footer"      },
    { E_INVALID_HEADER,           "Cannot read header"      },
    { E_NOT_A_TGA,                "Given file is not a valid TGA" },
    { E_IMAGE_TYPE_NOT_SUPPORTED, "TGA Image Type is not supported" }
};

/*---== TGA Functions ==---*/

int readTgaFromFile(char *filename, STGAFile *);
char * getErrorDescription(int);

#ifdef TGA_COMPILE
static int isNotNewTga(char *filename); /* determine if given file is usable TGA file */
static int readHeader(STGAHeader *, FILE *from);
static int readFooter(STGAFooter *, FILE *from);
static int readImage(STGAFile *, FILE *from);


static void printFooter(STGAFooter *);
static void printHeader(STGAHeader *);
static TGAASCII const * printBits(TGAbyte);
#endif

#endif /* ifndef _S_TGA */
