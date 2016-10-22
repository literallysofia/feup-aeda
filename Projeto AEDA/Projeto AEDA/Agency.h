#pragma once
class Agency
{
private:
	static Agency* singleton_instance;
public:
	Agency();
	~Agency();

	static Agency* instance()
	{
		if (!singleton_instance)
			singleton_instance = new Agency;

		return singleton_instance;
	}

};

