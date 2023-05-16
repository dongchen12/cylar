#ifndef CYLAR_LOG_H
#define CYLAR_LOG_H

#include<string>
#include<memory>

namespace cylar {

    // 定义日志事件
    class LogEvent {
    public:
        typedef std::shared_ptr <LogEvent> ptr;

        LogEvent();

    private:
        const char *m_file = nullptr;   // 文件名
        int32_t m_line = 0;             // 行号
        uint32_t m_elapse = 0;          // 程序启动后毫秒数
        uint32_t m_threadId = 0;        // 线程号
        uint32_t m_fiberId = 0;           // 协程id
        uint64_t m_time;                // 时间戳
        std::string m_content;
    };

    // 日志格式
    class LogLevel {
    public:
        enum Level {
            DEBUG = 1;
            INFO = 2;
            WARN = 3;
            ERROR = 4;
            FATAL = 5;
        };
    };

    // 日志格式器
    class LogFormatter {
    public:
        typedef std::shared_ptr <LogFormatter> ptr;

        std::string format(LogEvent::ptr event);
    };

    // 日志器
    class Logger {
    public:
        typedef std::shared_ptr <Logger> ptr;

        Logger(const std::string &name = "root");

        void log(LogLevel::Level level, LogEvent::ptr event);

        void debug(LogEvent::ptr event);

        void info(LogEvent::ptr event);

        void warn(LogEvent::ptr event);

        void error(LogEvent::ptr event)

        void fatal(LogEvent::ptr event);

        void addAppender(LogAppender::ptr appender);

        void delAppender(LogAppender::ptr appender);

        LogLevel::Level getLevel() const { return m_level; };

        void setLevel(LogLevel::Level level) { m_level = level; };
    private:
        LogLevel::Level m_level;
        std::string m_name;
        std::list <LogAppender::ptr> m_appenders;
    };

    // 日志输出地
    class LogAppender {
    public:
        virtual ~LogAppender();

        typedef std::shared_ptr <LogAppender> ptr;

        void log(LogLevel::Level level, LogEvent::ptr event);

    private:
        LogLevel::Level m_level;
    };

    // 输出到控制台
    class StdoutLogAppender : public LogAppender {

    };

    // 输出到文件
    class FileLogAppender : public LogAppender {

    };

}

#endif //CYLAR_LOG_H
