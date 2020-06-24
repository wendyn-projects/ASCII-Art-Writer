# ASCII Art Writer
Application allows you to easilly convert any ASCII coded text into some ASCII art.

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

*If you want to view available fonts just add `??` option.*

### Chaining Multiple Commands
You are also allowed to chain multiple commands, here is an example:
```
-font?? -font -spacing -space -print
```
The command above will show you avaliable fonts then asks you for the font, for spacing, for background and then finally for the text you want to print.

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
/*-------------------------------- RIGHT HERE --------------------------------*/
    case 4:
        font = YOUR_FONT;
        break;
/*----------------------------------------------------------------------------*/
    }

    return font;
}
```
### Custom Commands
So maybe you want to add a command that helps you to choose the right font by showing your text printed in all fonts. How, you ask? Simple, every command function has 2 parameters - `listSender` *(where it was called from)* and `args` *(command arguments)* and it must return end of its input from `args`.

It's 00:00 and I'm gonna finnish this later.
