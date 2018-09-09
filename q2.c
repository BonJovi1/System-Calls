#include<stdio.h>
#include<sys/types.h> // stat
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h> // stat
#include<sys/stat.h> // stat

int compare(long long fd_read1, long long fd_read2)
{
	long long ret;
	int ans;
	ans=0;
	ret = lseek (fd_read1, 0, SEEK_END);

	long long i,k,j;
	char a[10000], b[10000], f[10000];
	i=ret;

	for(i=ret;i>10000;i-=10000)
	{
		lseek(fd_read1, i-10000, SEEK_SET);
		read(fd_read1, &a, 10000);
		for(k=0;k<10000;k++)
		{
			//inversion
			if(a[k]>=97 && a[k]<=122)//small case alphabets
				a[k]-=32;
			else if(a[k]>=65 && a[k]<=90)//capital alphabets
				a[k]+=32;
			//reverse
			b[9999-k] = a[k];
		}
		read(fd_read2,&f,10000);
		for(j=0;j<10000;j++)
		{
			if(b[j]!=f[j])
			{
				ans=1;
				return ans;
			}
		}
	}

	if(i!=0)
	{
		char c[i], d[i], e[i];
		lseek(fd_read1,0,SEEK_SET);
		read(fd_read1, &c, i);
		for(k=0;k<i;k++)
		{
			//inversion
			if(c[k]>=97 && c[k]<=122)//small case alphabets
				c[k]-=32;
			else if(c[k]>=65 && c[k]<=90)//capital alphabets
				c[k]+=32;
			//reverse
			d[i-1-k] = c[k];
		}
		read(fd_read2,&e,i);
		for(j=0;j<i;j++)
		{
			if(d[j]!=e[j])
			{
				ans=1;
				break;
			}
		}
	}
	close(fd_read1);
	close(fd_read2);
	return ans;
	
}

void printit1()
{
	write(1,"User has read permission on file: No\n",37);
	write(1,"User has write permission on file: No\n",38);
	write(1,"User has execute permission on file: No\n",40);
	
	write(1,"Group has read permission on file: No\n",38);
	write(1,"Group has write permission on file: No\n",39);
	write(1,"Group has execute permission on file: No\n",41);
	
	write(1,"Others have read permission on file: No\n",40);
	write(1,"Others have write permission on file: No\n",41);
	write(1,"Others have execute permission on file: No\n",43);
}

void printit2()
{
	write(1,"User has read permission on directory: No\n",42);
	write(1,"User has write permission on directory: No\n",43);
	write(1,"User has execute permission on directory: No\n",45);
	
	write(1,"Group has read permission on directory: No\n",43);
	write(1,"Group has write permission on directory: No\n",44);
	write(1,"Group has execute permission on directory: No\n",46);
	
	write(1,"Others have read permission on directory: No\n",45);
	write(1,"Others have write permission on directory: No\n",46);
	write(1,"Others have execute permission on directory: No\n",48);
}

