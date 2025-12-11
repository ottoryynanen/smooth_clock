#include "timeprovider.h"

#include <QDateTime>

TimeProvider::TimeProvider(QObject *parent)
    : QObject{parent}
{
    m_timer.setTimerType(Qt::TimerType::PreciseTimer);
    m_timer.setSingleShot(true);
    m_timer.start(std::chrono::milliseconds{1000});
    connect(&m_timer, &QTimer::timeout, this, &TimeProvider::secondChanged);
    refreshAngles(QDateTime::currentDateTime().time());
}

qreal TimeProvider::hourAngle() const
{
    return m_hourAngle;
}

qreal TimeProvider::minuteAngle() const
{
    return m_minuteAngle;
}

qreal TimeProvider::secondAngle() const
{
    return m_secondAngle;
}

void TimeProvider::secondChanged()
{
    const auto time = QDateTime::currentDateTime().time();
    /* if msec is 500-999, offset is positive (from 500 to 1)
     * else offset is negative (from 0 to 499
     */
    const auto msec = time.msec();
    int offset = msec > 500 ? 1000 : 0;
    offset -= msec;
    m_timer.start(std::chrono::milliseconds{1000 + offset});
    refreshAngles(time);
    emit angleChanged();
}

void TimeProvider::refreshAngles(const QTime &time)
{
    m_secondAngle = 6.0 * time.second();
    const auto secondFraction = static_cast<qreal>(time.second()) / 60.0;
    m_minuteAngle = 6.0 * (static_cast<qreal>(time.minute()) + secondFraction);
    const auto minuteFraction = (static_cast<qreal>(time.minute()) + secondFraction) / 60.0;
    auto hour = time.hour();
    if (hour > 11)
        hour -= 12;
    m_hourAngle = 30.0 * (static_cast<qreal>(hour) + minuteFraction);
}
