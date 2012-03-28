#ifndef SINGLETON_H
#define SINGLETON_H

/*!
 \brief General template for creating Singleton classes.
*/
template <typename T> class Singleton
{
protected:
	Singleton () { }
	~Singleton () { }

public:
	/*!
	 Returns the single instance of T.

	 On the first call to getInstance(), the single instance of T doesn't exist
	 yet. It will then be created.

	 \return T *
	 \see kill()
	*/
	static T *getInstance ()
	{
		if (0 == _singleton)
		{
			_singleton = new T;
		}
		return (static_cast<T*> (_singleton));
	}

	/*!
	Destroy the single instance of T.

	If another instance of T is then requested by a call to getInstance(),
	a fresh new instance of T will be created.

	\see getInstance()
	*/
	static void kill ()
	{
		if (0 != _singleton)
		{
			delete _singleton;
			_singleton = 0;
		}
	}

private:
	static T *_singleton;
};

template <typename T> T *Singleton<T>::_singleton = 0;


#endif
