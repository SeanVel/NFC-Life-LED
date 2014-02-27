#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED 1

#include <iostream>
#include <stdlib.h>

class Life {
public:
	Life(const char rows, const char cols);
	~Life();
	void setCell(const int row, const int col);
	void clearCell(const int row, const int col);
	void tick();
	void death();
	void inputNFCID(const char msb, const char lsb);
//	std::ostream& print(std::ostream& out) const;
//private:
	int rows_, cols_;
	char* grid_;
	char* newGrid_;
	int checkCell(const int row, const int col) const;
	int neighbors(const int row, const int col) const;
	int rcToIndex(const int row, const int col) const;
};

#endif
