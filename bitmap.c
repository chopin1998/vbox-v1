#include "bitmap.h"




const unsigned char font_3x6[]= {
    0x00,0x00,0x00, /* Space */         
    0x00,0x5C,0x00, /* ! */                         
    0x0C,0x00,0x0C, /* " */                         
    0x7C,0x28,0x7C, /* # */                         
    0x7C,0x44,0x7C, /* 0x */                        
    0x24,0x10,0x48, /* % */                         
    0x28,0x54,0x08, /* & */                         
    0x00,0x0C,0x00, /* ' */                         
    0x38,0x44,0x00, /* ( */                         
    0x44,0x38,0x00, /* ) */                         
    0x20,0x10,0x08, /* // */                        
    0x10,0x38,0x10, /* + */                         
    0x80,0x40,0x00, /* , */                         
    0x10,0x10,0x10, /* - */                         
    0x00,0x40,0x00, /* . */                         
    0x20,0x10,0x08, /* / */    
    0x38,0x44,0x38, /* 0 */                     
    0x00,0x7C,0x00, /* 1 */                         
    0x64,0x54,0x48, /* 2 */                         
    0x44,0x54,0x28, /* 3 */                         
    0x1C,0x10,0x7C, /* 4 */                         
    0x4C,0x54,0x24, /* 5 */                         
    0x38,0x54,0x20, /* 6 */                         
    0x04,0x74,0x0C, /* 7 */                         
    0x28,0x54,0x28, /* 8 */                         
    0x08,0x54,0x38, /* 9 */                         
    0x00,0x50,0x00, /* : */                         
    0x80,0x50,0x00, /* ; */                         
    0x10,0x28,0x44, /* < */                         
    0x28,0x28,0x28, /* = */                  
    0x44,0x28,0x10, /* > */                        
    0x04,0x54,0x08, /* ? */                         
    0x38,0x4C,0x5C, /* @ */                          
    0x78,0x14,0x78, /* A */                         
    0x7C,0x54,0x28, /* B */                         
    0x38,0x44,0x44, /* C */                         
    0x7C,0x44,0x38, /* D */                         
    0x7C,0x54,0x44, /* E */                         
    0x7C,0x14,0x04, /* F */                         
    0x38,0x44,0x34, /* G */                         
    0x7C,0x10,0x7C, /* H */                         
    0x00,0x7C,0x00, /* I */                         
    0x20,0x40,0x3C, /* J */                         
    0x7C,0x10,0x6C, /* K */                         
    0x7C,0x40,0x40, /* L */                         
    0x7C,0x08,0x7C, /* M */                         
    0x7C,0x04,0x7C, /* N */                         
    0x7C,0x44,0x7C, /* O */                         
    0x7C,0x14,0x08, /* P */                 
    0x38,0x44,0x78, /* Q */                         
    0x7C,0x14,0x68, /* R */                         
    0x48,0x54,0x24, /* S */                         
    0x04,0x7C,0x04, /* T */                         
    0x7C,0x40,0x7C, /* U */                         
    0x3C,0x40,0x3C, /* V */                         
    0x7C,0x20,0x7C, /* W */                         
    0x6C,0x10,0x6C, /* X */                         
    0x1C,0x60,0x1C, /* Y */                         
    0x64,0x54,0x4C, /* Z */                         
    0x7C,0x44,0x00, /* [ */                         
    0x08,0x10,0x20, /* \ */                         
    0x44,0x7C,0x00, /* ] */                         
    0x08,0x04,0x08, /* ^ */                         
    0x80,0x80,0x80, /* _ */                         
    0x04,0x08,0x00  /* ` */                 
};

