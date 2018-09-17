# darray

Simple dynamic arrays in C. This is not meant to be something anyone would actually use, but instead project to get a little more comfortable with C.

## `struct dynamic_array`

The struct used to represent a dynamic array contains the following properties:

### `size_t size;`

The number of elements in the array.

### `size_t capacity;`

The maximum number of elements the array can hold before needing to expand.

### `void **arr;`

The array itself.

## functions

The following functions make up the operations that can be performed on a dynamic_array.

### `struct dynamic_array *darray_new(size_t capacity);`

Make a new dynamic array with an initial capacity of your choosing. Memory is allocated for the dynamic array, so it must be freed later.

### `struct dynamic_array *darray_from(void **arr, size_t size, size_t cap);`

Make a new dynamic array from an existing array. The given size should be the length of the array passed in, and the capacity is the desired initial capacity.

### `void darray_set(struct dynamic_array *darray, size_t i, void *thing);`

Set the value at a given index of a dynamic array. If the index is out of range, more memory will be allocated.

### `void darray_append(struct dynamic_array *darray, void *thing);`

Append a thing to the end of the array. If this would exceed the capacity, more memory will be allocated.

### `void darray_insert(struct dynamic_array *darray, size_t i, void *thing);`

Insert a thing at the specified index.

### `void *darray_get(struct dynamic_array *darray, size_t i);`

Get the thing at the given index. If the index is out of range, NULL is returned.

### `void darray_foreach(struct dynamic_array *darray, void (*fn)(void *));`

Iterate over the array, calling the given function with the current element for each one.

### `void darray_free(struct dynamic_array *darray);`

Free the memory allocated for the given dynamic array.

## Example

```c
void print_elem(void *elem) {
  printf("%d\n", (int) elem);
}

int main() {
  struct dynamic_array *d = darray_new(3);

  printf("size: %zu\ncapacity: %zu\n", d->size, d->capacity);

  for (int i = 0; i < 5; i++) {
    darray_append(d, (void *) i);
  }

  printf("size: %zu\ncapacity: %zu\n", d->size, d->capacity);

  darray_set(d, 3, 42);

  darray_insert(d, 3, 10);

  darray_foreach(d, print_elem);

  darray_free(d);
}
```
