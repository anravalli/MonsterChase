# Game Loops

## By Objects - Self Contained 
```python
class World
	__init__(self):
		entities_facade = EntitiesFacade
	def update(self):
		self.entities_facade.update()

class EntitiesFacade
	__init__(self):
		entities = List(Entity)
	def update(self):
		for entity in entities:
			entity.update()

class Entity:
	__init__(self):
		id = ""
	update(self):
		move(self)
		check_collision(self)
		update_state(self)

        	
```
## In world - Explicit 

```python
class World
	__init__(self):
    	entities_facade = EntitiesFacade
        collision_checker = CollisionChecker
	def update(self):
    	self.entities_facade.move()
    	self.collision_checker.check(self.objects)
    	self.entities_facade.update_state()

class EntitiesFacade
	__init__(self):
    	entities = List(Entity)
    def move(self):
    	for entity in entities:
        	entity.move()
    def update_state(self):
    	for entity in entities:
        	entity.update_state()
    
class CollisionChecker:
	def check(self, entities):
    	for entity in entities:
            for other_entity in entities:
                if other_entity == entity:
                    continue
                if entity.colliding(other_entity):
                    entity.has_collision = True
                    other_entity.has_collision = True
                    
        	
```

