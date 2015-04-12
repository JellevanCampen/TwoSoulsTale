template<class T>
T* Singleton<T>::m_Instance = nullptr;

template<typename T>
const T*  const Singleton<T>::Create()
{
	if (!m_Instance)
	{
		m_Instance = new T;
	}
	return &GetInstance();
}

template<typename T>
void Singleton<T>::Destroy()
{
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

template<typename T>
T& Singleton<T>::GetInstance()
{
	return *m_Instance;
}
