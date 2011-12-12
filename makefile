SOURCES = main.cpp Particle.cpp Explosion.cpp Grid.cpp GameWindow.cpp Keyboard.cpp Point.cpp Vector.cpp \
	Circle.cpp Colour.cpp Player.cpp Projectile.cpp Mouse.cpp Globals.cpp \
	Utilities.cpp GreenEnemy.cpp OrangeEnemy.cpp Enemy.cpp GridNode.cpp lodepng.cpp \
	ResourceCache.cpp BlueEnemy.cpp GUI.cpp
OBJECTS = $(subst .cpp,.o,$(SOURCES))
DEPENDANCIES = $(subst .cpp,.d,$(SOURCES))
COMPILER = g++
EXECUTIVE = program.out
FLAGS = -Wall -ansi -pedantic-errors -g -O3 -pg
LIBS  = -lglut -lGLU -lGL

$(EXECUTIVE): $(OBJECTS)
	@ echo Compiling main executive
	@ $(COMPILER) -o $(EXECUTIVE) $(OBJECTS) $(FLAGS) $(LIBS)

clean:
	clear
	@ rm -rf *.o *.d gmon.out profile.txt $(EXECUTIVE)
	@ echo Cleaning done

run: $(EXECUTIVE)
	@ ./$(EXECUTIVE)

-include $(DEPENDANCIES)

%.d: %.cpp
	@ $(COMPILER) -MM $(FLAGS) $< > $@.tmp; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
	rm -f $@.tmp
	@ echo Generating dependencies for file $<
	
%.o: %.cpp
	@ echo Compiling file $<
	@ $(COMPILER) $< -c $(FLAGS) $(LIBS)

