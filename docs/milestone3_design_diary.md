# Design Diary
Use this space to talk about your process.  For inspiration, see [my prompts](../../../docs/sample_reflection.md) 


I started this milestone by trying to get my keyboard input to output to the screen.
We are rendering the screen in the loop, so if we edit currentLines in ContentController
Then that edit should automatically show up on the screen.
So now we just have to figure out how to edit the file.
I am trying to just replace characters in the vector. The trick is getting these
characters to replace at exactly the right point, there is a disconnect between cursorLocation.x
and the actual location that the character is in in the vector.