#ifndef LINEARSCALENODE_HPP
#define LINEARSCALENODE_HPP

#include <QtDeclarative/QSGGeometryNode>
#include <QtDeclarative/QSGGeometry>
#include <QtDeclarative/QSGFlatColorMaterial>

class LinearScale;

class LinearScaleNode : public QSGGeometryNode
{

public:

    LinearScaleNode();

    QColor color() const;
    void setColor(const QColor &color);

    void updateFromLinearScale(LinearScale* scale);

private:

    QSGGeometry m_geometry;
    QSGFlatColorMaterial m_material;
};

#endif // LINEARSCALENODE_HPP
