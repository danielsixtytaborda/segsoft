#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
gcc writer0.c -o writer0
./writer0
gcc stack.c -o stack
gcc -fno-stack-protector -D_FORTIFY_SOURCE=0 -W -no-pie stack.c -z execstack -o stack
objdumbp -d stack
./stack
echo $?

*/

void cpy(char *d, char *s, int n)
{
  while (n--!=0) *d++=*s++;
}

void foo(char *str, int s)
{
    char buffer[32];

    printf("buffer AT %lx\n",(long)&buffer+64);
    for(int i = 0; i<8; i++)
      printf("%d : %lx\n", i, ((long*)buffer)[i]);

    cpy(buffer, str, s); /* buffer overflow here */
    
}

int main(int argc, char **argv)
{

    char str[400];
    FILE *badfile;
    int retval = 0;
	
    badfile = fopen("smasher", "r");
    int s = fread(str, sizeof(char), 400, badfile);
    foo(str,s);
    retval = 0;  // write a virus that changes the retval to 66

 /*   char st[8];
    
    st[0]='H';
    st[1]='A';
    st[2]='C';
    st[3]='K';
    st[4]='E';
    st[5]='D';
    st[6]='\n';
    st[7]=0;


    ((int (*)(const char *, ...))(0x7fff676028ec))(st);
    
*/

    
    return retval;
}

/* utils to inspect frame of foo */

   /* 
    for(int i = 0; i<sizeof(buffer); i++)
      buffer[i]=(char)255;
   */
   /* 
    printf("buffer AT %lx\n",(long)&buffer);
    for(int i = 0; i<8; i++)
      printf("%d : %lx\n", i, ((long*)buffer)[i]);
   */ 

    /*
    for(int i = 0; i<8; i++)
      printf("%d : %lx\n", i, ((long*)buffer)[i]);
    */
