#include "F8.h"
#include <stdio.h>

F8::F8() : Benchmarks()
{
  Ovector = NULL;
  minX = -100;
  maxX = 100;
  ID = 8;
  s_size = 20;
  anotherz = new double[dimension];
  partials_num = s_size;
  partials = new double[partials_num];
}

F8::~F8()
{
  delete[] Ovector;
  delete[] Pvector;

  delete[] anotherz;
  for (int i = 0; i < 25; ++i)
  {
    delete[] r25[i];
  }
  for (int i = 0; i < 50; ++i)
  {
    delete[] r50[i];
  }
  for (int i = 0; i < 100; ++i)
  {
    delete[] r100[i];
  }
  delete[] r25;
  delete[] r50;
  delete[] r100;
  delete[] s;
  delete[] w;

  if (partials != NULL)
  {
    delete[] partials;
  }
}

double F8::compute(double *x)
{
  int i;
  double result = 0.0;

  if (Ovector == NULL)
  {
    Ovector = readOvector();
    Pvector = readPermVector();
    r25 = readR(25);
    r50 = readR(50);
    r100 = readR(100);
    s = readS(s_size);
    w = readW(s_size);
  }

  if (simpleWeights)
  {
    for (i = 0; i < s_size; i++)
    {
      w[i] = 1.0;
    }
  }

  for (i = 0; i < dimension; i++)
  {
    anotherz[i] = x[i] - Ovector[i];
  }

  // s_size non-separable part with rotation
  int c = 0;
  for (i = 0; i < s_size; i++)
  {
    // cout<<"c="<<c<<", i="<<i<<endl;
    anotherz1 = rotateVector(i, c);
    // cout<<"done rot"<<endl;
    double tmp = w[i] * elliptic(anotherz1, s[i]);
    result += tmp;
    partials[i] = tmp;
    delete[] anotherz1;
    // cout<<result<<endl;
  }

  update(result);
  return (result);
}
