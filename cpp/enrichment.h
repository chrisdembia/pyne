#if !defined(_PYNE_ENRICHMENT_)
#define _PYNE_ENRICHMENT_

#include "pyne.h"
#include "nucname.h"
#include "data.h"
#include "material.h"

/************************************************/
/*** Enrichment Component Class and Functions ***/
/************************************************/

namespace pyne {
namespace enrichment {

  class Cascade 
  {
    /** Set of physical parameters used to specify an enrichment cascade. **/

  public:
    // Constructors
    Cascade();
    ~Cascade();

    // Attributes
    double alpha; // stage separation factor
    double Mstar; // mass separation factor

    int j; // Component to enrich (U-235), zzaaam form
    int k; // Component to de-enrich, or strip (U-238), zzaaam form

    double N; // number of enriching stages
    double M; // number of stripping stages

    double x_feed_j; // enrichment of the jth isotope in the feed stream
    double x_prod_j; // enrichment of the jth isotope in the product stream
    double x_tail_j; // enrichment of the jth isotope in the tails stream

    pyne::Material mat_feed; // feed material
    pyne::Material mat_prod; // product material
    pyne::Material mat_tail; // tails material

    double l_t_per_feed; // Total flow rate per feed rate.
    double swu_per_feed; // This is the SWU for 1 kg of Feed material.
    double swu_per_prod; // This is the SWU for 1 kg of Product material.

    // member functions
    void _reset_xjs();
  };


  Cascade _fill_default_uranium_cascade();
  extern Cascade default_uranium_cascade;

  double prod_per_feed(double, double, double);
  double tail_per_feed(double, double, double);
  double tail_per_prod(double, double, double);

  double alphastar_i(double, double, double);

  void _recompute_nm(Cascade &, double=1.0E-7);
  void _recompute_prod_tail_mats(Cascade &);
  Cascade _norm_comp_secant(Cascade &, double=1.0E-7, int=100);
  double _deltaU_i_OverG(Cascade &, int);

  Cascade ltot_per_feed(Cascade &, double=1.0E-7, int=100);
  Cascade multicomponent(Cascade &, double=1.0E-7, int=100);

  /******************/
  /*** Exceptions ***/
  /******************/
  class EnrichmentInfiniteLoopError: public std::exception
  {
    virtual const char* what() const throw()
    {
      return "Inifinite loop found while calculating enrichment cascade.";
    };
  };

  class EnrichmentIterationLimit: public std::exception
  {
    virtual const char* what() const throw()
    {
      return "Iteration limit hit durring enrichment calculation.";
    };
  };

  class EnrichmentIterationNaN: public std::exception
  {
    virtual const char* what() const throw()
    {
      return "Iteration has hit a point where some values are not-a-number.";
    };
  };

// end enrichment
};
// end pyne
};

#endif


