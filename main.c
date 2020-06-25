#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

#include "program.h"
#include "shell.h"

int main(int argc, char **argv)
{
    char* buffer = NULL;
    char* bufferHelper;
    size_t bufferLen = 0;
    size_t allocLen = 0;
    LCMD* commands = lcmdCreate();

    lcmdAddItem(commands, "-print",
                "Prints text in ASCII art.\n"
                "(interactive)\tAsks for the text.\n"
                "-i\tAsks for the text.\n"
                "+ [text]\tPrints the text.\n",
                &cmdPrint);

    lcmdAddItem(commands, "-font",
                "Font setting\n"
                "(interactive)\tAsks for the font.\n"
                "+ [font id]\tSets font and appropriate spacing.\n"
                "+ ?\tShows current font.\n"
                "+ ??\tShows available fonts.",
                &cmdSetFont);

    lcmdAddItem(commands, "-spacing",
                "Letter spacing setting\n"
                "(interactive)\tAsks for the letter spacing.\n"
                "+ [space]\tSets how many spaces are put between letters.\n"
                "+ ?\tShows how many spaces are put between letters.\n\n"
                "Negative value is allowed.",
                &cmdSetSpacing);

    lcmdAddItem(commands, "-space",
                "Background of the text\n"
                "(interactive)\tAsks for the character.\n"
                " -[char]\tSets the character the space is filled with.\n"
                "+ ?\tShows which character is used to fill the space.",
                &cmdSetBG);

    lcmdAddItem(commands, "-fill",
                "Inside of the text\n"
                "(interactive)\tAsks for the character.\n"
                " -[char]\tSets the character the letters are filled with.\n"
                "+ ?\tShows which character is used to fill the letters.",
                &cmdSetFG);

    lcmdAddItem(commands, "-info", "Shows current setting.", &cmdInfo);

    lcmdAddItem(commands, "-clean", "Cleans console screen.", &cmdClean);

    lcmdAddItem(commands, "-help",
                "Provides information for commands.\n"
                "+ *\tShows list of commands\n"
                "+ [command]\tprovides detailed informations on specified command",
                &cmdHelp);

    if(argc == 1)
    {
        printf("ASCII Art Writer\n\n"
               "\tAuthor:  Vaclav [WENDYN] Nemec\n"
               "\tVersion: 1.0\n\n"
               "Tip: Type -help to show a list of available commands.\n\n");

        while(1)
        {
            bufferHelper = cmdGetLine(buffer, &bufferLen, stdin);

            if(bufferHelper == NULL)
            {
                fprintf(stderr, "Error %03d (0x%02X) - %s\n",
                        ENOMEM, ENOMEM, strerror(ENOMEM));
                lcmdFree(commands);
                free(buffer);
                return ENOMEM;
            }

            if(bufferHelper != buffer)
            {
                free(buffer);
                buffer = bufferHelper;
            }

            lcmdRunBatch(commands, buffer);
        }
    }
    else
    {
        int argIndex, argLen;

        for(argIndex = 1; argIndex < argc; argIndex++)
        {
            allocLen += strlen(argv[argIndex]) + 1;
        }

        buffer = (char*)malloc(allocLen * sizeof(char));

        if(buffer == NULL)
        {
            fprintf(stderr, "Error %03d (0x%02X) - %s\n",
                    ENOMEM, ENOMEM, strerror(ENOMEM));
            lcmdFree(commands);
            return ENOMEM;
        }

        for(argIndex = 1; argIndex < argc; argIndex++)
        {
            sprintf(buffer, "%s%n", argv[argIndex], &argLen);
            buffer += argLen;
            *buffer++ = ' ';
        }
        *buffer = '\0';

        buffer -= allocLen;

        lcmdRunBatch(commands, buffer);
    }

    //clean up
    lcmdFree(commands);
    free(buffer);

    return EXIT_SUCCESS;
}
