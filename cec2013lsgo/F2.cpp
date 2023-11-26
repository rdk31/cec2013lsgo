#include "F2.h"

F2::F2() : Benchmarks()
{
  Ovector = NULL;
  minX = -5;
  maxX = 5;
  ID = 2;
  anotherz = new double[dimension];
  partials_num = dimension;
}

F2::~F2()
{
  delete[] Ovector;
  delete[] anotherz;

  if (partials != NULL)
  {
    delete[] partials;
  }
}

double F2::compute(double *x)
{
  int i;
  double result;

  if (Ovector == NULL)
  {
    // Ovector = createShiftVector(dimension,minX,maxX);
    Ovector = readOvector();
  }

  if (partials != NULL)
  {
    delete[] partials;
  }

  partials = new double[partials_num];

  for (i = 0; i < dimension; i++)
  {
    anotherz[i] = x[i] - Ovector[i];
  }

  // // T_{osz}
  // transform_osz(anotherz, dimension);

  // // T_{asy}^{0.2}
  // transform_asy(anotherz, 0.2);

  // // lambda
  // Lambda(anotherz, 10);

  result = rastrigin(anotherz, dimension);
  update(result);
  return (result);
}
