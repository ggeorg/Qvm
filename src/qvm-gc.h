#ifndef QVM_GC_H
#define QVM_GC_H

void *q_gc_init();
void *q_gc_malloc(size_t size);
void *q_gc_realloc(void *ptr, size_t size);

#endif
