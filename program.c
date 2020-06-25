#include "program.h"

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <stdarg.h>
#include <string.h>

#include "shell.h"
#include "ascii_art_writer.h"
#include "aaw_sline_fonts.h"
#include "aaw_dbline_fonts.h"
#include "aaw_round_fonts.h"
#include "aaw_grid_fonts.h"


static const unsigned char DEFAULT_FONT = 1;

static int helpDescIndent = 20;
static int interacDescIndent = 32;

static TxtDec* printFont = NULL;
static unsigned char printFontId;
static char printFontSpacing;


static TxtDec* getFont(unsigned char id)
{
    TxtDec* font = NULL;

    switch(id)
    {
    case 1:
        font = aawGetSLNFont3();
        break;

    case 2:
        font = aawGetDBLFont3();
        break;

    case 3:
        font = aawGetRNDFont5();
        break;

    case 4:
        font = aawGetGRDFont8();
        break;
    }

    return font;
}

static int scanfLine(const char* format, ...)
{
    int result;
    char c;
    va_list args;

    va_start(args, format);
    result = vscanf(format, args);
    do {
        scanf("%c", &c);
    } while (c != '\n');
    va_end(args);

    return result;
}

void prgSetFont(unsigned char id)
{
    printFont = getFont(id);
    if(printFont != NULL)
    {
        printFontId = id;
        printFontSpacing = printFont->spacing;
    }
    else
    {
        printFont = getFont(DEFAULT_FONT);
    }
}

void prgSetHelpDescIndent(int indent)
{
    helpDescIndent = indent;
}

void prgSetInteracDescIndent(int indent)
{
    interacDescIndent = indent;
}

char* cmdPrint(LCMD* listSender, const char* args)
{
    char* text2Print;
    char* inputEnd;
    char spacingHolder;
    char* arguments = (char*)args;

    if(printFont == NULL)
        prgSetFont(DEFAULT_FONT);

    spacingHolder = printFont->spacing;

    while(*arguments == ' ')
        ++arguments;

    if(*arguments == '\0')
    {
        printf("%*s", interacDescIndent, "text: ");
        text2Print = cmdGetLine(NULL, NULL, stdin);

        if(text2Print == NULL)
        {
            fprintf(stderr, "%s: \nError %03d (0x%02X) - %s\n", "-print",
                    ENOMEM, ENOMEM, strerror(ENOMEM));
        }
        else
        {
            printFont->spacing = printFontSpacing;
            aawPrint(printFont, text2Print, stdout);
            printFont->spacing = spacingHolder;

            free(text2Print);
        }
    }
    else
    {
        if(*arguments == '"')
        {
            inputEnd = strchr(arguments + 1, '"');

            if(inputEnd != NULL)
            {
                text2Print = (char*)malloc((inputEnd - arguments) * sizeof(char));

                if(text2Print == NULL)
                {
                    fprintf(stderr, "%s: \nError %03d (0x%02X) - %s\n", "-print",
                            ENOMEM, ENOMEM, strerror(ENOMEM));
                }
                else
                {
                    sscanf(arguments + 1, "%[^\"]", text2Print);
                    printFont->spacing = printFontSpacing;
                    aawPrint(printFont, text2Print, stdout);
                    printFont->spacing = spacingHolder;
                    free(text2Print);
                }

                arguments = inputEnd + 1;
            }
            else if(inputEnd != arguments)
            {
                fprintf(stderr, "%s: \nError %03d (0x%02X) - %s\n", "-print",
                        EINVAL, EINVAL, "Invalid input format");

                arguments += strlen(arguments);
            }

        }
        else if(*arguments == '-' && arguments[1] == 'i' && (arguments[2] == ' ' || arguments[2] == '\0'))
        {
            cmdPrint(listSender, "");
            arguments += 2;
        }
        else
        {
            inputEnd = strchr(arguments, ' ');

            if(inputEnd == NULL)
            {
                printFont->spacing = printFontSpacing;
                aawPrint(printFont, arguments, stdout);
                printFont->spacing = spacingHolder;

                arguments += strlen(arguments);
            }
            else
            {
                text2Print = (char*)malloc((inputEnd - arguments + 1) * sizeof(char));

                sscanf(arguments, "%[^ ]", text2Print);
                printFont->spacing = printFontSpacing;
                aawPrint(printFont, text2Print, stdout);
                printFont->spacing = spacingHolder;
                free(text2Print);

                arguments = inputEnd;
            }
        }
    }

    return arguments;
}

char* cmdSetFont(LCMD* listSender, const char* args)
{
    unsigned char f;
    char* arguments = (char*)args;

    while(*arguments == ' ')
        ++arguments;

    if(sscanf(arguments, "%hhu", &f) > 0)
    {
        prgSetFont(f);

        while(*arguments != ' ' && *arguments != '\0')
            ++arguments;

    }
    else
    {
        if(*arguments++ == '?' && (*arguments == ' ' || *arguments == '\0'))
        {
            printf("%*s", interacDescIndent, "font: ");
            printf("%hhu", printFontId);
            putchar('\n');
            aawPrint(printFont, printFont->name, stdout);
        }
        else if(*arguments++ == '?' && (*arguments == ' ' || *arguments == '\0'))
        {
            TxtDec* font;

            for(f = 1; (font = getFont(f)) != NULL; f++)
            {
                printf("%hhu\n", f);
                aawPrint(font, font->name, stdout);
            }
        }
        else
        {
            printf("%*s", interacDescIndent, "font: ");
            if(scanfLine("%hhu", &f) == 0)
            {
                printf("%*s", interacDescIndent, "L invalid input\n");
            }
            else
            {
                prgSetFont(f);
            }

            arguments -= 2;
        }
    }

    return arguments;
}

