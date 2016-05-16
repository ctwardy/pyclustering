/**
*
* Copyright (C) 2014-2016    Andrei Novikov (pyclustering@yandex.ru)
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

#include "interface/kmedians_interface.h"

#include "cluster/kmedians.hpp"


pyclustering_package * kmedians_algorithm(const data_representation * const sample, const data_representation * const initial_medians, const double tolerance) {
    std::unique_ptr<dataset> data(read_sample(sample));
    std::unique_ptr<dataset> medians(read_sample(initial_medians));

    cluster_analysis::kmedians algorithm(*medians, tolerance);

    cluster_analysis::kmedians_data output_result;
    algorithm.process(*data, output_result);

    pyclustering_package * package = new pyclustering_package((unsigned int) pyclustering_type_data::PYCLUSTERING_TYPE_LIST);
    package->size = output_result.size();
    package->data = new pyclustering_package * [package->size];

    for (unsigned int i = 0; i < package->size; i++) {
        ((pyclustering_package **) package->data)[i] = create_package(&output_result[i]);
    }

    return package;
}
