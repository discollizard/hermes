#ifndef DATA_STRUCTURES_H_
#define DATA_STRUCTURES_H_

#include <stddef.h>
#include <stdlib.h>

// array stuff
typedef struct {
  int count;
  size_t size;
  char** elements;
} dynamic_array;

dynamic_array* init_array();

#define grow_array(arr)                                                        \
  arr->elements = realloc(arr->elements, size * 2);                            \
  arr->size = arr->array_size * 2;

void array_push(dynamic_array *arr, char* element);

// pair stuff
typedef struct {
  char *key;
  void *value;
} pair;

// map stuff
typedef struct {
  int size;
  int count;
  pair *items;
} map;

map *init_map();

#endif
