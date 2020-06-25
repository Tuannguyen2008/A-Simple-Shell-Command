#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int command_cd(char *input);
char *get_input();
char **get_parse(char *input);
int new_process(char **input);
int command_dir(char *input[]);
int command_pause(char *input);
int command_environ();
int command_help();
int command_echo(char *input[]);
int redirection(int status,char *inputfile1, char *outputfile2);

extern int errno;
extern char **environ;

int main(){
    char *input;
    char *currentDir;
    char **argument;
    //int dirSize = 1000;

    int sizeOfArgument = sizeof(argument)/ sizeof(argument[0]);

    while(1){  // run until user hit quit
         printf("%s", getenv("PWD"));
         char cwd[20];
         getcwd(cwd,sizeof(cwd));
         printf("/%s ",cwd); //print current directory
         input = get_input();
         argument = get_parse(input);

         
                if(strncmp(argument[0] , "cd", 2) == 0){
                    command_cd(argument[1]);
                    //printf("%s",argument[1]);
                    //strcat(argument[1],getenv("PWD"));
                }       
                else if(strncmp(argument[0], "dir",3) == 0){
                    command_dir(argument);
                }
                else if(strncmp(argument[0] , "clear", 5) == 0){
                    printf("\033[H\033[2J");
                }
                else if(strncmp(argument[0] , "pause", 5) == 0){
                    command_pause(argument[1]);
                }
                else if(strncmp(argument[0] , "environ", 7) == 0){
                    command_environ();
                }
                else if(strncmp(argument[0] , "exit", 4) == 0){
                    printf("Shell is exit\n");
                    break;
                }
                else if(strncmp(argument[0] , "help", 4) == 0){
                    command_help();
                }
                else if(strncmp(argument[0] , "echo", 4) == 0){
                    command_echo(argument);
                }
        }
}

//change current directory
int command_cd(char *input){
        printf("In command Cd\n");
        char *currentpath= getenv("PWD");
        /* if(chdir(input[1]) == -1){
            printf("Cannot change current directory\n");
            return EXIT_FAILURE;}

        //printf("new cd: %s",input);
        for (int i = 0; input[1] != NULL; i ++){
               path = getcwd(path,100);
               printf("path: %s",path);
               chdir(input[1]);
            }*/
        //printf("input: %s",input);
       // printf(getenv("PWD"));

        if(chdir(input) == 0){ // user enter cd <namedir>
                
                printf("Had sucessful change home directory to / %s\n", input);
               // currentpath= getenv("PWD");
                //printf("New path: %s / %s \n", currentpath,input);
                return EXIT_SUCCESS;
		}
        if(input == NULL){ // user enter cd with no argument
                //char *currentpath= getenv("PWD");
                printf("current path: %s \n", currentpath);
                //char *currentpath2= getenv("PATH");
                //printf("current path2: %s \n", currentpath2);
                return EXIT_SUCCESS;
        }
		else {    // print cannot change current directory
           perror(input);
           return EXIT_FAILURE;  
		}
    return 0; //successful change current directory*/
}

//read user command input can store in a buffer
char *get_input(){

	int buffer_size = 1000;  //initiated buffer size to 1000
    int character; //store the character that user input

	int position = 0; //the position of character

	char *input = malloc(sizeof(char)*buffer_size); //allocate the buffer

	while(1){

		character = getchar(); //get character
		if(character == EOF || character == '\n'){  //get the character till end of file or end of line
			input[position] = '\0'; // get input position until end of string
			//putchar(input); // put character to outout
			return input;
		}
		else{
			input[position] = character; //if input position equal character
		}
		position++; //increment position

	}
        free(input); //free input after done using

}

