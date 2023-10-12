//Adapted from The Cherno: https://gist.github.com/TheCherno/31f135eea6ee729ab5f26a6908eb3a5e
//Open in Chrome: chrome://tracing

#ifndef __XE_BENCHMARKER_H__
#define __XE_BENCHMARKER_H__

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <memory>

#include <thread>

#define DO_BENCHMARK

namespace xe
{
    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        uint32_t ThreadID;
    };

    struct BenchmarkSession
    {
        std::string Name;
        BenchmarkSession() = default;
        inline Benchmark(const std::string& name) : Name(name) {}
    };

    class Benchmarker
    {
    private:
        std::unique_ptr<BenchmarkSession> _currentSession;
        std::ofstream _outputStream;
        int _profileCount;
    public:
        Benchmarker()
            : _currentSession(nullptr), _profileCount(0)
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            _outputStream.open(filepath);
            WriteHeader();
            _currentSession = std::make_unique<BenchmarkSession>(name);
        }

        void EndSession()
        {
            WriteFooter();
            _outputStream.close();
            _currentSession = nullptr;
            _profileCount = 0;
        }

        void WriteProfile(const ProfileResult& result)
        {
            if (_profileCount++ > 0)
                _outputStream << ",";

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            _outputStream << "{";
            _outputStream << "\"cat\":\"function\",";
            _outputStream << "\"dur\":" << (result.End - result.Start) << ',';
            _outputStream << "\"name\":\"" << name << "\",";
            _outputStream << "\"ph\":\"X\",";
            _outputStream << "\"pid\":0,";
            _outputStream << "\"tid\":" << result.ThreadID << ",";
            _outputStream << "\"ts\":" << result.Start;
            _outputStream << "}";

            _outputStream.flush();
        }

        void WriteHeader()
        {
            _outputStream << "{\"otherData\": {},\"traceEvents\":[";
            _outputStream.flush();
        }

        void WriteFooter()
        {
            _outputStream << "]}";
            _outputStream.flush();
        }

        static Benchmarker& Get()
        {
            static Benchmarker instance;
            return instance;
        }
    };

    class BenchmarkTimer
    {
    public:
        BenchmarkTimer(const char* name)
            : _name(name), _stopped(false)
        {
            _startTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~BenchmarkTimer()
        {
            if (!_stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(_startTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Benchmarker::Get().WriteProfile({ _name, start, end, threadID });

            _stopped = true;
        }
    private:
        const char* _name;
        std::chrono::time_point<std::chrono::high_resolution_clock> _startTimepoint;
        bool _stopped;
    };
}

#ifdef DO_BENCHMARK
#define XEBenchmarkScope(name) xe::BenchmarkTimer timer##__LINE__(name)
#define XEBenchmarkFunction XEBenchmarkScope(__FUNCSIG__)
#else
#define XEBenchmarkScope(name)
#define XEBenchmarkFunction
#endif // DO_BENCHMARK

#endif //__XE_BENCHMARKER_H__
