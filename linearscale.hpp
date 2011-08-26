#ifndef LINEARSCALEITEM_HPP
#define LINEARSCALEITEM_HPP

#include <QtDeclarative/QSGItem>
#include <QtCore/QPointer>

class ScaleMap;

class LinearScale : public QSGItem
{
    Q_OBJECT
    Q_DISABLE_COPY(LinearScale)

    Q_PROPERTY(ScaleMap* scaleMap READ scaleMap WRITE setScaleMap NOTIFY scaleMapChanged)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

public:

    explicit LinearScale(QSGItem* parent = 0);

    ScaleMap* scaleMap() const;
    Qt::Orientation orientation() const;

public slots:

    void setScaleMap(ScaleMap* scaleMap);
    void setOrientation(Qt::Orientation orientation);

signals:

    void scaleMapChanged(ScaleMap* scaleMap);
    void orientationChanged(Qt::Orientation orientation);

protected:

    virtual void geometryChanged(const QRectF &newGeometry,
                                 const QRectF &oldGeometry);

    virtual QSGNode *updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* data);

private:

    QPointer<ScaleMap> m_scaleMap;
    Qt::Orientation m_orientation;
};

QML_DECLARE_TYPE(LinearScale)

#endif // LINEARSCALEITEM_HPP
