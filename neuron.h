# include "clists.h"


const char error[65] = "The two input lists should be the same size when they are not.\n"; // defines the constant error mesage

typedef struct { // defines a neuron
    node * prevact;
    node * wgt;
    double bias;
    double act;
    int out;
} neuron;

// some activation functions

double hyptan (double in, int der){ // scaling function from -1 to 1
    if (der == 1){
        return 1/(pow(cosh(in), 2.00));
    } else {
        return tanh(in);
    }
}

double normhyptan (double in, int der){ // scaling function from 0 to 1
    if (der == 1){
        return (tanh(in)+1)/2;
    } else {
        return 1/(pow(cosh(in), 2.00));
    }
}

double sigmoid (double in, int der){ // scaling function from 0 to 1
    if (der == 1){
        return (exp(in))/(pow((1+exp(in)), 2.00));
    } else {
        return 1/(1 + exp(-1*in));
    }    
}

double ReLU (double in, int der){
    if (der == 1){
        if (in <= 0) return 0;
        if (in > 0) return 1;
    } else {
        if (in <= 0) return 0;
        if (in > 0) return in;
    }
}

double LeakyReLU (double in, double a, int der){
    if (der == 1){
        if (in <= 0) return a;
        if (in > 0) return 1;
    } else {
        if (in <= 0) return in * a;
        if (in > 0) return in;
    }
}

double SiLU (double in, int der){
    if (der == 1){
        return in * sigmoid(in, 1) + sigmoid(in, 0);
    } else {
        return in * sigmoid(in, 0);
    }     
}

double ELU (double in, double a, int der){
    if (der == 1){
        if (in <= 0) return a * exp(in);
        if (in > 0) return 1;
    } else {
        if (in <= 0) return a * (exp(in) - 1);
        if (in > 0) return in;
    }
}

double middlelayer (double in){
    return LeakyReLU(in, .1, 0);
}

double outlayer (double in){
    return normhyptan(in, 0);
}

double derivative (double in, int output){ // derivitives of the scaling functions
    if (output) {
        return normhyptan(in, 1);
    } else {
        return LeakyReLU(in, .1, 1);
    }
}

double calc_z (node * act, node * wgt, double bias){ // calculates what the output of one neuron should be without scaling
    if (len(act) != len(wgt)){
        printf(error);
        return NAN;
    }

    double a;
    for (int i = 0; i < len(act); i++){
        a += atIndex(act, i) * atIndex(wgt, i);
    }

    return a + bias;
}

double calc_act (node * act, node * wgt, double bias, int output){ // calculates what the output of one neuron should be
    if (len(act) != len(wgt)){
        printf(error);
        return NAN;
    }

    if (!output) return middlelayer(calc_z(act, wgt, bias));
    if (output) return outlayer(calc_z(act, wgt, bias));
}

double cost (double wanted, double given){ // calculates how bad the machine performes    
    return pow(given - wanted, 2.00);
}

node * calc_impact (node * act, node * wgt, double bias, double wanted, int output){ // returns a list to indicate which variable has the most impact on the cost and how much it should change
    if (len(act) != len(wgt)){
        printf(error);
        node * err = NULL;
        return err;
    }

    double a;
    node * impact_wgt = newList(); 
    for (int i = 0; i < len(act); i++){ //calculating the impact of the weights
        a = 2 * (calc_act(act, wgt, bias, output) - wanted) * derivative(calc_z(act, wgt, bias), output) * atIndex(act, i);
        app(impact_wgt, a);
    }

    node * impact_bias = newList(); 
    for (int j = 0; j < len(act); j++){ //calculating the impact of the biases
        a = 2 * (calc_act(act, wgt, bias, output) - wanted) * derivative(calc_z(act, wgt, bias), output);
        app(impact_bias, a);
    }

    node * impact_act = newList();
    for (int k = 0; k < len(act); k++){ //calculating the impact of the previous activations
        a = 2 * (calc_act(act, wgt, bias, output) - wanted) * derivative(calc_z(act, wgt, bias), output) * atIndex(wgt, k);
        app(impact_act, a);
    }

    //averaging the impacts of the parameters and adding them at constant indices to the return list
    double avib = average(impact_bias);
    double aviw = average(impact_wgt);
    double avia = average(impact_act);
    node * returnvalue = newList();

    app(returnvalue, avib);
    app(returnvalue, aviw);
    app(returnvalue, avia);
    app(returnvalue, len(act));
    extend(returnvalue, impact_wgt);
    extend(returnvalue, impact_act);

    return returnvalue;
}