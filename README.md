# Competing Systems' Course Project

## Objective
	Learn how to use POSIX semaphores 

## Context
	Synchronize the differents action in a museum between the visitors,
	the director and the guard(Contrôleur in French).
	
	After the museum's creation, the director can open or close it at will, 
	a visitor can wait in the queue even if the museum is closed, but only after its creation.

	The Museum have a maximum capacity and the wait line too. And after the closure, 
	no more visitors can enter, and after the last visitor left the musuem, 
	the guard ends his job.

## Usage
```
	make
	make test
```

	You can use the Dump file to see the state of the museum.