const unsigned char font_5x8[]= 
{
    0x00,0x00,0x00,0x00,0x00, /* Space */
    0x00,0x00,0x4f,0x00,0x00, /* ! */
    0x00,0x07,0x00,0x07,0x00, /* " */
    0x14,0x7f,0x14,0x7f,0x14, /* # */
    0x24,0x2a,0x7f,0x2a,0x12, /* 0x */
    0x23,0x13,0x08,0x64,0x62, /* % */
    0x36,0x49,0x55,0x22,0x20, /* & */
    0x00,0x05,0x03,0x00,0x00, /* ' */
    0x00,0x1c,0x22,0x41,0x00, /* ( */
    0x00,0x41,0x22,0x1c,0x00, /* ) */
    0x14,0x08,0x3e,0x08,0x14, /* // */
    0x08,0x08,0x3e,0x08,0x08, /* + */
    0x50,0x30,0x00,0x00,0x00, /* , */
    0x08,0x08,0x08,0x08,0x08, /* - */ 
    0x00,0x60,0x60,0x00,0x00, /* . */
    0x20,0x10,0x08,0x04,0x02, /* / */
    0x3e,0x51,0x49,0x45,0x3e, /* 0 */
    0x00,0x42,0x7f,0x40,0x00, /* 1 */
    0x42,0x61,0x51,0x49,0x46, /* 2 */
    0x21,0x41,0x45,0x4b,0x31, /* 3 */
    0x18,0x14,0x12,0x7f,0x10, /* 4 */
    0x27,0x45,0x45,0x45,0x39, /* 5 */
    0x3c,0x4a,0x49,0x49,0x30, /* 6 */
    0x01,0x71,0x09,0x05,0x03, /* 7 */
    0x36,0x49,0x49,0x49,0x36, /* 8 */
    0x06,0x49,0x49,0x29,0x1e, /* 9 */
    0x00,0x36,0x36,0x00,0x00, /* : */
    0x00,0x56,0x36,0x00,0x00, /* ; */
    0x08,0x14,0x22,0x41,0x00, /* < */
    0x14,0x14,0x14,0x14,0x14, /* = */
    0x00,0x41,0x22,0x14,0x08, /* > */
    0x02,0x01,0x51,0x09,0x06, /* ? */
    0x3e,0x41,0x5d,0x55,0x1e, /* @ */
    0x7e,0x11,0x11,0x11,0x7e, /* A */
    0x7f,0x49,0x49,0x49,0x36, /* B */
    0x3e,0x41,0x41,0x41,0x22, /* C */
    0x7f,0x41,0x41,0x22,0x1c, /* D */
    0x7f,0x49,0x49,0x49,0x41, /* E */
    0x7f,0x09,0x09,0x09,0x01, /* F */
    0x3e,0x41,0x49,0x49,0x7a, /* G */
    0x7f,0x08,0x08,0x08,0x7f, /* H */
    0x00,0x41,0x7f,0x41,0x00, /* I */
    0x20,0x40,0x41,0x3f,0x01, /* J */
    0x7f,0x08,0x14,0x22,0x41, /* K */
    0x7f,0x40,0x40,0x40,0x40, /* L */
    0x7f,0x02,0x0c,0x02,0x7f, /* M */
    0x7f,0x04,0x08,0x10,0x7f, /* N */
    0x3e,0x41,0x41,0x41,0x3e, /* O */
    0x7f,0x09,0x09,0x09,0x06, /* P */
    0x3e,0x41,0x51,0x21,0x5e, /* Q */
    0x7f,0x09,0x19,0x29,0x46, /* R */
    0x26,0x49,0x49,0x49,0x32, /* S */
    0x01,0x01,0x7f,0x01,0x01, /* T */
    0x3f,0x40,0x40,0x40,0x3f, /* U */
    0x1f,0x20,0x40,0x20,0x1f, /* V */
    0x3f,0x40,0x38,0x40,0x3f, /* W */
    0x63,0x14,0x08,0x14,0x63, /* X */
    0x07,0x08,0x70,0x08,0x07, /* Y */
    0x61,0x51,0x49,0x45,0x43, /* Z */
    0x00,0x7f,0x41,0x41,0x00, /* [ */
    0x02,0x04,0x08,0x10,0x20, /* \ */ 
    0x00,0x41,0x41,0x7f,0x00, /* ] */
    0x04,0x02,0x01,0x02,0x04, /* ^ */
    0x40,0x40,0x40,0x40,0x40, /* _ */
    0x00,0x00,0x03,0x05,0x00, /* ` */
    0x20,0x54,0x54,0x54,0x78, /* a */
    0x7F,0x44,0x44,0x44,0x38, /* b */
    0x38,0x44,0x44,0x44,0x44, /* c */
    0x38,0x44,0x44,0x44,0x7f, /* d */
    0x38,0x54,0x54,0x54,0x18, /* e */
    0x04,0x04,0x7e,0x05,0x05, /* f */
    0x08,0x54,0x54,0x54,0x3c, /* g */
    0x7f,0x08,0x04,0x04,0x78, /* h */
    0x00,0x44,0x7d,0x40,0x00, /* i */
    0x20,0x40,0x44,0x3d,0x00, /* j */
    0x7f,0x10,0x28,0x44,0x00, /* k */
    0x00,0x41,0x7f,0x40,0x00, /* l */
    0x7c,0x04,0x7c,0x04,0x78, /* m */
    0x7c,0x08,0x04,0x04,0x78, /* n */
    0x38,0x44,0x44,0x44,0x38, /* o */
    0x7c,0x14,0x14,0x14,0x08, /* p */
    0x08,0x14,0x14,0x14,0x7c, /* q */
    0x7c,0x08,0x04,0x04,0x00, /* r */
    0x48,0x54,0x54,0x54,0x24, /* s */
    0x04,0x04,0x3f,0x44,0x44, /* t */
    0x3c,0x40,0x40,0x20,0x7c, /* u */
    0x1c,0x20,0x40,0x20,0x1c, /* v */
    0x3c,0x40,0x30,0x40,0x3c, /* w */
    0x44,0x28,0x10,0x28,0x44, /* x */
    0x0c,0x50,0x50,0x50,0x3c, /* y */
    0x44,0x64,0x54,0x4c,0x44, /* z */
    0x08,0x36,0x41,0x41,0x00, /* { */
    0x00,0x00,0x77,0x00,0x00, /* | */
    0x00,0x41,0x41,0x36,0x08, /* } */
    0x08,0x08,0x2a,0x1c,0x08, /* <- */
    0x08,0x1c,0x2a,0x08,0x08, /* -> */
    0xff,0xff,0xff,0xff,0xff, /*  */
};


