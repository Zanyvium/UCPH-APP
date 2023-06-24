#include <iostream>
#include <cmath>
#include <string>
#include <cassert>

#include "armadillo.hpp"
using namespace arma;

//LogisticRegression training and prediction function
void logisticRegression(const std::string x_train_filename, const std::string y_train_filename, const std::string x_test_filename, const double learning_rate = 0.3, const double epsilon = 1e-7, const unsigned int maxit = 1e6) {
    //Load in data with arma
    dmat x_train, x_test;
    icolvec y_train;
    x_train.load(x_train_filename);
    y_train.load(y_train_filename);
    x_test.load(x_test_filename);
    
    //Establish parameters of data
    const unsigned int x_test_nrows = x_test.n_rows; 
    const unsigned int x_train_ncols = x_train.n_cols;
    const unsigned int x_train_nrows = x_train.n_rows;
    

    //Set up and initialisation of quantaties
    icolvec y_pred(x_test_nrows);
    y_pred.fill(0);
    arma::dcolvec w_coeffs(x_train_ncols);
    arma::dcolvec grad_vec(x_train_ncols);
    w_coeffs.fill(0);
    grad_vec.fill(0);
    double norm_gradient_log_likelihood = 1;
    unsigned int iterator_counter = 0;

    //training: Minimise log likelihood via gradient descent
    while(norm_gradient_log_likelihood > epsilon && iterator_counter < maxit) {
        grad_vec.fill(0); //Initialise the gradient vector of the likelihood function

        //Calculation of unnormalised gradient
        for (int i = 0; i < x_train_nrows; i++) {
            grad_vec += y_train(i) * (1.0/(1.0+exp(arma::as_scalar(y_train(i) * w_coeffs.t() * x_train.row(i).t())))) * x_train.row(i).t();
        } 
        //normalisation of gradient
        //??? Can complain of ambiguity amoungst arma '*' operators, but seems to figure it out
        //??? potential for rewrite to ensure roboustness?
        grad_vec = -1.0/x_train_nrows * grad_vec;

        //Calculation of norm of gradient to determine exit from gradient descent while loop.
        norm_gradient_log_likelihood = arma::norm(grad_vec,2);

        //update parameters based on gradient of likelihood and calculate 
        w_coeffs -= learning_rate * grad_vec;
        
        //Possibility of updates for long descent
        /* if(iterator_counter % 10000 == 0) {
            std::cout << "iterator counter: " << iterator_counter << ", norm_gradient: " << norm_gradient_log_likelihood << std::endl;
        } */
        iterator_counter++;
    }
    //print final parameters
    w_coeffs.print("w_coeffs");

    //prediction based on sign()
    for (int i = 0; i < x_test_nrows; i++) {
        double temp = arma::as_scalar(w_coeffs.t() * x_test.row(i).t());
        if (temp > 0) {
            y_pred(i) = 1;
        } else if(temp<0) {
            y_pred(i) = -1;
        } else {
            //y_pred(i) = 0, i.e. there are equal elements of either class
            //To settle the tie, we flip a balanced coin as to which class we assign.
            //Unlike in kNN, this case is very unlikely for LogReg,
            //save for, possibly, very sparse test data, or 
            //gradient descent convergence of parameters towards 0.
            y_pred(i) = 2*(int)(arma::randu()>=0) - 1;
        }
    }
    //y_test.print();
    y_pred.save("LogReg.dat", arma::raw_ascii);
}

void testLR() {
    //simple training accuracy test for algorithm
    arma::arma_rng::set_seed(314); //set seed for tie-settling.

    //inputs
    const double learning_rate = 0.7;
    const double epsilon = 1e-7;
    const unsigned int maxit = 10e5;
    //Train the algorithm on the training set, and use training data for prediction as well
    logisticRegression("dataX.dat", "dataY.dat", "dataX.dat", learning_rate, epsilon, maxit);

    //Read in the result
    icolvec y_train;
    icolvec y_pred;
    imat y_train_test_mat;
    y_train.load("dataY.dat");
    y_pred.load("LogReg.dat");
    double train_accuracy = 0;
    int train_pred_size = y_train.size();

    //test against truth
    for(int i = 0; i < train_pred_size; i++) {
        train_accuracy+= y_train(i) == y_pred(i);
    }
    //report back training accuracy
    std::cout << "For learning rate alpha = " << learning_rate << ", epsilon = " 
    << epsilon << " and maxit = " << maxit << ", logreg training_accuracy : " 
    << train_accuracy/train_pred_size << std::endl;
}

int main() {
    //set up
    arma::arma_rng::set_seed(314); //set seed for tie-settling.
    const double learning_rate = 0.7;
    const double epsilon = 1e-7;
    const unsigned int maxit = 10e5;

    //train on training data, predict based on test data
    logisticRegression("dataX.dat", "dataY.dat", "dataXtest.dat", learning_rate, epsilon, maxit);
    
    //train on training data, predict based on training data
    //testLR();
    return 0;
}
