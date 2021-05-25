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
//For signal
#include <signal.h>
//For bool
#include <stdbool.h>

void
handler (int signal);

int
main ()
{
  printf("%s\n", "Welcome to Andrew's shell");  
  if (signal (SIGCHLD, handler) == SIG_ERR)
  {
    fprintf (stderr, "signal error (%s) -- exiting \n", strerror(errno));
    exit(0);
  } 

  const int MAX = 80;
  const int MAX_ARGS = 5;

  bool active = true;
  while(active)
  {
    char *args[MAX_ARGS];
    char buf[MAX];
    printf("shell> ");
    fgets(buf, sizeof(buf), stdin);


    //Separate all the commands that were inputted into the buffer
    //And place them into the array,
    const char* DELIMS = " \t\n";
    char* token = strtok (buf, DELIMS);
    int i = 0;
    while (token != NULL && i < MAX_ARGS - 1)
    {
      args[i++] = token;
      token = strtok(NULL, DELIMS);
    }

    //Means input was only whitespace/nothing
    if (args[0] == NULL)
        return 0;

    //Last argument in array must be NULL
    args[i] = NULL;

    //Check to see if user types "exit"
    //if they do, exit the shell
    if (strcmp(args[0], "exit") == 0)
    {
      printf("%s", "Exiting shell...\n");
      exit(0);
    }

    pid_t pid = fork ();

    if (pid < 0)
    {
      fprintf (stderr, "fork error (%s) -- exiting\n",
         strerror (errno));
      exit (-1);
    }

    if (pid == 0)
    {
      printf ("[ PID: %d ]\n", getpid());
      int ret = execvp (args[0], args); 
      if (ret < 0)
      {
        fprintf (stderr, "exec error (%s) -- exiting\n",
           strerror (errno));
        exit (1);
      }
    }
    
    // Invoke waitpid with correct arguments
    sleep(2);
    // Print the child's exit status
    //printf("[* %s *] (Exit: %d)\n", args[0], returnStatus);
    // ...


  }
}

  //Signal handler
  //Need while loop in here to reap ALL children
  void
  handler (int signal)
  {
    (void) signal;
    int status;
    pid_t w_pid; 
    //Reap children
    while ((w_pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
      //  printf("%s \n", "I AM IN WHILE LOOP HURRAY");

      if (WIFEXITED(status))
      {
        int exitStatus = WEXITSTATUS(status);
        printf("[ PID: %d (Exit: %d) ]\n", w_pid, exitStatus);
      }
      else 
      {
        fprintf (stderr, "signal error (%s) -- exiting \n", strerror(errno));
      }
    }
    
  }
