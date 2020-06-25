#include "ascii_art_writer.h"

/*
 * ASCII Art Writer Library
 *
 * File:    ascii_art_writer.c
 * Author:  Vaclav [WENDYN] Nemec
 * Version: 1.0
 */

#include <stdio.h>

static char bgChar = ' ';
static char fgChar = ' ';

char aawAOverlay(char a, char b)
{
    return (a == '\0')? b: a;
}

char aawBOverlay(char a, char b)
{
    return (b == '\0')? a: b;
}

char aawGetBG(void)
{
    return bgChar;
}

char aawGetFG(void)
{
    return fgChar;
}

void aawSetBG(char bg)
{
    bgChar = bg;
}

void aawSetFG(char fg)
{
    fgChar = fg;
}

void aawPrint(const TxtDec* decoration, char* s, FILE* f)
{
    unsigned char line, line_max = 1, sub_char;
    size_t letter, s_len;
    char c;
    ASCIISprite* sprite;

    for(s_len = 0; s[s_len] != '\0'; s_len++);

    for(line = 0; line < line_max; line++)
    {
        for(letter = 0; letter < s_len; letter++)
        {
            sprite = decoration->font +
                decoration->lookUpTable[(unsigned char)s[letter]];

            //makes sure that all lines are printed
            if(sprite->height > line_max)
                line_max = sprite->height;

            //calculates starting offset of a letter (needed for negative spacing)
            sub_char = (decoration->spacing >= 0 || letter == 0)?
                        0:
                        -decoration->spacing;

            //prints out one row of the letter
            while(sub_char < sprite->width + decoration->spacing)
            {

                c = (sub_char < sprite->width && line < sprite->height)?
                        sprite->sprite[sub_char + line * sprite->width]:
                        '\0';

                fputc((c == '\0')? bgChar: (c == ' ')? fgChar: c, f);

                ++sub_char;
            }

            //if overlapping
            if(decoration->spacing < 0 && letter + 1 < s_len)
            {
                ASCIISprite* sprite_next = decoration->font +
                    decoration->lookUpTable[(unsigned char)s[letter + 1]];
                unsigned char sub_char_next = 0;
                char c_next;

                while(sub_char < sprite->width)
                {
                    c = (line < sprite->height)?
                            sprite->sprite[sub_char + line * sprite->width]:
                            '\0';

                    c_next = (line < sprite_next->height)?
                            sprite_next->sprite[sub_char_next + line * sprite_next->width]:
                            '\0';

                    c = (decoration->overlayFunc == NULL)?
                            aawAOverlay(c, c_next):
                            (*decoration->overlayFunc)(c, c_next);

                    fputc((c == '\0')? bgChar: (c == ' ')? fgChar: c, f);

                    ++sub_char;
                    ++sub_char_next;
                }
            }
        }

        //just to be sure there is some last letter
        if(s_len > 0)
        {
            //last column of last letter
            --letter;
            while(sub_char < sprite->width)
            {
                c = (line < sprite->height)?
                        sprite->sprite[sub_char + line * sprite->width]:
                        '\0';

                fputc((c == '\0')? bgChar: (c == ' ')? fgChar: c, f);
                ++sub_char;
            }
        }

        fputc('\n', f);
    }
}
