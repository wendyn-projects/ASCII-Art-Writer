#include "aaw_sline_fonts.h"

/*
 * "Single-line" fonts for ASCII Art Writer
 *
 * File:    aaw_sbline_fonts.c
 * Author:  Vaclav [WENDYN] Nemec
 * Version: 1.0
 */

char AAW_SLINE_OVERLAY(char a, char b)
{
    char i, found = 0;
    char directions[] = {   //WENS - WEST, EAST, NORTH, SOUTH (inverted)
        '\xC5',             //0000
        '\xC1',             //0001
        '\xC2',             //0010
        '\xC4',             //0011
        '\xB4',             //0100
        '\xD9',             //0101
        '\xBF',             //0110
        '\xFF',             //plaC5-holder
        '\xC3',             //1000
        '\xC0',             //1001
        '\xDA',             //1010
        '\xFF',             //plaC5-holder
        '\xB3',             //1100

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

static const ASCIISprite AAW_FONT_3_SPRITES[] = {

    {
        2, 3,
        "\x00\x00"
        "\x00\x00"
        "\x00\x00"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xB3\xC2\xB3"
        "\xC0\xC1\xD9"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xB3\x20\xB4"
        "\xC0\xC4\xD9"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xB3\xC3\xB4"
        "\xC0\xC4\xD9"
    },

    {
        3, 3,
        "\x00\xDA\xBF"
        "\xDA\xD9\xB3"
        "\xC0\xC4\xD9"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xB3\xC1\xB4"
        "\xC0\xC4\xD9"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xB3\xC4\xB4"
        "\xC0\xD9\x00"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xB3\xDA\xB4"
        "\xC0\xC4\xD9"
    },

    {
        3, 3,
        "\xDA\xC2\xBF"
        "\xB3\xC4\xB3"
        "\xC0\xC1\xD9"
    },

    {
        2, 3,
        "\xDA\xBF"
        "\xB3\xB3"
        "\xC0\xD9"
    },

    {
        3, 3,
        "\x00\xDA\xBF"
        "\xDA\xB4\xB3"
        "\xC0\xC4\xD9"
    },

    {
        3, 3,
        "\xDA\xC2\xBF"
        "\xB3\x20\xB4"
        "\xC0\xC1\xD9"
    },

    {
        3, 3,
        "\xDA\xBF\x00"
        "\xB3\xC0\xBF"
        "\xC0\xC4\xD9"
    },

    {
        4, 3,
        "\xDA\xC4\xC4\xBF"
        "\xB3\xB3\xB3\xB3"
        "\xC0\xC1\xC1\xD9"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xB3\xB3\xB3"
        "\xC0\xC1\xD9"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xB3\xB3\xB3"
        "\xC0\xC4\xD9"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xB3\xDA\xD9"
        "\xC0\xD9\x00"
    },

    {
        4, 3,
        "\xDA\xC4\xBF\x00"
        "\xB3\xB3\xC0\xBF"
        "\xC0\xC4\xC4\xD9"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xB3\x20\xB4"
        "\xC0\xC1\xD9"
    },

    {
        4, 3,
        "\x00\xDA\xC4\xBF"
        "\xDA\xB3\xB3\xD9"
        "\xC0\xC4\xD9\x00"
    },

    {
        4, 3,
        "\xDA\xC4\xC4\xBF"
        "\xC0\xBF\xDA\xD9"
        "\x00\xC0\xD9\x00"
    },

    {
        4, 3,
        "\xDA\xBF\xDA\xBF"
        "\xB3\xC0\xD9\xB3"
        "\xC0\xC4\xC4\xD9"
    },

    {
        3, 3,
        "\xDA\xC2\xBF"
        "\xB3\xB3\xB3"
        "\xC0\xC4\xD9"
    },

    {
        4, 3,
        "\xDA\xC2\xC2\xBF"
        "\xB3\xB3\xB3\xB3"
        "\xC0\xC4\xC4\xD9"
    },

    {
        3, 3,
        "\xDA\xC2\xBF"
        "\xC3\x20\xB4"
        "\xC0\xC1\xD9"
    },

    {
        3, 3,
        "\xDA\xC2\xBF"
        "\xC3\xBF\xB3"
        "\xC0\xC4\xD9"
    },

    {
        4, 3,
        "\xDA\xC4\xC4\xBF"
        "\xC3\xD9\xDA\xB4"
        "\xC0\xC4\xC4\xD9"
    },

    {
        3, 3,
        "\x00\x00\x00"
        "\xDA\xC4\xBF"
        "\xC0\xC4\xD9"
    },

    {
        2, 3,
        "\x00\x00"
        "\xDA\xBF"
        "\xC0\xD9"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xC3\xC4\xB4"
        "\xC0\xC4\xD9"
    },

    {
        3, 3,
        "\xDA\xC4\xBF"
        "\xC0\xC2\xB4"
        "\x00\xC0\xD9"
    },

    {
        3, 2,
        "\xDA\xC2\xBF"
        "\xC0\xC1\xD9"
    },

    {
        2, 2,
        "\xDA\xBF"
        "\xC0\xD9"
    },

    {
        4, 3,
        "\x00\x00\x00\x00"
        "\xDA\xC4\xC4\xBF"
        "\xC0\xC4\xC4\xD9"
    },

    {
        4, 3,
        "\x00\xDA\xBF\x00"
        "\x00\xB3\xB4\x00"
        "\x00\xC0\xD9\x00"
    },

    {
        4, 3,
        "\x00\xDA\xBF\x00"
        "\x00\xC3\xB3\x00"
        "\x00\xC0\xD9\x00"
    }
};

static TxtDec AAW_SLN_FONT_3 = { (ASCIISprite*)AAW_FONT_3_SPRITES, {
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
}, -1, &AAW_SLINE_OVERLAY, "single_line" };

TxtDec* aawGetSLNFont3()
{
    return &AAW_SLN_FONT_3;
}
