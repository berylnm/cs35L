//
//  main.c
//  sfrob
//
//  Created by Binyi Wu on 4/27/16.
//  Copyright © 2016 Binyi Wu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int cmp(const void*a, const void*b);
int compare(char const *a,char const *b);
int frobcmp(char const *a, char const *b);

int main(int argc, char **argv)
{
  if (argc!=1)
    {
      fprintf(stderr,"input error");
      exit(1);
    }

  int length = 100;
  char* buffer =malloc(length*sizeof(char));
  if (buffer==0)
    {
      fprintf(stderr,"memory allocating error");
      exit(1);
    }

  char ch=getchar();
  int n=1;
  int wordnum=0;
  if (ch==EOF&&errno==0)
    exit(0);
  if (ch!=' ')
    wordnum=1;
  while (ch!= EOF)
    {
      if (n==length-1)
	{
	  length*=2;
	  buffer=realloc(buffer,length*sizeof(char));
	  if(buffer==NULL)
	    {
	      fprintf(stderr,"memory allocating error");
	      exit(1);
	    }
	}
 
      if (ch==' '&& n==1 && wordnum==0)
	{       ch=getchar();
	        continue;
	}
      if (ch==' '&&n>1&&buffer[n-2]==' ')
	{      ch=getchar();
	  continue;
	}
      if (ch==' '&&n>1)
	{
	  if (wordnum==0)
	    wordnum=1;
	  wordnum++;
	  buffer[n-1]=ch;
	  ch=getchar();
	}
     else
      {
	  buffer[n-1]=ch;
	  ch=getchar();
       }
      n++;
    }
  if (n>1&&buffer[n-2]==' ')
    {  wordnum--;
      n--;
    }
  else
    buffer[n-1]=' ';
  //printf("%d",wordnum);
   
  /*     for (int i=0;i<n;i++)
     putchar(buffer[i]);
  */
  //    buffer="*~BO *{_CIA *hXE]D *LER #@_GZY #E\\OX #^BO #FKPS #NEM\4";
  //    int wordnum=9;
  //    int n=sizeof(buffer);
  //

  if (errno!=0)
    {
      fprintf(stderr,"input error");
      exit(1);
    }
  
  char** word=malloc(wordnum*sizeof(char *));
  if (word==0)
    {
      fprintf(stderr,"memory allocating error");
      exit(1);
    }

  int mark=0;

  for (int i=0;i<wordnum;i++)
    {
      int wordl=100;
      word[i]=malloc(sizeof(char)*wordl);

      if (word[i]==0)
	{
	  fprintf(stderr,"memory allocating error");
	  exit(1);
	}

      int k=0;
      while(buffer[mark]!=' ')
	{
	  word[i][k]=buffer[mark];
	  //  putchar(word[i][k]);
	  if (k+2==wordl)
	    {
	      wordl*=2;
	      word[i]=realloc(word[i],sizeof(char)*wordl);
	      if (word[i]==0)
		{
		  fprintf(stderr,"memory allocating error");
		  exit(1);
		}
	    }
	  k++;
	  if (mark==n-2)
	    break;
	  else
	    mark++;

	}
      if (word[i][k-1]!=' ')
      word[i][k]=' ';
      mark++;
    }
  /*for (int i=0;i<wordnum;i++)
     {
     int j=0;
     while(word[i][j]!='\0')
     {    putchar(word[i][j]);
     j++;
     }
     }
  */

  // qsort(word,wordnum,sizeof(char*),cmp);
  for (int i=0;i<wordnum;i++)
    {
      int j=0;
      while(word[i][j]!=' ')
	{    putchar(word[i][j]);
	  j++;
	}
      putchar(' ');
    }

  for (int i=0;i<wordnum;i++)
    {
      free (word[i]);
    }
  free (word);
  free (buffer);
  exit(0);
}

/*
 int frobcmp(char const *a, char const *b)
 {
 return cmp(a,b);
 }
 
 int cmp(const void*a, const void*b)
 {
 return compare((char*)a,(char*)b);
 
 }
 //suppose a and b have the same size
 int compare(char *a,char *b)
 {
 
 for (int n=0;n<sizeof(a);n++)
 {    if (((*(a+n))^00101010)<((*(b+n))^00101010))
 return -1;
 else if (((*(a+n))^00101010)>((*(b+n))^00101010))
 return 1;
 }
 return 0;
 
 }
*/
/*
 int compare(char const *a, char const *b)
 {
 for (int n=0;n<sizeof(a);n++)
 {
 char cha=a[n]^00101010;
 char chb=b[n]^00101010;
 if (cha<chb)
 return -1;
 else if (cha>chb)
 return 1;
 }
 return 0;
 }*/

int frobcmp(char const *a, char const *b)
{
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
