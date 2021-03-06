#include "Lever.h"
#include<iostream>

void Lever::contactEvent(b2Contact * contact, bool is_begin)
{
	if ((*current_player) == contact->GetFixtureA()->GetBody()->GetUserData() || (*current_player) == contact->GetFixtureB()->GetBody()->GetUserData())
	{
		if (is_begin == 1)
		{
			object->left = 0;
			object->top = 16 * 2;
		}
		else
		{
			object->left = 0;
			object->top = 0;
		}
	}
}

Lever::Lever(std::list<ManualSwitchObj*> _observables, bool _repeat_allowed, b2Body * _body, Object * _object, Player** _current_player, std::vector<Action> _stages):
	object(_object),
	current_player(_current_player),
	observables(_observables),
	repeat_allowed(_repeat_allowed),
	body(_body),
	stages(_stages),
	stage_iter(0)
{
	body->SetUserData(this);
	if (stages.empty())
	{
		stages.push_back(Action::DEFAULT);
	}
}

void Lever::activate()
{
	for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
	{
		if ((*current_player) == edge->contact->GetFixtureA()->GetBody()->GetUserData() || (*current_player) == edge->contact->GetFixtureB()->GetBody()->GetUserData())
		{
			if (!repeat_allowed)
			{
				for (auto it : observables)
				{
					if (it->isActive() == true)
					{
						return;
					}
				}
			}
			for (auto it : observables)
			{
				it->makeAction(stages[stage_iter]);
			}
			if (stage_iter == stages.size() - 1)
			{
				stage_iter = -1;
			}
			stage_iter++;
		}
	}
}
