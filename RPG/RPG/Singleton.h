#pragma once

template<class T>
class CSingleton
{
public:
	static T& Instance();  //ȡ��ʵ��	
protected:
	CSingleton(){}
	virtual ~CSingleton() {}	
private:
	//��ֹ��������		
	CSingleton(const CSingleton&);
	CSingleton& operator= (const CSingleton&);
};


//ȡ��ʵ��
template<class T>
T& CSingleton<T>::Instance()
{
	static T instance;  //�ֲ���̬����    
	return instance;
}