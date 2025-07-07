#pragma once

class NandFlashMemory {
public:
	virtual int read(int LBA) = 0;
};