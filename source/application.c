#include <stdio.h>

void another_function() {
    printf("hello, from another_function.\n");
}

int main(){
    printf("hello, world!\n");
    another_function();
    return 0;
}
