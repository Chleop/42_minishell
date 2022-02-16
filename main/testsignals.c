#define NSIGMAX 5
#include <signal.h>
# include <stdio.h>
# include <unistd.h>

void set_default() 
{
    struct sigaction sa;

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    
}

void int_handler(int sig) 
{
    static int nsig = 0;

    if (nsig++ < NSIGMAX)
        printf(" C-c won’t kill me\n");
    else 
    { 
        printf(" unless you insist...\n");
        set_default();
    }
}

int main () 
{
    struct sigaction sa;

    sa.sa_handler = int_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    for(;;) { pause(); }
    fprintf(stderr, "bye\n");
    return 0;
}