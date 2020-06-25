# ASCII Art Writer
Application allows you to easilly convert any ASCII coded text into some ASCII art.

---

## Instalation
```bash
git clone https://github.com/wendyn-projects/ASCII-Art-Writer.git
make -C ASCII-Art-Writer

```

---

## Usage
Documentation is implemented within the `-help` command but here are some examples:
### Printing a Word
```
-print word
```
### Printing Multiple Words
```
-print "lorem ipsul dolor sit amet"
```
*`-print` command is also interactive if you leave it without any input or if you add `-i` option.*

### Changing the Font
```
-font number
```
*`-font` is also interactive if you leave it without input.*

*Do you want to view available fonts? Just add `??` option.*

### Chaining Multiple Commands
You are also allowed to chain multiple commands, here is an example:
```
-font?? -font -spacing -space -print
```
The command above will show you avaliable fonts then asks you for the font - for spacing - for background - and then finally for the text you want to print.

---

## Modifications
### Custom Fonts
Do you want to create your own font? That's Easy. Just store it in this format:

#### Structure of Fonts
* Array of Sprites
    * Sprite
        * Width
        * Height
        * 1D Char Array
            * `\0` is used for background
* Character Lookup Table
    * Indexes are mapped to sprites in the sprite array
* Default Letter Spacing
    * How many spaces are put between letters (negative value is possible)
* Overlay Function
    * In case of negative letter spacing the letters are overlapping and this is where this function comes in, its purpose is to decide which character to choose.
    * If you are unsure on how to write your own then just leave it `NULL` and the `aawPrint` function will use its default.
* Font Name

*(also defined in `ascii_art_writer.h`)*
#### `-font` Command
Now if you want your font to show up, just add the option to the swicth statement inside of `getFont` function within the `program.c` file.
```c
static TxtDec* getFont(unsigned char id)
{
    TxtDec* font = NULL;

    switch(id)
    {
    case 1:
        font = aawGetDBLFont3();
        break;

    case 2:
        font = aawGetRNDFont5();
        break;

    case 3:
        font = aawGetGRDFont8();
        break;
        
    ...
    
/*-------------------------------- RIGHT HERE --------------------------------*/
    case FOLLOWING_ID:
        font = YOUR_FONT;
        break;
/*----------------------------------------------------------------------------*/
    }

    return font;
}
```
### Custom Commands
So maybe you want to add your own command. 
How, you ask? 
Simple, every command function has 2 parameters - `listSender` *(where it was called from)* and `args` *(command arguments)* and it must return end of its input from `args`.

If it takes 0 arguments, just return `args`.
```c
char* customCmd(LCMD* listSender, const char* args)
{
    /* your code goes here */
    return (char*)args;
}
```
But what if you also want it to have some input? Then you need to parse it from `args` and return where you ended up.
```c
char* customCmd(LCMD* listSender, const char* args)
{
    int input;
    char* arguments2Parse = (char*)args;
    
    //let's skip the spaces first
    while(*arguments2Parse++ == ' ');
    
    //now the parsing
    if(sscanf(arguments2Parse, "%d", &input) != 0)
    {
        /* your code goes here */
    
        //and now we need to skip to the end of what we just parsed
        while(*arguments2Parse != ' ' && *arguments2Parse != '\0');
            ++arguments2Parse;
    }
    else
    {
        /* in case of invalid input */
    }
    
    return arguments2Parse;
}
```
Now we just need to list it in our command list `commands` in the `main.c` file and that's it, done.
```c
lcmdAddItem(commands, CUSTOM_CMD_NAME, CUSTOM_CMD_DESCRIPTION, &customCmd);
```
Just recompile the code.
```bash
make
```
