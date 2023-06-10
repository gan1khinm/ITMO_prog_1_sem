#include <stdio.h>
#include <stdint.h>


typedef struct uint1024_t{
    
    uint8_t mas[1024];
    int size;
} uint1024_t;



uint1024_t from_uint(unsigned int x){   //Генерация из числа
    uint1024_t res = {
        .mas = {0},
        .size = 0
    };
    
    int i = 0;
    while(x != 0){
        res.mas[i] = x%2;
        i++;
        x = x / 2;
    }

    res.size = i;
    
    return res;
}



void printf_value(uint1024_t x){    //Вывод в стандартный поток вывода

    for(int i = 0; i < x.size; i++){
        
        printf("%d", x.mas[x.size-1-i]);

    }
    
}



uint1024_t add_op(uint1024_t  y, uint1024_t x){     //сложение  
    
    uint1024_t res = {
        .mas = {0},
        .size = 0
        
    };

    int mSize;  

    if(y.size > x.size){
       mSize = y.size; 
       
    }
    else{
        mSize = x.size;
    }
    for (int i = 0; i < mSize; i++){
        res.mas[i] = x.mas[i] + y.mas[i];
        if (res.mas[i] > 1){
            res.mas[i] = res.mas[i] % 2;
            res.mas[i + 1]++;
        
        }
    
    }
    if(res.mas[mSize] == 1){
        mSize++;
    }
    res.size = mSize;

    return res;

}



uint1024_t subtr_op(uint1024_t x, uint1024_t y){    //Вычитание
     uint1024_t res = {
        .mas = {0},
        .size = 0   
    };
    
    int mSize;  


    if(y.size > x.size){
        return res; 
    
    }
    else{
        mSize = x.size;
    }   

    for(int i = 0; i < mSize; i++){
        
        if(x.mas[i] < y.mas[i]){
            int a = i + 1;
            while (x.mas[a] != 1){
                x.mas[a - 1] += 1;
                
                a++;   
            }
            x.mas[a] --;
        }
        res.mas[i] = x.mas[i] - y.mas[i];
    }
    
    res.size = 1;
    for(int b = 1; b < mSize; b++){
       if(res.mas[b] == 1){
           res.size = b + 1;
       } 
    }

    return res;

}



uint1024_t mult_op(uint1024_t x, uint1024_t y){     //Умножение
     uint1024_t res = {
        .mas = {0},
        .size = 0   
    };

    for(int i = 0; i < x.size; i++){
        for ( int j = 0; j < y.size; j++){
            res.mas[i+j] += x.mas[i] * y.mas[j];    
        }
        for ( int a = 0; a < x.size + y.size; a++)
        {
            if(res.mas[a] > 1){
                res.mas[a + 1] += res.mas[a] / 2; 
                res.mas[a] %= 2;
            }
        }
    }
    
    res.size = 1;

    for(int b = 1; b < x.size + y.size; b++){
        if(res.mas[b] == 1)
        {
            res.size = b + 1;
        }
    }
    
    return res;   
}



void scanf_value(uint1024_t* x){       //Чтение из стандартного потока ввода
    char buffer[1024] = {0};
    scanf("%s", buffer);
    int i = 0;
    
    uint8_t mas[1024];

    while(buffer[i] != 0){      // 0 читается как символ строки
        mas[i] = buffer[i] - '0';
        i++;
    }
                                    
    for(int j = 0; j < i; j++){
        
        x->mas[j] = mas[i-1-j];
    }

    x->size = i;
}



int main(){
    uint1024_t n = from_uint(2);    //генерация из числа
                        
    printf_value(n);    //вывод
    
    printf("\n");

    uint1024_t z = from_uint(0);    //генерация из числа
    
    uint1024_t m = add_op(n ,z);    //сумма
    
    printf_value(m);    //вывод суммы

    printf("\n");
    
    uint1024_t a;
    
    scanf_value(&a);    //Чтение из стандартного потока ввода
    printf_value(a);    

    printf("\n");

    uint1024_t g = mult_op(n, z);   //Умножение
    printf_value(g);

    printf("\n");

    printf_value(subtr_op(n, z));   //Вычитание
}
