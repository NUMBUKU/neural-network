# include "neural_net.cpp"

using std::cout, std::endl;

node * input;
node * wanted;

void testcases (int c){ // defines the test cases with known input and output values, here the net should return {1,0} if the input is -1 and it should return {0,1}
    switch (c){
        case 0:
            changeAtIndex(input, 0, -1);
            changeAtIndex(wanted, 0, 1); changeAtIndex(wanted, 1, 0);
            break;
        case 1:
            changeAtIndex(input, 0, 1);
            changeAtIndex(wanted, 0, 0); changeAtIndex(wanted, 1, 1);
            break;
        default:
            break;
    }
}

int main (){
    // defines a new neural net
    net::neural_net neurnet0(1/*the number of cullumns of neurons in the net (excluding inputs and outputs)*/, 1/*number of rows of neurons in the net (excluding inputs and outputs)*/, 2/*number of output neurons (and thus number of outputs)*/, 1/*number of input neurons (and thus number of inputs)*/, false/*optional, when set to true the values of the net are printed so you can export the net*/, false/*optional, when set to true the net is printed as a function after death so you can export the net*/, .1/*optional, sets the coeffincients of the activation functions that have coefficients*/);
    
    // initialises the input and wanted lists
    input = newList();
    wanted = newList();

    //initial values for input and wanted
    app(input, -1);
    app(wanted, 1); app(wanted, 0);
    
    // prints the output of the net (the index of the highest output neuron activation), so if the output list is {0.035, 0.894} then the output is 1 since that's the index of the highest number
    cout << "output: " << neurnet0.calc_out(input) << endl;

    // the calc_out method also stores the output list in neurnet0.outl and the certainty in neurnet0.certainty
    cout << "certainty: " << neurnet0.certainty << "%" << endl;
    cout << "output list:" << endl;
    printlist(neurnet0.outl);

    // calculates how bad the net is doing, the higher the output, the worse the net is doing (this only works when the calc_out has already been run)
    cout << "cost before: " << neurnet0.calc_cost(wanted) << endl;

    // to improve the net's performance and have it give us the correct output, we use the improve() method (this only works when the calc_out has already been run)
    neurnet0.improve(wanted, 1/*the learning rate, the longer you train the net the lower it should become, this allows the net to progressively refine details*/);

    neurnet0.calc_out(input);
    cout << "cost after (should be lower): " << neurnet0.calc_cost(wanted) << endl;

    // example of training the neural net
    
    // double learningrate = 1;
    // for (int i = 0; i < 100; i++){
    //     testcases(i % 2); // oscillates between the testcases
    //     neurnet0.calc_out(input);
    //     neurnet0.improve(wanted, learningrate);
    //     learningrate -= .1; // reducing the learning rate
    // }

    // after training we can input other inputs than just the testcase inputs

    delete (input); // deleting the pointers
    delete (wanted);

	return 0;
}