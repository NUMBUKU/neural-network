# include "neural_net.h"

using namespace std;

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
    app(wanted, 0);

    //cout << test.calc_out(input) << ", " << test.calc_cost(wanted) << endl;

    // for (int i = 0; i < 10; i++){
    //     //tes(1);
    test.calc_out(input);
    //     test.improve(wanted, 1);
    // }

    //tes(1);
    //test.calc_out(input);
    //cout << test.calc_out(input) << ", " << test.calc_cost(wanted) << endl;
    //cout << pow(test.calc_out(input) - atIndex(wanted, 0), 2.00);

    cout << test.net[0,1].act;


    delete (input);
    delete (wanted);

	return 0;
}