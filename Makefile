# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jhendrik <marvin@42.fr>                      +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/28 11:19:10 by jhendrik      #+#    #+#                  #
#    Updated: 2023/08/31 16:47:58 by jhendrik      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Defining directories
SRCDIR := ./src
OBJDIR := ./obj
LIBDIR := ./src/libs

MYLIBDIR := libft
MLXDIR := MLX42

SUBDIRS := libs \
		   libs/libft \
		   libs/MLX42 \
		   Utils \
		   Parsing
SRCDIRS := $(foreach dir,$(SUBDIRS),$(addprefix $(SRCDIR)/,$(dir)))
OBJDIRS := $(foreach dir,$(SUBDIRS),$(addprefix $(OBJDIR)/,$(dir)))

MLXINCL := $(LIBDIR)/$(MLXDIR)/include/MLX42
SRCINCL := ./include

# Defining extentions
SRCEX = .c
OBJEX = .o

# Add the SRCDIRS to VPATH so make knows where to find the srcfiles
VPATH := $(SRCDIRS)

# Define target
NAME := fdf

# Defining files
SRCHEADER := -I $(SRCINCL)
MLXHEADER := -I $(MLXINCL)

MLXLIB := $(LIBDIR)/$(MLXDIR)
MYLIB := $(LIBDIR)/$(MYLIBDIR)

LIBS := $(MYLIB)/libft.a \
		$(MLXLIB)/build/libmlx42.a
SRCFILES := Parsing/init_coordinate_array.c \
			Parsing/init_data.c \
			Parsing/parsing.c \
			Utils/counting.c \
			Utils/fdf_atoi.c \
			Utils/math.c \
			Utils/scaling_translating.c \
			Utils/test_utils.c \
			Lines/draw_lines.c \
			Lines/bresenham_lines.c \
			Lines/vertical_and_horizontal.c \
			main.c
OBJFILES := $(addprefix $(OBJDIR)/,$(SRCFILES:$(SRCEX)=$(OBJEX)))

# Defining flags
CFLAGS ?= -Wall -Werror -Wextra -g
MLXFLAGS := -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw3

# Prettifying output
# Reset
Reset="\033[0m"			# Text Reset

# Regular Colors
Black="\033[0;30m"			# Black
Red="\033[0;31m"			# Red
Green="\033[0;32m"			# Green
Yellow="\033[0;33m"			# Yellow
Blue="\033[0;34m"			# Blue
Light_Blue="\033[1;34m"		#Light Blue
Purple="\033[0;35m"			# Purple
Cyan="\033[0;36m"			# Cyan
White="\033[0;37m"			# White

# Bold text style
Bold="\033[1m"

all: make_libs $(NAME)

make_libs: $(MYLIB)/obj $(MLXLIB)/build

$(MYLIB)/obj:
	@make bonus -C $(MYLIB)

$(MLXLIB)/build:
	git submodule init
	git submodule update
	@cmake $(MLXLIB) -B $(MLXLIB)/build && make -C $(MLXLIB)/build -j4

$(NAME): $(OBJFILES) | $(OBJDIR)
	@echo $(Light_Blue) Compiling ... $(NAME) $(Reset)
	@$(CC) $(LIBS) $(OBJFILES) -o $(NAME) $(MLXFLAGS) $(MLXHEADER)
	@echo $(Green) Succesfully made program $(NAME) $(Reset)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCINCL)/src.h
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) $(SRCHEADER) $(MLXHEADER) $<
	@mv ./$(notdir $@) $(@D)

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@if [ -d $(OBJDIR) ]; then \
		rm -R $(OBJDIR); \
	fi
	@$(MAKE) clean -C $(MYLIB)
	@if [ -d $(MLXLIB)/build ]; then \
		rm -rf $(MLXLIB)/build; \
	fi
	@echo $(Yellow) Files with extension $(OBJEX) are gone $(Reset)

fclean: clean
	@if [ -f $(NAME) ]; then \
		$(RM) -f $(NAME); \
	fi
	@$(MAKE) fclean -C $(MYLIB)
	@echo $(Yellow) The program $(NAME) is no more $(Reset)

re: fclean all

.PHONY: all, clean, fclean, make_libs, re 
