#pragma once

#include <stdlib.h>

struct dynamic_array {
  size_t size;
  size_t capacity;
  void **arr;
};

struct
dynamic_array *darray_new(size_t);

struct
dynamic_array *darray_from(void **, size_t, size_t);

void _darray_expand(struct dynamic_array *);

void darray_set(struct dynamic_array *, size_t, void *);

void darray_insert(struct dynamic_array *, size_t, void *);

void *darray_get(struct dynamic_array *, size_t);

void darray_append(struct dynamic_array *, void *);

void darray_free(struct dynamic_array *);

void darray_foreach(struct dynamic_array *, void (*)(void *));

