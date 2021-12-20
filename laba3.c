#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




typedef struct{
    Node *head;
    Node *tail;
} q;


typedef struct Node{
    time_t value;
    struct Node *next;
} Node;


void add(q **queue, time_t x){
    Node *tmp;
    tmp = (Node*)malloc(sizeof(Node));
    tmp->value = x;
    tmp->next = NULL;

    if(((*queue)->head) == NULL){
        *queue = (q*)malloc(sizeof(queue));
        (*queue)->head = (*queue)->tail = tmp;
    }

    else{
        (*queue)->tail->next = tmp;
        (*queue)->tail = (*queue)->tail->next;
    }
}


void delete(q **queue){

    if((*queue)->head == (*queue)->tail){
        *queue = NULL;
    }

    else{
        (*queue)->head = (*queue)->head->next;
    }
}



void convert_t(time_t a, char *str_t){
    struct tm *tmp = local_t(&a);
    strftime(str_t, 21, "%d/%b/%Y:%H:%M:%S", tmp);
}


time_t return_date(char *str){
    char Request[340];
    char Bytes_send[16];
    char Remote_addr[32];
    char Local_t[32];
    long long c = 0;
    int status = 0;

    sscanf(str, "%s - - [%[^]]] \"%[^\"]\" %d %s",Remote_addr, Local_t, Request, &status, Bytes_send);
    time_t date;
    char months[12][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug", "Sep", "Oct", "Nov", "Dec"};
    struct tm time;
    time.tm_isdst = -1;
    char month[4];
    sscanf(Local_t, "%d/%3s/%d:%d:%d:%d", &time.tm_mday, month, &time.tm_year, &time.tm_hour, &time.tm_min, &time.tm_sec);
    

    for(int a = 0; a <= 11; a++){
        if(strcmp(months[a], month) == 0){
            time.tm_mon = a;
        }
    }
    time.tm_year -= 1900;
    date = mktime(&time);

    return date;
}


int err(char f[]){
    FILE * file = fopen(f, "r");
    char Request[340];
    char Bytes_send[16];
    char Remote_addr[32];
    char Local_t[32];
    long long c = 0;
    int status = 0;
    char str[2048];
    

    while(fgets(str, 2048, file)){
        sscanf(str, "%s - - [%[^]]] \"%[^\"]\" %d %s",Remote_addr, Local_t, Request, &status, Bytes_send);
        if(status / 100 == 5){
            printf("%s",str);
            c++;
        }
    }

    fclose(file);
    return c;
}


void time_window(char f_name[], char window_time[]){
    FILE *f = fopen(f_name, "r");
    q *queue = malloc(sizeof(queue));
    queue->head = NULL;
    queue->tail = NULL;
    
    char str[2048];
    long long window_time_ll = atoi(window_time);
    char tmp[22];
    time_t arr = (time_t)malloc(32 * sizeof(time_t));
    long long count = 0;
    int window_count = 0;
    time_t start_time;
    time_t end_time;
    time_t d = 0;
    time_t date;

    

    while (fgets(str, 2048, f)){

        date = return_date(str);
        if (queue->head != NULL && queue->tail != NULL){

            while ((count > 0) && ((long long)(difftime(queue->tail->value, queue->head->value)) > window_time_ll)){
                delete(&queue);
                count--;
            }
        }

        if (count > window_count){
            start_time = queue->head->value;
            end_time = queue->tail->value;
            window_count = count;
            
        }

        add(&queue, date);
        count++;
    }

    printf("Count of requests: %d\n", window_count);
    convert_t(start_time, tmp);
    printf("from: %s\n", tmp);
    convert_t(end_time, tmp);
    printf("to: %s\n", tmp);
    fclose(f);
}


int main(){
    long long error_count;
    error_count = err("D:\\work\\Lab 3\\access_log_Jul95.txt");
    time_window("D:\\work\\Lab 3\\access_log_Jul95.txt", "10");
    return 0;
}