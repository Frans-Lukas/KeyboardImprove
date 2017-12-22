#include "execute.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


#define STDIN_NO 0
#define STDOUT_NO 1

#define READ_END 0
#define WRITE_END 1

/* Duplicate a pipe to a standard I/O file descriptor, and close both pipe ends
 * Arguments:     pip   the pipe
 *          end   tells which end of the pipe shold be dup'ed; it can be
 *                one of READ_END or WRITE_END
 *          destfd      the standard I/O file descriptor to be replaced
 * Returns: -1 on error, else destfd
 */
int dupPipe(int pip[2], int end, int destfd){
      if(end > STDOUT_NO || end < STDIN_NO)
            return -1;

      if(close(destfd) < 0)
            return -1;
      if(dup(pip[end]) < 0)
            return -1;
      if(close(pip[STDIN_NO]) < 0)
            return -1;
      if(close(pip[STDOUT_NO]) < 0)
            return -1;

      return destfd;
}


/* Redirect a standard I/O file descriptor to a file
 * Arguments:     filename    the file to/from which the standard I/O file
 *                      descriptor should be redirected
 *          flags indicates whether the file should be opened for reading
 *                or writing
 *          destfd      the standard I/O file descriptor which shall be
 *                redirected
 * Returns: -1 on error, else destfd
 */
int redirect(char *filename, int flags, int destfd){
      int fdPos;
      if(flags == STDIN_NO){
            if((fdPos = open(filename, O_RDONLY)) == -1)
                  return -1;
      } else{
            if((fdPos = open(filename, O_RDWR | O_CREAT | O_EXCL, S_IRWXU)) == -1)
                  return -1;
      }

      if(close(destfd) < 0)
            return -1;
      if(dup(fdPos) < 0)
            return -1;
      if(close(fdPos))
            return -1;


      return destfd;
}
