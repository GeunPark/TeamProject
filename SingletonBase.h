#pragma once
//=============================================================
//	## SingletonBase ## (싱글톤 패턴)
//=============================================================

template <typename T>
class SingletonBase
{
protected:
	//싱글톤 인스턴스 선언
	static T* Singleton;

	SingletonBase() {}
	~SingletonBase() {}

public:
	//싱글톤 가져오기
	static T* GetSingleton(void);
	//싱글톤 메모리에서 해제하기
	void ReleaseSingleton(void);
};

//싱글톤 초기화
template <typename T>
T* SingletonBase<T>::Singleton = 0;

//싱글톤 가져오기
template<typename T>
inline T * SingletonBase<T>::GetSingleton(void)
{
	//싱글톤이 없으면 새로 생성하자
	if (!Singleton) Singleton = new T;
	return Singleton;
}

//싱글톤 메모리에서 해제하기
template<typename T>
inline void SingletonBase<T>::ReleaseSingleton(void)
{
	//싱글톤이 있다면 메모리에서 해제하자
	if (Singleton)
	{
		delete Singleton;
		Singleton = 0;
	}
}