const unsigned char font_7x8[]= 
{
     0,   0,   0,   0,   0,   0,   0, //' '
     0,   6,  95,  95,   6,   0,   0, //'!'
     0,   7,   7,   0,   7,   7,   0, //'"'
    20, 127, 127,  20, 127, 127,  20, //'#'
    36,  46, 107, 107,  58,  18,   0, //'$'
    70, 102,  48,  24,  12, 102,  98, //'%'
    48, 122,  79,  93,  55, 122,  72, //'&'
     4,   7,   3,   0,   0,   0,   0, //'''
     0,  28,  62,  99,  65,   0,   0, //'('
     0,  65,  99,  62,  28,   0,   0, //')'
     8,  42,  62,  28,  28,  62,  42, //'*'
     8,   8,  62,  62,   8,   8,   0, //'+'
     0, 128, 224,  96,   0,   0,   0, //','
     8,   8,   8,   8,   8,   8,   0, //'-'
     0,   0,  96,  96,   0,   0,   0, //'.'
    96,  48,  24,  12,   6,   3,   1, //'/'
    62, 127, 113,  89,  77, 127,  62, //'0'
    64,  66, 127, 127,  64,  64,   0, //'1'
    98, 115,  89,  73, 111, 102,   0, //'2'
    34,  99,  73,  73, 127,  54,   0, //'3'
    24,  28,  22,  83, 127, 127,  80, //'4'
    39, 103,  69,  69, 125,  57,   0, //'5'
    60, 126,  75,  73, 121,  48,   0, //'6'
     3,   3, 113, 121,  15,   7,   0, //'7'
    54, 127,  73,  73, 127,  54,   0, //'8'
     6,  79,  73, 105,  63,  30,   0, //'9'
     0,   0, 102, 102,   0,   0,   0, //':'
     0, 128, 230, 102,   0,   0,   0, //';'
     8,  28,  54,  99,  65,   0,   0, //'<'
    36,  36,  36,  36,  36,  36,   0, //'='
     0,  65,  99,  54,  28,   8,   0, //'>'
     2,   3,  81,  89,  15,   6,   0, //'?'
    62, 127,  65,  93,  93,  31,  30, //'@'
    124,126,  19,  19, 126, 124,   0, //'A'
    65, 127, 127,  73,  73, 127,  54, //'B'
    28,  62,  99,  65,  65,  99,  34, //'C'
    65, 127, 127,  65,  99,  62,  28, //'D'
    65, 127, 127,  73,  93,  65,  99, //'E'
    65, 127, 127,  73,  29,   1,   3, //'F'
    28,  62,  99,  65,  81, 115, 114, //'G'
    127,127,   8,   8, 127, 127,   0, //'H'
     0,  65, 127, 127,  65,   0,   0, //'I'
    48, 112,  64,  65, 127,  63,   1, //'J'
    65, 127, 127,   8,  28, 119,  99, //'K'
    65, 127, 127,  65,  64,  96, 112, //'L'
    127,127,  14,  28,  14, 127, 127, //'M'
    127,127,   6,  12,  24, 127, 127, //'N'
    28,  62,  99,  65,  99,  62,  28, //'O'
    65, 127, 127,  73,   9,  15,   6, //'P'
    30,  63,  33, 113, 127,  94,   0, //'Q'
    65, 127, 127,   9,  25, 127, 102, //'R'
    38, 111,  77,  89, 115,  50,   0, //'S'
     3,  65, 127, 127,  65,   3,   0, //'T'
    127,127,  64,  64, 127, 127,   0, //'U'
    31,  63,  96,  96,  63,  31,   0, //'V'
    127,127,  48,  24,  48, 127, 127, //'W'
    67, 103,  60,  24,  60, 103,  67, //'X'
     7,  79, 120, 120,  79,   7,   0, //'Y'
    71,  99, 113,  89,  77, 103, 115, //'Z'
     0, 127, 127,  65,  65,   0,   0, //'['
     1,   3,   6,  12,  24,  48,  96, //'\'
     0,  65,  65, 127, 127,   0,   0, //']'
     8,  12,   6,   3,   6,  12,   8, //'^'
    128,128, 128, 128, 128, 128, 128, //'_'
     0,   0,   3,   7,   4,   0,   0, //'`'
    32, 116,  84,  84,  60, 120,  64, //'a'
    65, 127,  63,  72,  72, 120,  48, //'b'
    56, 124,  68,  68, 108,  40,   0, //'c'
    48, 120,  72,  73,  63, 127,  64, //'d'
    56, 124,  84,  84,  92,  24,   0, //'e'
    72, 126, 127,  73,   3,   2,   0, //'f'
    56, 188, 164, 164, 252, 120,   0, //'g'
    65, 127, 127,   8,   4, 124, 120, //'h'
     0,  68, 125, 125,  64,   0,   0, //'i'
    96, 224, 128, 128, 253, 125,   0, //'j'
    65, 127, 127,  16,  56, 108,  68, //'k'
     0,  65, 127, 127,  64,   0,   0, //'l'
    120,124,  28,  56,  28, 124, 120, //'m'
    124,124,   4,   4, 124, 120,   0, //'n'
    56, 124,  68,  68, 124,  56,   0, //'o'
    0,  252, 252, 164,  36,  60,  24, //'p'
    24,  60,  36, 164, 248, 252, 132, //'q'
    68, 124, 120,  76,   4,  28,  24, //'r'
    72,  92,  84,  84, 116,  36,   0, //'s'
     0,   4,  62, 127,  68,  36,   0, //'t'
    60, 124,  64,  64,  60, 124,  64, //'u'
    28,  60,  96,  96,  60,  28,   0, //'v'
    60, 124, 112,  56, 112, 124,  60, //'w'
    68, 108,  56,  16,  56, 108,  68, //'x'
    60, 188, 160, 160, 252, 124,   0, //'y'
    76, 100, 116,  92,  76, 100,   0, //'z'
     8,   8,  62, 119,  65,  65,   0, //'{'
     0,   0,   0, 119, 119,   0,   0, //'|'
    65,  65, 119,  62,   8,   8,   0, //'}'
     2,   3,   1,   3,   2,   3,   1, //'~'
    255,129, 129, 129, 129, 129, 255, //''
    14, 159, 145, 177, 251,  74,   0 //'�'
};
  

