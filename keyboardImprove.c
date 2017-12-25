#include<stdio.h>
#include<linux/input.h>


/*
 * A program that will run in background and record what 
 * keystrokes you use the most.
 */
int main(int argc, char *argv[]){
    /* Creating a demon
    * 1. Fork
    * 2. setsid to create a new session
    * 3. change current directory to root.
    * 4. set file mode creation mask to 0
    * 5. Close all fildescriptors that will not be used.
    */
    
    printf("Hello, world! %s\n", argv[argc-1]);
    int fd;

    fd = open("/dev/input/event0", O_RDONLY);
    struct input_event ev;
    if(fd < 0){
        return EXIT_FAILURE;
    }


}
