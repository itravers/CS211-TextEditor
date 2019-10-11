# Design Diary

I did a LARGE amount of refactoring going into this milestone.
I've decided to completely redesign the entire application using
better object oriented design. I would also like to incorporate 
some design patterns I've been learning into this milestone.

I've decided to use an inhertitance scheme to design my objects.
Each curses window has a window and a panel which allow us to
manipulate them. I have decided to wrap those up in a basic compontent
object. Then I am going to slowing extend the component object piece 
by piece adding on new functionality until I have a set of extended
compontents that will do exactly what I want them to do.

So Far I've implemented the classes:
EditorComponent : Wraps curses objects and gives basic functionality.
EditorWindow    : Has a _buffer that gets rendered to the curses window
EditorWindowResizable: Allows the window to be resized
EditorWindowMoveable:  Allow the window to be moved.
EditorWindowScrollable: Allows the window to be scrolled.
EditorWindowEditable: Allows a client to edit the buffer in the window
EditorWindowInteractive: Allows a user to interact and type in the window.

EditorMenu also extends EditorWindowMoveable allowing a menu to
be displayed. EditorMenu uses the "stragegy pattern" from head
first design patterns to allow the menu to swap out MenuBehaviours,
of which their are currently two.

I have also updated the issue and project tracker for the project to include
pretty much all of the issues that are left to be done to get to the next milestone.

Next on my list before milestone 5, I need to get a dialog box working and
I need to get the menu's working. Then I will need to use the menu
to allow a word completion menu. Which should be fun.