#include "log.h"

namespace cylar {

    void Logger::addAppender(LogAppender::ptr appender) {
        m_appenders.push_back(appender);
    }

    void Logger::delAppender(LogAppender::ptr appender) {
        for (auto it = m_appenders.begin(); it != m_appenders.end(); it++) {
            if (*it == appender) {
                m_appenders.erase(it);
                break;
            }
        }
    }

    void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
        if (level >= m_level) {
            for (auto i = m_appenders.begin(); i != m_appenders.end(); i++) {
                i->log(level, event);
            }
        }
    }
}