#include "Role.h"

class CAi;

class CNpc : public CRole
{
public:
	CNpc(hgeResourceManager*, char* name, CMap* map, CAi*, float spd = 100.f);
	~CNpc(){}

	//bool Init();
	void Update(float);
	//void Render();
	//void Cleanup(){}

private:
	CAi*	m_pAi;

};