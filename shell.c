#include "shell.h"

/*
 * Ez Shell Library
 *
 * File:    shell.c
 * Author:  Vaclav [WENDYN] Nemec
 * Version: 1.0
 */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

char* cmdGetLine(char* buffer, size_t* length, FILE* f)
{
    struct charLItem {
        char c;
        struct charLItem* next;
    };

    struct charLItem* list;
    struct charLItem* listCursor;
    char c;
    char* output;
    size_t l = 1;

    list = (struct charLItem*)malloc(sizeof(struct charLItem));                  //tries to allocate space for new char item

    if(list == NULL)                                                             //checks if allocation was successful
        return NULL;

    fscanf(f, "%c", &c);
    list->c = c;
    listCursor = list;

    while(c != '\n' && c != '\0' && c != EOF)                                    //goes through characters of the file until the end of the line
    {
        listCursor->next = (struct charLItem*)malloc(sizeof(struct charLItem));  //tries to allocate space for a new char item

        if(listCursor->next == NULL)                                             //checks if allocation was successful
        {
            while(list != NULL)                                                  //deallocates allocated
            {
                listCursor = list;
                list = list->next;
                free(listCursor);
            }

            return NULL;
        }

        listCursor = listCursor->next;                                           //moves on the new char item
        fscanf(f, "%c", &c);                                                     //gets a new character from the stream
        listCursor->c = c;                                                       //puts it into the char list
        ++l;                                                                     //increases length for an array
    }

    listCursor->c = '\0';
    listCursor->next = NULL;

    if(length == NULL || l > *length || buffer == NULL)                          //checks if allocation is necessary
    {
        output = (char*)malloc(l * sizeof(char));                                //tries to create the new array

        if(output == NULL)                                                       //checks if allocation was successful
        {
            while(list != NULL)                                                  //deallocates allocated
            {
                listCursor = list;
                list = list->next;
                free(listCursor);
            }

            return NULL;
        }

        if(length != NULL)
            *length = l;
    }
    else
    {
        output = buffer;
    }

    while(list != NULL)                                                          //copies all the characters into the array
    {
        listCursor = list;
        *output++ = list->c;
        list = list->next;
        free(listCursor);
    }

    return output - l;
}

LCMD* lcmdCreate()
{
    LCMD* list = (LCMD*)malloc(sizeof(LCMD));                                    //tries to allocate space for the new list

    if(list == NULL)                                                             //checks if allocation was successful
        return NULL;

    list->firstItem = NULL;

    return list;
}

LCMDItem* lcmdAddItem(LCMD* list, char* name, char* desc, char* (*func)(LCMD* listSender, const char* args))
{
    CMD* command;
    LCMDItem* item;

    command = (CMD*)malloc(sizeof(CMD));                                         //tries to allocate space for the new command

    if(command == NULL)                                                          //checks if allocation was successful
        return NULL;

    item = (LCMDItem*)malloc(sizeof(LCMDItem));                                  //tries to allocate space for a new item

    if(item == NULL)                                                             //checks if allocation was successful
    {
        free(command);
        return NULL;
    }

    command->name = name;
    command->desc = desc;
    command->func = func;

    item->cmd = command;
    item->next = NULL;

    if(list->firstItem == NULL)
    {
        list->firstItem = item;
    }
    else
    {
        LCMDItem* listCursor = list->firstItem;

        while(listCursor->next != NULL)                                          //finds end of the list
            listCursor = listCursor->next;

        listCursor->next = item;                                                 //puts the new item there
    }

    return item;
}

void lcmdFree(LCMD* list)
{
    LCMDItem* listItem2Delete;
    LCMDItem* listCursor = list->firstItem;

    while(listCursor != NULL)                                                    //goes through the list
    {
        listItem2Delete = listCursor;                                            //stores the item for later
        listCursor = listCursor->next;                                           //moves on the next item

        free(listItem2Delete->cmd);
        free(listItem2Delete);
    }

    free(list);
}

LCMDItem* lcmdFindItem(const LCMD* list, const char* cmd)
{
    char* lcmdCursor;
    char* cmdCursor;
    LCMDItem* listCursor = list->firstItem;

    while(listCursor != NULL)                                                    //goes through the list
    {
        cmdCursor = (char*)cmd;
        lcmdCursor = listCursor->cmd->name;

        while(*cmdCursor == *lcmdCursor)                                         //compares them
        {
            ++cmdCursor;
            ++lcmdCursor;

            if((*cmdCursor == ' ' || *cmdCursor == '\0') && *lcmdCursor == '\0') //checks if match was found
                return listCursor;                                               //returns result
        }

        listCursor = listCursor->next;
    }
    return NULL;
}

char* lcmdRun(LCMD* list, const char* cmd)
{
    LCMDItem* listCursor;
    char* formattedCmd;
    char* lcmdCursor;
    char* cmdCursor;

    if(list == NULL)
        return NULL;

    if(cmd == NULL)
        return NULL;

    listCursor = list->firstItem;

    formattedCmd = (char*)cmd;

    while(*formattedCmd == ' ')                                                  //skips all the spaces
        ++formattedCmd;

    while(listCursor != NULL)                                                    //goes through the list
    {
        lcmdCursor = listCursor->cmd->name;                                      //resets 'command name to check' pointer
        cmdCursor = formattedCmd;                                                //resets command input pointer

        while(*cmdCursor == *lcmdCursor)                                         //compares them
        {
            ++cmdCursor;
            ++lcmdCursor;

            if((*cmdCursor == ' ' || *cmdCursor == '\0') && *lcmdCursor == '\0') //checks if match was found
                return listCursor->cmd->func(list, cmdCursor);                   //then calls associated command and returns
        }

        listCursor = listCursor->next;
    }

    while(*formattedCmd == ' ')                                                  //skips all the spaces
        ++formattedCmd;

    return formattedCmd;                                                         //invalid input returns NULL
}

char* lcmdRunBatch(LCMD* list, const char* cmdBatch)
{
    LCMDItem* listCursor;
    char* cmdBatchCursor;
    char* lcmdCursor;
    char* cmdCursor;

    if(list == NULL)
        return NULL;

    if(cmdBatch == NULL)
        return NULL;

    listCursor = list->firstItem;
    cmdBatchCursor = (char*)cmdBatch;


    while(*cmdBatchCursor == ' ')                                                //skips all the spaces
        ++cmdBatchCursor;

    while(listCursor != NULL)                                                    //goes through the list
    {
        lcmdCursor = listCursor->cmd->name;                                      //resets 'command name to check' pointer
        cmdCursor = cmdBatchCursor;                                              //resets command input pointer

        while(*cmdCursor == *lcmdCursor)                                         //compares them
        {
            ++cmdCursor;
            ++lcmdCursor;

            if((*cmdCursor == ' ' || *cmdCursor == '\0') && *lcmdCursor == '\0') //checks if match was found
                return
                    lcmdRunBatch(list, listCursor->cmd->func(list, cmdCursor));  //then calls associated command and calls itself again
        }

        listCursor = listCursor->next;
    }

    while(*cmdBatchCursor == ' ')                                                //skips all the spaces
        ++cmdBatchCursor;

    return cmdBatchCursor;
}
