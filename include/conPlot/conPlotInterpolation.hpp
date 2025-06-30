#pragma once

#include "output.hpp"

#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <vector>

using namespace std::literals;

namespace steppable::graphing
{
    void linearInterpolateFill(std::map<long long, long long>* data, long long xMin, long long xMax)
    {
        if (data->size() < 2)
            output::error("graphing::linearInterpolateFill"s,
                          "At least 2 points are required for linear interpolation."s);

        std::vector<long long> xs;
        std::vector<long long> ys;
        for (const auto& kv : *data)
        {
            xs.push_back(kv.first);
            ys.push_back(kv.second);
        }
        auto n = static_cast<long long>(xs.size());

        for (long long x = xMin; x <= xMax; ++x)
        {
            // Find the interval [x0, x1] for x (or clamp to endpoints)
            auto it = std::lower_bound(xs.begin(), xs.end(), x);
            long long idx1 = std::distance(xs.begin(), it);
            long long i0 = 0;
            long long i1 = 0;
            if (x <= xs.front())
            {
                i0 = 0;
                i1 = 1;
            }
            else if (x >= xs.back())
            {
                i0 = n - 2;
                i1 = n - 1;
            }
            else
            {
                i0 = idx1 - 1;
                i1 = idx1;
            }

            long long x0 = xs[i0];
            long long x1 = xs[i1];
            long long y0 = ys[i0];
            long long y1 = ys[i1];
            long double t = 0;
            if (x1 == x0)
                t = 0.0;
            else
                t = static_cast<long double>(x - x0) / static_cast<long double>(x1 - x0);
            long long y = llround(static_cast<long double>(y0) + (t * static_cast<long double>(y1 - y0)));
            (*data)[x] = y;
        }
    }

    void cubicInterpolateFill(std::map<long long, long long>* data, long long xMin, long long xMax)
    {
        if (data->size() < 4)
            linearInterpolateFill(data, xMin, xMax);
        std::vector<long long> xs;
        std::vector<long long> ys;
        for (const auto& kv : *data)
        {
            xs.push_back(kv.first);
            ys.push_back(kv.second);
        }
        auto n = static_cast<long long>(xs.size());

        for (long long x = xMin; x <= xMax; ++x)
        {
            // Find the correct window of 4 points for interpolation
            auto it = std::ranges::lower_bound(xs, x);
            long long idx1 = std::distance(xs.begin(), it);
            long long i1 = std::clamp(idx1 - 1, 1LL, n - 3);
            long long i0 = i1 - 1;
            long long i2 = i1 + 1;
            long long i3 = i1 + 2;

            if (x <= xs[1])
            {
                i0 = 0;
                i1 = 1;
                i2 = 2;
                i3 = 3;
            }
            if (x >= xs[n - 2])
            {
                i0 = n - 4;
                i1 = n - 3;
                i2 = n - 2;
                i3 = n - 1;
            }

            long long x0 = xs[i0];
            long long x1 = xs[i1];
            long long x2 = xs[i2];
            long long x3 = xs[i3];
            long long y0 = ys[i0];
            long long y1 = ys[i1];
            long long y2 = ys[i2];
            long long y3 = ys[i3];

            long double t0 = static_cast<long double>((x - x1) * (x - x2) * (x - x3)) /
                             static_cast<long double>((x0 - x1) * (x0 - x2) * (x0 - x3));
            long double t1 = static_cast<long double>((x - x0) * (x - x2) * (x - x3)) /
                             static_cast<long double>((x1 - x0) * (x1 - x2) * (x1 - x3));
            long double t2 = static_cast<long double>((x - x0) * (x - x1) * (x - x3)) /
                             static_cast<long double>((x2 - x0) * (x2 - x1) * (x2 - x3));
            long double t3 = static_cast<long double>((x - x0) * (x - x1) * (x - x2)) /
                             static_cast<long double>((x3 - x0) * (x3 - x1) * (x3 - x2));

            long long y = llround((static_cast<long double>(y0) * t0) + (static_cast<long double>(y1) * t1) +
                                  (static_cast<long double>(y2) * t2) + (static_cast<long double>(y3) * t3));
            (*data)[x] = y;
        }
    }
} // namespace steppable::graphing
