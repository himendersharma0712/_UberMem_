#ifndef PROCESSDATA_H
#define PROCESSDATA_H

#include <QString>

struct ProcessInfo {
    unsigned int pid;
    QString name;
    QString status;      // "Foreground" or "Background"
    double cpuUsage;     // %
    double diskUsage;    // KB/s
    double pagefileUsage; // MB
    double memUsage; // In MB
    double importanceScore; // 0.0 to 1.0 (ML output)
};


#endif // PROCESSDATA_H
