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
typedef char TGAASCII;

/*---== TGA Header ==---*/ // Filed numbers according to the specification
struct STGAHeader {
    TGAbyte IDlength;      // 1
    TGAbyte colorMapType;  // 2. 0 - color map is not included, 1 - color map is included
    TGAbyte imageType;     // 3
    
    /*-= Color Map Spec - 5 bytes =-*/
    TGAshort firstEntryIndex;   // 4.1
    TGAshort colorMapLength;    // 4.2
    TGAbyte colorMapEntrySize;  // 4.3
    
    /*-= Image Specification - 10 bytes  =-*/
    TGAshort xOrigin;           // 5.1
    TGAshort yOrigin;           // 5.2
    TGAshort width;             // 5.3
    TGAshort height;            // 5.4
    TGAbyte pixelDepth;         // 5.5
    TGAbyte imageDescriptor;    // 5.6
};
typedef struct STGAHeader STGAHeader;

/*---== TGA Image/Color Map Data ==---*/
struct STGAImage {
    TGAbyte *imageID;      // 6; length - field 1
    TGAbyte *colorMapData; // 7; type - field 2
                           //    number of entries - filed 4.2
                           //    width of each entry - filed 4.3
    TGAbyte *imageData;    // 8; length = 5.3 * 5.4 pixels.
                           //    number of attribute and color-definition bits for each pixel are defined in fields 5.5 and 5.6. So, byte length is 5.3 * 5.4 * 5.5 / 8
                           //    each pixel is stored as an integral number of bytes
};
typedef struct STGAImage STGAImage;
    
/*---== TGA Developer Area ==---*/
struct STGADevArea {
    TGAbyte *devData; // 9; Size and format are totally up to developer
                      //    Recommended to be used only for application specific information
    // Developer Directory
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
    void *pass; // fields 10 - 27
    // TODO (or not to do)
};
typedef struct STGAExtArea STGAExtArea;

/*---== TGA Footer ==---*/
struct STGAFooter {
    /*4*/    TGAlong extAreaOffset;      // 28; if 0, no Extnsion Area
    /*4*/    TGAlong devDirectoryOffset; // 29; if 0, no Developer Area
    /*16*/    TGAASCII signature[16];         // 30
    /*1*/    TGAASCII reservedChar;      // 31
    /*1*/    TGAASCII terminator;        // 32
    /*26 bytes total*/
};
typedef struct STGAFooter STGAFooter;

/*---== TGA File ==---*/
struct STGAFile {
    STGAHeader *header;
    STGAImage *image;
    STGADevArea *devArea;
    STGAExtArea *extArea;
    STGAFooter *footer;
};
typedef struct STGAFile STGAFile;

/*---== TGA Functions ==---*/
static int isNewTga(char *filename); // determine if a file is usable TGA file

#endif /* ifndef _S_TGA */
