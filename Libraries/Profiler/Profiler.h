#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>

namespace Profiler {

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string name;

		FloatingPointMicroseconds start;
		std::chrono::microseconds elapsedTime;
		std::thread::id threadID;
	};

	struct InstrumentationSession
	{
		std::string name;
	};

	class Profiler
	{
	private:
		std::mutex mutex;
		InstrumentationSession* currentSession;
		std::ofstream outputStream;
	public:
		Profiler();

		void beginSession(const std::string& name, const std::string& filepath = "results.json");

		void endSession();

		void writeProfile(const ProfileResult& result);

		static Profiler& Get() {
			static Profiler instance;
			return instance;
		}

	private:

		void writeHeader();

		void writeFooter();

		// Note: you must already own lock on mutex before
		// calling InternalEndSession()
		void internalEndSession();

	};

	class Timer
	{
	public:
		Timer(const char* name);

		~Timer();

		void stop();
	private:
		const char* name;
		std::chrono::time_point<std::chrono::steady_clock> startTimepoint;
		bool stopped;
	};
}

#define PROFILER 1
#if PROFILER
// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define IN_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define IN_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define IN_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define IN_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define IN_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define IN_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define IN_FUNC_SIG __func__
	#else
		#define IN_FUNC_SIG "IN_FUNC_SIG unknown!"
	#endif

	#define PROFILER_BEGIN_SESSION(name, filepath) ::Profiler::Profiler::Get().beginSession(name, filepath)
	#define PROFILER_END_SESSION() ::Profiler::Profiler::Get().endSession()
	#define PROFILER_SCOPE(name) ::Profiler::Timer timer##__LINE__(name);
	#define PROFILER_FUNCTION() PROFILER_SCOPE(IN_FUNC_SIG)
#else
	#define PROFILER_BEGIN_SESSION(name, filepath)
	#define PROFILER_END_SESSION()
	#define PROFILER_SCOPE(name)
	#define PROFILER_FUNCTION()
#endif