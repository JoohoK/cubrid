/*
 * Copyright 2008 Search Solution Corporation
 * Copyright 2016 CUBRID Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

/*
 * timers.hpp - time stuff maybe to compare performance
 */

#ifndef _TEST_TIMERS_HPP_
#define _TEST_TIMERS_HPP_

#include <chrono>

namespace test_common
{

/* timer - time durations between checkpoints.
 *
 *  Templates:
 *
 *      Units - desired duration unit.
 */
template <typename Units>
class timer
{
  public:
    inline timer ()
    {
      reset ();
    }

    inline Units time ()
    {
      return (std::chrono::duration_cast<Units> (get_now () - m_saved_time));
    }

    inline void reset ()
    {
      m_saved_time = get_now ();
    }

    inline Units time_and_reset ()
    {
      Units diff = time ();
      reset ();
      return diff;
    }

  private:

    static inline std::chrono::system_clock::time_point get_now (void)
    {
      return std::chrono::system_clock::now ();
    }

    std::chrono::system_clock::time_point m_saved_time;
};

/* Specialization for microseconds and milliseconds */
typedef class timer<std::chrono::milliseconds> ms_timer;
typedef class timer<std::chrono::microseconds> us_timer;

} // namespace test_common

#endif // _TEST_TIMERS_HPP_
