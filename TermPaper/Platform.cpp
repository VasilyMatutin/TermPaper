#include "Platform.h"

Platform::Platform(int _level_width, int _level_height, b2Body * _body, Object * _object, std::vector<std::pair<double, double>> traj_coord, int _fixed_speed, bool _is_rounded, int _node_number) : NonStaticObj(_level_width, _level_height, _body, _object, _fixed_speed),
	coord_set(traj_coord),
	point_iter(0),
	incr(1),
	is_rouded(_is_rounded),
	node_number(_node_number),
	counter_incr(1),
	is_active(1)
{
	body->SetTransform(b2Vec2(coord_set[0].first, coord_set[0].second), 0);
	body->GetFixtureList()->SetFriction(0.0f);
	body->SetUserData(this);
	tmp = body->GetPosition();
	object->x = tmp.x * PIXEL_PER_METER;
	object->y = tmp.y * PIXEL_PER_METER;
}

void Platform::contactEvent(b2Contact * contact, bool is_begin)
{
	b2Manifold* contact_information = contact->GetManifold();
	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);
	if (is_begin && contact_information->localNormal.y != 0 && worldManifold.points[0].y - object->y / PIXEL_PER_METER > 0 && body->GetLinearVelocity().y>0)
	{
		tmp = body->GetPosition();
		reverseMoving();
		counter_incr = -1;
		return;
	}
}

void Platform::update()
{
	if (node_number == 0 || counter <= node_number)
	{
		tmp = body->GetPosition();
		object->x = tmp.x * PIXEL_PER_METER;
		object->y = tmp.y * PIXEL_PER_METER;
		if (abs(tmp.x - coord_set[point_iter].first) < 0.1 && abs(tmp.y - coord_set[point_iter].second) < 0.1)
		{
			if (point_iter == coord_set.size() - 1)
			{
				if (is_rouded)
				{
					point_iter = -1;
					toNextPoint();
					counter_incr = 1;
					return;
				}
				else
				{
					reverseMoving();
					return;
				}
			}
			else if (point_iter == 0)
			{
				incr = 1;
				toNextPoint();
				counter_incr = 1;
				return;
			}
			toNextPoint();
		}
		else if (object->x + object->width / 2 > level_width - 0.001 || object->x - object->width / 2 < 0.001 || object->y + object->height / 2 > level_height - 0.001 || object->y - object->height / 2 < 0.001) //check of collisions with level boundaries
		{
			is_rouded = false;
			reverseMoving();
		}
	}
}

Platform::~Platform()
{
}

void Platform::reverseMoving()
{
	counter_incr = 1;
	incr = -incr;
	toNextPoint();
}

void Platform::toNextPoint()
{
	if (node_number != 0)
	{
		counter += counter_incr;
		if (counter == node_number+1)
		{
			is_active = false;
			body->SetLinearVelocity(b2Vec2(0, 0));
			return;
		}
	}
	point_iter += incr;
	b2Vec2 direction(coord_set[point_iter].first - tmp.x, coord_set[point_iter].second - tmp.y);
	direction.Normalize();
	body->SetLinearVelocity(b2Vec2(fixed_speed*direction.x, fixed_speed*direction.y));
}