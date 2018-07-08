#---------------------------------------------------------------------
# Assume-se uma distribuição Linux como sistema operacional padrão
#---------------------------------------------------------------------

# O compilador
CC = g++
# Comando para remover pastas
RMDIR = rm -rdf
# Comando para remover arquivos
RM = rm -f

# "Flags" para geração automática de dependências
DEP_FLAGS = -MM -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF $@
# Bibliotecas a serem linkadas
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
# Caminho dos includes
INC_PATHS = -I$(INC_PATH) -I$(EXT_PATH) $(addprefix -I,$(SDL_INC_PATH))

# Diretivas de compilacao
FLAGS = -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self -I/usr/include/SDL2
# Diretivas extras para debug
DFLAGS = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address,undefined -fno-sanitize-recover -ggdb -O0 -DDEBUG
# Diretivas extras para release
RFLAGS = -O3 -mtune=native
# Diretivas extras para release com simbolos de debug
RDFLAGS = -O3 -mtune=native -ggdb -DDEBUG
# Diretivas extras para release com otimizacoes mais agressivas
RFFLAGS = -Ofast -flto -mtune=native -s

INC_PATH = include
EXT_PATH = extern
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

# Uma lista de arquivos por extensão:
CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
INC_FILES = $(wildcard $(INC_PATH)/*.h)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h=)))
DEP_FILES = $(addprefix $(DEP_PATH)/,$(addsuffix .d,$(FILE_NAMES)))
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))

# Nome do executável
EXEC = JOGO
ifeq ($(NAME), GIT)
EXEC = $(shell git describe --tags --dirty --long)
endif

#---------------------------------------------------------------------
# Caso o sistema seja windows
#---------------------------------------------------------------------
ifeq ($(OS),Windows_NT)

# Comando para remover um diretório recursivamente
RMDIR = rd /s /q

# Comando para deletar um único arquivo
RM = del /q

# Possíveis Path da SDL. Caso seja possível ter mais de um local, adicione com espaço entre eles
# Por ex.: SDL_PATHs = C:/SDL2 D:/Tools/SDL2 C:/dev-tools/SDL2
SDL_PATHS = C:/x86_64-w64-mingw32 C:/Tools/msys64/mingw64

SDL_INC_PATH += $(addsuffix /include,$(SDL_PATHS))
LINK_PATH = $(addprefix -L,$(addsuffix /lib,$(SDL_PATHS)))
FLAGS += -mwindows
DFLAGS += -mconsole
LIBS := -lmingw32 -lSDL2main $(LIBS)

# Nome do executável
EXEC := $(EXEC).exe

else

UNAME_S := $(shell uname -s)

#---------------------------------------------------------------------
# Caso o sistema seja Mac
#---------------------------------------------------------------------

ifeq ($(UNAME_S), Darwin)

LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

endif
endif

#---------------------------------------------------------------------
# Cross-compile de Linux para Windows (estático)
#---------------------------------------------------------------------
ifeq ($(TARGET), WIN)

CC = x86_64-w64-mingw32-g++
BIN_PATH = binw

PATH := /usr/local/cross-tools/x86_64-w64-mingw32/bin:$(PATH)
INC_PATHS = -I$(INC_PATH) -I$(EXT_PATH) -I/usr/local/cross-tools/x86_64-w64-mingw32/include/SDL2 -Dmain=SDL_main
#LINK_PATH =  $(shell sdl2-config --static-libs) -static-libstdc++ -lz -logg -lvorbis -lpng -ljpeg
LINK_PATH =  -L/usr/local/cross-tools//x86_64-w64-mingw32/lib  --static -lmingw32 -lSDL2main -lSDL2 -mwindows -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc -static-libstdc++ -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lfreetype -lm  -ljpeg -lpng -lz -lwinmm -lvorbisfile -lvorbis -logg

RC_FILE = jogo.rc
RES_FILE = jogo.res
OBJ_FILES += $(BIN_PATH)/$(RES_FILE)

EXEC := $(EXEC).exe

endif

##############################################################################################

.PRECIOUS: $(DEP_FILES)
.PHONY: release debug clean folders help

# Regra geral
all: FLAGS += $(RDFLAGS)
all: $(EXEC)

# Gera o executável
$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

# Gera os arquivos objetos
$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(CC) $(INC_PATHS) $(addprefix $(SRC_PATH)/,$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

# Gera os arquivos de dependencia
$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(CC) $(INC_PATHS) $< $(DEP_FLAGS) $(FLAGS)

# Gera o arquivo res
$(BIN_PATH)/%.res: $(RC_FILE)
	x86_64-w64-mingw32-windres $^ -O coff -o $@

clean:
	-$(RMDIR) $(DEP_PATH)
	-$(RMDIR) $(BIN_PATH)
	-$(RM) $(EXEC)
	-$(RM) cout.txt cerr.txt jogo.res

release: FLAGS += $(RFLAGS)
release: $(EXEC)

#clang++ anterior a 3.9 possui um bug na hora da linkagem com -flto, usar 3.9+
releasefast: FLAGS += $(RFFLAGS)
releasefast: $(EXEC)

debug: FLAGS += $(DFLAGS)
debug: $(EXEC)

folders:
ifeq ($(OS), Windows_NT)
	@if NOT exist $(DEP_PATH) ( mkdir $(DEP_PATH) )
	@if NOT exist $(BIN_PATH) ( mkdir $(BIN_PATH) )
	@if NOT exist $(INC_PATH) ( mkdir $(INC_PATH) )
	@if NOT exist $(SRC_PATH) ( mkdir $(SRC_PATH) )
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
endif

android:
	rsync -vah src/* ../org.pedro.marmota/app/jni/src/
	rsync -vah include/* ../org.pedro.marmota/app/jni/src/
	rsync -vah extern/* ../org.pedro.marmota/app/jni/src/
	cd ../org.pedro.marmota && ./gradlew assembleDebug
	cp ../org.pedro.marmota/app/build/outputs/apk/app-debug.apk $(EXEC).apk

androidrun:
	adb install -r $(EXEC).apk
	adb shell monkey -p org.pedro.marmota -v 500
	adb logcat org.pedro.marmota:I S:* | grep --color=never marmolog

# Regra pra debug
print-% : ; @echo $* = $($*)

help:
ifeq ($(OS), Windows_NT)
	@echo.
endif
	@echo Available targets:
	@echo - release:  Builds the release version [default target]
	@echo - debug:    Builds the debug version
	@echo - clean:    Cleans generated files
	@echo - folders:  Generates project directories
	@echo - help:     Shows this help
ifeq ($(OS), Windows_NT)
	@echo.
endif

.SECONDEXPANSION:
-include $$(DEP_FILES)

