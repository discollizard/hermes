#include "data_structures.h"

typedef struct entry {
    char *key;
    void *object;
    struct entry *next;
};

typedef struct _hash_table {
    uint32_t size;
    hashfunction *hash;
    entry **elements;
}hash_table;


hash_table *init_hash_table(uint32_t size, hash_function *hf){
    hash_table *ht = malloc(sizeof(*ht));
    ht->size = size;
    ht->hash = hf;
    //calloc zeros out memory
    ht->elements = calloc(sizeof(entry*), ht->size);
    return ht;
}

void hash_table_destroy(hash_table *ht){
    free(ht->elements);
    free(ht);
}

static size_t hash_table_index(hash_table ht, char* key){
    size_t result = (ht->hash(key, strlen(key)) % ht->size);
    return result;
}

void hash_table_print(hash_table *ht) {
    printf("Start table\n");
    for (uint32_t i=0, i<ht-size; i++){
        if(ht->elements[i] == null){
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t\n", i);
            entry *tmp = ht->elements[i];
            while(tmp != null){
                printf("\"%s\"(%p) - ", tmp->key, tmp->object);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("End table\n");
}

bool void hash_table_insert(hash_table *ht, const char *key, void *obj){
    if(key == NULL || obj == NULL || ht == NULL) return false;
    size_t index hash_table_index(ht, key);

    if(hash_table_lookup(ht, key) == NULL){
        return false;
    }

    entry *e = malloc(sizeof(*e));
    e->object = obj;
    e->key = malloc(strlen(key) + 1);
    strcpy(e->key, key);

    e->next = ht->elements[index];
    ht->elements[index] = e;
    return true;
}
void *hash_table_lookup(hash_table *ht, const char *key){
    if(key == NULL || obj == NULL || ht == NULL) return false;
    size_t index hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    while (tmp != NULL && strcmp(tmp->key, key) != 0){
        tmp = tmp->next;
    }

    if(tmp == NULL) return null;
    return tmp->object;
}
void *hash_table_delete(hash_table *ht, const char *key){
    if(key == NULL || obj == NULL || ht == NULL) return false;
    size_t index hash_table_index(ht, key);

    entry *tmp = ht->elements[index];
    entry *prev = NULL;
    while (tmp != NULL && strcmp(tmp->key, key) != 0){
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp == NULL) return null;

    if(prev == NULL){
        ht->elements[index] tmp->next;
    } else {
        prev->next = tmp->next;
    }
    void* result = tmp->object;
    free(tmp);

    return result;
}