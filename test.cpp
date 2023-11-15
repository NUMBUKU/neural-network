# include "clists.h"
# include <iostream>

//using std::cout, std::endl;

int main(){
    node * list = newList();
    changeAtIndex(list, 0, 1);
    changeAtIndex(list, 1, 2);
    printlist(list);

    return 0;
}