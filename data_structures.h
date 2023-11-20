#ifndef DATA_STRUCTURES_H_
#define DATA_STRUCTURES_H_
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef uint64_t hash_function (const char*, size_t);
typedef struct _hash_table hash_table;

hash_table *init_hash_table(uint32_t size, hash_function *hf);
void hash_table_destroy(hash_table *ht);
void hash_table_print(hash_table *ht);
bool hash_table_insert(hash_table *ht, const char *key, void *obj);
void *hash_table_lookup(hash_table *ht,  char *key);
void *hash_table_delete(hash_table *ht,  const char *key);

#endif