const unsigned char font_8x8[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,       // ASCII -  32
    0x00,0x00,0x00,0x5F,0x5F,0x00,0x00,0x00,       // ASCII -  33
    0x00,0x00,0x03,0x07,0x00,0x07,0x03,0x00,       // ASCII -  34
    0x00,0x10,0x74,0x1C,0x77,0x1C,0x17,0x04,       // ASCII -  35
    0x00,0x24,0x2E,0x2A,0x7F,0x2A,0x3A,0x10,       // ASCII -  36
    0x00,0x4C,0x6A,0x76,0x1A,0x6A,0x56,0x33,       // ASCII -  37
    0x00,0x30,0x7A,0x4F,0x5D,0x37,0x7A,0x48,       // ASCII -  38
    0x00,0x00,0x04,0x07,0x03,0x00,0x00,0x00,       // ASCII -  39
    0x00,0x00,0x00,0x1C,0x3E,0x63,0x41,0x00,       // ASCII -  40
    0x00,0x00,0x41,0x63,0x3E,0x1C,0x00,0x00,       // ASCII -  41
    0x00,0x08,0x2A,0x3E,0x1C,0x3E,0x2A,0x08,       // ASCII -  42
    0x00,0x08,0x08,0x3E,0x3E,0x08,0x08,0x00,       // ASCII -  43
    0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00,       // ASCII -  44
    0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00,       // ASCII -  45
    0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00,       // ASCII -  46
    0x00,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,       // ASCII -  47
    0x00,0x1C,0x3E,0x61,0x43,0x3E,0x1C,0x00,       // ASCII -  48
    0x00,0x00,0x44,0x7F,0x7F,0x40,0x00,0x00,       // ASCII -  49
    0x00,0x46,0x67,0x71,0x59,0x4F,0x66,0x00,       // ASCII -  50
    0x00,0x22,0x63,0x49,0x4D,0x7F,0x32,0x00,       // ASCII -  51
    0x00,0x18,0x1C,0x52,0x7F,0x7F,0x50,0x00,       // ASCII -  52
    0x00,0x2F,0x6F,0x45,0x45,0x7D,0x39,0x00,       // ASCII -  53
    0x00,0x3C,0x7E,0x4B,0x49,0x79,0x30,0x00,       // ASCII -  54
    0x00,0x07,0x43,0x71,0x7D,0x0F,0x03,0x00,       // ASCII -  55
    0x00,0x36,0x7F,0x4D,0x59,0x7F,0x36,0x00,       // ASCII -  56
    0x00,0x06,0x4F,0x49,0x69,0x3F,0x1E,0x00,       // ASCII -  57
    0x00,0x00,0x00,0x66,0x66,0x00,0x00,0x00,       // ASCII -  58
    0x00,0x00,0x00,0x66,0x66,0x00,0x00,0x00,       // ASCII -  59
    0x00,0x00,0x08,0x1C,0x36,0x63,0x41,0x00,       // ASCII -  60
    0x00,0x14,0x14,0x14,0x14,0x14,0x14,0x00,       // ASCII -  61
    0x00,0x00,0x41,0x63,0x36,0x1C,0x08,0x00,       // ASCII -  62
    0x00,0x02,0x07,0x51,0x59,0x0F,0x06,0x00,       // ASCII -  63
    0x00,0x3E,0x41,0x5D,0x55,0x5D,0x51,0x1E,       // ASCII -  64
    0x00,0x40,0x70,0x1D,0x17,0x1F,0x78,0x60,       // ASCII -  65
    0x00,0x41,0x7F,0x7F,0x49,0x4F,0x7E,0x30,       // ASCII -  66
    0x00,0x1C,0x3E,0x63,0x41,0x41,0x42,0x27,       // ASCII -  67
    0x00,0x41,0x7F,0x7F,0x41,0x63,0x3E,0x1C,       // ASCII -  68
    0x00,0x41,0x7F,0x7F,0x49,0x5D,0x41,0x63,       // ASCII -  69
    0x00,0x41,0x7F,0x7F,0x49,0x1D,0x01,0x03,       // ASCII -  70
    0x00,0x1C,0x3E,0x63,0x41,0x51,0x72,0x77,       // ASCII -  71
    0x00,0x7F,0x7F,0x08,0x08,0x7F,0x7F,0x00,       // ASCII -  72
    0x00,0x00,0x41,0x7F,0x7F,0x41,0x00,0x00,       // ASCII -  73
    0x00,0x30,0x70,0x41,0x41,0x7F,0x3F,0x01,       // ASCII -  74
    0x00,0x7F,0x7F,0x08,0x1C,0x77,0x63,0x41,       // ASCII -  75
    0x00,0x41,0x7F,0x7F,0x41,0x40,0x60,0x70,       // ASCII -  76
    0x00,0x7F,0x7E,0x0C,0x18,0x0C,0x7E,0x7F,       // ASCII -  77
    0x00,0x7F,0x7E,0x0C,0x18,0x30,0x7F,0x7F,       // ASCII -  78
    0x00,0x1C,0x3E,0x63,0x41,0x63,0x3E,0x1C,       // ASCII -  79
    0x00,0x41,0x7F,0x7F,0x49,0x09,0x0F,0x06,       // ASCII -  80
    0x00,0x1C,0x3E,0x63,0x51,0x63,0x3E,0x1C,       // ASCII -  81
    0x00,0x7F,0x7F,0x09,0x19,0x7F,0x66,0x40,       // ASCII -  82
    0x00,0x66,0x6F,0x4D,0x59,0x7B,0x33,0x00,       // ASCII -  83
    0x00,0x03,0x41,0x7F,0x7F,0x41,0x03,0x00,       // ASCII -  84
    0x00,0x3F,0x7F,0x40,0x40,0x40,0x7F,0x3F,       // ASCII -  85
    0x00,0x03,0x0F,0x3D,0x70,0x1D,0x07,0x01,       // ASCII -  86
    0x00,0x0F,0x7F,0x30,0x1C,0x30,0x7F,0x0F,       // ASCII -  87
    0x00,0x63,0x77,0x1C,0x1C,0x77,0x63,0x00,       // ASCII -  88
    0x01,0x03,0x47,0x7C,0x78,0x47,0x03,0x01,       // ASCII -  89
    0x00,0x67,0x73,0x59,0x4D,0x67,0x73,0x00,       // ASCII -  90
    0x00,0x00,0x00,0x7F,0x7F,0x41,0x41,0x00,       // ASCII -  91
    0x00,0x01,0x03,0x06,0x0C,0x18,0x30,0x60,       // ASCII -  92
    0x00,0x00,0x41,0x41,0x7F,0x7F,0x00,0x00,       // ASCII -  93
    0x00,0x00,0x04,0x06,0x03,0x06,0x04,0x00,       // ASCII -  94
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,       // ASCII -  95
    0x00,0x00,0x01,0x03,0x06,0x04,0x00,0x00,       // ASCII -  96
    0x00,0x68,0x6C,0x54,0x54,0x3C,0x78,0x40,       // ASCII -  97
    0x00,0x41,0x7F,0x3F,0x6C,0x44,0x7C,0x38,       // ASCII -  98
    0x00,0x38,0x7C,0x44,0x44,0x6C,0x2C,0x00,       // ASCII -  99
    0x00,0x38,0x7C,0x44,0x49,0x3F,0x7F,0x40,       // ASCII - 100
    0x00,0x38,0x7C,0x54,0x54,0x5C,0x58,0x00,       // ASCII - 101
    0x00,0x00,0x48,0x7E,0x7F,0x49,0x0B,0x02,       // ASCII - 102
    0x00,0x48,0x7C,0x34,0x34,0x2C,0x68,0x44,       // ASCII - 103
    0x00,0x41,0x7F,0x7F,0x08,0x04,0x7C,0x78,       // ASCII - 104
    0x00,0x00,0x44,0x7D,0x7D,0x40,0x00,0x00,       // ASCII - 105
    0x00,0x60,0x60,0x04,0x7D,0x7D,0x00,0x00,       // ASCII - 106
    0x00,0x41,0x7F,0x7F,0x10,0x78,0x6C,0x44,       // ASCII - 107
    0x00,0x00,0x41,0x7F,0x7F,0x40,0x00,0x00,       // ASCII - 108
    0x00,0x7C,0x7C,0x0C,0x78,0x0C,0x7C,0x78,       // ASCII - 109
    0x00,0x44,0x7C,0x7C,0x08,0x04,0x7C,0x78,       // ASCII - 110
    0x00,0x38,0x7C,0x44,0x44,0x7C,0x38,0x00,       // ASCII - 111
    0x00,0x04,0x7C,0x78,0x24,0x24,0x3C,0x18,       // ASCII - 112
    0x00,0x18,0x3C,0x24,0x24,0x78,0x7C,0x00,       // ASCII - 113
    0x00,0x44,0x7C,0x78,0x4C,0x04,0x1C,0x18,       // ASCII - 114
    0x00,0x48,0x5C,0x5C,0x74,0x74,0x24,0x00,       // ASCII - 115
    0x00,0x00,0x04,0x3E,0x7F,0x44,0x24,0x00,       // ASCII - 116
    0x00,0x3C,0x7C,0x40,0x40,0x3C,0x7C,0x40,       // ASCII - 117
    0x00,0x04,0x1C,0x3C,0x60,0x30,0x1C,0x04,       // ASCII - 118
    0x00,0x1C,0x7C,0x30,0x1C,0x30,0x7C,0x1C,       // ASCII - 119
    0x00,0x44,0x6C,0x3C,0x10,0x78,0x6C,0x44,       // ASCII - 120
    0x00,0x44,0x4C,0x1C,0x70,0x64,0x1C,0x0C,       // ASCII - 121
    0x00,0x4C,0x64,0x74,0x5C,0x4C,0x64,0x00,       // ASCII - 122
    0x00,0x08,0x08,0x3E,0x77,0x41,0x41,0x00,       // ASCII - 123
    0x00,0x00,0x00,0x7F,0x7F,0x00,0x00,0x00,       // ASCII - 124
    0x00,0x41,0x41,0x77,0x3E,0x08,0x08,0x00,       // ASCII - 125
    0x00,0x02,0x01,0x01,0x03,0x02,0x02,0x01,       // ASCII - 126
    0x00,0x60,0x78,0x4E,0x47,0x5E,0x78,0x60,       // ASCII - 127
    0x00,0x1C,0x3E,0x23,0x41,0x41,0x42,0x27,       // ASCII - 128
    0x00,0x3D,0x7D,0x40,0x41,0x3D,0x7C,0x40,       // ASCII - 129
};