char* cmdSetSpacing(LCMD* listSender, const char* args)
{
    char* arguments = (char*)args;

    while(*arguments == ' ')
        ++arguments;

    if(sscanf(arguments, "%hhd", &printFontSpacing) <= 0)
    {
        printf("%*s", interacDescIndent, "letter-spacing: ");

        if(*arguments++ == '?' && (*arguments == ' ' || *arguments == '\0'))
        {
            printf("%hhd", printFontSpacing);
            putchar('\n');
        }
        else
        {
            if(scanfLine("%hhd", &printFontSpacing) == 0)
            {
                printf("%*s", interacDescIndent, "L invalid input\n");
            }

            --arguments;
        }
    }
    else
    {
        while(*arguments != ' ' && *arguments != '\0')
            ++arguments;
    }

    return arguments;
}

char* cmdSetBG(LCMD* listSender, const char* args)
{
    char* arguments = (char*)args;

    while(*arguments == ' ')
        ++arguments;

    if(*arguments == '?')
    {
        printf("%*s", interacDescIndent, "background-character: ");
        printf("%c", aawGetBG());
        putchar('\n');
        ++arguments;
    }
    else if(*arguments++ == '-' && *arguments != '\0' && *arguments != '\t' && (arguments[1] == ' ' || arguments[1] == '\0'))
    {
        aawSetBG(*arguments);
    }
    else
    {
        char bg;
        printf("%*s", interacDescIndent, "background-character: ");
        scanfLine("%c", &bg);
        if(bg == '\n' || bg == '\t')
            bg = ' ';

        aawSetBG(bg);
        --arguments;
    }

    return arguments;
}

char* cmdSetFG(LCMD* listSender, const char* args)
{
    char* arguments = (char*)args;

    while(*arguments == ' ')
        ++arguments;

    if(*arguments == '?')
    {
        printf("%*s", interacDescIndent, "foreground-character: ");
        printf("%c", aawGetFG());
        putchar('\n');
        ++arguments;
    }
    else if(*arguments++ == '-' && *arguments != '\0' && *arguments != '\t' && (arguments[1] == ' ' || arguments[1] == '\0'))
    {
        aawSetFG(*arguments);
    }
    else
    {
        char fg;
        printf("%*s", interacDescIndent, "foreground-character: ");
        scanfLine("%c", &fg);
        if(fg == '\n' || fg == '\t')
            fg = ' ';

        aawSetFG(fg);
        --arguments;
    }

    return arguments;
}

char* cmdInfo(LCMD* listSender, const char* args)
{
    printf("-font %hhu -spacing %hhd -space -%c -fill -%c\n",
           printFontId, printFontSpacing, aawGetBG(), aawGetFG());
    return (char*)args;
}

char* cmdClean(LCMD* listSender, const char* args)
{
    system("@cls||clear");
    return (char*)args;
}

char* cmdHelp(LCMD* listSender, const char* args)
{
    int spaceLen;
    LCMDItem* itemCursor;
    char* descCursor;
    char* arguments = (char*)args;

    while(*arguments == ' ')
        ++arguments;

    if(*arguments == '\0')
    {
        itemCursor = listSender->firstItem;

        printf("Command list:\n\n");
        while(itemCursor != NULL)
        {
            printf(" %s%n", itemCursor->cmd->name, &spaceLen);

            descCursor = itemCursor->cmd->desc;

            if(helpDescIndent > spaceLen)
            {
                printf("%*c", helpDescIndent - spaceLen, ' ');
            }
            else
            {
                putchar('\n');
                printf("%*c", helpDescIndent, ' ');
            }

            while(*descCursor != '\n' && *descCursor != '\0')
            {
                putchar(*descCursor);
                ++descCursor;
            }

            putchar('\n');
            putchar('\n');

            itemCursor = itemCursor->next;
        }
        putchar('\n');
    }
    else if(*arguments == '*' && (arguments[1] == ' ' || arguments[1] == '\0'))
    {
        cmdHelp(listSender, "");

        return arguments + 1;
    }
    else
    {

        itemCursor = lcmdFindItem(listSender, arguments);

        if(itemCursor != NULL)
        {
            spaceLen = 1;
            putchar(' ');

            while(*arguments != ' ' && *arguments != '\0')
            {
                putchar(*arguments++);
                ++spaceLen;
            }

            descCursor = itemCursor->cmd->desc;


            if(helpDescIndent > spaceLen)
            {
                printf("%*c", helpDescIndent - spaceLen, ' ');
            }
            else
            {
                putchar('\n');
                printf("%*c", helpDescIndent, ' ');
            }

            while(*descCursor != '\n' && *descCursor != '\0')
            {
                putchar(*descCursor);
                ++descCursor;
            }

            putchar('\n');

            while(*descCursor != '\0')
            {
                if(*descCursor == '\t')
                {
                    if(helpDescIndent > spaceLen)
                    {
                        printf("%*c", helpDescIndent - spaceLen, ' ');
                    }
                    else
                    {
                        putchar('\n');
                        printf("%*c", helpDescIndent, ' ');
                    }
                }
                else
                {
                    putchar(*descCursor);
                    ++spaceLen;
                }

                if(*descCursor == '\n')
                {
                    spaceLen = 1;
                    putchar(' ');
                }

                ++descCursor;
            }

            putchar('\n');
            putchar('\n');
        }
        else
        {
            fprintf(stderr, "%s: \nError %03d (0x%02X) - %s\n", "-help",
                    EINVAL, EINVAL, "Input is not a valid command.");
        }
    }

    return arguments;
}
