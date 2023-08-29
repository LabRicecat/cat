#ifndef CAT_LIFESPAN_HPP
#define CAT_LIFESPAN_HPP

#include <functional>
#include <vector>
#include <map>
#include <thread>
#include <chrono>

#include "drawing.hpp"
#include "signals.hpp"
#include "config.hpp"

namespace cat {

enum class Priority {
    HIGH,
    NORMAL,
    LOW
};

using process = std::function<void()>;
using process_queue = std::vector<process>; 

static inline std::map<Priority,process_queue> processes;
static inline std::map<Priority,process_queue> async_processes;

void pass_input(int input);

void update();

void cycle();

void queue_process(const Priority& priority, const process& process);
void async(const Priority& priority, const process& process);

} // namespace cat

#endif
