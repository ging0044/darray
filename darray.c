#include <stdio.h>
#include <string.h>
#include "darray.h"

struct
dynamic_array *darray_new(size_t cap) {
  struct dynamic_array *darray = malloc(sizeof(struct dynamic_array));

  darray->arr = malloc(sizeof(void *) * cap);
  darray->capacity = cap;
  darray->size = 0;

  return darray;
}

struct
dynamic_array *darray_from(void **arr, size_t size, size_t cap) {
  struct dynamic_array *darray = darray_new(cap);
  for (size_t i = 0; i < size; i++) {
    printf("setting: i=%zu, a[i]=%d\n", i, (int) arr[i]);
    darray_set(darray, i, arr[i]);
  }
  return darray;
}

void _darray_expand(struct dynamic_array *darray) {
  size_t capacity = darray->capacity;
  void **newarray = realloc(darray->arr, sizeof(void *) * capacity * 2);
  darray->arr = newarray;
  darray->capacity = capacity * 2;
}

void *darray_get(struct dynamic_array *darray, size_t i) {
  if (i > darray->capacity) {
    return NULL;
  }
  return darray->arr[i];
}

void darray_set(struct dynamic_array *darray, size_t i, void *thing) {
  if (i >= darray->capacity) {
    _darray_expand(darray);
    darray_set(darray, i, thing);
    return;
  }
  darray->arr[i] = thing;
  if (i >= darray->size) {
    darray->size = i + 1;
  }
}

void darray_insert(struct dynamic_array *darray, size_t i, void *thing) {
  size_t cap = darray->capacity;
  size_t size = darray->size;
  if (i >= cap || size + 1 > cap) {
    _darray_expand(darray);
    darray_insert(darray, i, thing);
    return;
  }
  void **arr = darray->arr;
  memmove((arr + i + 1), (arr + i), sizeof(void *) * (size - i));
  arr[i] = thing;
}

void darray_append(struct dynamic_array *darray, void *thing) {
  size_t size = darray->size;
  if (size == darray->capacity) {
    _darray_expand(darray);
  }
  darray->arr[size] = thing;
  darray->size++;
}

void darray_free(struct dynamic_array *darray) {
  void **arr = darray->arr;
  /*for (size_t i = 0; i < darray->size; i++) {
    void *ptr = arr[i];
    if (ptr != NULL) {
      free(ptr);
    }
  }*/
  free(arr);
  free(darray);
}

void darray_foreach(struct dynamic_array *d, void (*fn)(void *)) {
  for (size_t i = 0; i < d->size; i++) {
    (*fn)(darray_get(d, i));
  }
}
