#ifndef VOICECALLHANDLER_H
#define VOICECALLHANDLER_H

#include <QObject>
#include <QDateTime>

#include <QDBusPendingCallWatcher>

class VoiceCallHandler : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString handlerId READ handlerId)
    Q_PROPERTY(QString providerId READ providerId)
    Q_PROPERTY(int status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusChanged)
    Q_PROPERTY(QString lineId READ lineId NOTIFY lineIdChanged)
    Q_PROPERTY(QDateTime startedAt READ startedAt)
    Q_PROPERTY(int duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(bool isEmergency READ isEmergency NOTIFY emergencyChanged)
    Q_PROPERTY(bool isMultiparty READ isMultiparty NOTIFY multipartyChanged)

public:
    explicit VoiceCallHandler(const QString &handlerId, QObject *parent = 0);
            ~VoiceCallHandler();

    QString handlerId() const;
    QString providerId() const;
    int status() const;
    QString statusText() const;
    QString lineId() const;
    QDateTime startedAt() const;
    int duration() const;
    bool isMultiparty() const;
    bool isEmergency() const;

Q_SIGNALS:
    void error(const QString &error);
    void statusChanged();
    void lineIdChanged();
    void durationChanged();
    void emergencyChanged();
    void multipartyChanged();

public Q_SLOTS:
    void answer();
    void hangup();
    void deflect(const QString &target);

protected Q_SLOTS:
    void initialize(bool notifyError = false);

    void onPendingCallFinished(QDBusPendingCallWatcher *watcher);

private:
    class VoiceCallHandlerPrivate *d;

    Q_DISABLE_COPY(VoiceCallHandler)
};

#endif // VOICECALLHANDLER_H