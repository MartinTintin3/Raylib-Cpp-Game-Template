#include "entity.hpp"

#include <raylib-cpp.hpp>

#include "constants.hpp"
#include "utils.hpp"

Entity::Entity(Vector2 position, Vector2 size, float speed, Color color, Health health):
		position{ position }, previous_position{ position.x, position.y },
		velocity{ 0, 0 }, acceleration{ 0, 0 }, speed{ speed },
		size{ size }, color{ color }, health{ health } { }

void Entity::tick(const double& delta) {
	this->update_values(delta);
}

void Entity::render(const double& alpha) { }

void Entity::update_values(const double& delta) {
	velocity.x += acceleration.x * delta;
	velocity.y += acceleration.y * delta;
	this->move(velocity, delta);
}

void Entity::reset_values() {
	this->position = Vector2{ 0, 0 };
	this->velocity = Vector2{ 0, 0 };
	this->acceleration = Vector2{ 0, 0 };
}

Vector2 Entity::interpolate(const double& alpha) const {
	return Utils::interpolate_vectors(this->previous_position, this->position, alpha);
}

bool Entity::check_collision(Rectangle collision_area) const {
	return CheckCollisionRecs(collision_area, Rectangle{ this->position.x, this->position.y, this->size.x, this->size.y });
}

bool Entity::check_collision(Vector2 collision_point) const {
	return CheckCollisionPointRec(collision_point, Rectangle{ this->position.x, this->position.y, this->size.x, this->size.y });
}

Vector2 Entity::get_center() const {
	return Vector2{ this->position.x + this->size.x / 2, this->position.y + this->size.y / 2 };
}

void Entity::move(Vector2 position) {
	this->previous_position = this->position;
	this->position.x += position.x;
	this->position.y += position.y;
}

void Entity::move_to(Vector2 position) {
	this->previous_position = this->position;
	this->position = position;
}

void Entity::teleport(Vector2 position) {
	this->previous_position = position;
	this->position.x += position.x;
	this->position.y += position.y;
}

void Entity::teleport_to(Vector2 position) {
	this->previous_position = position;
	this->position = position;
}
