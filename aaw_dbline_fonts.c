#include "aaw_dbline_fonts.h"

/*
 * "Grid-line" (vertical/horizontal lines only) fonts for ASCII Art Writer
 *
 * File:    aaw_dbline_fonts.c
 * Author:  Vaclav [WENDYN] Nemec
 * Version: 1.0
 */

char AAW_DBLINE_OVERLAY(char a, char b)
{
    char i, found = 0;
    char directions[] = {   //WENS - WEST, EAST, NORTH, SOUTH (inverted)
        '\xCE',             //0000
        '\xCA',             //0001
        '\xCB',             //0010
        '\xCD',             //0011
        '\xB9',             //0100
        '\xBC',             //0101
        '\xBB',             //0110
        '\xFF',             //place-holder
        '\xCC',             //1000
        '\xC8',             //1001
        '\xC9',             //1010
        '\xFF',             //place-holder
        '\xBA',             //1100

        '\x20',             //1101
        '\x00',             //1110
    };

    //adding them together (bitwise)
    for(i = 0; i <= 0b00001110 && found != 0b00000011; i++)
    {
        if(a == directions[i])
        {
            a = i;
            found |= 0b00000001;
        }
        if(b == directions[i])
        {
            b = i;
            found |= 0b00000010;
        }
    }

    if(found != 0b00000011)  //not found
    {
        return '\x20';
    }
    else if(a > 0b00001100)
    {
        if(b <= 0b00001110)
        {
            return directions[b];
        }
        else if(a == 0b00001101 || b == 0b00001101)
        {
            return '\x20';
        }
        else
        {
            return '\x00';
        }
    }
    else if(b > 0b00001100)
    {
        return directions[a];
    }

    return directions[a & b];
}

const ASCIISprite AAW_FONT_3_SPRITES[] = {

    {
        2, 3,
        "\x00\x00"
        "\x00\x00"
        "\x00\x00"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xBA\xCB\xBA"
        "\xC8\xCA\xBC"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xBA\x20\xB9"
        "\xC8\xCD\xBC"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xBA\xCC\xB9"
        "\xC8\xCD\xBC"
    },

    {
        3, 3,
        "\x00\xC9\xBB"
        "\xC9\xBC\xBA"
        "\xC8\xCD\xBC"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xBA\xCA\xB9"
        "\xC8\xCD\xBC"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xBA\xCD\xB9"
        "\xC8\xBC\x00"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xBA\xC9\xB9"
        "\xC8\xCD\xBC"
    },

    {
        3, 3,
        "\xC9\xCB\xBB"
        "\xBA\xCD\xBA"
        "\xC8\xCA\xBC"
    },

    {
        2, 3,
        "\xC9\xBB"
        "\xBA\xBA"
        "\xC8\xBC"
    },

    {
        3, 3,
        "\x00\xC9\xBB"
        "\xC9\xB9\xBA"
        "\xC8\xCD\xBC"
    },

    {
        3, 3,
        "\xC9\xCB\xBB"
        "\xBA\x20\xB9"
        "\xC8\xCA\xBC"
    },

    {
        3, 3,
        "\xC9\xBB\x00"
        "\xBA\xC8\xBB"
        "\xC8\xCD\xBC"
    },

    {
        4, 3,
        "\xC9\xCD\xCD\xBB"
        "\xBA\xBA\xBA\xBA"
        "\xC8\xCA\xCA\xBC"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xBA\xBA\xBA"
        "\xC8\xCA\xBC"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xBA\xBA\xBA"
        "\xC8\xCD\xBC"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xBA\xC9\xBC"
        "\xC8\xBC\x00"
    },

    {
        4, 3,
        "\xC9\xCD\xBB\x00"
        "\xBA\xBA\xC8\xBB"
        "\xC8\xCD\xCD\xBC"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xBA\x20\xB9"
        "\xC8\xCA\xBC"
    },

    {
        4, 3,
        "\x00\xC9\xCD\xBB"
        "\xC9\xBA\xBA\xBC"
        "\xC8\xCD\xBC\x00"
    },

    {
        4, 3,
        "\xC9\xCD\xCD\xBB"
        "\xC8\xBB\xC9\xBC"
        "\x00\xC8\xBC\x00"
    },

    {
        4, 3,
        "\xC9\xBB\xC9\xBB"
        "\xBA\xC8\xBC\xBA"
        "\xC8\xCD\xCD\xBC"
    },

    {
        3, 3,
        "\xC9\xCB\xBB"
        "\xBA\xBA\xBA"
        "\xC8\xCD\xBC"
    },

    {
        4, 3,
        "\xC9\xCB\xCB\xBB"
        "\xBA\xBA\xBA\xBA"
        "\xC8\xCD\xCD\xBC"
    },

    {
        3, 3,
        "\xC9\xCB\xBB"
        "\xCC\x20\xB9"
        "\xC8\xCA\xBC"
    },

    {
        3, 3,
        "\xC9\xCB\xBB"
        "\xCC\xBB\xBA"
        "\xC8\xCD\xBC"
    },

    {
        4, 3,
        "\xC9\xCD\xCD\xBB"
        "\xCC\xBC\xC9\xB9"
        "\xC8\xCD\xCD\xBC"
    },

    {
        3, 3,
        "\x00\x00\x00"
        "\xC9\xCD\xBB"
        "\xC8\xCD\xBC"
    },

    {
        2, 3,
        "\x00\x00"
        "\xC9\xBB"
        "\xC8\xBC"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xCC\xCD\xB9"
        "\xC8\xCD\xBC"
    },

    {
        3, 3,
        "\xC9\xCD\xBB"
        "\xC8\xCB\xB9"
        "\x00\xC8\xBC"
    },

    {
        3, 2,
        "\xC9\xCB\xBB"
        "\xC8\xCA\xBC"
    },

    {
        2, 2,
        "\xC9\xBB"
        "\xC8\xBC"
    },

    {
        4, 3,
        "\x00\x00\x00\x00"
        "\xC9\xCD\xCD\xBB"
        "\xC8\xCD\xCD\xBC"
    },

    {
        4, 3,
        "\x00\xC9\xBB\x00"
        "\x00\xBA\xB9\x00"
        "\x00\xC8\xBC\x00"
    },

    {
        4, 3,
        "\x00\xC9\xBB\x00"
        "\x00\xCC\xBA\x00"
        "\x00\xC8\xBC\x00"
    }
};

static TxtDec AAW_DBL_FONT_3 = { (ASCIISprite*)AAW_FONT_3_SPRITES, {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0, 31,  0,  0,  0,  0, 32, 34, 35,  0,  0, 28,  0, 27,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 29, 30,  0,  0,  0,  0,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,  0,  0,  0,  0, 33,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
}, -1, &AAW_DBLINE_OVERLAY, "double_line" };

TxtDec* aawGetDBLFont3()
{
    return &AAW_DBL_FONT_3;
}
