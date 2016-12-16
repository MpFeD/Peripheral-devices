#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#define NBLED 2
#define NBBTN 1
char led[NBLED];
char btn[NBBTN];

int main()
{
   int i;
   int fd = open("/dev/module", O_RDWR);
   if (fd < 0) {
     printf("%d\n",errno);
     fprintf(stderr, "Erreur d'ouverture du pilote LED et Boutons\n");
     exit(1);
   }
   printf ("yy");
   for( i = 0; i < NBLED; i ++)
     led[i] = '0';
   write( fd, led, NBLED);
}

/*
 fflush(stdout);
   for( i = 0; i < NBLED; i ++)
      led[i] = '0';
   do { 
      led[0] = (led[0] == '0') ? '1' : '0';
      write( fd, led, NBLED);
      sleep( 1);
      read( fd, btn, NBBTN);
   } while (btn[0] == '1');
   return 0;
}
*/
