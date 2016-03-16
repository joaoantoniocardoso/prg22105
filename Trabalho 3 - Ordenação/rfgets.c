/* This code was originally taken from comp.lang.c
 * news:pan.2005.11.28.12.14.54.651503@erinye.com
 * It has been fairly heavily modified.
 *
 * A bug/feature remains: malloc failures are not propagated.  The
 * feature is that only the part of the line for which there is enough
 * memory available is allocated.  The rest of the line is unavoidably lost.
 *
 * The better solution is to propagate any memory allocation failure all
 * the way back up to rfgets().  Then, the caller would be responsible
 * for calling feof and ferror to see whether EOF, or malloc failure or
 * input error caused the NULL return.
 */

/*
 * rfgets.c
 * dynamically allocating fgets
 * daniel.fischer at iitb.fraunhofer.de
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { RFGETS_CHUNK_SIZE = 32 };

static char *rfg(FILE *f, size_t n){
  char b[RFGETS_CHUNK_SIZE + 1], *const e = b + sizeof b - 2, *p;
  size_t x;
  /* store '\0' in the second-to-last character of b */
  *e = '\0';
  /* read into b */
  if (!fgets(b, sizeof b, f))
    return 0;
  /* check for an incomplete line */
  if (*e != '\0' && *e != '\n' && (p = rfg(f, n + (x = sizeof b - 1))))
    return memcpy(p - x, b, x);
  /* this is the end of the line (or EOF); allocate a buffer for the line */
  else if ((p = malloc(n + (x = strlen(b) + 1))))
    return memcpy(p + n, b, x);
  else
    return 0;
}

char *rfgets(FILE *f){
  return rfg(f, 0);
}

int main(void){
  char *line;
  for (; line = rfgets(stdin); free(line))
    printf(">>%s<<\n", line);
  if (!feof(stdin))
    puts("Error?");
  return 0;
}
