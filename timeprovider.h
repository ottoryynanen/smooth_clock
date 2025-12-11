#ifndef TIMEPROVIDER_H
#define TIMEPROVIDER_H

#include <QObject>
#include <QQmlEngine>
#include <QTime>
#include <QTimer>

class TimeProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(qreal hourAngle READ hourAngle NOTIFY angleChanged FINAL)
    Q_PROPERTY(qreal minuteAngle READ minuteAngle NOTIFY angleChanged FINAL)
    Q_PROPERTY(qreal secondAngle READ secondAngle NOTIFY angleChanged FINAL)
public:
    explicit TimeProvider(QObject *parent = nullptr);
    qreal hourAngle() const;
    qreal minuteAngle() const;
    qreal secondAngle() const;

signals:
    void angleChanged();

private slots:
    void secondChanged();

private:
    void refreshAngles(const QTime &time);
    QTimer m_timer{};
    qreal m_hourAngle{};
    qreal m_minuteAngle{};
    qreal m_secondAngle{};
};

#endif // TIMEPROVIDER_H
