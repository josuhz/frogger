# Compilador que vamos a usar.
CXX = g++

# Opciones de compilacion:
# -std=c++17 usa el estandar C++17.
# -Wall -Wextra muestran advertencias utiles.
# -Iinclude le dice al compilador que busque headers en la carpeta include.
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -IC:/msys64/ucrt64/include/ncursesw

# Libreria que necesitamos para ncurses.
LDLIBS = -lncursesw

# Nombre del ejecutable final.
TARGET = frogger.exe

# Archivos fuente del proyecto.
SRC = main.cpp \
      interfaz/tableroNcurses.cpp \
      logica/rana.cpp \
	  logica/carro.cpp \
	  controlador/revisionEntradas.cpp \
	  logica/movCarros.cpp \
	  controlador/cicloPrincipal.cpp \
	  logica/agua.cpp

# Convierte cada archivo .cpp en su respectivo .o.
OBJ = $(SRC:.cpp=.o)

# Regla principal: compila todo el proyecto.
all: $(TARGET)

# Regla para crear el ejecutable final usando los archivos objeto.
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDLIBS)

# Regla general para convertir un .cpp en un .o.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compila y ejecuta el juego.
run: $(TARGET)
	./$(TARGET)

# Borra archivos generados por la compilacion.
clean:
	rm -f $(OBJ) $(TARGET)
