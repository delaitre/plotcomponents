#ifndef CURVENODE_HPP
#define CURVENODE_HPP

#include <QtQuick/QSGGeometryNode>
#include <QtQuick/QSGGeometry>
#include <QtQuick/QSGFlatColorMaterial>

class Curve;
class QPainterPath;

class CurveNode : public QSGGeometryNode
{

public:

    CurveNode();

    QColor color() const;
    void setColor(const QColor &color);

    void updateFromCurve(Curve* curve, const QPainterPath& path);

private:

    QSGGeometry m_geometry;
    QSGFlatColorMaterial m_material;
};

#endif // CURVENODE_HPP
