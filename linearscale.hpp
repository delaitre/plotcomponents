#ifndef LINEARSCALEITEM_HPP
#define LINEARSCALEITEM_HPP

#include <QtQuick/QQuickItem>
#include <QtCore/QPointer>
#include <QtCore/QTimer>

class ScaleMap;
class QDeclarativeComponent;

class LinearScale : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(LinearScale)

    Q_PROPERTY(ScaleMap* scaleMap READ scaleMap WRITE setScaleMap NOTIFY scaleMapChanged)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(QDeclarativeComponent* delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)

public:

    explicit LinearScale(QQuickItem* parent = 0);

    ScaleMap* scaleMap() const;
    Qt::Orientation orientation() const;
    QDeclarativeComponent* delegate() const;

public slots:

    void setScaleMap(ScaleMap* scaleMap);
    void setOrientation(Qt::Orientation orientation);
    void setDelegate(QDeclarativeComponent* delegate);

signals:

    void scaleMapChanged(ScaleMap* scaleMap);
    void orientationChanged(Qt::Orientation orientation);
    void delegateChanged(QDeclarativeComponent* delegate);

protected:

    virtual void geometryChanged(const QRectF &newGeometry,
                                 const QRectF &oldGeometry);

private slots:

    void updateTicks();

private:

    QPointer<ScaleMap> m_scaleMap;
    Qt::Orientation m_orientation;
    QPointer<QDeclarativeComponent> m_delegate;
    QList<QQuickItem*> m_ticks;
    QTimer m_timer;
};

QML_DECLARE_TYPE(LinearScale)

#endif // LINEARSCALEITEM_HPP
