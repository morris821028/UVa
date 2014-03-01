/* pcrypt.c */

#include <stdio.h>
#include <crypt.h>


void
pcrypt(char key[8], char salt[2], char ans[32])
{
  static char my_key[9];
  static char my_salt[3];
  static char *ret;

  bcopy(key, my_key, 8);
  bcopy(salt, my_salt, 2);
  my_key[8] = '\0';
  my_salt[2] = '\0';

  bzero(ans, 32);
  ret = crypt(key, salt);
  strcpy(ans, ret);
}

