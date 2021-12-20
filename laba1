#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


bool is_line(const char* str){
    int a = strcmp(str, "-l");
    int b = strcmp(str, "--lines");
    if (a == 0 || b == 0){
        return true;
    }
    else{
        return false;
    }
}


bool is_word(const char* str){
    int c = strcmp(str, "-w");
    int z = strcmp(str, "--words");
    if (c == 0 || z == 0){
        return true;
    }
    else{
        return false;
    }
}


bool is_byte(const char* str){
    int v = strcmp(str, "-c");
    int w = strcmp(str, "--bytes");
    if (v == 0 || w == 0){
        return true;
    }
    else{
        return false;
    }
}



int words(const char* str){
    int Wcount = 1;
    int len = strlen(str);
    for(int i = 0 ; i < len ; i++){
        
        if(str[i] == ' ' || str[i] == '\n'){
            Wcount++;
        }
    }
    return Wcount;
}



float lines(const char* str){
    float Lcount=0;
    int len=strlen(str);
    for(int i = 0 ; i < len ; i++){

        if(str[i] == '\n'){
            Lcount++;
    
    }        
    } 
    return Lcount + 1;
}




float bytes(const char* str){
    
    int charSize = sizeof(str);
       
    return charSize;
}








int main(int argc , char** argv){
    if (argc < 3){
        return -1;
    }
    printf("%d\n" , argc);
    for(int i = 0 ; i<argc ; i++){
        printf("%s\n" , argv[i]);
    }
    
    
    bool Lines = false;
    bool Words = false;
    bool Bytes = false;
    char* Name = NULL;
    for(int i = 1; i < argc; i++){
        if(is_word(argv[i]) == true){
            Words = true;
        }
        else if(is_line(argv[i]) == true){
            Lines = true;
        }
        else if(is_byte(argv[i]) == true){
            Bytes = true;
        }
        else{
            Name = argv[i];
        }    
    
    }


    FILE *f;
    f = fopen(Name , "r");
    if(f != NULL){
        fseek(f , 0 , SEEK_END);
        long lSize = ftell(f);                            
        rewind(f); 
        char * buffer = (char*) malloc(sizeof(char) * lSize);
        if (buffer == NULL)
        {
            fputs("Ошибка памяти", stderr);
            return 1;
        }
 
        size_t result = fread(buffer, 1, lSize, f);
        fclose(f);
        
        if(Lines == true){
            
            printf("Колличество строк: %f\n", lines(buffer));
        }
        if(Words == true){
            printf("Колличество слов: %d\n", words(buffer));

        }
        if(Bytes == true){
            printf("Размер файла: %f\n", bytes(buffer));

        }    
        
        printf("Среднее колличество байт на строку: %f\n ", bytes(buffer) / lines(buffer));
        
        free(buffer);
        
    }
    


    
    else{
        printf("Ошибка");
        return 1;
    }


    return 0;    
}
