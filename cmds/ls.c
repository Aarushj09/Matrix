#include "../utils/libraries.h"

int cmd_ls(int argc, char **argv)
{
    int flag_l=0, flag_a=0;
    int opt;

    while((opt = getopt(argc, argv, "-al")) != -1 && opt !=1) {
        switch (opt) {
            case 'l':
                flag_l = 1;
                break;
            case 'a':
                flag_a = 1;
                break;
            default:
                return 0;
        }
    }
    if(argc==optind && opt != 1){
        display_dir(".",flag_l,flag_a);
        optind = 1;
        return 0;
    }
    optind = 1;
    int dir_count=0;
    char **dir_sorted = (char**)(malloc(100*(sizeof(char*))));
    for(int x=1;x<argc;x++)
    {
        if(argv[x][0]!='-')
        {
            if(file_dir_exists(argv[x])){
                dir_sorted[dir_count] = argv[x];
                dir_count++;
            }
        }
    }
    //sort
    for(int x=0;x<dir_count;x++)
    {
        for(int y=0;y<dir_count-1-x;y++)
        {
            if(strcmp(dir_sorted[y],dir_sorted[y+1])>0)
            {
                // swap strings
                char *temp = NULL;
                temp=dir_sorted[y];
                dir_sorted[y]=dir_sorted[y+1];
                dir_sorted[y+1]=temp;
            }
        }
    }
    //////////////////////////////////////

    for(int x=0;x<dir_count;x++){
        if(file_exists(dir_sorted[x])) {
            if (flag_l) {
                DIR *dir = opendir(".");
                struct dirent *file_subdir;
                while ((file_subdir = readdir(dir)) != NULL) {
                    if (strcmp(file_subdir->d_name, dir_sorted[x]) == 0) {
                        handle_l(".", file_subdir);
                        break;
                    }
                }
                closedir(dir);
            } else {
                printf("%s\n", dir_sorted[x]);
            }
        }
    }
    for(int x=0;x<dir_count;x++){
        if(dir_exists(dir_sorted[x])){
            if(dir_count>1)
                printf("%s:\n",dir_sorted[x]);
            display_dir(dir_sorted[x],flag_l,flag_a);
        }
    }
    return 1;
}

void display_dir(char *s, int flag_l, int flag_a)
{
    if(flag_l){
        int total=0;
        DIR *dir = opendir(s);
        struct dirent *file_subdir;
        while((file_subdir = readdir(dir))!= NULL){
            if(!flag_a && file_subdir->d_name[0]=='.')
                continue;
            struct stat st;
            char path[MAX_PATH_SIZE];
            sprintf(path,"%s/%s",s,file_subdir->d_name);
            if(lstat(path,&st)<0){
                perror("lstat"); return;
            }
            total+=(int)(st.st_blocks)/2;
        }
        printf("total %d\n",total);
        closedir(dir);
    }
    DIR *dir = opendir(s);
    struct dirent *file_subdir;
    while((file_subdir = readdir(dir))!= NULL){
        handle_flags(s,file_subdir,flag_l,flag_a);
    }
    closedir(dir);
}

void handle_flags(char* dir,struct dirent *file_subdir, int flag_l, int flag_a)
{
    if(flag_a==0 && file_subdir->d_name[0]=='.')
        return;
    if(flag_l)
        handle_l(dir,file_subdir);
    else
        printf("%s\n",file_subdir->d_name);
}

void handle_l(char* dir,struct dirent *file_subdir)
{
    struct stat data;
    char path[MAX_PATH_SIZE];
    sprintf(path, "%s/%s", dir, file_subdir->d_name);
    if(stat(path, &data) == -1) {
        perror("stat");
        return;
    }
    if(S_ISDIR(data.st_mode)) printf("d");
    else if(S_ISREG(data.st_mode)) printf("-");

    printf((data.st_mode & S_IRUSR) ? "r" : "-");
    printf((data.st_mode & S_IWUSR) ? "w" : "-");
    printf((data.st_mode & S_IXUSR) ? "x" : "-");
    printf((data.st_mode & S_IRGRP) ? "r" : "-");
    printf((data.st_mode & S_IWGRP) ? "w" : "-");
    printf((data.st_mode & S_IXGRP) ? "x" : "-");
    printf((data.st_mode & S_IROTH) ? "r" : "-");
    printf((data.st_mode & S_IWOTH) ? "w" : "-");
    printf((data.st_mode & S_IXOTH) ? "x " : "- ");
    printf("%li ", data.st_nlink);

    struct passwd *pw;
    struct group *gid;
    pw = getpwuid(data.st_uid);
    if(pw == NULL) {
        perror("getpwuid");
        printf("%d ", data.st_uid);
    }else {
        printf("%s ", pw->pw_name);
    }
    gid = getgrgid(data.st_gid);
    if(gid == NULL) {
        perror("getpwuid");
        printf("%d ", data.st_gid);
    }else  {
        printf("%s ", gid->gr_name);
    }

    printf("%ld ",(long)data.st_size);

    struct tm *tm;
    char last_modified[200];
    time_t t = data.st_mtime;
    tm = localtime(&t);
    if(tm == NULL) {
        perror("localtime");
        return;
    }
    time_t current_time = time(0);
    if(current_time-t<15780000)
        strftime(last_modified, sizeof(last_modified), "%b %d %R", tm);
    else
        strftime(last_modified, sizeof(last_modified), "%b %d %Y", tm);
    printf("%s ", last_modified);

    printf("%s\n", file_subdir->d_name);
}


int file_dir_exists(char *path)
{
    if(!file_exists(path) && !dir_exists(path)){
        fprintf(stderr,"ls: cannot access '%s'\n",path);
        fflush(stderr);
        return 0;
    }
    return 1;
}
int file_exists(char *path)
{
    FILE *f = fopen(path,"r+");
    if(f==NULL)
        return 0;
    fclose(f);
    return 1;
}
int dir_exists(char *path)
{
    DIR *d = opendir(path);
    if(d==NULL)
        return 0;
    closedir(d);
    return 1;
}