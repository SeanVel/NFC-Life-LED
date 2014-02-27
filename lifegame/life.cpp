#include "life.h"

using namespace std;

Life::Life(const char rows, const char cols)
: 
rows_(rows), cols_(cols)
{
  grid_ = (char*) calloc(rows_ * cols_, sizeof(char));
  /*
	grid_ = new int[rows_ * cols_];
   	for (int i = 0; i < (rows_ * cols_); ++i)
   		grid_[i] = 0;
   	*/
}

Life::~Life()
{
  free(grid_);
}

void Life::inputNFCID(const char msb, const char lsb)
{
	
    char startRow = 9 * (msb >> 7); // startRow = (msb_7) ? 9 : 0;
    char startCol = 17 * (lsb >> 7); // startCol = (lsb_7) ? 17 : 0;
    char rowBit, colBit;
    for (char row = 0; row < 7; ++row)
    {
        rowBit = 1;
        rowBit <<= row;
        rowBit = msb&rowBit;
        rowBit >>= row;
        for (char col = 0; col < 7; ++col)
        {
            colBit = 1;
            colBit <<= col;
            colBit = lsb&colBit;
            colBit >>= col;
            if (rowBit ^ colBit)
                setCell(row+startRow, col+startCol);
        }
    }
}

int Life::rcToIndex(const int row, const int col) const
{
  int rowNum = row % rows_;
  if (rowNum < 0)
    rowNum += rows_;
  int colNum = col % cols_;
  if (colNum < 0)
    colNum += cols_;
  return rowNum * cols_ + colNum;
}

void Life::setCell(const int row, const int col)
{
  grid_[rcToIndex(row, col)] = 1;
}

void Life::clearCell(const int row, const int col)
{
  grid_[rcToIndex(row, col)] = 0;
}

void Life::death()
{
	free(grid_);
	grid_ = (char*) calloc(rows_ * cols_, sizeof(char));
}
/*
ostream& Life::print(ostream& out) const
{
  for (int row = 0; row < rows_; ++row)
  {
    for (int col = 0; col < cols_; ++col)
      out << grid_[rcToIndex(row, col)] << " ";
    if (row != (rows_-1))
      out << endl;
  }
  out << endl;
}*/
/*
ostream& operator<<(ostream& out, const Life& life)
{
  return life.print(out);
}*/

int Life::checkCell(const int row, const int col) const
{
  return grid_[rcToIndex(row, col)];
}

int Life::neighbors(const int row, const int col) const
{
  int neighbors = 0;
  neighbors += checkCell(row-1, col-1);
  neighbors += checkCell(row-1, col);
  neighbors += checkCell(row-1, col+1);
  neighbors += checkCell(row, col-1);
  neighbors += checkCell(row, col+1);
  neighbors += checkCell(row+1, col-1);
  neighbors += checkCell(row+1, col);
  neighbors += checkCell(row+1, col+1);
  return neighbors;
}

void Life::tick()
{
  int neighborCount;
  newGrid_ = (char*) calloc(rows_ * cols_, sizeof(char));
  for (int row = 0; row < rows_; ++row)
    for (int col = 0; col < cols_; ++col)
    {
      if (checkCell(row, col))
      {
        neighborCount = neighbors(row, col);
        if ((neighborCount == 2) || (neighborCount == 3))
          newGrid_[rcToIndex(row, col)] = 1;
        else
          newGrid_[rcToIndex(row, col)] = 0;
      }
      else
      {
        if (neighbors(row, col) == 3)
          newGrid_[rcToIndex(row, col)] = 1;
        else
          newGrid_[rcToIndex(row, col)] = 0;
      }
    }
  free(grid_);
  grid_ = newGrid_;
}


