#include "linearscale.hpp"
#include "scalemap.hpp"
#include <QtDeclarative/QDeclarativeContext>

LinearScale::LinearScale(QSGItem* parent)
    : QSGItem(parent)
    , m_scaleMap(0)
    , m_orientation(Qt::Horizontal)
    , m_delegate(0)
{
    m_timer.setSingleShot(true);
    m_timer.setInterval(100);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateTicks()));
}

ScaleMap* LinearScale::scaleMap() const
{
    return m_scaleMap;
}

void LinearScale::setScaleMap(ScaleMap* scaleMap)
{
    if (m_scaleMap != scaleMap)
    {
        m_scaleMap = scaleMap;
        emit scaleMapChanged(scaleMap);
    }
}

Qt::Orientation LinearScale::orientation() const
{
    return m_orientation;
}

void LinearScale::setOrientation(Qt::Orientation orientation)
{
    if (m_orientation != orientation)
    {
        m_orientation = orientation;
        emit orientationChanged(orientation);
    }
}

QDeclarativeComponent* LinearScale::delegate() const
{
    return m_delegate;
}

void LinearScale::setDelegate(QDeclarativeComponent *delegate)
{
    if (m_delegate != delegate)
    {
        m_delegate = delegate;
        emit delegateChanged(delegate);
    }
}

void LinearScale::geometryChanged(const QRectF &newGeometry,
                                  const QRectF &oldGeometry)
{
    QSGItem::geometryChanged(newGeometry, oldGeometry);

    if (m_scaleMap)
    {
        if (m_orientation == Qt::Horizontal)
            m_scaleMap->setPixelLength(newGeometry.width());
        else
            m_scaleMap->setPixelLength(newGeometry.height());
    }

    if (!m_timer.isActive())
        m_timer.start();
}

void LinearScale::updateTicks()
{
    qDeleteAll(m_ticks);
    m_ticks.clear();
    if (!m_delegate || !m_scaleMap)
        return;

    QList<double> ticks;
    ticks << 1 << 10 << 100 << 1000 << 10000;

    foreach (double tick, ticks)
    {
        double pixelTick = m_scaleMap->mapToPixel(tick);
        if (m_orientation == Qt::Vertical)
            pixelTick = height() - pixelTick;

        QDeclarativeContext* context = new QDeclarativeContext(qmlContext(this));
        context->setContextProperty("tickValue", tick);
        context->setContextProperty("tickPosition", pixelTick);
        QObject* o = m_delegate->create(context);
        context->setParent(o);

        QSGItem* item = qobject_cast<QSGItem*>(o);
        if (item)
        {
            item->setParent(this);
            item->setParentItem(this);
            m_ticks << item;
        }
        else
        {
            delete o;
        }
    }

    update();
}
