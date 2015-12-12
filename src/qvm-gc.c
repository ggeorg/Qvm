#include <stdlib.h>
#include <stdio.h>
#include <gc.h>

#include "qvm-gc.h"

void *q_gc_init() {
	GC_INIT();
}

void *q_gc_malloc(size_t size) {
	//printf("Heap size = %zu\n", GC_get_heap_size());
	return GC_MALLOC(size);
}

void *q_gc_realloc(void *ptr, size_t size) {
	//printf("Heap size = %zu\n", GC_get_heap_size());
	return GC_REALLOC(ptr, size);
}
