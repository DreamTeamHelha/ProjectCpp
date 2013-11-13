#include "tilemap.h"

GroundType Tilemap::tile(int x, int y) const
{
    if (x < 0 || x >= width() || y < 0 || y >= height())
    {
        return GroundType::Grass;
    }
    else
    {
        return m_tiles[y][x];
    }
}

void Tilemap::setTile(int x, int y, GroundType value)
{
    if (x < 0 || x >= width() || y < 0 || y >= height())
        return;

    m_tiles[y][x] = value;
}

int Tilemap::width() const
{
    if (m_tiles.size() > 0)
    {
        return m_tiles[0].size();
    }
    else
    {
        return 0;
    }
}

int Tilemap::height() const
{
    return m_tiles.size();
}

void Tilemap::setHeight(int height)
{
    if (height < 0) return;

    int oldHeight = this->height();
    m_tiles.resize(height);

    // crée les nouvelles colonnes
    for (unsigned int i=oldHeight; i<height; i++)
    {
        m_tiles[i].resize(width(), GroundType::Grass);
    }
}

void Tilemap::setWidth(int width)
{
    if (width < 0) return;

    for (std::vector<GroundType>& row : m_tiles)
    {
        row.resize(width);
    }
}
