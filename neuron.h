# include <tilists.h>

const char error[63] = "The two input lists should be the same size when they are not."; // defines the constant error mesage

typedef struct { // defines a neuron
    node * prevact;
    node * wgt;
    double bias;
    double act;
} neuron;

double sigmoid (double in){ // scaling function from 0 to 1
    return 1/(1 + exp(-1*in));
}

double dsigmoid (double in){ // derivitive of the scaling function
    return (exp(in))/(pow((1+exp(in)), 2.00));
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

double calc_act (node * act, node * wgt, double bias){ // calculates what the output of one neuron should be
    if (len(act) != len(wgt)){
        printf(error);
        return NAN;
    }
    return sigmoid(calc_z(act, wgt, bias));
}

double cost (node * wanted, node * given){ // calculates how bad the machine performes
    if (len(wanted) != len(given)){
        printf("The two input lists should be the same size when they are not.");
        return NAN;
    }
    
    double a;
    for (int i = 0; i < len(wanted); i++){
        a += pow((atIndex(given, i) - atIndex(wanted, i)), 2.00);
    }
}

node * calc_impact (node * act, node * wgt, double bias, double wanted){ // returns integer from zero to two to indicate which variable has the most impact on the cost and how much it should change
    if (len(act) != len(wgt)){
        printf(error);
        node * err = newList();
        return err;
    }

    double a;
    node * impact_wgt = newList(); 
    for (int i = 0; i < len(act); i++){ //calculating the impact of the weights
        a = 2 * (calc_act(act, wgt, bias) - wanted) * dsigmoid(calc_z(act, wgt, bias)) * atIndex(act, i);
        app(impact_wgt, a);
    }

    node * impact_bias = newList(); 
    for (int j = 0; j < len(act); j++){ //calculating the impact of the biases
        a = 2 * (calc_act(act, wgt, bias) - wanted) * dsigmoid(calc_z(act, wgt, bias));
        app(impact_bias, a);
    }

    node * impact_act = newList();
    for (int k = 0; k < len(act); k++){ //calculating the impact of the previous activations
        a = 2 * (calc_act(act, wgt, bias) - wanted) * dsigmoid(calc_z(act, wgt, bias)) * atIndex(wgt, k);
        app(impact_act, a);
    }

    //averaging the impacts of the parameters and adding them at constant indices to the return list
    double avib = average(impact_bias);
    double aviw = average(impact_wgt);
    double avia = average(impact_act);
    node * returnvalue = newList();
    // node * avi = newList();
    // app(avi, abs(avib));
    // app(avi, abs(aviw));
    // app(avi, abs(avia));
    // double mav = max(avi);
    // double miv = min(avi);

    // if (mav == abs(avib)){ // if all or some impacts are the same it will return a value with this priority: 1. bias, 2. weight, 3. previous activation
    //     app(returnvalue, 0);
    //     app(returnvalue, avib);
    // } else if (mav == abs(aviw)){
    //     app(returnvalue, 1);
    //     app(returnvalue, aviw);
    // } else if (mav == abs(avia)){
    //     app(returnvalue, 2);
    //     app(returnvalue, avia);
    // }

    // if (miv == abs(avib)){
    //     app(returnvalue, 0);
    //     app(returnvalue, avib);
    // } else if (miv == abs(aviw)){
    //     app(returnvalue, 1);
    //     app(returnvalue, aviw);
    // } else if (miv == abs(avia)){
    //     app(returnvalue, 2);
    //     app(returnvalue, avia);
    // }

    app(returnvalue, avib);
    app(returnvalue, aviw);
    app(returnvalue, avia);

    return returnvalue;
}