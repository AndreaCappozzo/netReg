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

#ifndef NETREG_LINEAR_MODEL_DATA_HPP
#define NETREG_LINEAR_MODEL_DATA_HPP

#include <vector>
#include <string>
#include <utility>

#ifdef USE_RCPPARMADILLO
// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#else
#include "armadillo"
#endif
#include "family.hpp"

namespace netreg
{
    /**
     * Data-structure for all required data for a linear model
     */
    class linear_model_data
    {
    protected:

<<<<<<< HEAD
        linear_model_data()
        {}

=======
>>>>>>> upstream/master
        /**
         * Protected constructor in order to avoid instantiation.
         *
         * @param x the design matrix as pointer
         * @param y the desponse matrix as pointer
         * @param n number of samples
         * @param p number of covariables
         * @param q number of responses
         * @param niter maximal number of iterations
         * @param thresh the convergence threshold
         * @param fam of distribution of y
         */
        linear_model_data(double *x, double *y,
                          const int n, const int p, const int q,
                          const int niter, const double thresh,
                          const family fam)
            : N(n), P(p), Q(q),
<<<<<<< HEAD
              X(x, n, p, false, true),
=======
              X(x, n, p , false, true),
>>>>>>> upstream/master
              Y(y, n, q, false, true),
              THRESH(thresh), N_ITER(niter),
              TXY(p, q), txx_rows_(p),
              family_(fam)
        {
            arma::Mat<double> TX = X.t();
            arma::Mat<double> TXX = TX * X;
            TXY = TX * Y;
<<<<<<< HEAD
            for (std::vector<arma::Row<double> >::size_type i = 0;
                 i < TXX.n_rows; ++i)
=======
            for(std::vector< arma::Row<double> >::size_type i = 0; i < TXX.n_rows;  ++i)
>>>>>>> upstream/master
            {
                txx_rows_[i] = TXX.row(i);
            }
        }

    public:

        /**
         * Getter for the family of the distribution of the response.
         *
         * @return returns the family
         */
        const family distribution_family()
        {
            return family_;
        }

        /**
         * Getter for number of samples.
         *
         * @return returns the number of samples
         */
        const int sample_count()
        {
            return N;
        }

        /**
         * Getter for number of responses.
         *
         * @return returns the number of responses
         */
        const int response_count()
        {
            return Q;
        }

        /**
         * Getter for number of covariables.
         *
         * @return returns the number of covariables
         */
        const int covariable_count()
        {
            return P;
        }

        arma::rowvec& txx_row(const int i)
        {
            return txx_rows_[i];
        }

<<<<<<< HEAD
        std::vector<arma::rowvec>& txx_rows()
=======
        std::vector< arma::rowvec >& txx_rows()
>>>>>>> upstream/master
        {
            return txx_rows_;
        }

        /**
         * Getter for the design matrix.
         *
         * @return a reference to the design matrix
         */
<<<<<<< HEAD
        arma::Mat<double>& design()
=======
         arma::Mat<double> &design()
>>>>>>> upstream/master
        {
            return X;
        }

        /**
         * Getter for the response matrix.
         *
         * @return a reference to the response matrix
         */
<<<<<<< HEAD
        arma::Mat<double>& response()
=======
         arma::Mat<double> &response()
>>>>>>> upstream/master
        {
            return Y;
        }

        /**
         * Getter for X'Y matrix.
         *
         * @return a reference to X'Y matrix.
         */
<<<<<<< HEAD
        arma::Mat<double>& txy()
=======
        arma::Mat<double> &txy() 
>>>>>>> upstream/master
        {
            return TXY;
        }

        /**
         * Getter for the number of maximal iterations.
         *
         * @return the max number of iterations
         */
<<<<<<< HEAD
        const int max_iter()
=======
        const int max_iter() 
>>>>>>> upstream/master
        {
            return N_ITER;
        }

        /**
         * Getter for the convergence threshold of CCD.
         *
         * @return the convergence threshold.
         */
        double threshold()
        {
            return THRESH;
        }

    protected:
<<<<<<< HEAD
        int N;             // number of samples: n
        int P;             // number of covariables: p
        int Q;             // number of responses: q
        arma::Mat<double> X;        // (n x p)-dimensional design matrix
        arma::Mat<double> Y;        // (n x q)-dimensional response matrix
        double THRESH;     // convergence threshold
        int N_ITER;        // max number iterations if CCD does not converge
        arma::Mat<double> TXY;      // (p x q)-dimensional matrix: X'Y
        std::vector<arma::Row<double> > txx_rows_;
        enum family family_;      // family of distribution of y
=======
        const int N;             // number of samples: n
        const int P;             // number of covariables: p
        const int Q;             // number of responses: q
        arma::Mat<double> X;        // (n x p)-dimensional design matrix
        arma::Mat<double> Y;        // (n x q)-dimensional response matrix
        const double THRESH;     // convergence threshold
        const int N_ITER;        // max number iterations if CCD does not converge
        arma::Mat<double> TXY;      // (p x q)-dimensional matrix: X'Y
        std::vector< arma::Row<double> > txx_rows_;
        const enum family family_;      // family of distribution of y
>>>>>>> upstream/master
    };
}
#endif //NETREG_LINEARMODELDATA_HPP
