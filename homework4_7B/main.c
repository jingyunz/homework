#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define LINE_MAX 500
#define NAME_MAX 20
#define DEP_MAX 20
struct stuinfo
{
int id;
char name[NAME_MAX];
char dep[DEP_MAX];
int age;
}__attribute__((packed));

int readline(int fin,char *line,int maxlength)
{int i,stat;
for(i=0;i<maxlength;i++)
{
  stat=read(fin,(line+i),1);
  if( (*(line+i)=='\n')||stat==0)
   {
      *(line+i)='\0';
      break;
    }
}
return stat;
}

void csv2bin(int fin,int fout,struct stuinfo *stu_info)
{       
        char line[LINE_MAX];
        pid_t child;
        int rnt,i=1;
        readline(fin, line, LINE_MAX);
	while(readline(fin, line, LINE_MAX))
	{
	        child=fork();
               if(child==-1)
                {
                 printf("fork error!\n");
                 exit(1);
               }
               else if(child==0)
               {
                char *token = strtok(line, ",");
		stu_info->id = atoi(token);
       
		token = strtok(NULL, ",");
		strcpy(stu_info->name, token);

		token = strtok(NULL, ",");
		strcpy(stu_info->dep, token);

		token = strtok(NULL, ",");
		stu_info->age = atoi(token);

                write(fout,stu_info,sizeof(*stu_info));  
                break;
                 }
              else
              {
               wait(&rnt);
               printf("child_precess%d ended\n",i++);
                  }
                                             
	}
}


int main ()
{
        struct stuinfo *stu_info=(struct stuinfo *)malloc(sizeof(struct stuinfo));
        int fin,fout;
        fin=open("./input.csv",O_RDONLY);
        fout=open("./output",O_WRONLY);
	if(fin==-1)
	{
		printf("error!\n");
		return -1;
	}

	if(fout==-1)
	{
		printf("error!\n");
		return -1;
	}

       csv2bin(fin,fout,stu_info);

       close(fin);
       close(fout);
       return 0;
}
