#pragma once

#include <vector>

///
/// Énumération des différents types de sols du jeu
///
enum class GroundType
{
    Grass,
    Asphalt,
    Dirt,

    _count // nombre de types de sol disponible
};

///
/// Représente une map découpée en cases, où chacune contient un type de sol particulier.
///
class Tilemap
{
public:

    ///
    /// Retourne le type de sol à la case (x; y).
    /// Si la case indiquée se trouve en dehors des limites de la map, la valeur GroundTYpe::Grass est retournée par défaut.
    ///
    GroundType tile(int x, int y) const;

    ///
    /// Change le type de sol de la case (x; y)
    /// Si la case indiquée se trouve en dehors des limites de la map, celle-ci n'est pas modifiée.
    ///
    void setTile(int x, int y, GroundType value);

    ///
    /// Permet la récupération de la taille de la grille, ainsi que son redimentionnement.
    ///
    int width () const;
    int height() const;

    void setWidth (int width);
    void setHeight(int height);

    ///
    /// Taille d'une case de la grille
    ///
    static int tileSize()
    {
        return 32;
    }

private:

    // tuiles[ligne][colonne]
    std::vector<std::vector<GroundType>> m_tiles;
};
