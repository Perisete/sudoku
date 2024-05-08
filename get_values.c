#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "get_values.h"

int *get_values(int size){
    int i, j, pos = 0, num, found = 0;
    int *array = malloc(size * sizeof(int));

    if(array == NULL){
        return NULL;
    }

    srand(time(NULL));

    for(pos=0;pos<size;pos++){
        array[pos] = 0;
    }

    for(pos=0;pos<size;pos++){
        do{
            num = (rand() % 9) + 1;
            found = 0;
            for(i=0;i<pos;i++){
                if(num == array[i]){
                    found = 1;
                }
            }
        }while(found == 1);
        array[pos] = num;
    }
    printf("[");
    for(pos=0;pos<size;pos++){
        printf("%d",array[pos]);
        if(pos < size -1){
            printf(", ");
        }
    }
    printf("]\n");
    return array;
}
