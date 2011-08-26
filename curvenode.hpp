#ifndef CURVENODE_HPP
#define CURVENODE_HPP

#include <QtDeclarative/QSGGeometryNode>
#include <QtDeclarative/QSGGeometry>
#include <QtDeclarative/QSGFlatColorMaterial>

class Curve;

class CurveNode : public QSGGeometryNode
{

public:

    CurveNode();

    QColor color() const;
    void setColor(const QColor &color);

    void updateFromCurve(Curve* curve);

private:

    QSGGeometry m_geometry;
    QSGFlatColorMaterial m_material;
};

#endif // CURVENODE_HPP
