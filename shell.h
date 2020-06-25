#ifndef SHELL_H_
#define SHELL_H_

/*
 * Ez Shell Library
 *
 * File:    shell.h
 * Author:  Vaclav [WENDYN] Nemec
 * Version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>

struct LCMDItem;

///structure of command list
typedef struct {
    struct LCMDItem* firstItem;
} LCMD;

///structure of command
typedef struct {
    char* name;
    char* desc;
    char* (*func)(LCMD* listSender, const char* args);
} CMD;

///structure of command list item
typedef struct LCMDItem {
    CMD* cmd;
    struct LCMDItem* next;
} LCMDItem;

/**
 * Reads a line from a stream and stores it into a buffer, if the buffer isn't big enough it creates a new buffer
 * @param f - is the stream the line gets read from
 * @return current buffer
 */
char* cmdGetLine(char* buffer, size_t* length, FILE* f);

/**
 * Creates a new list.
 */
LCMD* lcmdCreate();

/**
 * Adds a command to the command list.
 * @param func - the function the command runs - must return end of its input in 'args'
 */
LCMDItem* lcmdAddItem(LCMD*, char* name, char* desc, char* (*func)(LCMD* listSender, const char* args));

///Deallocates the whole list.
void lcmdFree(LCMD*);

/**
 * Locates a command item in the list
 * @param cmd - the command
 */
LCMDItem* lcmdFindItem(const LCMD*, const char* cmd);

/**
 * Runs a command from the list.
 * @param cmd - is the command this functions runs
 * @return (invalid arguments)? NULL: end of the command
 */
char* lcmdRun(LCMD*, const char* cmd);

/**
 * Runs a batch of commands (starting left ofc) from the list.
 * @param cmdBatch - is the batch
 * @return end of the runnable part
 */
char* lcmdRunBatch(LCMD*, const char* cmdBatch);

#endif // SHELL_H_
