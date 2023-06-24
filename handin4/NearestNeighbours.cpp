#include <iostream>
#include <cmath>
#include <string>
#include <cassert>

//#include "readfile.hpp" //!!! <- delete before delivery
#include "armadillo.hpp"
using namespace arma;

double norm_ell_p_raised_ell_p(drowvec x, drowvec xi, const unsigned int ell_p = 2) {
    assert(ell_p>=1);
    unsigned int x_size = x.size();
    assert(x.size() == xi.size());
    double d = 0;
    for (unsigned int i = 0; i < x_size; i++) {
        d+=pow(fabs(x(i)-xi[i]),ell_p);
    }   
    return d;
}


void nearestNeighbours(const std::string x_train_filename, const std::string y_train_filename, const std::string x_test_filename, const unsigned int n_neighbours = 5, const unsigned int ell_p = 2) {
    //Simple binary NearestNeighbours implementation made while learning and utilising armadillo.
    //Labels of training (located in y_train_filename) assumed to be Rademacher.
    //Could be made more efficient by limiting the sorting which this implementation uses.
    //Ties settled by flipping a coin.

    dmat x_train, x_test;
    icolvec y_train;
    x_train.load(x_train_filename);
    y_train.load(y_train_filename);
    x_test.load(x_test_filename);
    const unsigned int x_test_size = x_test.n_rows;
    const unsigned int x_train_size = x_train.n_rows;
    icolvec y_test(x_test_size);
    y_test.fill(0);
    for(unsigned int i = 0; i < x_test_size; i++) {
        //running through rows (datapoints) of x_test
        dcolvec d_i(x_train_size);
       
        for(unsigned int j = 0; j < x_train_size; j++) {
            //for fixed datapoint i of x_test
            //calculate the distances to each x_train datapoint j
            //std::cout << "(i,j) = " << "(" << i << "," << j << ")" << std::endl;
            d_i(j) = norm_ell_p_raised_ell_p(x_test.row(i), x_train.row(j), ell_p);
        }

        //create a sorting of the distances calculated in d_i
        //and sort the labels according to this sorting
        uvec sorting = arma::sort_index(d_i);
        icolvec y_train_sorted = y_train(sorting);
        //std::cout << "went here" << std::endl;
        

        //with the sorted binary labels of -1 and 1,
        //we can sum the first n_neighbours of these
        //and if the result is negative (there are more negative than positive) 
        for(unsigned int n = 0; n<n_neighbours; n++) {
            y_test(i)+=y_train_sorted(n);
            //std::cout << "n: " << n << ". " << "y_test(i): " <<  y_test(i) << std::endl;
        }

        //std::cout << "also here" << std::endl;
        //We assign the label of the most similar elements of x_train to x_test
        if (y_test(i) > 0) {
            y_test(i) = 1;
        } else if(y_test(i)<0) {
            y_test(i) = -1;
        } else {
            //y_test(i) = 0, i.e. there are equal elements of either class
            //To settle the tie, we flip a balanced coin as to which class we assign.
            y_test(i) = 2*(int)(arma::randu()>=0) - 1;
        }
        //std::cout << "i: " << i << std::endl;
    }
    //y_test.print();
    y_test.save("NN.dat", arma::raw_ascii);
}

void testNN() {
    arma::arma_rng::set_seed(314); //set seed for tie-settling.
    const unsigned int k = 5;
    const unsigned int p = 2;
    nearestNeighbours("dataX.dat", "dataY.dat", "dataX.dat", k, p);
    icolvec y_train;
    icolvec y_test;
    imat y_train_test_mat;
    y_train.load("dataY.dat");
    y_test.load("NN.dat");
    double train_accuracy = 0;
    int train_test_size = y_train.size();
    for(int i = 0; i < train_test_size; i++) {
        train_accuracy+= y_train(i) == y_test(i); 
    }
    std::cout << "For k = " << k << ", p = " << p <<", kNN training_accuracy : " << train_accuracy/train_test_size << std::endl;
}

int main() {
    arma::arma_rng::set_seed(314); //set seed for tie-settling.
    const unsigned int k = 5;
    const unsigned int p = 2;
    nearestNeighbours("dataX.dat", "dataY.dat", "dataXtest.dat", k, p);
    //testNN();
    return 0;
}
