#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(){
    int size = 3, i, j, pos = 0, num, found = 0;
    int array [size];
    srand(time(NULL));

    for(pos=0;pos<size;pos++){
        array[i] = 0;
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
}
