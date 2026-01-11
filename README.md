# purpose
i need to debug lua code, i need to add breakpoint and stepping through the code  
so i think i will use lua debug by actboy168  
in order to do that, i create the lua module (library) that i can load  
and then just call the lua script  

# research
i build executable and library, the executable is able to load the library successfully  
the problem is with the "lib" prefix

lua require doesn't want to load raylib_lua, it wanted libraylib.lua  

# result
yess! we can debug using lua debug!  
but auto reloading is much faster than closing and re-runnning the debug  
solved by reloading the scripts on update.lua feels so much faster!