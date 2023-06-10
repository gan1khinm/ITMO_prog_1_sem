#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#define ID3V2_MAX_SIZE 128


typedef struct ID3v2Tag
{
    char signature[3];
    char name[30];
    char artist[30];
    char album[30];
    char year[4];
    char description[30];
    unsigned short ganre;
}id3v2;


bool is_filepath(const char* str){
    printf(str);
    int a = strcmp(str, "--filepath");
    if(a == 0){
        return true;
    }
    else{
        return false;
    }
}


bool is_show(const char* str){
    int a = strcmp(str, "--show");
    if (a == 0){
        return true;
    }
    else{
        return false;
    }
}


bool is_get(const char* str){
    int a = strcmp(str, "--get");
    if (a == 0){
        return true;
    }
    else{
        return false;
    }
}


bool is_set(const char* str){
    int a = strcmp(str, "--set");
    if (a == 0){
        return true;
    }
    else{
        return false;
    }
}


long file_offset(FILE* file)       //размер mp3 файла
{
    fseek(file, 0L, SEEK_END);
    return ftell(file) - ID3V2_MAX_SIZE;
}


int main(int argc , char** argv){

    setlocale(LC_ALL,"RUS");
    char name[30], filepath[10], test[6];

    sscanf(argv[1],"%10s=%s",filepath,name);

    if (is_filepath(filepath) == false){
        printf("Не указан filepath");
        return 0;
    }

    FILE *file = fopen(name, "ab+");

    if(!file){
        perror(name);
        return 0;
    }

    char* buf = malloc(ID3V2_MAX_SIZE+2);
    memset(buf, 0x00, ID3V2_MAX_SIZE);
    fseek(file, file_offset(file), SEEK_SET);
    fread(buf, 1, ID3V2_MAX_SIZE, file);

    id3v2 *mp3 = NULL;

    bool show = false;
    bool get = false;
    bool set = false;
    for(int i = 2; i < argc; i++){
        memcpy(test,argv[i],5);
        if(is_show(argv[i])){
            show = true;
        }
        else if(is_get(test)){
            get = true;
        }
        else if(is_set(test)){
            set = true;
        }
    }


    if(show){
        if ((mp3 = (id3v2*)(buf)) != NULL){
            printf("Name:        %s\n",mp3->name);
            printf("Artist:      %s\n",mp3->artist);
            printf("Album:       %s\n",mp3->album);
            printf("Year:        %s\n",mp3->year);
            printf("Description: %s\n",mp3->description);
            printf("Ganre:       %d\n",mp3->ganre);
        }


    }

    if(get){
        char prop_name[10];
        sscanf(argv[2], "%5s=%s", test,prop_name);
        if(strcmp(prop_name,"name") == 0){
            if ((mp3 = (id3v2*)(buf)) != NULL)
            {
                    printf("Name:        %s\n",mp3->name);
            }
        }

        if(strcmp(prop_name,"artist") == 0){
            if ((mp3 = (id3v2*)(buf)) != NULL)
                {
                printf("Artist:      %s\n",mp3->artist);
            }
        }

        if(strcmp(prop_name,"album") == 0){
            if ((mp3 = (id3v2*)(buf)) != NULL)
            {
                printf("Album:       %s\n",mp3->album);
            }
        }

        if(strcmp(prop_name,"year") == 0){
            if ((mp3 = (id3v2*)(buf)) != NULL)
            {
                printf("Year:        %s\n",mp3->year);
            }
        }

        if(strcmp(prop_name,"description") == 0){
            if ((mp3 = (id3v2*)(buf)) != NULL)
            {
                printf("Description: %s\n",mp3->description);
            }
        }

        if(strcmp(prop_name,"ganre") == 0){
            if ((mp3 = (id3v2*)(buf)) != NULL)
            {
                printf("Ganre:       %d\n",mp3->ganre);
            }
        }
        fclose(file);
        return 0;
    }

    if(set){
        char prop_name[10];
        char prop_value[10];
        mp3 = (id3v2*)(buf);
        sscanf(argv[2], "%5s=%s", test,prop_name);
        sscanf(argv[3], "%7s=%s", test,prop_value);
        if(strcmp(prop_name,"name") == 0){
            if (mp3 != NULL)
            {
                strcpy(mp3->name,prop_value);
            }
        }

        if(strcmp(prop_name,"artist") == 0){
            if (mp3 != NULL)
            {
                strcpy(mp3->artist,prop_value);

            }
        }

        if(strcmp(prop_name,"album") == 0){
            if (mp3 != NULL)
            {
                strcpy(mp3->album,prop_value);
            }
        }

        if(strcmp(prop_name,"year") == 0){
            if (mp3 != NULL)
            {
                strcpy(mp3->year,prop_value);
            }
        }

        if(strcmp(prop_name,"description") == 0){
            if (mp3 != NULL)
            {
                strcpy(mp3->description,prop_value);
            }
        }

        if(strcmp(prop_name,"ganre") == 0){
            if (mp3 != NULL)
            {
                mp3->ganre = atoi(prop_value);
            }
        }

        buf = (char*)mp3;
        fseek(file, file_offset(file), SEEK_SET);
        fwrite(buf, 1, ID3V2_MAX_SIZE, file);
        fclose(file);
    }
    
    return 0;
}
