#include <stdio.h>
#include <stdlib.h>
#define PRINT_LIST(X) temp = X; for(temp=X; temp != NULL; temp = temp->next)printf("%d ->", temp->elem); printf("\n");
#define PRINT_ARRAY(X, L) _tmp = 0; for(; _tmp < L; _tmp++)printf("%d->", X[_tmp]);printf("\n");
//scanf("%d%*[\t\n ]%c", &j, &ch);
struct node {
    int elem;
    struct node *next;
};

struct node* temp;
int _tmp;
void fill_list(struct node* list, int arr[], int len){
    int i = 0;
    struct node *temp = list;
    for(; i < len; i++){
        temp->elem = arr[i];
        temp->next = (i < len-1)?(struct node*)malloc(sizeof(struct node)):NULL;
        temp = temp->next;
    }
}

int list_length(struct node *list){
    int cnt = 0;
    while(list){
        cnt++;
        list = list->next;
    }
    return cnt;
}


int partition(int arr[], int begin, int end){
    int pivot = arr[end];
    int left = 0, right = end-1;

    while(left <= right){
            if(arr[left] <= pivot)
                left++;
            if(arr[right] >= pivot){
                right--;
            }

            if((arr[right] < pivot) && (arr[left] > pivot)){
                int c = arr[right];
                arr[right] = arr[left];
                arr[left] = c;
            }
        }
    int c = arr[end];
    arr[end] = arr[right+1];
    arr[right+1] = c;
    return right+1;
}


void qsort_array(int arr[], int begin, int end){
    if(begin < end){
        int pivot = partition(arr, begin, end);
        qsort_array(arr, begin, pivot-1);
        qsort_array(arr, pivot+1, end);
    }
}


void sort_list(struct node *list, int ascending){
   int length = list_length(list);
   int arr[length], i = 0;
   struct node *tmp = list;
   while(tmp){
       arr[i++] = tmp->elem;
       tmp = tmp->next;
   }
   qsort_array(arr, 0, length-1);
   tmp = list;
   i = 0;
   while(tmp){
       if(ascending)
           tmp->elem = arr[i++];
       else
           tmp->elem = arr[length-1-i++];

       tmp = tmp->next;
   }
}

void find_triplet(struct node* list1, struct node* list2, struct node* list3, int sum){
    sort_list(list2, 1);
    sort_list(list3, 0);
    struct node* tmp = list1;
    int found = 0;
    while(tmp){
        struct node *tmp2 = list2, *tmp3 = list3;
        while(tmp2 && tmp3){
            int cur_sum = tmp->elem + tmp2->elem + tmp3->elem;
            if(cur_sum == sum){
                printf("TRIPLET FOUND: %d, %d, %d\n", tmp->elem, tmp2->elem, tmp3->elem);
                found = 1;
                break;
            }
            if(cur_sum < sum)
               tmp3 = tmp3->next;
            if(cur_sum > sum)
                tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }
    if(!found)
        printf("Sorry bro, no triplet found\n");
}


int main(){
    struct node *list1 = (struct node*)malloc(sizeof(struct node));
    struct node *list2 = (struct node*)malloc(sizeof(struct node));
    struct node *list3 = (struct node*)malloc(sizeof(struct node));
    int arr1[] = {12, 6, 29};
    int arr2[] = {23, 5, 8};
    int arr3[] = {90, 20, 59};
    fill_list(list1, arr1, 3);
    fill_list(list2, arr2, 3);
    fill_list(list3, arr3, 3);
    find_triplet(list1, list2, list3, 142);
    exit(0);
}

