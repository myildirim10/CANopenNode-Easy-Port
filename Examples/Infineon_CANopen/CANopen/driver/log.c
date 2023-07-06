#include "log.h"

#ifdef LOG_ENABLE
#include "stdio.h"
#include "CANopenHardware.h"
struct __FILE
{
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};
/* FILE is typedef’d in stdio.h. */
FILE __stdout;
int fputc(int ch, FILE *f)
{
    (void)*f;
    /* Your implementation of fputc(). */
    vLogTransmit(ch);
  return ch;
}
#endif /* LOG_ENABLE */
