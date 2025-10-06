#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void make_toks(char *s, char *tok[]) {
    int i = 0;
    char *p;
    p = strtok(s, " ");
    while (p != NULL) {
        tok[i++] = p;
        p = strtok(NULL, " ");
    }
    tok[i] = NULL;
}

void search(char *fn,char op,char *pattern)
{
int fh,count=0,i=0,j=0;
char buff[255],c,*p;
fh=open(fn,O_RDONLY);
if(fh==-1)
{
printf("file %s not found\n",fn);
return;

}
switch(op)
{
case 'f':
	while(read(fh,&c,1))
	{
	buff[j++]=c;
	if(c=='\n')
	{
	buff[j]='\0';
	j=0;
	i++;
	if(strstr(buff,pattern))
	{
	printf("%d : %s",i,buff);
	break;
	}
	}
	}
	break;
	
case 'c':
	while(read(fh,&c,1))
	{
	buff[j++]=c;
	if(c=='\n')
	{
	buff[j]='\0';
	j=0;
	p=buff;
	while(p=strstr(p,pattern))
	{
	count++;
	p++;
	}
	}
	}
	printf("total no. of occurrence = %d\n",count);
	break;
	
	
case 'a': 
	while(read(fh,&c,1))
	{
	buff[j++]=c;
	if(c=='\n')
	{
	buff[j]='\0';
	j=0;
	i++;
	if(strstr(buff,pattern))
	printf("%d : %s",i,buff);
	}
	
	}
}
close(fh);
}

int main()
{
    char buff[80],*args[10];
    int pid;
    while(1)
    {
        printf("Myshell$");
        fflush(stdin);
        fgets(buff,80,stdin);
        buff[strlen(buff)-1]='\0';
        make_toks(buff,args);
        if(strcmp(args[0],"search")==0)
            search(args[3],args[1][0],args[2]);
        else
        {
            pid=fork();
            if(pid>0)
                wait(NULL);
            else
            {
                if((execvp(args[0],args)==-1))
                    printf("Bad Command\n");
            }
        }
    }
    return 0;
    }


