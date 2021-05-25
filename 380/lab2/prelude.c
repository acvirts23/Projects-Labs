#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int
main ()
{
    
  int MAX = 80;
  char buf[MAX];
  printf("shell> ");
  fgets(buf, MAX, stdin);
  strtok(buf, "\n");


  pid_t pid = fork ();
  if (pid < 0)
  {
    fprintf (stderr, "fork error (%s) -- exiting\n",
	     strerror (errno));
    exit (-1);
  }
  if (pid == 0)
  {
    printf ("Child says: PID = %d, parent PID = %d, '%s'\n", getpid(), getppid(), buf);
    exit (0); 
  }
  printf ("Parent says: PID = %d, child PID = %d, parent PID = %d\n", getpid(), pid, getppid()); 
  
  return 0;
}
