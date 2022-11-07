#ifndef SHAREDMEM_H
#define SHAREDMEM_H

#define IPC_RESULT_ERROR (-1)
#define SEM_PRODUCER "/myproducer"
#define SEM_CONSUMER "/myconsumer"

char *attach_mem_block(char *filename, int size);
bool detach_mem_block(char *block);

bool destroy_mem_block(char *filename);

#endif