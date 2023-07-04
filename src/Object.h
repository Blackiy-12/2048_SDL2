#pragma once

class Object
{
public:
	Object();

	~Object();

	virtual void update()=0;
};

