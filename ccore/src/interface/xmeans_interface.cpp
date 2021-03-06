/**
*
* Copyright (C) 2014-2017    Andrei Novikov (pyclustering@yandex.ru)
*
* GNU_PUBLIC_LICENSE
*   pyclustering is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   pyclustering is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#include "interface/xmeans_interface.h"

#include "cluster/xmeans.hpp"
#include "utils.hpp"


pyclustering_package * xmeans_algorithm(const pyclustering_package * const p_sample, const pyclustering_package * const p_centers, const std::size_t p_kmax, const double p_tolerance, const unsigned int p_criterion) {
    dataset data, centers;
    p_sample->extract(data);
    p_centers->extract(centers);

    cluster_analysis::xmeans solver(centers, p_kmax, p_tolerance, (cluster_analysis::splitting_type) p_criterion);

    cluster_analysis::xmeans_data output_result;
    solver.process(data, output_result);

    pyclustering_package * package = create_package(output_result.clusters().get());
    return package;
}
