#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// For strerror
#include <string.h>

// For fork, getpid, execve, read, write, close,
//   and other Linux system calls
#include <unistd.h>
// For waitpid
#include <sys/wait.h>
// For errno
#include <errno.h>

int
main ()
{

  int MAX = 80;
  int MAX_ARGS = 5;
  char *args[MAX_ARGS];
  char buf[MAX];
  printf("shell> ");
  fgets(buf, MAX, stdin);
  strtok(buf, "\n");

  //Last argument in array must be NULL

  //Separate all the commands that were inputted into the buffer
  //And place them into the array,
  char* token = strtok (buf, " ");
  int i = 0;
  while (token != NULL)
  {
    args[i] = token;
    token = strtok(NULL, " ");
    ++i;
  }
  args[i] = NULL;


  pid_t pid = fork ();

  if (pid < 0)
  {
    fprintf (stderr, "fork error (%s) -- exiting\n",
       strerror (errno));
    exit (-1);
  }

  if (pid == 0)
  {
    printf ("[ %s ] (PID: %d)\n", args[0], getpid());
    int ret = execvp (args[0], args); 
    if (ret < 0)
    {
      fprintf (stderr, "exec error (%s) -- exiting\n",
         strerror (errno));
      exit (1);
    }
  }
  // Invoke waitpid with correct arguments
  int status;
  pid_t w_pid = waitpid(pid, &status, 0);
  int returnStatus = WEXITSTATUS(status);
  // assert that the return value of waitpid matches 'pid'
  assert(pid = w_pid);
  // Print the child's exit status
  printf("[* %s *] (Exit: %d)\n", args[0], returnStatus);
  // ...
  
  return 0;
}
