/**
 * Author: Simon Dirmeier
 * Email: netreg@simon-dirmeier.net
 */

#include "edgenet_model_selection.hpp"

#ifndef ARMA_DONT_USE_WRAPPER
#define ARMA_DONT_USE_WRAPPER
#endif
#include <armadillo>

#include <numeric>
#include <vector>

#include "edgenet_loss_function.hpp"
#include "optim.hpp"

namespace netreg
{
    std::vector<double>
    edgenet_model_selection::regularization_path
        (graph_penalized_linear_model_data &data, const int nfolds,
         std::vector<int> &folds)
    {
        cv_set cvset(data.design().n_rows, nfolds);
        return regularization_path_(data, cvset, folds);
    }

    std::vector<double>
    edgenet_model_selection::regularization_path
        (graph_penalized_linear_model_data &data, int *const foldid,
         std::vector<int> &folds)
    {
        cv_set cvset(data.design().n_rows, foldid);
        return regularization_path_(data, cvset, folds);
    }

    std::vector<double>
    edgenet_model_selection::regularization_path_
        (graph_penalized_linear_model_data &data, cv_set &cvset,
         std::vector<int> &folds)
    {
        if (static_cast<int>(folds.size()) != data.sample_count())
            folds.resize(data.sample_count());
        for (int i = 0; i < cvset.fold_count(); i++)
        {
            cv_fold &fold = cvset.get_fold(i);
            for (arma::uvec::iterator j = fold.test_set().begin();
                 j != fold.test_set().end(); ++j)
                folds[*j] = i;
        }

        optim opt;
        std::vector<double> start{0, 0, 0};
        std::vector<double> lower_bound{0.0, 0.0, 0.0};
        std::vector<double> upper_bound{100.0, 10000.0, 10000.0};
        const double rad_start = 0.49, rad_end = 1e-6;
        const int niter = 1000;
        return opt.bobyqa<edgenet_loss_function>
                      (data, cvset,
                       start, lower_bound, upper_bound,
                       rad_start, rad_end, niter);
    }
}