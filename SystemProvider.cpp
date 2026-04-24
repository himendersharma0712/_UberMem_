#include "SystemProvider.h"
#include <windows.h>

SystemProvider::SystemProvider(QObject *parent) : QObject(parent) {
    // Initialize CPU times
    GetSystemTimes(&m_prevIdleTime, &m_prevKernelTime, &m_prevUserTime);

    // Pre-fill history so the graph doesn't start empty
    for(int i = 0; i < 60; i++) {
        m_ramHistory.append(0.0);
    }

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SystemProvider::updateStats);
    m_timer->start(1000); // Update every 1 second
}

uint64_t SystemProvider::fileTimeToUint64(const FILETIME &ft) {
    return (((uint64_t)ft.dwHighDateTime) << 32) | ((uint64_t)ft.dwLowDateTime);
}

void SystemProvider::updateStats() {
    // --- RAM USAGE ---
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memInfo)) {
        m_ramUsage = memInfo.dwMemoryLoad;
        emit ramUsageChanged();

        // Push to history
        m_ramHistory.append(m_ramUsage);
        if (m_ramHistory.size() > 60) {
            m_ramHistory.removeFirst();
        }
        emit ramHistoryChanged();
    }

    // --- CPU USAGE ---
    FILETIME idleTime, kernelTime, userTime;
    if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        uint64_t idle = fileTimeToUint64(idleTime) - fileTimeToUint64(m_prevIdleTime);
        uint64_t kernel = fileTimeToUint64(kernelTime) - fileTimeToUint64(m_prevKernelTime);
        uint64_t user = fileTimeToUint64(userTime) - fileTimeToUint64(m_prevUserTime);

        uint64_t sys = kernel + user;
        if (sys > 0) {
            m_cpuUsage = (sys - idle) * 100.0 / sys;
            emit cpuUsageChanged();
        }

        m_prevIdleTime = idleTime;
        m_prevKernelTime = kernelTime;
        m_prevUserTime = userTime;
    }


    // Calculate Velocity (m) over the last 5 seconds
    if (m_ramHistory.size() >= 10) {
        double now = m_ramHistory.last().toDouble();
        double then = m_ramHistory.at(m_ramHistory.size() - 6).toDouble();

        m_m_pressureVelocity = (now - then) / 5.0; // % per second
        emit pressureVelocityChanged();
    }
}