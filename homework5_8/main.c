#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h> 

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
{
	int i,stat=0;
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

void bincat()  
{  
    int fp,size; 
    if((fp = open("./output",O_RDONLY)) < 0 )  
    {  
        printf("open file error \n");  
        exit(1); 
    } 
    struct stat st;
    fstat(fp,&st); 
    void *point=mmap(0,st.st_size,PROT_READ, MAP_SHARED, fp,size);  
    for(size=0;size<st.st_size;size+=sizeof(struct stuinfo))
    {
    	struct stuinfo *stu_info = (struct stuinfo *)(point+size);
    	printf("%d,%s,%s,%d\n",stu_info->id,stu_info->name,stu_info->dep,stu_info->age);  //将文件中的内容输出  
    }
}  

void childread(int rdfd,int wrfd)
{
	char line[LINE_MAX];
	struct stuinfo *stu_info=(struct stuinfo *)malloc(sizeof(struct stuinfo));
	readline(rdfd,line,LINE_MAX);
	char *token = strtok(line, ",");
	stu_info->id = atoi(token);

	token = strtok(NULL, ",");
	strcpy(stu_info->name, token);

	token = strtok(NULL, ",");
	strcpy(stu_info->dep, token);

	token = strtok(NULL, ",");
	stu_info->age = atoi(token);

	write(wrfd,stu_info,sizeof(*stu_info));  
}


void csv2bin()
{       
	int pipe1[2];
	char line[LINE_MAX];
	pid_t child;
	int rnt,i=1;
	int fin,fout;
	fin=open("./input.csv",O_RDONLY);
	fout=open("./output",O_WRONLY);
	if(fin==-1)
	{
		printf("error!\n");
		exit(1);
	}

	if(fout==-1)
	{
		printf("error!\n");
		exit(1);
	}

	readline(fin, line, LINE_MAX);
	do
	{

		if(pipe(pipe1)) 
		{
			printf("pipe1 error!\n");
			exit(1);
		}

		child=fork();
		if(child==-1)
		{
			printf("fork error!\n");
			exit(1);
		}
		else if(child==0)
		{   
			close(pipe1[1]);              
			sleep(1);
			childread(pipe1[0],fout);
			_exit(0);
		}
		else
		{
			close(pipe1[0]);               
			if(write(pipe1[1],line,sizeof(line)) != -1)
			{
				printf("Parent write over!\n");
			}
			else
			{
				printf("Write failed!\n");
				exit(1);
			}

			waitpid(child, NULL, 0);
			printf("child_precess%d ended\n",i++);
		}
	}
	while( readline(fin, line, LINE_MAX) );

	close(fin);
	close(fout);
}


int main ()
{       
	csv2bin();
	bincat();
	return 0;
}

