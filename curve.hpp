#ifndef CURVE_HPP
#define CURVE_HPP

#include <QtDeclarative/QSGItem>
#include <QtCore/QPointer>

class ScaleMap;

class Curve : public QSGItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Curve)

    Q_PROPERTY(ScaleMap* xScaleMap READ xScaleMap WRITE setXScaleMap NOTIFY xScaleMapChanged)
    Q_PROPERTY(ScaleMap* yScaleMap READ yScaleMap WRITE setYScaleMap NOTIFY yScaleMapChanged)

public:

    explicit Curve(QSGItem *parent = 0);

    ScaleMap* xScaleMap() const;
    ScaleMap* yScaleMap() const;

    const QVector<double>& data() const;

public slots:

    void setXScaleMap(ScaleMap* scaleMap);
    void setYScaleMap(ScaleMap* scaleMap);

signals:

    void xScaleMapChanged(ScaleMap* scaleMap);
    void yScaleMapChanged(ScaleMap* scaleMap);

protected:

    virtual void geometryChanged(const QRectF &newGeometry,
                                 const QRectF &oldGeometry);

    virtual QSGNode *updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* data);

private:

    QPointer<ScaleMap> m_xScaleMap;
    QPointer<ScaleMap> m_yScaleMap;
    QVector<double> m_data;
};

QML_DECLARE_TYPE(Curve)

#endif // CURVE_HPP
