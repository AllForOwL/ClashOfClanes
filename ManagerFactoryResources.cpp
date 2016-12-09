#include "ManagerFactoryResources.h"

ManagerFactoryResources::ManagerFactoryResources()
{
	m_stateManagerFactoryResources = StateManagerResources::UPDATE;
}

ManagerFactoryResources::ManagerFactoryResources(ManagerFactoryResources& i_ManagerFactoryResources)
{

}

void ManagerFactoryResources::Update(ManagerComponent& i_manager)
{
	switch (m_stateManagerFactoryResources)
	{
		case UPDATE:
		{
			UpdateAllFactoryResources(i_manager);

			break;
		}
	}
}

void ManagerFactoryResources::UpdateAllFactoryResources(ManagerComponent& i_manager)
{
	for (int i = 0; i < m_vecFactoryResources.size(); i++)
	{
		m_vecFactoryResources[i]->Update(i_manager);
	}
}

ManagerFactoryResources::~ManagerFactoryResources()
{

}