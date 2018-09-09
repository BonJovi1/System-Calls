#include<stdio.h>
#include<sys/types.h> //mkdir, open (some UNIX), lseek
#include<stdlib.h>
#include<fcntl.h> //open
#include<unistd.h> // lseek, write, read, close
#include<sys/stat.h> //mkdir, open(some UNIX)

int main(int argc, char *argv[])
{
	int fd_read, fd_write; //file descriptors

	if(argc != 2)
	{
		printf("Usage: ./a.out [input filename] \n");
		return 0;
	}
	
	fd_read = open(argv[1], O_RDONLY);
	
	mkdir("./Assignment", 0700); //read,write,execute permissions to the folder
	fd_write = open("./Assignment/output.txt", O_CREAT | O_WRONLY, 0600);

	long long ret;
	ret = lseek (fd_read, 0, SEEK_END);

	long long i,k;
	char a[10000], b[10000];
	i=ret;

	for(i=ret;i>10000;i-=10000)
	{
		lseek(fd_read, i-10000, SEEK_SET);
		read(fd_read, &a, 10000);
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
		write(fd_write,&b,10000);

	}
	if(i!=0)
	{
		char c[i], d[i];
		lseek(fd_read,0,SEEK_SET);
		read(fd_read, &c, i);
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
		write(fd_write,&d,i);
	}
	close(fd_read);
	close(fd_write);
	
	return 0;
}