const unsigned char font_8x8thin[]= {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x5F,0x00,0x00,0x00,0x00,
    0x00,0x00,0x07,0x00,0x00,0x07,0x00,0x00,
    0x00,0x14,0x7F,0x14,0x14,0x7F,0x14,0x00,
    0x00,0x24,0x2A,0x6B,0x6B,0x2A,0x12,0x00,
    0x00,0x46,0x26,0x10,0x08,0x64,0x62,0x00,
    0x30,0x4A,0x45,0x4D,0x32,0x48,0x48,0x00,
    0x00,0x00,0x04,0x03,0x00,0x00,0x00,0x00,
    0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00,
    0x00,0x00,0x41,0x22,0x1C,0x00,0x00,0x00,
    0x08,0x2A,0x1C,0x1C,0x1C,0x2A,0x08,0x00,
    0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00,
    0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,
    0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00,
    0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,
    0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x00,
    0x00,0x3E,0x61,0x51,0x49,0x45,0x3E,0x00,
    0x00,0x44,0x42,0x7F,0x40,0x40,0x00,0x00,
    0x00,0x62,0x51,0x51,0x49,0x49,0x66,0x00,
    0x00,0x22,0x41,0x49,0x49,0x49,0x36,0x00,
    0x10,0x18,0x14,0x52,0x7F,0x50,0x10,0x00,
    0x00,0x27,0x45,0x45,0x45,0x45,0x39,0x00,
    0x00,0x3C,0x4A,0x49,0x49,0x49,0x30,0x00,
    0x00,0x03,0x01,0x71,0x09,0x05,0x03,0x00,
    0x00,0x36,0x49,0x49,0x49,0x49,0x36,0x00,
    0x00,0x06,0x49,0x49,0x49,0x29,0x1E,0x00,
    0x00,0x00,0x00,0x66,0x00,0x00,0x00,0x00,
    0x00,0x00,0x80,0x66,0x00,0x00,0x00,0x00,
    0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00,
    0x00,0x24,0x24,0x24,0x24,0x24,0x24,0x00,
    0x00,0x00,0x00,0x41,0x22,0x14,0x08,0x00,
    0x00,0x02,0x01,0x01,0x51,0x09,0x06,0x00,
    0x00,0x3E,0x41,0x5D,0x55,0x55,0x1E,0x00,
    0x00,0x7C,0x12,0x11,0x11,0x12,0x7C,0x00,
    0x00,0x41,0x7F,0x49,0x49,0x49,0x36,0x00,
    0x00,0x1C,0x22,0x41,0x41,0x41,0x22,0x00,
    0x00,0x41,0x7F,0x41,0x41,0x22,0x1C,0x00,
    0x00,0x41,0x7F,0x49,0x5D,0x41,0x63,0x00,
    0x00,0x41,0x7F,0x49,0x1D,0x01,0x03,0x00,
    0x00,0x1C,0x22,0x41,0x51,0x51,0x72,0x00,
    0x00,0x7F,0x08,0x08,0x08,0x08,0x7F,0x00,
    0x00,0x00,0x41,0x7F,0x41,0x00,0x00,0x00,
    0x00,0x30,0x40,0x40,0x41,0x3F,0x01,0x00,
    0x00,0x41,0x7F,0x08,0x14,0x22,0x41,0x40,
    0x00,0x41,0x7F,0x41,0x40,0x40,0x60,0x00,
    0x00,0x7F,0x01,0x02,0x04,0x02,0x01,0x7F,
    0x00,0x7F,0x01,0x02,0x04,0x08,0x7F,0x00,
    0x00,0x3E,0x41,0x41,0x41,0x41,0x3E,0x00,
    0x00,0x41,0x7F,0x49,0x09,0x09,0x06,0x00,
    0x00,0x1E,0x21,0x21,0x31,0x21,0x5E,0x40,
    0x00,0x41,0x7F,0x49,0x19,0x29,0x46,0x00,
    0x00,0x26,0x49,0x49,0x49,0x49,0x32,0x00,
    0x00,0x03,0x01,0x41,0x7F,0x41,0x01,0x03,
    0x00,0x3F,0x40,0x40,0x40,0x40,0x3F,0x00,
    0x00,0x0F,0x10,0x20,0x40,0x20,0x10,0x0F,
    0x00,0x3F,0x40,0x40,0x38,0x40,0x40,0x3F,
    0x00,0x41,0x22,0x14,0x08,0x14,0x22,0x41,
    0x00,0x01,0x02,0x44,0x78,0x44,0x02,0x01,
    0x00,0x43,0x61,0x51,0x49,0x45,0x43,0x61,
    0x00,0x7F,0x41,0x41,0x41,0x00,0x00,0x00,
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x00,
    0x00,0x41,0x41,0x41,0x7F,0x00,0x00,0x00,
    0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x00,
    0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
    0x00,0x00,0x00,0x03,0x04,0x00,0x00,0x00,
    0x00,0x20,0x54,0x54,0x54,0x54,0x78,0x40,
    0x00,0x01,0x7F,0x30,0x48,0x48,0x48,0x30,
    0x00,0x38,0x44,0x44,0x44,0x44,0x28,0x00,
    0x00,0x30,0x48,0x48,0x48,0x31,0x7F,0x40,
    0x00,0x38,0x54,0x54,0x54,0x54,0x18,0x00,
    0x00,0x00,0x48,0x7E,0x49,0x01,0x02,0x00,
    0x00,0x98,0xA4,0xA4,0xA4,0xA4,0x78,0x04,
    0x00,0x41,0x7F,0x08,0x04,0x04,0x78,0x00,
    0x00,0x00,0x44,0x7D,0x40,0x00,0x00,0x00,
    0x00,0x60,0x80,0x80,0x80,0x84,0x7D,0x00,
    0x00,0x01,0x7F,0x10,0x28,0x44,0x40,0x00,
    0x00,0x00,0x41,0x7F,0x40,0x00,0x00,0x00,
    0x00,0x7C,0x04,0x04,0x78,0x04,0x04,0x78,
    0x00,0x7C,0x08,0x04,0x04,0x04,0x78,0x00,
    0x00,0x38,0x44,0x44,0x44,0x44,0x38,0x00,
    0x00,0x84,0xFC,0x98,0x24,0x24,0x18,0x00,
    0x00,0x18,0x24,0x24,0x98,0xFC,0x84,0x00,
    0x00,0x44,0x7C,0x48,0x04,0x04,0x18,0x00,
    0x00,0x48,0x54,0x54,0x54,0x54,0x24,0x00,
    0x00,0x04,0x04,0x3F,0x44,0x44,0x20,0x00,
    0x00,0x3C,0x40,0x40,0x40,0x20,0x7C,0x00,
    0x00,0x0C,0x10,0x20,0x40,0x20,0x10,0x0C,
    0x00,0x3C,0x40,0x40,0x38,0x40,0x40,0x3C,
    0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00,
    0x00,0x9C,0xA0,0xA0,0xA0,0xA0,0x7C,0x00,
    0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00,
    0x00,0x08,0x08,0x36,0x41,0x41,0x00,0x00,
    0x00,0x00,0x00,0x77,0x00,0x00,0x00,0x00,
    0x00,0x00,0x41,0x41,0x36,0x08,0x08,0x00,
    0x00,0x02,0x01,0x01,0x02,0x02,0x01,0x00,
    0x00,0x70,0x48,0x44,0x42,0x44,0x48,0x70,
    0x00,0x0E,0x91,0x91,0xB1,0xB1,0x4A,0x00,
    0x00,0x3A,0x40,0x40,0x40,0x7A,0x40,0x00,
    0x00,0x38,0x54,0x54,0x55,0x55,0x18,0x00,
    0x00,0x22,0x55,0x55,0x55,0x79,0x42,0x00,
    0x00,0x21,0x54,0x54,0x54,0x78,0x41,0x00,
    0x00,0x20,0x55,0x55,0x54,0x78,0x40,0x00,
    0x00,0x20,0x54,0x55,0x54,0x78,0x40,0x00,
    0x00,0x18,0x24,0xA4,0xA4,0xE4,0x40,0x00,
    0x00,0x3A,0x55,0x55,0x55,0x55,0x1A,0x00,
    0x00,0x39,0x54,0x54,0x54,0x54,0x19,0x00,
    0x00,0x38,0x55,0x55,0x54,0x54,0x18,0x00,
    0x00,0x00,0x01,0x44,0x7C,0x41,0x00,0x00,
    0x02,0x01,0x45,0x7D,0x41,0x01,0x02,0x00,
    0x00,0x00,0x01,0x45,0x7C,0x40,0x00,0x00,
    0x00,0x79,0x14,0x12,0x12,0x14,0x79,0x00,
    0x00,0x70,0x28,0x2B,0x2B,0x28,0x70,0x00,
    0x00,0x44,0x7C,0x54,0x55,0x45,0x00,0x00,
    0x00,0x20,0x54,0x54,0x58,0x38,0x54,0x54,
    0x00,0x7C,0x0A,0x09,0x09,0x7F,0x49,0x49,
    0x00,0x30,0x4A,0x49,0x49,0x4A,0x30,0x00,
    0x00,0x32,0x48,0x48,0x48,0x48,0x32,0x00,
    0x00,0x30,0x49,0x4A,0x48,0x48,0x30,0x00,
    0x00,0x38,0x42,0x41,0x41,0x42,0x38,0x00,
    0x00,0x38,0x41,0x42,0x40,0x40,0x38,0x00,
    0x00,0x1A,0xA0,0xA0,0xA0,0xA0,0x7A,0x00,
    0x00,0x19,0x24,0x42,0x42,0x24,0x19,0x00,
    0x00,0x3D,0x40,0x40,0x40,0x40,0x3D,0x00,
    0x00,0x18,0x24,0x24,0xE7,0x24,0x24,0x00,
    0x00,0x68,0x5E,0x49,0x41,0x42,0x20,0x00,
    0x00,0x15,0x16,0x7C,0x16,0x15,0x00,0x00,
    0x81,0xFF,0x85,0x05,0x17,0xFA,0x90,0x50,
    0x40,0x88,0x88,0x7F,0x09,0x09,0x02,0x00,
    0x00,0x20,0x54,0x54,0x55,0x79,0x40,0x00,
};

const BM_t BM_FONT_3x6 = { 3, 6, font_3x6 };
const BM_t BM_FONT_5x8 = { 5, 8, font_5x8 };
const BM_t BM_FONT_7x8 = { 7, 8, font_7x8 };
const BM_t BM_FONT_8x8 = { 8, 8, font_8x8 };
const BM_t BM_FONT_8x8THIN = { 8, 8, font_8x8thin };
