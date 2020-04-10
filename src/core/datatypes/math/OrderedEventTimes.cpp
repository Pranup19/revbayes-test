/*
 * EventTime.cpp
 *
 *  Created on: Apr 9, 2020
 *      Author: mike
 */

#include <ostream>

#include "OrderedEventTimes.h"

namespace RevBayesCore {

OrderedEventTimes::OrderedEventTimes()
{
}

OrderedEventTimes::~OrderedEventTimes()
{
}

OrderedEventTimes* OrderedEventTimes::clone(void) const
{
    return new OrderedEventTimes( *this );
}

bool OrderedEventTimes::operator==(const OrderedEventTimes &oet) const
{
	return event_times == oet.event_times;
}

bool OrderedEventTimes::operator!=(const OrderedEventTimes &oet) const
{
	return event_times != oet.event_times;
}

bool OrderedEventTimes::operator<(const  OrderedEventTimes &oet) const
{
	return false;
}


bool OrderedEventTimes::addEvent(double time)
{
	// check if the event already exists
	std::set<double>::iterator it = event_times.find(time);
	if ( it != event_times.end() )
	{
		// event found
		return false;
	}

	// otherwise, add the event
	event_times.insert(time);

	return true;
}

bool OrderedEventTimes::removeEvent(double time)
{
	// check if the event exists
	std::set<double>::iterator it = event_times.find(time);
	if ( it == event_times.end() )
	{
		// event not found
		return false;
	}

	// otherwise, remove the event
	event_times.erase(it);

	return true;
}

bool OrderedEventTimes::changeEventTime(double old_time, double new_time)
{
	// check if the event exists
	std::set<double>::iterator it = event_times.find(old_time);
	if ( it == event_times.end() )
	{
		// event not found
		return false;
	}

	// otherwise, remove the event
	event_times.erase(it);

	// add a new event
	event_times.insert(new_time);

	return true;
}


const std::set<double>& OrderedEventTimes::getEventTimes() const
{
	return event_times;
}

size_t OrderedEventTimes::size() const
{
	return event_times.size();
}

} /* namespace RevBayesCore */



std::ostream& RevBayesCore::operator<<(std::ostream& o, const RevBayesCore::OrderedEventTimes& x)
{
	size_t num_events = x.size();
	const std::set<double>& events = x.getEventTimes();
	o << "[ ";
	std::set<double>::const_iterator it = events.begin();
	for(size_t i = 1; i < num_events ; ++i)
	{
		o << *it << ", ";
		++it;
	}
	if ( it != events.end() )
	{
		o << *it;
	}
	o << " ]";

	return o;
}



