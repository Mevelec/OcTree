#include "Profiler.h"
#include <Logger.h>
namespace Profiler {
	Profiler::Profiler()
		: currentSession(nullptr)
	{
	}

	void Profiler::beginSession(const std::string& name, const std::string& filepath)
	{
		CORE_INFO("Profiler::BeginSession('{0}') with path('{1}').", name, filepath);
		std::lock_guard<std::mutex> lock(this->mutex);
		if (this->currentSession) {
			// If there is already a current session, then close it before beginning new one.
			// Subsequent profiling output meant for the original session will end up in the
			// newly opened session instead.  That's better than having badly formatted
			// profiling output.
			if (Logger::Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
				CORE_ERROR("Profiler::BeginSession('{0}') when session '{1}' already open.", name, this->currentSession->name);
			}
			this->internalEndSession();
		}
		this->outputStream.open(filepath);

		if (this->outputStream.is_open()) {
			this->currentSession = new InstrumentationSession({ name });
			this->writeHeader();
		}
		else {
			if (Logger::Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
				CORE_ERROR("Profiler could not open results file '{0}'.", filepath);
			}
		}
	}

	void Profiler::endSession()
	{
		std::lock_guard<std::mutex> lock(this->mutex);
		this->internalEndSession();
	}

	void Profiler::writeProfile(const ProfileResult& result)
	{
		std::stringstream json;

		std::string name = result.name;
		std::replace(name.begin(), name.end(), '"', '\'');

		json << std::setprecision(3) << std::fixed;
		json << ",{";
		json << "\"cat\":\"function\",";
		json << "\"dur\":" << (result.elapsedTime.count()) << ',';
		json << "\"name\":\"" << name << "\",";
		json << "\"ph\":\"X\",";
		json << "\"pid\":0,";
		json << "\"tid\":" << result.threadID << ",";
		json << "\"ts\":" << result.start.count();
		json << "}";

		std::lock_guard<std::mutex> lock(this->mutex);
		if (this->currentSession) {
			this->outputStream << json.str();
			this->outputStream.flush();
		}
	}

	void Profiler::writeHeader()
	{
		this->outputStream << "{\"otherData\": {},\"traceEvents\":[{}";
		this->outputStream.flush();
	}

	void Profiler::writeFooter()
	{
		this->outputStream << "]}";
		this->outputStream.flush();
	}

	// Note: you must already own lock on mutex before
	// calling InternalEndSession()
	void Profiler::internalEndSession() {
		if (this->currentSession) {
			this->writeFooter();
			this->outputStream.close();
			delete this->currentSession;
			this->currentSession = nullptr;
		}
	}
}

namespace Profiler {
	Timer::Timer(const char* name)
		: name(name), stopped(false)
	{
		this->startTimepoint = std::chrono::steady_clock::now();
	}

	Timer::~Timer()
	{
		if (!this->stopped)
			this->stop();
	}

	void Timer::stop()
	{
		auto endTimepoint = std::chrono::steady_clock::now();
		auto highResStart = FloatingPointMicroseconds{ this->startTimepoint.time_since_epoch() };
		auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(this->startTimepoint).time_since_epoch();

		Profiler::Get().writeProfile({ this->name, highResStart, elapsedTime, std::this_thread::get_id() });

		this->stopped = true;
	}
}