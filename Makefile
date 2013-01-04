# GNU Make solution makefile autogenerated by Premake
# Type "make help" for usage help

ifndef config
  config=debug
endif
export config

PROJECTS := proceduralCity glfw glew stb_image

.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

proceduralCity: glfw glew stb_image
	@echo "==== Building proceduralCity ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f proceduralCity.make

glfw: 
	@echo "==== Building glfw ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f glfw.make

glew: 
	@echo "==== Building glew ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f glew.make

stb_image: 
	@echo "==== Building stb_image ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f stb_image.make

clean:
	@${MAKE} --no-print-directory -C . -f proceduralCity.make clean
	@${MAKE} --no-print-directory -C . -f glfw.make clean
	@${MAKE} --no-print-directory -C . -f glew.make clean
	@${MAKE} --no-print-directory -C . -f stb_image.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "   debug"
	@echo "   release"
	@echo "   debug64"
	@echo "   release64"
	@echo "   debug32"
	@echo "   release32"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   proceduralCity"
	@echo "   glfw"
	@echo "   glew"
	@echo "   stb_image"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"