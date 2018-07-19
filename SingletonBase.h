#pragma once
//=============================================================
//	## SingletonBase ## (�̱��� ����)
//=============================================================

template <typename T>
class SingletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* Singleton;

	SingletonBase() {}
	~SingletonBase() {}

public:
	//�̱��� ��������
	static T* GetSingleton(void);
	//�̱��� �޸𸮿��� �����ϱ�
	void ReleaseSingleton(void);
};

//�̱��� �ʱ�ȭ
template <typename T>
T* SingletonBase<T>::Singleton = 0;

//�̱��� ��������
template<typename T>
inline T * SingletonBase<T>::GetSingleton(void)
{
	//�̱����� ������ ���� ��������
	if (!Singleton) Singleton = new T;
	return Singleton;
}

//�̱��� �޸𸮿��� �����ϱ�
template<typename T>
inline void SingletonBase<T>::ReleaseSingleton(void)
{
	//�̱����� �ִٸ� �޸𸮿��� ��������
	if (Singleton)
	{
		delete Singleton;
		Singleton = 0;
	}
}
