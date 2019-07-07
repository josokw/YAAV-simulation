#ifndef RANDOM_H
#define RANDOM_H

#include <boost/random/linear_congruential.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <ctime>
#include <sys/time.h>

static boost::mt19937 seed;

template <class T>
struct distribution { // general case, assuming T is of integral type
   typedef boost::uniform_int<> type;
};

template <> struct distribution<float> { // float case
   typedef boost::uniform_real<> type;
};

template <> struct distribution<double> { // double case
   typedef boost::uniform_real<> type;
};

template <typename N> N getRandom(N min, N max)
{
   typedef typename distribution<N>::type distro_type;

   static bool seedIsInitialised = false;
   if (!seedIsInitialised) {
      timeval t;
      gettimeofday(&t, nullptr);
      seed.seed(static_cast<const unsigned int>(t.tv_sec));
      seedIsInitialised = true;
   }
   distro_type dist(min, max);
   boost::variate_generator<boost::mt19937 &, distro_type> random(seed,
                                                                  dist);
   return random();
}

#endif // RANDOM_H
