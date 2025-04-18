#pragma once

class TetrisEvents
{
public:
	TetrisEvents();
	__event void OnTetrisLineClear();
	~TetrisEvents();
};