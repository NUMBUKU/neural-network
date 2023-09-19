# include "neural_net.h"

using std::cout; using std::endl;

node * input = newList();
node * wanted = newList();

void tes (int c){
    switch (c)
    {
    case 0:
        changeAtIndex(input, 0, -1);
        changeAtIndex(wanted, 0, 1);
        break;
    case 1:
        changeAtIndex(input, 0, 1);
        changeAtIndex(wanted, 0, 0);
        break;
    default:
        break;
    }
}

int main (){
    net::neural_net test(1, 2, 1, 1, false);
    app(input, 1);
    // app(wanted, 0);

    //cout << test.calc_out(input) << endl;
    //printlist(test.outl);
    //printlist(input);

    printf("hi");

    del(input);
    del(wanted);

	return 0;
}