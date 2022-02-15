#pragma once
#include <algorithm>
#include <limits>
#include <math.h>

#include "Vector3.h"
#include <iomanip>

using std::endl;
using std::max;
using std::min;

namespace Mearth
{
    class AABB {
      public:
        Vector3<double> min;
        Vector3<double> max;
        Vector3<double> size;

        AABB() {
            min = Vector3<double>(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
                                  std::numeric_limits<double>::max());
            max = Vector3<double>(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max(),
                                  -std::numeric_limits<double>::max());
            size = Vector3<double>(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
                                   std::numeric_limits<double>::max());
        }

        AABB(Vector3<double> min, Vector3<double> max) {
            this->min = min;
            this->max = max;
            size = max - min;
        }

        bool isInside(const Vector3<double>& p) {
            if (min.x <= p.x && p.x <= max.x) {
                if (min.y <= p.y && p.y <= max.y) {
                    if (min.z <= p.z && p.z <= max.z) {
                        return true;
                    }
                }
            }

            return false;
        }

        Vector3<double> center() const {
            return (max + min) / 2;
        }

        void update(const Vector3<double>& point) {
            min.x = std::min(min.x, point.x);
            min.y = std::min(min.y, point.y);
            min.z = std::min(min.z, point.z);

            max.x = std::max(max.x, point.x);
            max.y = std::max(max.y, point.y);
            max.z = std::max(max.z, point.z);

            size = max - min;
        }

        void update(const AABB& aabb) {
            min.x = std::min(min.x, aabb.min.x);
            min.y = std::min(min.y, aabb.min.y);
            min.z = std::min(min.z, aabb.min.z);

            max.x = std::max(max.x, aabb.max.x);
            max.y = std::max(max.y, aabb.max.y);
            max.z = std::max(max.z, aabb.max.z);

            size = max - min;
        }

        void makeCubic() {
            max = min + Vector3<double>(size.maxValue(), size.maxValue(), size.maxValue());
            size = max - min;
        }

        friend ostream& operator<<(ostream& output, const AABB& value) {
            output << "min: " << value.min << endl;
            output << "max: " << value.max << endl;
            output << "size: " << value.size << endl;
            return output;
        }

        void reset() {
            min = Vector3<double>(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
                                  std::numeric_limits<double>::max());
            max = Vector3<double>(-std::numeric_limits<double>::max(), -std::numeric_limits<double>::max(),
                                  -std::numeric_limits<double>::max());
            size = Vector3<double>(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
                                   std::numeric_limits<double>::max());
        }

        AABB operator+(Vector3<double> offset) {
            AABB noOffset = *this;
            noOffset.min += offset;
            noOffset.max += offset;
            return noOffset;
        };
    };

}  // namespace Mearth
