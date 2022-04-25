#include "utils/libraries.h"

int main()
{
    current_dir = malloc(MAX_PATH_SIZE*sizeof (char));
    history_path = malloc(MAX_PATH_SIZE*sizeof (char));
    format = malloc(MAX_VAR_NAME*sizeof (char));
    system_name = malloc(MAX_VAR_NAME*sizeof (char));
    history = calloc(MAX_HISTORY,sizeof(char *));
    char *user_name = getlogin();   //gets the username
    gethostname(system_name,MAX_VAR_NAME);  // gets the system name
    init_process_list();

    sprintf(history_path,"%s/history.txt",getcwd(NULL,0));
    sprintf(format,"<%s@%s:",user_name,system_name);    // format contains "<username@systemname:"
    home_dir = getcwd(NULL,0);
    current_dir = getcwd(NULL,0);
    prev_dir = NULL;
    load_history();
    shell_grpid = getpgid(getpid());

    signal(SIGCHLD,process_signal);
    signal(SIGINT,ctrlc);
    signal(SIGTSTP,ctrlz);

    while(1)
    {
        fflush(stdout);
        fg_running.pid = -1;
        prompt();
        char *input = NULL;
        size_t sz = MAX_INPUT_SIZE;
        ssize_t flag1 = getline(&input,&sz,stdin);

        if(input == NULL)
            break;
        save_history();
        if(flag1 == -1){
            break;
        }
        int flag = break_input(input);
        if(flag==-1)
            break;
    }


    save_history();
    free(system_name);
    free(current_dir);
    free(format);
    free(history_path);
    for(int x=0;x<MAX_HISTORY;x++)
        if(history[x]!=NULL)
            free(history[x]);
    free(history);
    return 0;
}
