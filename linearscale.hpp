#ifndef LINEARSCALEITEM_HPP
#define LINEARSCALEITEM_HPP

#include <QtDeclarative/QSGItem>
#include <QtCore/QPointer>

class ScaleMap;
class QDeclarativeComponent;

class LinearScale : public QSGItem
{
    Q_OBJECT
    Q_DISABLE_COPY(LinearScale)

    Q_PROPERTY(ScaleMap* scaleMap READ scaleMap WRITE setScaleMap NOTIFY scaleMapChanged)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(QDeclarativeComponent* delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)

public:

    explicit LinearScale(QSGItem* parent = 0);

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

private:

    QPointer<ScaleMap> m_scaleMap;
    Qt::Orientation m_orientation;
    QPointer<QDeclarativeComponent> m_delegate;
    QList<QSGItem*> m_ticks;
};

QML_DECLARE_TYPE(LinearScale)

#endif // LINEARSCALEITEM_HPP
