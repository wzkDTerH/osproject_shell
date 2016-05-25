#ifndef __ERR_H_
#define __ERR_H_

void Err(char errword[])
{
	fprintf(stderr, "%s: %s\n",errword,strerror(errno));
	exit(1);
}
#endif
