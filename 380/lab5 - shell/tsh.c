/*
 * tsh - A tiny shell program
 * ******************
 * Andrew Virts
 * CSCI 380
 * Dr. Zoppetti
 * ******************
 * DISCUSS YOUR IMPLEMENTATION HERE!
 * 
 * There were a lot of tricky bits and pieces to this assignment that took
 * hours of dedication to complete.
 * The result was extremely rewarding and I look forward to continue expanding this shell. 
 * The sigint and sigstp handlers were rather simple to implement. 
 * For the sigint_handler, All I do is check to see if there is an active runningPID when the signal is sent, 
 * if there is... I send a SIGINT signal to it. 
 * Similarly for my sigstp handler I check to see if there is a current process in the foreground, 
 * and if there is I send a SIGSTP signal to it. 
 * Lastly, for my sigchld handler I begin by looping while there are children to be reaped, 
 * if the child is stopped and is the current running process, 
 * I send a message to the terminal; otherwise I send a message showing the signal. 
 * For waitpid I pass WNOHANG flag so the parent process oesnt wait, 
 * and the wuntrace flag gets status info from the stopped process. 
 * To wait for a foreground job I start by creating a mask and initializing it. 
 * Then, while the job is running I wait for a sigchild signal to come in and 
 * then finally suspend the job until the signal is delivered. 
 * 
 */

/*
 *******************************************************************************
 * INCLUDE DIRECTIVES
 *******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 *******************************************************************************
 * TYPE DEFINITIONS
 *******************************************************************************
 */

typedef void handler_t (int);

/*
 *******************************************************************************
 * PREPROCESSOR DEFINITIONS
 *******************************************************************************
 */

// max line size 
#define MAXLINE 1024 
// max args on a command line 
#define MAXARGS 128

/*
 *******************************************************************************
 * GLOBAL VARIABLES
 *******************************************************************************
 */

// defined in libc
extern char** environ;   

// command line prompt 
char prompt[] = "tsh> ";

// for composing sprintf messages
char sbuf[MAXLINE];

// PID of the foreground process
volatile pid_t g_runningPid = 0;
// PID of the suspended process
volatile pid_t g_suspendedPid = 0; 

/*
 *******************************************************************************
 * FUNCTION PROTOTYPES
 *******************************************************************************
 */

void
eval (char* cmdline);

void
waitfg(pid_t pid);

int
builtin_cmd (char** argv);

int
parseline (const char* cmdline, char** argv);

void
sigint_handler (int sig);

void
sigtstp_handler (int sig);

void
sigchld_handler (int sig);

void
sigquit_handler (int sig);

void
unix_error (char* msg);

void
app_error (char* msg);

handler_t*
Signal (int signum, handler_t* handler);

/*
 *******************************************************************************
 * MAIN
 *******************************************************************************
 */

int
main (int argc, char** argv)
{
  /* Redirect stderr to stdout */
  dup2 (1, 2);

  /* Install signal handlers */
  Signal (SIGINT, sigint_handler);   /* ctrl-c */
  Signal (SIGTSTP, sigtstp_handler); /* ctrl-z */
  Signal (SIGCHLD, sigchld_handler); /* Terminated or stopped child */
  Signal (SIGQUIT, sigquit_handler); /* quit */

  /* TODO -- shell goes here*/
  char cmdline[MAXLINE];
  while(1)
  {

    //Display the shell
    printf("%s", prompt);
    fflush(stdout);

    fgets(cmdline, MAXLINE, stdin);
    //If we reach the end of the file
    if (feof (stdin)) 
    {
      exit(0);
    }
    eval (cmdline);
  }
  /* Quit */
}

/*
*  parseline - Parse the command line and build the argv array.
*
*  Characters enclosed in single quotes are treated as a single
*  argument.
*
*  Returns true if the user has requested a BG job, false if
*  the user has requested a FG job.
*/
int
parseline (const char* cmdline, char** argv)
{
  static char array[MAXLINE]; /* holds local copy of command line*/
  char* buf = array;          /* ptr that traverses command line*/
  char* delim;                /* points to first space delimiter*/
  int argc;                   /* number of args*/
  int bg;                     /* background job?*/

  strcpy (buf, cmdline);
  buf[strlen (buf) - 1] = ' ';  /* replace trailing '\n' with space*/
  while (*buf && (*buf == ' ')) /* ignore leading spaces*/
    buf++;

  /* Build the argv list*/
  argc = 0;
  if (*buf == '\'')
  {
    buf++;
    delim = strchr (buf, '\'');
  }
  else
  {
    delim = strchr (buf, ' ');
  }

  while (delim)
  {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;
    while (*buf && (*buf == ' ')) /* ignore spaces*/
      buf++;

    if (*buf == '\'')
    {
      buf++;
      delim = strchr (buf, '\'');
    }
    else
    {
      delim = strchr (buf, ' ');
    }
  }
  //Set last argument to NULL so our shell works!
  argv[argc] = NULL;

  if (argc == 0) /* ignore blank line*/
    return 1;

  //Checks to see if the last arg is an ampersand, if it does, then the job runs in the background
  /* should the job run in the background?*/
  if ((bg = (*argv[argc - 1] == '&')) != 0)
  {
    argv[--argc] = NULL;
  }
  return bg;
}

