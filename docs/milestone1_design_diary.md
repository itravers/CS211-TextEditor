# Design Diary
Use this space to talk about your process.  For inspiration, see [my prompts](../../../docs/sample_reflection.md) 

I usually use vim to edit code on the command line, however it has several issues that
hinder beginners. First, when a beginner doesn't know vim commands it's impossible to
use without consulting a search engine. Very simple things like opening and closing
a file, changing color schemes etc is impossible for a beginner. Having a clickable
menu system where you can do these items the common standard way, via point and click
interface would be preferable, as I don't think anyone other than a beginner would
actually utilize a text editor I created.

The first thing I need to do to finish my goal is to actually find out how curses
works. Some of my progress in this reguards can be found in github issue #2
at https://github.com/itravers/2019-fall-cs211/issues/2
I've also listed several of the tutorials and documentation I've found for curses
on the [guide](../../../docs/guides.md) 

Now I'll actually start experimenting with printing text to the screen. Colored Text.
I found a good Linux Journal article that explains how to print in curses.
It's pretty simple.
https://github.com/itravers/2019-fall-cs211/issues/3

Next I need to figure out how to print a status at the bottom of the screen that
doesn't get written over by the rest of the tings on the window. It looks like
I'll have to figure out how to use multiple windows in one screen. I can just 
write to the individual windows and not have to worry about keeping track of
exactly where I'm writing to.
https://github.com/itravers/2019-fall-cs211/issues/4

Next I'll figure out how to draw a file menu at the top of the screen. To just
draw the text of the words and manually place them should be pretty easy, but
I want a menu system that decides on it's own exactly how to place all the menu
items. So I'll break out all the code into it's own MenuController.cpp file 
[here](../../../projects/TextEditor/src/EditorOfText/EditorOfText/MenuController.cpp) 
and its corresponding header file 
[here](../../../projects/TextEditor/src/EditorOfText/EditorOfText/MenuController.h) 
This is investiged in issue #5 and #10
https://github.com/itravers/2019-fall-cs211/issues/5
https://github.com/itravers/2019-fall-cs211/issues/10

Next, drawing a border around the window is pretty easy as the teacher showed
us how to do this in the first lab. I don't want a border around the entire window
though, I want the file menu and the status bar to be outside the border.
https://github.com/itravers/2019-fall-cs211/issues/6

So, if we are going to have sub menu items, we have to actually have the menu windows 
themselves. These are the boxes that the sub menu items are shown in. They need to
only appear when the user wants them, and they need to leave when the user does not
want them. They need to popup, which might cover some text, so they also need to
be removed and allow the text that was under them to display again. This looks like
a good time to investigate curses panel.h library, which seems to have some of this
functionality built in. 
https://github.com/itravers/2019-fall-cs211/issues/8


====================================================
Further work in this area
- Investigate how to get a mouse click to trigger a menu.
-- https://github.com/itravers/2019-fall-cs211/issues/7

- Write function stubs for every submenu item that can be filled in as we design the functionality.
-- https://github.com/itravers/2019-fall-cs211/issues/14