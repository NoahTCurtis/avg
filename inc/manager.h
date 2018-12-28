#include <map>
#include <cassert>

template<typename T>
class Manager
{
public:
	unsigned CreateMember(unsigned key = -1);
	T& operator[](unsigned key);
	void DestroyMember(unsigned key);

private:
	unsigned getUnusedKey();
	std::map<unsigned, T*> members;
};


template<typename T>
unsigned Manager<T>::CreateMember(unsigned key)
{
	if (key == (unsigned)-1)
		key = getUnusedKey();
	members[key] = new T();
	return key;
}

template<typename T>
T& Manager<T>::operator[](unsigned key)
{
	T* w = members[key];
	assert(w != nullptr);
	return *w;
}

template<typename T>
void Manager<T>::DestroyMember(unsigned key)
{
	delete members[key];
	members.erase(key);
}

template<typename T>
unsigned Manager<T>::getUnusedKey()
{
	unsigned key = rand();
	/* //TODO: FIX THIS
	auto iter = members.begin();
	auto endr = members.end();
	while (iter != endr)
	{
		if (iter.first == key)
		{
			++key;
			iter = members.begin();
		}
		else iter++;
	}
	*/
	return key;
}