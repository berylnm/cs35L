//
//  main.c
//  tr2b.c
//
//  Created by Binyi Wu on 5/9/16.
//  Copyright © 2016 Binyi Wu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int checkdup(const char *a);

int main(int argc, const char *argv[])
{

  if (argc!=3)
    {
      fprintf(stderr,"wrong parameters\n");
      exit(1);
    }

  int i=0;
  while (argv[1][i]!='\0')
    i++;

  int j=0;
  while (argv[2][j]!='\0')
    j++;

  if (i!=j)
    {
      fprintf(stderr,"the length of operands is not the same.\n");
      exit(1);
    }

  if (checkdup(argv[1])==0)
    {
      fprintf(stderr,"there're duplicate bytes.\n");
      exit(1);
    }

  int a=getchar();
  while (a!=EOF)
    {   int k=0;
      for (k=0;k<i;k++)
	{
	  if (a==argv[1][k])
	    {  putchar(argv[2][k]);
	      break;
	    }
	}
      if (k==i)
	putchar(a);

      a=getchar();
    }
  exit(0);

}

int checkdup(const char *a)
{
  int i=0;
  while (a[i]!=0)
    i++;


  if (i==0)
    return 1;
  else
    {   char b[i];
      int j=0;
      while (j<i)
	{
	  b[j]=a[j];
	  j++;
	}

      for (int k=0;k<i-1;k++)
	{
	  for (j=k+1;j<i;j++)
	    {
	      if (a[k]==b[j])
		{
		  return 0;
		}
	    }
	}
    }
  return 1;
}
