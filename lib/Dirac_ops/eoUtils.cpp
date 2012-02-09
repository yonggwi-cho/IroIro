/*! @file  eoUtils.cpp
 *  @brief definition of utilities related to even/odd preconditioning
 */
#include "eoUtils.hpp"
#include<cassert>
namespace EvenOddUtils{

  void Inverter_WilsonLike::invert(Field& sol,const Field& src)const{
    assert(sol.size()==2*D_->fsize());
    assert(src.size()==2*D_->fsize());

    Field be = D_->mult_ee_inv(Field(src[esub_]));
    Field bo = D_->mult_oo_inv(Field(src[osub_]));
 
    be -= D_->mult_eo(bo);
    Field ye(D_->fsize());
    SolverOutput monitor = slv_->solve(ye,D_->mult_dag(be));
#if VERBOSITY > 0
    monitor.print();
#endif
    bo -= D_->mult_oe(ye);

    for(int ex=0; ex<fh_.Nex(); ++ex){
      for(int hs=0; hs<fh_.Nvol(); ++hs){
	sol.set(ff_.islice(idx_eo_->esec(hs),ex), ye[fh_.islice(hs,ex)]);
	sol.set(ff_.islice(idx_eo_->osec(hs),ex), bo[fh_.islice(hs,ex)]);
      }
    } 
  }

  void Inverter_WilsonLike::test(Field& Df, const Field& f)const{
    
    Field Dfe = D_->mult_ee(Field(f[esub_]));
    Dfe += D_->mult_ee(D_->mult_eo(Field(f[osub_])));

    Field Dfo = D_->mult_oo(Field(f[osub_]));
    Dfo += D_->mult_oo(D_->mult_oe(Field(f[esub_])));

    for(int i=0;i<Dfe.size()/2;++i)
      CCIO::cout<<" Dfe["<<i<<"]=("<< Dfe[2*i]<<","<<Dfe[2*i+1]<<")"
		<<" Dfo["<<i<<"]=("<< Dfo[2*i]<<","<<Dfo[2*i+1]<<")"
		<<std::endl;

    for(int ex=0; ex<fh_.Nex(); ++ex){
      for(int hs=0; hs<fh_.Nvol(); ++hs){
	Df.set(ff_.islice(idx_eo_->esec(hs),ex), Dfe[fh_.islice(hs,ex)]);
	Df.set(ff_.islice(idx_eo_->osec(hs),ex), Dfo[fh_.islice(hs,ex)]);
      }
    } 
  }

  /*
  void Inverter_WilsonLike::test(Field& Df, const Field& f)const{
    
    Field ff(Df.size()/2,1.0);
    Field Dfe = D_->mult_ee(ff);          Dfe += D_->mult_ee(D_->mult_eo(ff));
    Field Dfo = D_->mult_oo(D_->mult_oe(ff)); Dfo += D_->mult_oo(ff);
    
    CCIO::cout<<"Df.norm()="<<sqrt(Dfe*Dfe+Dfo*Dfo)<<std::endl;

    for(int i=0;i<Dfe.size()/2;++i)
      CCIO::cout<<" Dfe["<<i<<"]=("<< Dfe[2*i]<<","<<Dfe[2*i+1]<<")"
		<<" Dfo["<<i<<"]=("<< Dfo[2*i]<<","<<Dfo[2*i+1]<<")"
		<<std::endl;

    for(int ex=0; ex<fh_.Nex(); ++ex){
      for(int hs=0; hs<fh_.Nvol(); ++hs){
	Df.set(ff_.islice(idx_eo_->esec(hs),ex), Dfe[fh_.islice(hs,ex)]);
	Df.set(ff_.islice(idx_eo_->osec(hs),ex), Dfo[fh_.islice(hs,ex)]);
      }
    } 
  }
  */
}