#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int comparetime=0;

int frobcmp(char const *a, char const *b)
{
  comparetime++;
  int al,bl=0;
  for (int i=0;a[i]!=' ';i++)
    al++;
  for (int i=0;b[i]!=' ';i++)
    bl++;
  int len=0;
  if (bl<al)
    len=bl;
  else
    len=al;

  for (int n=0;n<len;n++)
    {
      char cha=a[n]^42;
      char chb=b[n]^42;

      if (cha>chb)
	return 1;
      else if (cha<chb)
	return -1;
      else
	continue;
    }
  if (len==al && len==bl)
    return 0;
  else if (al>len)
    return 1;
  else
    return -1;

}


int cmp(const void*a, const void*b)
{
  char* a1=*(char**)a;
  char* b1=*(char**)b;
  int k=frobcmp(a1,b1);
  return k;
}

int main(int argc, char **argv)
{
  if (argc!=1)
    {
      fprintf(stderr,"input error");
      exit(1);
    }
  int length = 1;
  
  struct stat file;
  if (fstat(0,&file) == -1)
    {
      fprintf(stderr,"Error when reading file");
      exit(1);
    }


  long fsize = file.st_size;
  if (S_ISREG(file.st_mode) && fsize >0)
    {
      length = fsize;
    }

  char ch;
  int n=1;
  int wordnum =0;
  if (length <= 1)
    length = 100;
  int state = read(0,&ch,1);
  if (state<0)
    {
      fprintf(stderr,"error when reading file");
      exit(1);
    }
  if (state== 0)
    {
      fprintf(stderr,"Comparisons: %d\n",comparetime);
     
      exit(0);
    }

  if (ch!=' ')
    wordnum=1;

  char* buffer =malloc(sizeof(char)*length);

                                                                              
  if (buffer==0)                                                               
    {                                                                          
      fprintf(stderr,"memory allocating error");                               
      exit(1);                                             
    }                                                                          
  
  while (state == 1)
    {
      if (n>length-2)
	{
	  length+=4096;
	  buffer =(char*)realloc(buffer,length*sizeof(char));
	  if(buffer==NULL)
	    {
	      fprintf(stderr,"memory allocating error");
	      exit(1);
	    }
       
	}

      if (ch==' '&& n==1 && wordnum==0)
	{
	  // printf("executed1\n");
	  state = read(0,&ch,1);
	  if (state<0)
	    {
	      fprintf(stderr,"error when reading file");
	      exit(1);

	    }
	  continue;
	}
      if (ch==' '&& n>1 && buffer[n-2]==' ')
	{ //printf("executed2\n");
	  state= read(0,&ch,1);
	  if (state<0)
	    {
	      fprintf(stderr,"error when reading file");
	      exit(1);

	    }

	  continue;
	}
      if (ch==' '&&n>1)
	{
	  //printf("execute3\n");
	  if (wordnum==0)
	    wordnum=1;
	  wordnum++;

	  buffer[n-1]=ch;
	  state = read(0,&ch,1);
	  if (state<0)
	    {
	      fprintf(stderr,"error when reading file");
	      exit(1);

	    }
	}
      else
	{
	  //printf("exectued4\n");
	  buffer[n-1]=ch;
	  state=read(0,&ch,1);
	  if (state<0)
	    {
	      fprintf(stderr,"error when reading file\n");
	      exit(1);

	    }

	}
      n++;
    }
  
  if (n>1&&buffer[n-2]==' ')
    {
      wordnum--;
      n--;
    }
  else
    buffer[n-1]=' ';
  
  /*    
  for (int i=0; i<n; i++)
    {
      write(1,&buffer[i],1);
    }
  putchar('\n');
  */ 
  char buff[n];
  for (int i=0; i<n; i++)
    buff[i]=buffer[i];
  char **word = malloc(wordnum*(1+sizeof(char*)));
  int numletter=100;
  int mark=0;
  /*
  for (int i=0; i<n; i++)
    {
      write(1,&buff[i],1);
    }
  putchar('\n');
  */
  for (int i=0;i<wordnum && mark<n;i++)
    {
      word[i]=malloc(numletter);
      int k=0;
      while (buff[mark]!=' '&& mark<n)
	{
	  if (k>numletter-3)
	    {
	      numletter*=2;
	     
	      word[i]=(char*)realloc(word[i],numletter*sizeof(char));
	      if (word[i]==0)
		{
		  fprintf(stderr,"memory allocating error");
		  exit(1);
		}
	    }
  
	  word[i][k]=buff[mark];
	  k++;
	  mark++;
	  if (mark==n-1)
	    break;
	}
      word[i][k]=' ';
      mark++;
	
    }
  /*
  putchar('\n');
  for (int i=0; i<n; i++)
    {
      write(1,&buff[i],1);
    }
    putchar('\n');*/
  qsort(word,wordnum,sizeof(char*),cmp);
  //printf("%d\n",mark);
  for (int i=0;i<wordnum;i++)
    {
      int j=0;
      while(word[i][j]!=' ')
	{
	  // putchar(word[i][j]);
	  write(1,&word[i][j],1);
	  j++;
	}
      char tmp = ' ';
      write(1,&tmp,1);
    }
  /*
      for (int i=0;i<wordnum;i++)
    {
      free (word[i]);
      }*/
    free (word);
    free (buffer);
  fprintf(stderr,"Comparison: %d\n",comparetime);
  exit(0);
    
}
