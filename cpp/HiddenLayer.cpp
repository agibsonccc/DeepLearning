#include <iostream>
#include <math.h>
#include "HiddenLayer.h"
using namespace std;

double uniform(double min, double max) {
  return rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int binomial(int n, double p) {
  if(p < 0 || p > 1) return 0;
  
  int c = 0;
  double r;
  
  for(int i=0; i<n; i++) {
    r = rand() / (RAND_MAX + 1.0);
    if (r < p) c++;
  }

  return c;
}

double sigmoid(double x) {
  return 1.0 / (1.0 + exp(-x));
}



HiddenLayer::HiddenLayer(int size, int in, int out, double **w, double *bp) {
  N = size;
  n_in = in;
  n_out = out;

  if(w == NULL) {
    W = new double*[n_out];
    for(int i=0; i<n_out; i++) W[i] = new double[n_in];
    double a = 1.0 / n_in;

    for(int i=0; i<n_out; i++) {
      for(int j=0; j<n_in; j++) {
        W[i][j] = uniform(-a, a);
      }
    }
  } else {
    W = w;
  }

  if(bp == NULL) {
    b = new double[n_out];
  } else {
    b = bp;
  }
}

HiddenLayer::~HiddenLayer() {
  for(int i=0; i<n_out; i++) delete W[i];
  delete[] W;
  delete[] b;
}

double HiddenLayer::output(int *input, double *w, double b) {
  double linear_output = 0.0;
  for(int j=0; j<n_in; j++) {
    linear_output += w[j] * input[j];
  }
  linear_output += b;
  return sigmoid(linear_output);
}

void HiddenLayer::sample_h_given_v(int *input, int *sample) {
  for(int i=0; i<n_out; i++) {
    sample[i] = binomial(1, output(input, W[i], b[i]));
  }
}



int main() {
  return 0;
}
