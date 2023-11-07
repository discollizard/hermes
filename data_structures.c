#include "data_structures.h"
#include "params.h"

map *init_map() {
  map *new_map, new_map_ref;
  new_map->size = 8;
  new_map->count = 0;
  new_map->items = malloc((sizeof(pair) * new_map->size));
  return new_map;
}

dynamic_array* init_array(){
	dynamic_array* arr, array;
	arr = &array;
	arr->count = 0;
	arr->size = 8;
	arr->elements = (char**)malloc(sizeof(char*) * arr->size);
	return arr;
}

void array_push(dynamic_array* arr, element){
	if (arr->count + 1 > arr->size){
		grow_array(arr);
	}
	  arr->elements[arr->count] = element;
	  arr->count++;
}
