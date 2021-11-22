#include <stdio.h>

int main(int argc, char const *argv[])
{   int valid = 0;
    int n = argc;
    for(int i=1; i<n; i++){
        if(argv[i][0] == '-'){
            continue;
        }
        else{
            valid++;
           printf("%s ",argv[i]);
        }
    }

    if(valid){
        printf("\n");
    } 
    
    return 0;
}