int main(int argc, char *argv[])
{
	struct stat dir;//for directory
	struct stat file;//for output.txt
	struct stat sym;//for symlink

	if(argc != 2)
	{
		printf("Usage: ./a.out [input filename] \n");
		return 0;
	}

	symlink("./Assignment/output.txt", "symlink");

	if(stat("./Assignment",&dir)==0)//0 means successful
		write(1,"Checking whether the directory has been created: Yes\n",53);//we can't use printf
	else
		write(1,"Checking whether the directory has been created: No\n",52);

	
	if(stat("./Assignment/output.txt",&file)==0)
		write(1,"Checking whether the file has been created: Yes\n",48);
	else
		write(1,"Checking whether the file has been created: No\n",47);

	
	if(stat("symlink",&sym)==0)
	{
		if(S_ISLNK(sym.st_mode)==0)
			write(1,"Checking whether the symlink has been created: Yes\n",51);
		else
			write(1,"Checking whether the symlink has been created: No\n",50);
	}
	else
		write(1,"Checking whether the symlink has been created: No\n",50);

	if(stat("./Assignment",&dir)==0 && stat("./Assignment/output.txt",&file)==0)
	{
		long long fd_read1, fd_read2; //file descriptors
		fd_read1 = open(argv[1],O_RDONLY);
		fd_read2 = open("./Assignment/output.txt",O_RDONLY);
		int flag;
		flag=compare(fd_read1, fd_read2);

		if(flag==0)
			write(1,"Checking whether file contents have been reversed and case-inverted: Yes\n",73);
		else if(flag==1)
			write(1,"Checking whether file contents have been reversed and case-inverted: No\n",72);
	}
	else
		write(1,"Checking whether file contents have been reversed and case-inverted: No\n",72);


	if(stat("./Assignment/output.txt",&file)==0)
	{
		if((file.st_mode & S_IRUSR) != 0)//sfile.st_mode & S_IRUSR
			write(1,"User has read permission on file: Yes\n",38);
		else
			write(1,"User has read permission on file: No\n",37);

		
		if((file.st_mode & S_IWUSR) != 0)
			write(1,"User has write permission on file: Yes\n",39);
		else
			write(1,"User has write permission on file: No\n",38);

		
		if((file.st_mode & S_IXUSR) != 0)
			write(1,"User has execute permission on file: Yes\n",41);
		else
			write(1,"User has execute permission on file: No\n",40);

		
		if((file.st_mode & S_IRGRP) != 0)
			write(1,"Group has read permission on file: Yes\n",39);
		else
			write(1,"Group has read permission on file: No\n",38);

		
		if((file.st_mode & S_IWGRP) != 0)
			write(1,"Group has write permission on file: Yes\n",40);
		else
			write(1,"Group has write permission on file: No\n",39);

		
		if((file.st_mode & S_IXGRP) != 0)
			write(1,"Group has execute permission on file: Yes\n",42);
		else
			write(1,"Group has execute permission on file: No\n",41);

		
		if((file.st_mode & S_IROTH) != 0)
			write(1,"Others have read permission on file: Yes\n",41);
		else
			write(1,"Others have read permission on file: No\n",40);

		if((file.st_mode & S_IWOTH) != 0)
			write(1,"Others have write permission on file: Yes\n",42);
		else
			write(1,"Others have write permission on file: No\n",41);

		if((file.st_mode & S_IXOTH) != 0)
			write(1,"Others have execute permission on file: Yes\n",44);
		else
			write(1,"Others have execute permission on file: No\n",43);
	}
	else
		printit1();

	if(stat("./Assignment",&dir)==0)
	{
		if((dir.st_mode & S_IRUSR) != 0)
			write(1,"User has read permission on directory: Yes\n",43);
		else
			write(1,"User has read permission on directory: No\n",42);

		if((dir.st_mode & S_IWUSR) != 0)
			write(1,"User has write permission on directory: Yes\n",44);
		else
			write(1,"User has write permission on directory: No\n",43);

		if((dir.st_mode & S_IXUSR) != 0)
			write(1,"User has execute permission on directory: Yes\n",46);
		else
			write(1,"User has execute permission on directory: No\n",45);

		if((dir.st_mode & S_IRGRP) != 0)
			write(1,"Group has read permission on directory: Yes\n",44);
		else
			write(1,"Group has read permission on directory: No\n",43);

		if((dir.st_mode & S_IWGRP) != 0)
			write(1,"Group has write permission on directory: Yes\n",45);
		else
			write(1,"Group has write permission on directory: No\n",44);

		if((dir.st_mode & S_IXGRP) != 0)
			write(1,"Group has execute permission on directory: Yes\n",47);
		else
			write(1,"Group has execute permission on directory: No\n",46);

		if((dir.st_mode & S_IROTH) != 0)
			write(1,"Others have read permission on directory: Yes\n",46);
		else
			write(1,"Others have read permission on directory: No\n",45);

		if((dir.st_mode & S_IWOTH) != 0)
			write(1,"Others have write permission on directory: Yes\n",47);
		else
			write(1,"Others have write permission on directory: No\n",46);

		if((dir.st_mode & S_IXOTH) != 0)
			write(1,"Others have execute permission on directory: Yes\n",49);
		else
			write(1,"Others have execute permission on directory: No\n",48);
	}
	else
		printit2();

	return 0;
}