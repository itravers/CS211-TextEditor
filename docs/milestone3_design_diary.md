# Design Diary
I have pretty much all the milestone requirements done in the branch "develop"
I'm now planning on redesigning everything, so it isn't so haphazard.

I'm considering turning the text editor into a manager that manager
submanagers. these submanagers would talk to the manager via the
service locator pattern. I didn't feel the observer pattern gave
a submanager proper access to other submanagers while still
staying decoupled enough to be resistant to change. The service
locator pattern, as I understand it, will allow 

https://stackify.com/service-locator-pattern/



I've done former work using the service locator pattern here:
https://github.com/itravers/ARaceInSpace/tree/master/core/src/com/araceinspace/EventSubSystem

This is an event subsystem I designed to decouple parts of 
a game I hobbled together in my spare time. I think
I will take this general idea and apply it to my text editor
making the main manager talk to all the submanagers using
a similar event subsystem. Later on I can actually incorporate
that event subsystem into my curses wrappers.

