//
//  unit_test_framework.h
//  Algorithms
//
//  Created by longjianjiang on 2019/2/22.
//  Copyright © 2019 longjianjiang. All rights reserved.
//

#ifndef unit_test_framework_h
#define unit_test_framework_h

#include <iostream>
#include <exception>

namespace jiang {

#ifndef EMPTY_STRING
#define EMPTY_STRING
    const std::string empty = std::string();
#endif /* EMPTY_STRING */

    enum RUN_TIME_COMPLEXITY {
        LOG_N, N, N_LOG_N, N2, N3
    };

#ifndef UNIT_TEST_DATA_NOT_FOUND
#define UNIT_TEST_DATA_NOT_FOUND

    struct unit_test_data_not_found : public std::exception {
        const char *what() const throw() {
            return "Unable to find a suitable data-set.";
        }
    };

#endif

    class method_test_case {
    public:
        method_test_case() {}

        virtual ~method_test_case() {}

        virtual bool run() = 0;
    };

#define MAX_UNIT_TEST_RUNS_TO_SHOW 5
#define DEBUG_CALCULATIONS false
#define USE_RSS false

    template <typename T>
    class method_test_with_complexity_analysis : public method_test_case {
    };
}

#endif /* unit_test_framework_h */