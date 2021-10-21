#include "defense.h"

void stack_dump(Stack_t* stack){
    FILE* res = fopen("log_stack.txt", "ab");
    const char* text_of_error = error_detect (stack);

    canary_t* left_arr_can  = (canary_t*)(stack -> data) - 1;
    canary_t* right_arr_can = (canary_t*)(stack -> data + stack -> capacity);

    fprintf (res, "\n********************************************STACK DUMP********************************************\n");
   
    #ifdef PROTECTION
        if (stack->error != 0)
            fprintf(res, "Error №%d found in the stack: %s\n", stack->error, text_of_error);
        else
            fprintf (res, "\t\t  Stack is OK!\n");
    #endif 

    fprintf(res, "Struct left  canary[%p] = %lld\n", &stack -> left_struct_canary, stack -> left_struct_canary);
    fprintf(res, "Stack  size                         = %ld\n", stack -> size) ;
    fprintf(res, "Stack  capacity                     = %ld\n", stack -> capacity);
    fprintf(res, "Array  left  canary[%p] = %lld\n", left_arr_can, *left_arr_can);
    fprintf(res, "Stack  data        [%p]\n", stack -> data);
    fprintf(res, "Array  right canary[%p] = %lld\n", right_arr_can, *right_arr_can);
    fprintf(res, "Struct right canary[%p] = %lld\n", &stack -> right_struct_canary, stack -> right_struct_canary);

    print_array(stack);
    fprintf (res, "**************************************************************************************************\n");
    fclose(res);
}

int stack_ok(Stack_t* stack){
    FILE* res = fopen("log_stack.txt", "ab");
    fprintf(res, "enter stack_ok\n" );

    if (stack->error != 0){
        fclose(res);
        return stack->error;
    }

    else{
        if (stack->capacity != 0 && stack->data == nullptr){
            stack->error = NULL_DATA;
            fclose(res);
            return NULL_DATA;
        }
        
        if (stack->data == nullptr){
            stack->error = NULL_DATA;
            fclose(res);
            return NULL_DATA;
        }
        
        if (stack->size < 0){
            stack->error = NEGATIVE_SIZE;
        }

        if (stack->left_struct_canary != Canary){
            stack->error = WRONG_CANARY_STRUCT_LEFT;
            fclose(res);
            return WRONG_CANARY_STRUCT_LEFT;
        }

        if (stack->right_struct_canary != Canary){
            stack->error = WRONG_CANARY_STRUCT_RIGHT;
            fclose(res);
            return WRONG_CANARY_STRUCT_RIGHT;
        }

        if (*((canary_t*)(stack->data) - 1) != Canary){
            stack->error = WRONG_CANARY_ARRAY_LEFT;
            fclose(res);
            return WRONG_CANARY_ARRAY_LEFT;
        }

        if (*((canary_t*)(stack->data + stack->capacity)) != Canary){    
            stack->error = WRONG_CANARY_ARRAY_RIGHT;
            fclose(res);
            return WRONG_CANARY_ARRAY_RIGHT;
        }

        if (stack->hash != stack_hash (stack)){
            stack->error = WRONG_HASH;
            fprintf (res, "Stack break!\n");
            fclose(res);
            return WRONG_HASH;
        }
    }
    fclose(res);
    return 0;
}

void stack_null (Stack_t* stack)
{
    FILE* res = fopen("log_stack.txt", "ab");
    if (stack == nullptr)
    {
        fprintf (res, "STACK IS NULL!\n");
    }
    fclose(res);
}

void poison_fill(Stack_t* stack, size_t beg, size_t end){
    for (size_t i = beg; i < end; i++){
        *(stack->data + i) = POISON;
    }
}

void placing_canaries(Stack_t* stack, void* memory){
    stack_null(stack);
    
    canary_t* canary_array_left = (canary_t*) memory;
    *canary_array_left = Canary;
        
    stack->data = (elem_t*)(canary_array_left + 1);
                        
    canary_t* canary_array_right = (canary_t*)(stack->data + stack->capacity);
    *canary_array_right = Canary;  
}

const char* error_detect(Stack_t* stack){
    switch (stack -> error){
        case 0:
            return "STACK_IS_OK";

        error_case(MEMORY_OUT);
        error_case(NEGATIVE_SIZE);
        error_case(NEGATIVE_CAPACITY);
        error_case(WRONG_CANARY_STRUCT_LEFT);
        error_case(WRONG_CANARY_STRUCT_RIGHT);
        error_case(WRONG_CANARY_ARRAY_LEFT);
        error_case(WRONG_CANARY_ARRAY_RIGHT);
        error_case(NULL_DATA);
        error_case(WRONG_HASH);

        default:
            return "UNNOWN_ERROR!";
    }
}  

void print_array(Stack_t* stack){
    #ifdef DOUBLE_TYPE
        FILE* res = fopen("log_stack.txt", "ab");
        for (int i = 0; i < stack -> capacity; i++) 
            fprintf (res, "\t\t[%d]: %f\n", i, *(stack->data + i));
        fclose(res); 
    #else
        #ifdef INT_TYPE
            FILE* res = fopen("log_stack.txt", "ab");
            for (int i = 0; i < stack->capacity; i++) 
                printf ("\t\t[%d]: %d\n", i, *(stack->data + i));
            fclose(res);
        #endif
    #endif
}

size_t stack_hash(Stack_t* stack){
    unsigned int total_hash = 0;

    unsigned int i_1 = 0;
    unsigned int hash_1 = 0;

    while (i_1 != stack -> size){
        hash_1 += stack->data[i_1++];
        hash_1 += hash_1 << 10;
        hash_1 ^= hash_1 >> 6;
    }

    hash_1 += hash_1 << 3;
    hash_1 ^= hash_1 >> 11;
    hash_1 += hash_1 << 15;

    total_hash += hash_1;

    unsigned int i_2 = 0;
    unsigned int hash_2 = 0;

    while (i_2 != strlen(stack->name)){
        hash_2 += stack->name[i_2++];
        hash_2 += hash_1 << 10;
        hash_2 ^= hash_1 >> 6;
    }

    hash_2 += hash_2 << 3;
    hash_2 ^= hash_2 >> 11;
    hash_2 += hash_2 << 15;

    total_hash += hash_2;

    unsigned int i_3 = 0;
    unsigned int hash_3 = 0;

    while (i_3 != stack->capacity){
        hash_3 += stack->name[i_3++];
        hash_3 += hash_1 << 10;
        hash_3 ^= hash_1 >> 6;
    }

    hash_3 += hash_3 << 3;
    hash_3 ^= hash_3 >> 11;
    hash_3 += hash_3 << 15;

    total_hash += hash_3;
    stack->hash = total_hash;
    return total_hash;
}