//parse user input into args which separated by " " space
char **get_parse(char *input){
    char **split_line;
    char *token;
    int sizeOfLine = 100;
    int position = 0;
    split_line = malloc(sizeof(char *) * sizeOfLine); // get the size of line

    token = strtok(input, " "); // use strtok that take input and delimiter to split string into token

    while(token != NULL){ // token is not end of line
        split_line[position++] = token; //increment the position of line
        token = strtok(NULL, " "); //split line into token use when user type cd > << &

    }
   /* printf("here0=%s\n", split_line[0]);
    printf("here1=%s\n", split_line[1]);
    printf("position: %d",position);*/
    split_line[position] = NULL; //split line until the end of string
    return split_line;
}

int new_process(char **input){
    pid_t processID; // set up process id

    processID = fork();  // call fork to create new process
    if (processID < 0){
        fprintf(stderr, "Process can not be created");
    }
    else if (processID == 0){ // create new child process
        execvp(input[0], input);  // execvp get full path name of command and the command
    }
    else{   //parent can run after child process has finished
        int status = 0; // mean wait for any child process.
        wait(&status);
    }
    return 1;
}
int command_dir(char *input[]){
    printf("In dir command\n");
    DIR *dir;
    struct dirent *s;
    char *dirname;

    FILE *outfile;
    char *file;

    
    //char file[1000]

    //printf("input1: %s",input[1]);
    //printf("input2 : %s",input[2]);
    
    //input[2];
    //if first direct is null
    if(input[1] == NULL || input[1][0] == '>'){
        dirname = ".";
    }

    if(input[1][0] == '>' && input[2] != NULL){
            printf("\nin this command\n");
            
                if(input[2] == s->d_name){
                    outfile = fopen(input[2],"w");
                     fprintf(outfile, "%s", s ->d_name);
                     //printf("file: %s", input[2]);
                    
        }
    }
         
                

    else{
        dirname = input[1];
    }
    dir = opendir(dirname);
       while((s = readdir(dir)) != NULL){
            
            printf("%s\n",s ->d_name);
        }
    
    return 0;
}
int command_pause(char *input){
    printf("Hit enter to continues");
    getchar();

    return 0;
}

int command_environ(){
    
    int i = 0;
    while(1){
        if(environ[i] != NULL ){
             printf("%s\n",environ[i]);
             i++;}
        else{
            break;
        }}
    return 0;
}
int command_help(){

    FILE *namefile;
    //char ch[1000];
    int ch= 1000; // number of character to read in file
    namefile = fopen("help.txt","r"); // open file to read

    if(namefile == NULL){ 
        printf("file cannot open to read");
    }
    /*
    while( fscanf(namefile, "%s", ch) != EOF) {  // scanf pass in name of file, string to read, size of string
            if(ch == "\n"){
             fprintf(stdout, "%s",ch); // write to console
            }
        
    }*/

    while ((ch = getc(namefile)) != EOF) // get each character in file until end of file
        putchar(ch); // print each character to screen
        printf("\n");
    return 0;
}


int redirection(int status,char *inputfile1, char *outputfile2){

    pid_t newProcess;
    //int sizeinput = 1000;

    newProcess = fork();
        if(newProcess < 0){
            printf("Fork cannot create child process");
        }
        else if (newProcess == 0){
                if(status == 0){ // input redirect
                    int inputfile = open(inputfile1, O_RDONLY); // open file descriptor to read input
                    dup2(inputfile, 0); //duplicate file descriptor
                    close(inputfile);
                }
                else if (status == 1){ // output redirect
                    int outputfile = open(outputfile2,O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXG|S_IRWXO); //// open file descriptor to write output
                    dup2(outputfile, 1); 
                    close(outputfile);
                } 
                else if (status == 2){ // append output 
                    int appendfile = open(outputfile2,O_WRONLY|O_CREAT|O_APPEND,S_IRWXU|S_IRWXG|S_IRWXO);
                    dup2(appendfile,1);
                    close(appendfile);
               }
        }
        else{
            int status = 0; 
            wait(&status);  // wait for child process to finish
        }

}
// echo back user input
int command_echo(char *input[]){  

   int i = 1;
   while(1){
         if(input[i] != NULL){   
            printf("%s\t",input[i]);
            i++;
    }
        else {
             break;
    }
}
    printf("\n");

    return 0;
}