#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once

#include <raylib-cpp.hpp>

#include "health.hpp"

class Entity {
	public:
		Entity(Vector2 position, Vector2 size, Color color = RED, Health health = Health{ 100 });
		virtual ~Entity() = default;
		Vector2 position;
		Vector2 previous_position;
		Vector2 velocity;
		Vector2 acceleration;
		Vector2 size;
		Color color;
		Health health;
		virtual void tick(const double& delta);
		virtual void render(const double& alpha);
		virtual Vector2 interpolate(const double& alpha) const;
		virtual void reset_values() final;
		virtual bool check_collision(Rectangle collision_area) const;
		virtual bool check_collision(Vector2 collision_point) const;
		virtual Vector2 get_center() const;
		virtual void move(Vector2 position) const;
		virtual void teleport(Vector2 position) const;
	protected:
		virtual void update_values(const double& delta) final;
};

#endif
