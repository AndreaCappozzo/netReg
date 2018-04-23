/**
 * netReg: graph-regularized linear regression models.
 * <p>
 * Copyright (C) 2015 - 2016 Simon Dirmeier
 * <p>
 * This file is part of netReg.
 * <p>
 * netReg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * <p>
 * netReg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * <p>
 * You should have received a copy of the GNU General Public License
 * along with netReg. If not, see <http://www.gnu.org/licenses/>.
 *
 * @author: Simon Dirmeier
 * @email: simon.dirmeier@gmx.de
 */

#ifndef NETREG_EDGENET_HPP
#define NETREG_EDGENET_HPP


#include <vector>
#include "params.hpp"
#include "graph_model_data.hpp"
#include "graph_model_cv_data.hpp"
#include "cv_fold.hpp"
#include "math_functions.hpp"
#include "stat_functions.hpp"

#ifdef USE_RCPPARMADILLO
// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#else
#include "armadillo"
#endif

namespace netreg
{
    /**
     * Class for estimating the coefficients of a edge-regularized linear
     * regression model.
     */
    class edgenet
    {
    public:

        edgenet(graph_model_data& data, params& pars):
          DATA_(data),
          LX_(data.lx_rows()),
          LY_(data.ly()),
          P_(static_cast<unsigned int>(data.covariable_count())),
          Q_(static_cast<unsigned int>(data.response_count())),
          lambda_(pars.lambda()),
          psigx_(pars.psigx()),
          psigy_(pars.psigy()),
          NITER_(pars.niter()),
          THRESH_(pars.thresh())
        {}

        /**
         * Calulates the coefficients of a graph-regularized regression model.
         *
         * @param data an object that holds all required data for the model
         */
        arma::Mat<double> run();

        /**
         * Calculates the optimal set of shrinkage parameters of a
         * graph-regularized regression model.
         *
         * @param lambda the shrinkage parameter you want to use for the LASSO
         * @param psigx penalization of laplacian for X
         * @param psigy penalization of laplacian for Y
         * @param fold the fold you want to use of the data
         *
         * @return returns the estimated coefficients
         */
        arma::Mat<double> run_cv(double lambda,
                                 double psigx,
                                 double psigy,
                                 cv_fold& fold) const;

        void set_lambda(double lambda) const
        {
            lambda_ = lambda;
        }

        void set_psigx(double psigx) const
        {
            psigx_ = psigx;
        }

        void set_psigy(double psigy) const
        {
            psigy_ = psigy;
        }

    protected:
        arma::Mat<double> mccd_(std::vector<arma::rowvec>& txx_rows,
                                arma::Mat<double>& txy) const;

        void uccd_(int qi,
                   std::vector<arma::rowvec>& txx_rows,
                   arma::Mat<double>& txy,
                   arma::Mat<double>& B,
                   arma::Mat<double>& B_old,
                   std::vector<arma::rowvec>& B_rows) const;

        inline void set_params(double& s,
                               double& norm,
                               const int pi,
                               const int qi,
                               arma::rowvec& txx_row,
                               arma::Mat<double>& txy,
                               arma::Mat<double>& B,
                               arma::rowvec& B_row) const
        {
            s = partial_least_squares(txx_row, txy, B, pi, qi);
            norm = txx_row(pi);
            graph_penalize(s, norm, pi, qi, B, B_row);
        }

        inline void graph_penalize(double& s,
                                   double& norm,
                                   const int pi,
                                   const int qi,
                                   arma::Mat<double>& B,
                                   arma::rowvec& B_row) const
        {
            if (psigx_ > 0.001 && LX_.size() == P_)
                lx_penalize(s, norm, pi, qi, B);
            if (psigy_ > 0.001 && LY_.n_rows == Q_ && Q_ > 1)
                ly_penalize(s, norm, pi, qi, B_row);
        }

        inline void lx_penalize(double& s,
                                double& norm,
                                const int pi,
                                const int qi,
                                arma::Mat<double>& B) const
        {
            double xPenalty =
              -LX_[pi](pi) * B(pi, qi) + arma::accu(LX_[pi] * B.col(qi));
            s = s - 2 * psigx_ * xPenalty;
            norm += 2 * psigx_ * LX_[pi](pi);
        }

        inline void ly_penalize(double& s,q
                                double& norm,
                                const int pi,
                                const int qi,
                                arma::rowvec& B_row) const
        {
            double yPenalty = -B_row(qi) * LY_(qi, qi)
                              + arma::accu(B_row * LY_.col(qi));
            s = s - 2 * psigy_ * yPenalty;
            norm += 2 * psigy_ * LY_(qi, qi);
        }

    private:
        inline bool converged_(const arma::vec& v1,
                               const arma::vec& v2,
                               int iter) const
        {
            return l1(v1, v2) > THRESH_ && iter < NITER_;
        }

        graph_model_data& DATA_;
        std::vector<arma::Row<double>>& LX_;
        arma::Mat<double>& LY_;
        unsigned int P_;
        unsigned int Q_;
        mutable double lambda_;
        mutable double psigx_;
        mutable double psigy_;
        int NITER_;
        double THRESH_;

    };
}

#endif
