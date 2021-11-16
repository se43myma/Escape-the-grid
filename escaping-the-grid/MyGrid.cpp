#include "MyGrid.hpp"
#include <utility>
#include <cassert>
#include <algorithm>

// TODO Define all member functions:
MyGrid::MyGrid(size_t rows, size_t cols, const Tile &initialTile)
: nr{rows} , nc{cols} , elements{new Tile[nr * nc]}
{
    std::fill_n(elements,rows*cols,initialTile);
}

MyGrid::MyGrid(const MyGrid& other)
    :nr(other.nr), nc(other.nc) {
    elements=other.elements;
    //elements = new Tile[other.nr * other.nc];
    //std::copy_n(other.elements, nr * nc, elements);
}

MyGrid& MyGrid::operator=(const MyGrid& other) {
    if(&other != this){
        nr = other.nr;
        nc = other.nc;
        elements = new Tile[other.nr * other.nc];
        std::copy_n(other.elements, nr * nc, elements);
    }
    return *this;
    // MyGrid grid(other);
    // std::swap(*this,grid);
    // return *this;
}

MyGrid::MyGrid(MyGrid&& other) noexcept
{
    if(&other != this){
        nr = other.nr;
        nc = other.nc;
        elements=other.elements;
        // elements = new Tile[other.nr * other.nc];
        // std::copy_n(other.elements, nr * nc, elements);
        //std::exchange(*this,other);

        other.nr=0;
        other.nc=0;
        other.elements=nullptr;
    }
}

MyGrid& MyGrid::operator=(MyGrid&& other) noexcept
{
    if(&other != this){
        nr = other.nr;
        nc = other.nc;
        //elements = new Tile[other.nr * other.nc];
        elements=other.elements;
        //std::copy_n(other.elements, nr * nc, elements);
        //std::exchange(*this,other);

        other.nr=0;
        other.nc=0;
        other.elements=nullptr;
    }
        //std::exchange(*this,other);
        return *this;
}

MyGrid::~MyGrid()
{
    delete[] elements;
}

[[nodiscard]] size_t MyGrid::rows() const{ return nr; }
[[nodiscard]] size_t MyGrid::cols() const{ return nc; }
[[nodiscard]] size_t MyGrid::size() const{ return nr*nc; }

[[nodiscard]] bool MyGrid::validPosition(size_t row, size_t col) const noexcept {
    return (row<nr && col < nc) ? true:false;
}

Tile& MyGrid::operator()(size_t row, size_t col) {
    if(row < nr && col < nc)
        return elements[nc*row+col];
    else
        throw std::out_of_range( "invalid_grid_position" );
}

const Tile& MyGrid::operator()(size_t row, size_t col) const {
    if(row<nr && col < nc)
        //return elements[nc*row-nc+col];
        return elements[nc*row+col];
    else
        throw std::out_of_range( "invalid_grid_position" );
}

MyGrid MyGrid::read(std::istream &in){
    size_t rows,cols;
    std::string c_rows,c_cols;
    std::string tile;
    std::getline(in,c_rows);
    std::getline(in,c_cols);
    rows=std::stoi(c_rows);
    cols=std::stoi(c_cols);
    //std::cout<<rows<<std::endl<<cols<<std::endl;
    //in>>cols;
    MyGrid grid(rows,cols,Path);
    for(size_t r=0 ; r < rows ; r++) {
        std::getline(in,tile);
        for(size_t c=0 ; c < cols ; c++){
            grid(r,c)=tile_from_char(tile[c]);
        }
    }
    return grid;
}

std::ostream& operator<<(std::ostream& out, const MyGrid& grid)
{
    out<<grid.rows()<<std::endl;
    out<<grid.cols()<<std::endl;

    for(size_t r=0 ; r < grid.nr ; r++) {
        for(size_t c=0 ; c < grid.nc ; c++) {
            out<<char_from_tile(grid(r,c));
        }
        out<<std::endl;
    }

    return out;
}