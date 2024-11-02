# Fichier executable final
EXEC = program

# Compilateur et options
CC = gcc
CFLAGS = -Wall

# Dossiers
SRC_DIR = sources
OBJ_DIR = objects
BIN_DIR = binaries

# Fichiers 
SRCS = $(wildcard $(SRC_DIR)/*.c) 
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/$(EXEC)


# Rèle spécifiant les executables cible (> make ou > make all), ! par defaut car placée en première !
all: $(TARGET)
	@echo "Création de l'executable terminée."

# Règle responsable de la création des dossiers (> make setup)
setup:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)
	@echo "Création des dossiers terminée."

# Compile chaque fichier source .c en un fichier objet .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilation terminée."

# Lie les fichiers objets .o ensemble en un executable avec le compilateur
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lm
	@echo "Liaisons terminées."


# Supprime les fichiers compilés (> make clean)
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*
	@echo "Nettoyage terminé."

# Recompile (> make rebuild donc > make clean puis > make all)
rebuild: clean all

.PHONY: all clean rebuild setup

#.PHONY spécifie que les règles ne sont pas des cibles (si clean existe en tant que fichier, makefile pourrait penser qu'il est a jour et ne rien faire)
# "$" déréférence les variables, "/*.c" récupère l'ensemble des .c, "/%" lie les noms, "wildcard" formatte
# (Ajouter "-Wextra -g" au CFLAGS pour le debbugage)
# Makefile résoud les dépendances, donc chaque appel dépendant d'une variable délenche la résolution de cette variable et ainsi de suite
# Ceci implique que l'ordre ne compte pas. --> Résoud d'abord la dépendances, puis effectue ces actions qui les impliques.
# Sur la meme ligne que la règle sont indiquées les cibles de résolution, en dessous les commandes.
#< est la cible.
#@ est la règle.