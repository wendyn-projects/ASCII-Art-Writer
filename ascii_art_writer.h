#ifndef ASCII_ART_WRITER_H_
#define ASCII_ART_WRITER_H_

/*
 * ASCII Art Writer Library
 *
 * File:    ascii_art_writer.h
 * Author:  Vaclav [WENDYN] Nemec
 * Version: 1.0
 */

#include <stdio.h>

///structure of a sprite
typedef struct{
    unsigned char width;
    unsigned char height;
    char* sprite;
} ASCIISprite;


///structure of an ASCII text decoration
typedef struct{
    ASCIISprite* font;
    unsigned char lookUpTable[256];
    char spacing;
    char (*overlayFunc)(char, char);
    char* name;
} TxtDec;

///overlay function for sprites
char aawAOverlay(char a, char b);

///overlay function for asprites
char aawBOverlay(char a, char b);

///gets the character the space is filled with
char aawGetBG(void);

///gets the character the letters are filled width
char aawGetFG(void);

///sets the character the space is filled with
void aawSetBG(char bg);

///sets the character the letters are filled with
void aawSetFG(char fg);

///prints text in ascii art font
void aawPrint(const TxtDec* decoration, char* s, FILE* f);

#endif // ASCII_ART_WRITER_H_
