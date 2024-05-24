#include <stdio.h>
void func();

int x = 1;
int y = 2;
int z = 3;

int main(){
    func();
    
    printf("%d\n", x + y + z);
    return 0;
}

// x = 3, y = 7, z = 10