#include "defense.h"

int main(){
  
    stack_constr(stk, 0);

    for (int i = 0; i < 11; i++){
        stack_push(&stk, i);   
    }

    stack_dump(&stk);
    //stk.data = nullptr;
    stack_destruct(&stk); 
}
