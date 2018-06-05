#pragma once
#include <boost/signals2.hpp>

using Signal = boost::signals2::signal<void()>;
using SignalSlot = Signal::slot_type;

using SignalConnection = boost::signals2::connection;
using ScopedSignalConnection = boost::signals2::scoped_connection;
