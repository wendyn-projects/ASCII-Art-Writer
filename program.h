#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "ascii_art_writer.h"
#include "shell.h"

void prgSetFont(unsigned char id);
void prgSetHelpDescIndent(int indent);
void prgSetInteracDescIndent(int indent);

char* cmdPrint(LCMD* listSender, const char* args);
char* cmdSetFont(LCMD* listSender, const char* args);
char* cmdSetSpacing(LCMD* listSender, const char* args);
char* cmdSetBG(LCMD* listSender, const char* args);
char* cmdSetFG(LCMD* listSender, const char* args);
char* cmdInfo(LCMD* listSender, const char* args);

char* cmdClean(LCMD* listSender, const char* args);
char* cmdHelp(LCMD* listSender, const char* args);

#endif // PROGRAM_H_
