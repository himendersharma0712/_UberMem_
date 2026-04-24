#ifndef SYSTEMPROVIDER_H
#define SYSTEMPROVIDER_H

#include <QObject>
#include <QTimer>
#include <QVariantList>
#include <windows.h>

class SystemProvider : public QObject {
    Q_OBJECT
    Q_PROPERTY(double ramUsage READ ramUsage NOTIFY ramUsageChanged)
    Q_PROPERTY(double cpuUsage READ cpuUsage NOTIFY cpuUsageChanged)
    Q_PROPERTY(QVariantList ramHistory READ ramHistory NOTIFY ramHistoryChanged)
    Q_PROPERTY(double pressureVelocity READ pressureVelocity NOTIFY pressureVelocityChanged)

public:
    explicit SystemProvider(QObject *parent = nullptr);
    double ramUsage() const { return m_ramUsage; }
    double cpuUsage() const { return m_cpuUsage; }
    QVariantList ramHistory() const { return m_ramHistory; }
    double pressureVelocity() const { return m_m_pressureVelocity; }

signals:
    void ramUsageChanged();
    void cpuUsageChanged();
    void ramHistoryChanged();
    void pressureVelocityChanged();

public slots:
    void updateStats();

private:
    double m_ramUsage = 0.0;
    double m_cpuUsage = 0.0;
    QVariantList m_ramHistory;
    QTimer *m_timer;
    double m_m_pressureVelocity = 0.0;

    // CPU calculation helpers
    FILETIME m_prevIdleTime;
    FILETIME m_prevKernelTime;
    FILETIME m_prevUserTime;
    uint64_t fileTimeToUint64(const FILETIME &ft);
};

#endif // SYSTEMPROVIDER_H