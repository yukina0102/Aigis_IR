#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#pragma once

template<class T>
class Singleton
{
public:
	static inline T& GetInstance()
	{
		static T instance;
		return instance;
	}

protected:
	Singleton() {} // 外部でのインスタンス作成は禁止
	virtual ~Singleton() {}

private:
	void operator=(const Singleton& obj) {} // 代入演算子禁止
	Singleton(const Singleton &obj) {} // コピーコンストラクタ禁止
};

#endif/*_SINGLETON_H_*/