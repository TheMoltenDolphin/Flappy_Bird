#include "Func.hpp"

TimeOfDay getNextTimeOfDay(TimeOfDay t) {
    switch (t) {
        case TimeOfDay::Morning : return TimeOfDay::Day;
        case TimeOfDay::Day : return TimeOfDay::Evening;
        case TimeOfDay::Evening : return TimeOfDay::Night;
        case TimeOfDay::Night : return TimeOfDay::Morning;
    }
    return TimeOfDay::Morning;
}