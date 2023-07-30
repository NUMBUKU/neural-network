#include <iostream>
#include <tilists.h>

using namespace std;

int main(){
    node * list = newList();
    app(list, 0);
    app(list, 15);
    printlist(list);

	return 0;
}