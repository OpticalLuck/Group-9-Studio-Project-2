#pragma once

template <typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new T();

		return Instance;
	}

	static void Destroy()
	{
		if (Instance)
		{
			delete Instance;
			Instance = nullptr;
		}
	}

protected:
	Singleton() {};
	virtual ~Singleton() {};

private:
	static T* Instance;
};

template <typename T>
T* Singleton<T>::Instance = nullptr;
