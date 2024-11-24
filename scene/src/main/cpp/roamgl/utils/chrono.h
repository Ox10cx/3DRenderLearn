//
// Created by gongxi on 2024/11/24.
//

#ifndef ASSIMPDEMO_CHRONO_H
#define ASSIMPDEMO_CHRONO_H

#include <chrono>
#include <string>

namespace roamgl {

    using Clock = std::chrono::steady_clock;
    using Seconds = std::chrono::seconds;
    using Milliseconds = std::chrono::milliseconds;

    using TimePoint = Clock::time_point;
    using Duration  = Clock::duration;

// Used to measure second-precision times, such as times gathered from HTTP responses.
    using Timestamp = std::chrono::time_point<std::chrono::system_clock, Seconds>;
}

#endif //ASSIMPDEMO_CHRONO_H
