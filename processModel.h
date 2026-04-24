#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "processData.h"

class ProcessModel : public QAbstractTableModel {
    Q_OBJECT

public:
    enum ProcessRoles {
        PidRole = Qt::UserRole + 1,
        NameRole,
        StatusRole,    // NEW
        CpuRole,       // NEW
        RawMemRole,
        MemRole,
        DiskRole,      // NEW
        PagefileRole,  // NEW
        PredictionRole
    };

    explicit ProcessModel(QObject *parent = nullptr);

    // Table requirements
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void refreshProcesses(); // Call this to update the list

    void setGamingMode(bool active) {
        m_isGamingMode = active;
        refreshProcesses(); // Force an immediate update when toggled
    }
    bool isGamingMode() const { return m_isGamingMode; }

    Q_INVOKABLE void purgeRiskProcesses();

    Q_INVOKABLE void setAutoMode(bool enabled) {
        m_autoMode = enabled;
    }

private:
    QVector<ProcessInfo> m_processes;
    bool m_isGamingMode = false;
    bool m_autoMode = false;
    qint64 m_lastAutoPurge = 0;
};

#endif // PROCESSMODEL_H