//Calls parseline
void
eval (char* cmdline)
{
  char* argv[MAXARGS];
  int bg = parseline (cmdline, argv); //holds if it is in the background or foreground
  if (argv[0] == NULL)
  {
    return; //Ignore empty lines
  }
  //If it is not a user command
  if (!builtin_cmd(argv)) 
  {
    sigset_t mask, prev;
    //Set mask
    sigemptyset (&mask);

    //Signal blockers
    sigaddset(&mask, SIGCHLD);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTSTP);

    sigprocmask (SIG_BLOCK, &mask, &prev);

    //Forks a process
    pid_t pid = fork();

    //If it was successful and we are in the child
    if (pid == 0)
    {

      //Set the process group ID so we can kill groups of processes
      setpgid (0, 0);
      sigprocmask (SIG_SETMASK, &prev, NULL);

      //Check to ensure the command entered is valid
      if (execve (argv[0], argv, environ) < 0) 
      {
        printf ("%s: Command not found\n", argv[0]);
        fflush(stdout);
        exit(0);
      }
    } 

    //If job is not in the background
    if (!bg) 
    {
      g_runningPid = pid;
      sigprocmask (SIG_SETMASK, &prev, NULL);
      waitfg(pid);
    } 
    else 
    {
      sigprocmask (SIG_SETMASK, &prev, NULL);
      printf("(%d) %s", pid, cmdline);
      fflush(stdout);
    }
  }

  return;
}

int
builtin_cmd (char** argv)
{
  //If user types 'quit', exit the shell
  if (!strcmp(argv[0], "quit")) 
  {
    exit (0);
  }

  //If user wants the job to be in the foreground
  if (!strcmp (argv[0], "fg"))
  {
    //See if theres currently a suspended job
    if (g_suspendedPid) 
    {
      //Un-suspend the job (make it runnning) and release the suspended job
      g_runningPid = g_suspendedPid; 
      g_suspendedPid = 0;

      //Sends the continue signal to the running process
      kill(-g_runningPid, SIGCONT); 

      //Waits for the process to finish
      waitfg(g_runningPid); 
    }
    return (1);
  }
  //Checks for extra trailing ampersands
  if (!strcmp (argv[0], "&"))
  {
    return (1);
  }
  //Ignore white space at the end//null commands
  if (!strcmp(argv[0], "")) 
  {
    return (1);
  }
  return (0);
}

void
waitfg(pid_t pid)
{
  //Create mask
  sigset_t mask;

  //empty mask set
  sigemptyset(&mask);

  //While job is running, wait for a sigchild to come in
  while (pid == g_runningPid) 
  {
    //Waits for a signal
    sigsuspend(&mask); 
  }
  return;
}

/*
 *******************************************************************************
 * SIGNAL HANDLERS
 *******************************************************************************
 */

/*
*  sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
*      a child job terminates (becomes a zombie), or stops because it
*      received a SIGSTOP or SIGTSTP signal. The handler reaps all
*      available zombie children, but doesn't wait for any other
*      currently running children to terminate.
*/
void
sigchld_handler (int sig)
{
    int status;
    pid_t pid; 
    //Reap children
    while ((pid = waitpid(-1, &status, WNOHANG|WUNTRACED)) > 0)
    {
      //If the child is stopped
      if (WIFSTOPPED(status)) 
      {
        if (pid == g_runningPid)
        {
          g_suspendedPid = g_runningPid;
          g_runningPid = 0;
          printf ("Job (%d) stopped by signal %d\n", pid, WSTOPSIG(status));
          fflush(stdout);
        }
      }
      //Checks if the child exited
      else if (WIFEXITED(status))
      {
        g_runningPid = 0;
      }
      //Checks for if the PID has a signal
      else if (WIFSIGNALED(status))
      {
        g_runningPid = 0;
        printf("Job (%d) terminated by signal %d\n", pid, WTERMSIG(status));
        fflush(stdout);
      }
    }
    return;
  }

/*
 *  sigint_handler - The kernel sends a SIGINT to the shell whenever the
 *     user types ctrl-c at the keyboard.  Catch it and send it along
 *     to the foreground job.
 */
void
sigint_handler (int sig)
{
  if (g_runningPid > 0)
  {
    //Send sigint to current running process
    kill(-g_runningPid, SIGINT); 
  }
  return; 
}

/*
 *  sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *      the user types ctrl-z at the keyboard. Catch it and suspend the
 *      foreground job by sending it a SIGTSTP.
 */
void
sigtstp_handler (int sig)
{
  //If there is a current process in the foreground
  if (g_runningPid > 0) 
  {
    //suspend the process currently in the foreground
    kill(-g_runningPid, SIGTSTP); 
  }
  return;
}

/*
 *******************************************************************************
 * HELPER ROUTINES
 *******************************************************************************
 */


/*
 * unix_error - unix-style error routine
 */
void
unix_error (char* msg)
{
  fprintf (stdout, "%s: %s\n", msg, strerror (errno));
  exit (1);
}

/*
*  app_error - application-style error routine
*/
void
app_error (char* msg)
{
  fprintf (stdout, "%s\n", msg);
  exit (1);
}

/*
*  Signal - wrapper for the sigaction function
*/
handler_t*
Signal (int signum, handler_t* handler)
{
  struct sigaction action, old_action;

  action.sa_handler = handler;
  sigemptyset (&action.sa_mask); /* block sigs of type being handled*/
  action.sa_flags = SA_RESTART;  /* restart syscalls if possible*/

  if (sigaction (signum, &action, &old_action) < 0)
    unix_error ("Signal error");
  return (old_action.sa_handler);
}

/*
*  sigquit_handler - The driver program can gracefully terminate the
*     child shell by sending it a SIGQUIT signal.
*/
void
sigquit_handler (int sig)
{
  printf ("Terminating after receipt of SIGQUIT signal\n");
  exit (1);
}
