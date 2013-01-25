#pragma once

template<class T>
class CSingleton
{
public:
	static T& Instance();  //取得实例	
protected:
	CSingleton(){}
	virtual ~CSingleton() {}	
private:
	//防止拷贝复制		
	CSingleton(const CSingleton&);
	CSingleton& operator= (const CSingleton&);
};


//取得实例
template<class T>
T& CSingleton<T>::Instance()
{
	static T instance;  //局部静态对象    
	return instance;
}