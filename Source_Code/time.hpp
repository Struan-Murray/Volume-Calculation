#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

intmax_t slowtime(){
	// Create a time point based on the system clock.
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now(); 

	// Get a duration based on now - epoch
	auto duration = now.time_since_epoch();

	// Cast that into seconds
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();

	intmax_t iseconds = (intmax_t)seconds;
	
	return iseconds;
}

#endif
