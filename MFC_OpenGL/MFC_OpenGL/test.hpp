#pragma once

class VTest
{
protected:
	virtual void luanch() = 0;
};

class BaseTest 
{
public:
	static void init();
	static void launch();
	static void show();
private:
	static GLfloat view;
};
