#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_BUCKETS 10
//scanf("%d%*[\t\n ]%c", &j, &ch);
struct node {
    void* key;
    void* value;
    struct node *next;
};


int hash_function(void* key){
    char *tmp = (char*)key;
    int val = 0;
    int i =0;
    for(i = strlen(tmp)-1; i > 0; i--){
        val += tmp[i] * pow(10, strlen(tmp)-1-i);
    }
    return (val % MAX_BUCKETS);
}

void* lookup(struct node* hash[], void* key){
    int hash_value = hash_function(key);
    struct node * bucket = hash[hash_value];
    while(bucket){
        if(!strcmp(key, bucket->key)){
            return bucket;
        }
        bucket = bucket->next;
    }
    return NULL;
}

void insert(struct node *hash[], void* key, void* value){
    struct node* tmp = (struct node*)lookup(hash, key);
    if(tmp){
        tmp->value = value;
        return;
    }

    int hash_value = hash_function(key);
    if(!hash[hash_value]){
        hash[hash_value] = (struct node*)malloc(sizeof(struct node));
        hash[hash_value]->value = value;
        hash[hash_value]->key = key;
        hash[hash_value]->next = NULL;
        //printf("inserted %s into hash\n", (char*)key);
    } else {
        struct node* temp = hash[hash_value];
        //printf("%p\n", temp->next);
        while(temp->next){
            temp = temp->next;
        }
        temp->next = (struct node*)malloc(sizeof(struct node));
        temp->next->value = value;
        temp->next->key = key;
        temp->next->next = NULL;
    }
}

int main(){
    struct node *hash[MAX_BUCKETS] = {NULL};
    insert(hash, "abhinav", "jha");
    insert(hash, "abhishek", "singh");
    insert(hash, "rahul", "verma");
    insert(hash, "abhinav", "god");
    struct node *elem = (struct node*)lookup(hash, "abhinav");
    printf("%s => %s\n", "abhinav", (char*)elem->value);
    exit(0);
}

